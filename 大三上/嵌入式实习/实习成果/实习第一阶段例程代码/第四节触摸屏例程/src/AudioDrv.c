#include "def.h"
#include "2440addr.h"
#include "2440lib.h"
#include "AudioDrv.h"
#include "dma.h"

#define	AUDIO_PLAY_DEV	0x100
#define	AUDIO_REC_DEV	0x101

#define	DEVICE_REC	2
#define	DEVICE_PLAY	1
#define	DEVICE_FREE	0	
#define	PLAY	0
#define	RECORD	1

#define	PLAY_DMA_ATTR	((AUDIO_PLAY_DEV<<16)|SRC_LOC_AHB|SRC_ADDR_INC|DST_LOC_APB|DST_ADDR_FIXED|REQ_IISDO)
#define	PLAY_DMA_MODE	(HANDSHAKE_MODE|SYNC_APB|DONE_GEN_INT|TSZ_UNIT|SINGLE_SVC|HW_TRIG|RELOAD_OFF|DSZ_16b)
#define	REC_DMA_ATTR	((AUDIO_REC_DEV<<16)|SRC_LOC_APB|SRC_ADDR_FIXED|DST_LOC_AHB|DST_ADDR_INC|REQ_IISDI)
#define	REC_DMA_MODE	(HANDSHAKE_MODE|SYNC_APB|DONE_GEN_INT|TSZ_UNIT|SINGLE_SVC|HW_TRIG|RELOAD_OFF|DSZ_16b)

static void IIS_PortSetting(void);
static void _WrL3Addr(U8 data);
static void _WrL3Data(U8 data,int halt);
static void Init1341(char mode);
static void AdjVolume(U16 volume);
static void PlayPause(U8 mode);
static void StartPlay(void);
static void __irq PlayDMA2Done(void);

static LPWAVEHDR lpPlayFstBlk, lpRecFstBlk;
static LPWAVEHDR lpPlayLstBlk, lpRecLstBlk;
static LPWAVEHDR lpPlayCurBlk, lpRecCurBlk;
static U32 PlayTotBlks, RecTotBlks;

static U32 save_MPLLCON;

static struct
{
	U16 Freq;
	U32 MPLL;
	U16 PreScaler;
	U8	ofs;
}CodecPara[7] = {{8000,(123<<12)|(6<<4)|0,(23<<5)|23,0},
				{11025,(229<<12)|(5<<4)|1,(11<<5)|11,1},
				{16000,(123<<12)|(6<<4)|0,(11<<5)|11,0},
				{22050,(229<<12)|(5<<4)|1,(5<<5)|5,1},
				{32000,(123<<12)|(6<<4)|0,(5<<5)|5,0},
				{44100,(229<<12)|(5<<4)|1,(2<<5)|2,1},
				{48000,(123<<12)|(6<<4)|0,(3<<5)|3,0}};

static struct
{
	HWAVEOUT handle;		
	U16 wFormatTag;
	U16 nChannels;	
	U16 wBitsPerSample;
	CallBackProc CallBack;
	U32 CallBackInst;	
	U8 FsIdx;
	U32 DevReq;	
	U8 Status;	
}PlayStatus, RecStatus; 						   	

static U16 PlayVolume = 0xffff;

void DbgChgUartDiv(void)
{
	Uart_Init(0, 115200);        		
}

static void SetSysFclk( U32 MPLL )
{
	U32 mdiv, pdiv, sdiv, val;
    U32 mclk;

    mdiv = (MPLL>>12)&0xff;
    pdiv = (MPLL>>4)&0xff;
    sdiv = MPLL&0xf;
    
    val = 1;
    while(sdiv--)
    {
    	val *= 2;
    }
    		
    mclk = ((mdiv+8)*12000000)/((pdiv+2)*val) ;	    	
    Uart_Init(mclk>>2, 115200) ;
}

/************************* Play Function ***********************/
MMRESULT waveOutOpen(
	LPHWAVEOUT phwo,
	UINT uDeviceID,
	LPWAVEFORMATEX pwfx,
	DWORD dwCallback,
	DWORD dwCallbackInstance,
	DWORD fdwOpen
)
{
	U8 i;
	U8 err = 0;	
	
	if(pwfx->wFormatTag!=WAVE_FORMAT_PCM)	//only support PCM
		err = 1;
	if(pwfx->nChannels!=2)					//must be stero
		err = 1;
	if(pwfx->wBitsPerSample%8)				//8 or 16 bits
		err = 1;
	for(i=0; i<7; i++)
		if(pwfx->nSamplesPerSec==CodecPara[i].Freq)
			break;
	if(i==7)
		err = 1;		
	if((pwfx->nChannels*pwfx->wBitsPerSample)/8!=pwfx->nBlockAlign)
		err = 1;
	if(pwfx->nAvgBytesPerSec!=pwfx->nSamplesPerSec*pwfx->nBlockAlign)
		err = 1;		
	if(err)											
		return WAVERR_BADFORMAT;			//check format parameters
	
	if(PlayStatus.Status!=DEVICE_FREE)
		return MMSYSERR_BADDEVICEID;
	PlayStatus.DevReq = RequestDMA(PLAY_DMA_ATTR, PLAY_DMA_MODE);				
	if(PlayStatus.DevReq==REQUEST_DMA_FAIL)
		return MMSYSERR_BADDEVICEID;						
	
	PlayStatus.handle		  =	*phwo; 
	PlayStatus.wFormatTag     = pwfx->wFormatTag;
	PlayStatus.nChannels      = pwfx->nChannels;	
	PlayStatus.wBitsPerSample = pwfx->wBitsPerSample;
	PlayStatus.FsIdx          = i;
	PlayStatus.CallBack		  = (CallBackProc)dwCallback;
	PlayStatus.CallBackInst	  = dwCallbackInstance;
	PlayStatus.Status		  = DEVICE_PLAY;
			
	save_MPLLCON = rMPLLCON;				//save MPLLCON value
	SetSysFclk(CodecPara[PlayStatus.FsIdx].MPLL);
	rCLKCON |= 0x20000;						//enable IIS clock	
	
	DbgChgUartDiv();		
	
	IIS_PortSetting();	    
	pISR_DMA2 = (U32)PlayDMA2Done;
	EnableIrq(BIT_DMA2);
	PlayTotBlks = 0;
	Init1341(PLAY);
	waveOutSetVolume(PlayStatus.handle, PlayVolume);
	
	return MMSYSERR_NOERROR;
}

MMRESULT waveOutClose(HWAVEOUT hwo)
{
	if((PlayStatus.handle!=hwo)||(PlayStatus.Status!=DEVICE_PLAY))
		return MMSYSERR_INVALHANDLE;		
		
	rIISCON      = 0x0;						//IIS Interface stop    
	rIISFCON     = 0x0; 						//For FIFO flush
	rCLKCON		&= ~0x20000;				//disable IIS colock
	SetSysFclk(save_MPLLCON);
	PlayStatus.Status = DEVICE_FREE;    
	ReleaseDMA(PlayStatus.DevReq);		
	DisableIrq(BIT_DMA2);
			
	return MMSYSERR_NOERROR;
}

MMRESULT waveOutPrepareHeader(HWAVEOUT hwo,	LPWAVEHDR pwh, UINT cbwh)
{
	if((PlayStatus.handle!=hwo)||(PlayStatus.Status!=DEVICE_PLAY))
		return MMSYSERR_INVALHANDLE;
	
	pwh->lpNext = 0;
	pwh->dwBytesRecorded = 0;
	pwh->dwUser  = 0;
	pwh->dwFlags = 0;	
	return MMSYSERR_NOERROR;
}
	
MMRESULT waveOutUnprepareHeader(HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh)
{
	if((PlayStatus.handle!=hwo)||(PlayStatus.Status!=DEVICE_PLAY))
		return MMSYSERR_INVALHANDLE;
		
	return MMSYSERR_NOERROR;
}

MMRESULT waveOutWrite(HWAVEOUT hwo,	LPWAVEHDR pwh, UINT cbwh)
{
	if((PlayStatus.handle!=hwo)||(PlayStatus.Status!=DEVICE_PLAY))
		return MMSYSERR_INVALHANDLE;
	
	if(!PlayTotBlks)
	{
		lpPlayFstBlk = pwh;
		lpPlayCurBlk = lpPlayFstBlk;
		StartPlay();					
	}
	else
	{
		lpPlayLstBlk -> lpNext = pwh ;
	}

	lpPlayLstBlk = pwh;
	pwh->lpNext = 0;
	PlayTotBlks++;		

	return MMSYSERR_NOERROR;
}

MMRESULT waveOutSetVolume(HWAVEOUT hwo,	DWORD dwVolume)
{
	if((PlayStatus.handle!=hwo)||(PlayStatus.Status!=DEVICE_PLAY))
		return MMSYSERR_INVALHANDLE;
		
	PlayVolume = dwVolume&0xffff;
	AdjVolume(PlayVolume);			
		
	return MMSYSERR_NOERROR;
}	

MMRESULT waveOutGetVolume(HWAVEOUT hwo,	LPDWORD pdwVolume)
{
	if((PlayStatus.handle!=hwo)||(PlayStatus.Status!=DEVICE_PLAY))
		return MMSYSERR_INVALHANDLE;
		
	*pdwVolume = PlayVolume; 
	return MMSYSERR_NOERROR;
}

MMRESULT waveOutPause (HWAVEOUT hwo)
{
	if((PlayStatus.handle!=hwo)||(PlayStatus.Status!=DEVICE_PLAY))
		return MMSYSERR_INVALHANDLE;

	PlayPause(1);
	return MMSYSERR_NOERROR;
}

MMRESULT waveOutRestart(HWAVEOUT hwo)
{
	if((PlayStatus.handle!=hwo)||(PlayStatus.Status!=DEVICE_PLAY))
		return MMSYSERR_INVALHANDLE;
		
	PlayPause(0);
	return MMSYSERR_NOERROR;
}

MMRESULT waveOutReset (HWAVEOUT hwo)
{
	if((PlayStatus.handle!=hwo)||(PlayStatus.Status!=DEVICE_PLAY))
		return MMSYSERR_INVALHANDLE;
		
	return MMSYSERR_NOERROR;
}

//==========================================================
static __inline void SetPlayDma(void)
{
	SetDMARun(PlayStatus.DevReq|DMA_START, (U32)lpPlayCurBlk->lpData, (U32)IISFIFO, lpPlayCurBlk->dwBufferLength/2);
}

static void StartPlay(void)
{
	SetPlayDma();	   	    	

	rIISPSR  = CodecPara[PlayStatus.FsIdx].PreScaler;
	rIISCON  = (1<<5)+(0<<4)+(0<<3)+(1<<2)+(1<<1);	//Tx DMA enable[5], Rx idle[2], Prescaler enable[1]	
	rIISMOD  = (0<<8)+(2<<6)+(0<<5)+(1<<4)+((PlayStatus.wBitsPerSample>>4)<<3)+(CodecPara[PlayStatus.FsIdx].ofs<<2)+(1<<0);	
	rIISFCON = (1<<15) + (1<<13);    
	rIISCON |= 0x1;    		      
}

static void __irq PlayDMA2Done(void)
{
	ClearPending(BIT_DMA2);							//Clear pending bit
    
	lpPlayCurBlk->dwLoops--;	    	
	if(lpPlayCurBlk->lpNext)
	{
		lpPlayCurBlk = lpPlayCurBlk->lpNext;    	   	
	}
	else
	{
		lpPlayCurBlk = lpPlayFstBlk;    	    	
	}    
	SetPlayDma();
}

/************************* Record Function *********************/
static __inline void SetRecDma(void)
{
	SetDMARun(RecStatus.DevReq|DMA_START, (U32)IISFIFO, (U32)lpRecCurBlk->lpData, lpRecCurBlk->dwBufferLength/2);
}

static void __irq RecDMADone(void)
{	
	if((RecStatus.DevReq&0xff)==0x12)
		ClearPending(BIT_DMA1);						//Clear pending bit
	if((RecStatus.DevReq&0xff)==0x21)
		ClearPending(BIT_DMA2);	    
    
    lpRecCurBlk->dwBytesRecorded = lpRecCurBlk->dwBufferLength;
    
    if(lpRecCurBlk->lpNext)
    {
    	lpRecCurBlk = lpRecCurBlk->lpNext;    	   	
    }
    else
    {
       	lpRecCurBlk = lpRecFstBlk;    	    	
    }
    SetRecDma();
}

MMRESULT waveInOpen(
	LPHWAVEIN phwi,
	UINT uDeviceID,
	LPWAVEFORMATEX pwfx,
	DWORD dwCallback,
	DWORD dwCallbackInstance,
	DWORD fdwOpen
)
{
	U8 i;
	U8 err = 0;	
	
	if(pwfx->wFormatTag!=WAVE_FORMAT_PCM)			//only support PCM
		err = 1;
	if(pwfx->nChannels!=2)							//must be stero
		err = 2;
	if(pwfx->wBitsPerSample%8)						//8 or 16 bits
		err = 3;
	for(i=0; i<7; i++)
		if(pwfx->nSamplesPerSec==CodecPara[i].Freq)
			break;
	if(i==7)
		err = 4;		
	if((pwfx->nChannels*pwfx->wBitsPerSample)/8!=pwfx->nBlockAlign)
		err = 5;
	if(pwfx->nAvgBytesPerSec!=pwfx->nSamplesPerSec*pwfx->nBlockAlign)
		err = 6;		
	if(err)
	{
		//printf("check err = %d\n", err);											
		return WAVERR_BADFORMAT;					//check format parameters
	}
	
	if(RecStatus.Status!=DEVICE_FREE)
		return MMSYSERR_BADDEVICEID;
	RecStatus.DevReq = RequestDMA(REC_DMA_ATTR, REC_DMA_MODE);			
	if(RecStatus.DevReq==REQUEST_DMA_FAIL)		
		return MMSYSERR_BADDEVICEID;											
	
	RecStatus.handle 		 =	*phwi; 
	RecStatus.wFormatTag     = pwfx->wFormatTag;
	RecStatus.nChannels      = pwfx->nChannels;	
	RecStatus.wBitsPerSample = pwfx->wBitsPerSample;
	RecStatus.FsIdx          = i;
	RecStatus.CallBack		 = (CallBackProc)dwCallback;
	RecStatus.CallBackInst	 = dwCallbackInstance;
	RecStatus.Status		 = DEVICE_REC;
	
	save_MPLLCON = rMPLLCON;						//save MPLLCON value
	//rMPLLCON = CodecPara[RecStatus.FsIdx].MPLL;
	SetSysFclk(CodecPara[RecStatus.FsIdx].MPLL);
	rCLKCON |= 0x20000;								//enable IIS clock	
	
		DbgChgUartDiv();		
			
	IIS_PortSetting();		
	if((RecStatus.DevReq&0xff)==0x12)
	{
		pISR_DMA1 = (U32)RecDMADone;
		EnableIrq(BIT_DMA1);
	}
	if((RecStatus.DevReq&0xff)==0x21)		    
	{
		pISR_DMA2 = (U32)RecDMADone;
		EnableIrq(BIT_DMA2);
	}
		
	RecTotBlks = 0;
	Init1341(RECORD);		
	
	return MMSYSERR_NOERROR;
}

MMRESULT waveInClose(HWAVEOUT hwi)
{
	if((RecStatus.handle!=hwi)||(RecStatus.Status!=DEVICE_REC))
		return MMSYSERR_INVALHANDLE;		

	rIISCON      = 0x0;				//IIS Interface stop    
	rIISFCON     = 0x0;     		//For FIFO flush
	rCLKCON		&= ~0x20000;		//disable IIS colock
	//rMPLLCON	 = save_MPLLCON;	//restore MPLLCON value
	SetSysFclk(save_MPLLCON);
    
	RecStatus.Status = DEVICE_FREE;    
	ReleaseDMA(RecStatus.DevReq);
	if((RecStatus.DevReq&0xff)==0x12)		
		DisableIrq(BIT_DMA1);
	if((RecStatus.DevReq&0xff)==0x21)
		DisableIrq(BIT_DMA2);
			
	return MMSYSERR_NOERROR;	
}

MMRESULT waveInStart(HWAVEIN hwi)
{
	if((RecStatus.handle!=hwi)||(RecStatus.Status!=DEVICE_REC))
		return MMSYSERR_INVALHANDLE;
	
	if(!RecTotBlks)
		return MMSYSERR_NOMEM;
	
	SetRecDma();	
	
	rIISPSR  = CodecPara[RecStatus.FsIdx].PreScaler;
	rIISCON  = (0<<5)+(1<<4)+(1<<3)+(0<<2)+(1<<1);	//Tx DMA disable,Rx DMA enable,Tx idle,Rx not idle,prescaler enable,stop		
	rIISMOD  = (0<<8)+(1<<6)+(0<<5)+(1<<4)+((RecStatus.wBitsPerSample>>4)<<3)+(CodecPara[RecStatus.FsIdx].ofs<<2)+(1<<0);	
		//Master mode[8],Rx mode[7:6],Low for Left Channel[5],IIS format[4],16/8bit [3],256/384fs [2],IISCLK 32fs[1:0]	    	
	rIISFCON = (1<<14)+(1<<12);		//Rx DMA,Rx FIFO --> start piling....    
	rIISCON |= 0x1;    				//start IIS 
	
	return MMSYSERR_NOERROR;
}

MMRESULT waveInStop(HWAVEIN hwi)
{
	if((RecStatus.handle!=hwi)||(RecStatus.Status!=DEVICE_REC))
		return MMSYSERR_INVALHANDLE;
	
	rIISCON     = 0x0;			//IIS Interface stop    
    rIISFCON    = 0x0;     		//For FIFO flush
    StopDMA(RecStatus.DevReq);    
		
	return MMSYSERR_NOERROR;
}

MMRESULT waveInPrepareHeader(HWAVEIN hwi, LPWAVEHDR pwh, UINT cbwh)
{
	if((RecStatus.handle!=hwi)||(RecStatus.Status!=DEVICE_REC))
		return MMSYSERR_INVALHANDLE;
	
	pwh->lpNext = 0;
	pwh->dwBytesRecorded = 0;
	pwh->dwUser  = 0;
	pwh->dwFlags = 0;	
	return MMSYSERR_NOERROR;
}

MMRESULT waveInUnprepareHeader(HWAVEIN hwi, LPWAVEHDR pwh, UINT cbwh)
{
	if((RecStatus.handle!=hwi)||(RecStatus.Status!=DEVICE_REC))
		return MMSYSERR_INVALHANDLE;
		
	return MMSYSERR_NOERROR;
}

MMRESULT waveInAddBuffer(HWAVEIN hwi, LPWAVEHDR pwh, UINT cbwh)
{
	if((RecStatus.handle!=hwi)||(RecStatus.Status!=DEVICE_REC))
		return MMSYSERR_INVALHANDLE;
	
	if(!RecTotBlks)
	{
		lpRecFstBlk = pwh;
		lpRecCurBlk = lpRecFstBlk;							
	}
	else
	{
		lpRecLstBlk->lpNext = pwh;		
	}
	lpRecLstBlk = pwh;
	pwh->lpNext = 0;
	RecTotBlks++;		

	return MMSYSERR_NOERROR;
}

MMRESULT waveInReset(HWAVEOUT hwi)
{
	return MMSYSERR_NOERROR;
}

/************************* Control Function *********************/
static void IIS_PortSetting(void)
{
//----------------------------------------------------------
//   PORT B GROUP
//Ports  :   GPB4    GPB3   GPB2  
//Signal :  L3CLOCK L3DATA L3MODE
//Setting:   OUTPUT OUTPUT OUTPUT 
//           [9:8]   [7:6}  [5:4]
//Binary :     01  ,   01    01 
//----------------------------------------------------------    
	rGPBUP  = rGPBUP  & ~(0x7<<2) | (0x7<<2);   //The pull up function is disabled GPB[4:2] 1 1100    
	rGPBCON = rGPBCON & ~(0x3f<<4) | (0x15<<4); //GPB[4:2]=Output(L3CLOCK):Output(L3DATA):Output(L3MODE)
//----------------------------------------------------------
//   PORT E GROUP
//Ports  :  GPE4    GPE3   GPE2  GPE1    GPE0 
//Signal : I2SSDO  I2SSDI CDCLK I2SSCLK I2SLRCK 
//Binary :   10  ,   10     10 ,  10      10    
//----------------------------------------------------------
	rGPEUP  = rGPEUP  & ~(0x1f)  | 0x1f;    //The pull up function is disabled GPE[4:0] 1 1111
	rGPECON = rGPECON & ~(0x3ff) | 0x2aa;   //GPE[4:0]=I2SSDO:I2SSDI:CDCLK:I2SSCLK:I2SLRCK
}    

//==========================================================
#define L3C (1<<4)              //GPB4 = L3CLOCK
#define L3D (1<<3)              //GPB3 = L3DATA
#define L3M (1<<2)              //GPB2 = L3MODE

static void _WrL3Addr(U8 data)
{       
	S32 i,j;

	rGPBDAT  = rGPBDAT & ~(L3D | L3M | L3C) | L3C;      //L3D=L, L3M=L(in address mode), L3C=H

	for(j=0;j<4;j++);                   //tsu(L3) > 190ns

      //GPB[4:2]=L3C:L3D:L3M
	for(i=0;i<8;i++)                    //LSB first
	{
		if(data & 0x1)                  //If data's LSB is 'H'
		{
			rGPBDAT &= ~L3C;            //L3C=L
			rGPBDAT |= L3D;             //L3D=H             
			for(j=0;j<4;j++);           //tcy(L3) > 500ns
			rGPBDAT |= L3C;             //L3C=H
			rGPBDAT |= L3D;             //L3D=H
			for(j=0;j<4;j++);           //tcy(L3) > 500ns
        	}
		else                            //If data's LSB is 'L'
		{
			rGPBDAT &= ~L3C;            //L3C=L
			rGPBDAT &= ~L3D;            //L3D=L
			for(j=0;j<4;j++);           //tcy(L3) > 500ns
			rGPBDAT |= L3C;             //L3C=H
			rGPBDAT &= ~L3D;            //L3D=L
			for(j=0;j<4;j++);           //tcy(L3) > 500ns            
		}
		data >>= 1;
	}
	rGPBDAT  = rGPBDAT & ~(L3D | L3M | L3C) | (L3C | L3M);       //L3M=H,L3C=H   
}

//==========================================================
static void _WrL3Data(U8 data,int halt)
{
	S32 i,j;

	if(halt)
	{
		rGPBDAT  = rGPBDAT & ~(L3D | L3M | L3C) | L3C;   //L3C=H(while tstp, L3 interface halt condition)        
		for(j=0;j<4;j++);                                //tstp(L3) > 190ns
	}

	rGPBDAT  = rGPBDAT & ~(L3D | L3M | L3C) | (L3C | L3M);   //L3M=H(in data transfer mode)        
	for(j=0;j<4;j++);                                        //tsu(L3)D > 190ns

	//GPB[4:2]=L3C:L3D:L3M
	for(i=0;i<8;i++)
	{
		if(data & 0x1)                   //if data's LSB is 'H'
		{
			rGPBDAT &= ~L3C;              //L3C=L
			rGPBDAT |= L3D;               //L3D=H
			for(j=0;j<4;j++);             //tcy(L3) > 500ns
			rGPBDAT |= (L3C | L3D);       //L3C=H,L3D=H
			for(j=0;j<4;j++);             //tcy(L3) > 500ns
		}
		else                             //If data's LSB is 'L'
		{
			rGPBDAT &= ~L3C;              //L3C=L
			rGPBDAT &= ~L3D;              //L3D=L
			for(j=0;j<4;j++);             //tcy(L3) > 500ns
			rGPBDAT |= L3C;               //L3C=H
			rGPBDAT &= ~L3D;              //L3D=L
			for(j=0;j<4;j++);             //tcy(L3) > 500ns
		}
		data >>= 1;                      //For check next bit
	}
    rGPBDAT  = rGPBDAT & ~(L3D | L3M | L3C) | (L3C | L3M);    //L3M=H,L3C=H
}

//==========================================================
static void Init1341(char mode)
{
	U16 FsIdx;
//Port Initialize
//----------------------------------------------------------
//   PORT B GROUP
//Ports  :   GPB4    GPB3   GPB2  
//Signal :  L3CLOCK L3DATA L3MODE
//Setting:   OUTPUT OUTPUT OUTPUT 
//           [9:8]   [7:6}  [5:4]
//Binary :     01  ,   01    01 
//----------------------------------------------------------    
	rGPBDAT = rGPBDAT & ~(L3M|L3C|L3D) |(L3M|L3C); //Start condition : L3M=H, L3C=H
	rGPBUP  = rGPBUP  & ~(0x7<<2) |(0x7<<2);       //The pull up function is disabled GPB[4:2] 1 1100    
	rGPBCON = rGPBCON & ~(0x3f<<4) |(0x15<<4);     //GPB[4:2]=Output(L3CLOCK):Output(L3DATA):Output(L3MODE)
	
	//L3 Interface
	_WrL3Addr(0x14 + 2);	//STATUS (000101xx+10)
	_WrL3Data(0x60,0);		//0,1,10, 000,0 : Status 0,Reset,256fs,IIS-bus,no DC-filtering
	
	_WrL3Addr(0x14 + 2);	//STATUS (000101xx+10)
	
	FsIdx = mode?RecStatus.FsIdx:PlayStatus.FsIdx;        
	if(CodecPara[FsIdx].ofs)
		_WrL3Data(0x18,0);	//0,0,01, 000,0 : Status 0,No reset,384fs,IIS-bus,no DC-filtering
	else
	 _WrL3Data(0x28,0);	//0,0,10, 000,0 : Status 0,No reset,256fs,IIS-bus,no DC-filtering
	
	_WrL3Addr(0x14 + 2);	//STATUS (000101xx+10)
	_WrL3Data(0xc1,0);		//1,0,0,0, 0,0,01 
							//Status 1,Gain of DAC 6 dB,Gain of ADC 0dB,ADC non-inverting,DAC non-inverting
							//,Single speed playback,ADC-Off DAC-On
    
	//Record
	if(mode)
	{
		_WrL3Addr(0x14 + 2);	//STATUS (000101xx+10)
//		_WrL3Data(0xa2,0);		//1,0,1,0, 0,0,10 
								//Status 1,Gain of DAC 0 dB,Gain of ADC 6dB,ADC non-inverting,DAC non-inverting
								//,Single speed playback,ADC-On DAC-Off       

		_WrL3Data(0xe3,0);		//1,1,1,0, 0,0,11 
								//Status 1,Gain of DAC 6 dB,Gain of ADC 6dB,ADC non-inverting,DAC non-inverting
								//,Single speed playback,ADC-On DAC-On,DAC打开使录音时可从耳机听到声音

//		_WrL3Addr(0x14 + 0);	//DATA0 (000101xx+00)
//		_WrL3Data(0x3f,0);		//00,11 1111  : Volume control (6 bits)  
//		_WrL3Data(0x00,0);		//00,00 0000  : Volume control (6 bits) 0dB    

		_WrL3Addr(0x14 + 0);	//DATA0 (000101xx+00)
		_WrL3Data(0x7b,0);		//01,11 10,11 : Data0, Bass Boost 18~24dB, Treble 6dB
		
//		_WrL3Addr(0x14 + 0);	//DATA0 (000101xx+00)
		_WrL3Data(0xc4,0);		//1100 0,100  : Extended addr(3bits), 100
//		_WrL3Data(0x90,0);		//100,1 00,00 : DATA0, Enable AGC, 00, input amplifier gain channel 2 (2bits)
		_WrL3Data(0xf0,0);		//111,1 00,00 : DATA0, Enable AGC, 00, input amplifier gain channel 2 (2bits)

//		_WrL3Addr(0x14 + 0);	//DATA0 (000101xx+00)
		_WrL3Data(0xc0,0);		//1100 0,000  : Extended addr(3bits), 000		
		_WrL3Data(0xe4,0);		//111, 00000  : MA = 0dB
		_WrL3Data(0xc1,0);		//1100 0,001  : Extended addr(3bits), 001 
		_WrL3Data(0xe4,0);		//111, 00000  : MB = 0dB
		
//		_WrL3Addr(0x14 + 0);	//DATA0 (000101xx+00)
		_WrL3Data(0xc2,0);		//1100 0,010  : Extended addr(3bits), 010
//		_WrL3Data(0x59,0);		//010,1 10,01 : DATA0, MIC Amplifier Gain 27dB, input channel 1 select(input channel 2 off)
		_WrL3Data(0xf9,0);		//111,1 10,11 : DATA0, MIC Amplifier Gain 27dB, input 1 X MA + input 2 X MB
	}
}

//==========================================================
static void PlayPause(U8 mode)
{
	if(mode) 
		rIISCON &= ~1;		//stop iis
	else
		rIISCON |= 1;		//start iis
}

#define	MAX_VOLUME	61
static void AdjVolume(U16 volume)	
{	
	rGPBDAT = rGPBDAT & ~(L3M|L3C|L3D) |(L3M|L3C); //Start condition : L3M=H, L3C=H
	rGPBUP  = rGPBUP  & ~(0x7<<2) |(0x7<<2);       //The pull up function is disabled GPB[4:2] 1 1100    
   	rGPBCON = rGPBCON & ~(0x3f<<4) |(0x15<<4);     //GPB[4:2]=Output(L3CLOCK):Output(L3DATA):Output(L3MODE)
	
	volume = (volume*MAX_VOLUME)/0xffff;		    
	    
	_WrL3Addr(0x14 + 0);				//DATA0 (000101xx+00)
   	_WrL3Data(MAX_VOLUME-volume, 0);
}

//==========================================================