#include "def.h"
#include "option.h"
#include "2440addr.h"
#include "2440lib.h"
#include "2440slib.h" 
#include "dma.h"

#define	DMA_CHECK_ATTR	1

typedef struct{						//can't use __packed???
    volatile U32 DISRC;	    //0x0
    volatile U32 DISRCC;    //0x4
    volatile U32 DIDST;	    //0x8
    volatile U32 DIDSTC;    //0xc
    volatile U32 DCON;	    //0x10
    volatile U32 DSTAT;	    //0x14
    volatile U32 DCSRC;	    //0x18
    volatile U32 DCDST;	    //0x1c
    volatile U32 DMASKTRIG; //0x20
}DMAReg;

static struct{
	U16 used;
	U16 DevID;
	DMAReg *pDMA;
}
DMAChannel[MAX_DMA_CHANNEL];

/********************************************************/
//attr高16位为设备ID,低16位的高8位为DMA传送源,目的属性(AHP/APB,INCREASE/FIX)
//低8位为请求源,返回值失败为REQUEST_DMA_FAIL,成功高16位为设备ID,低8位为申请到的通道
U32 RequestDMASW(U32 attr, U32 mode)
{
	U16 channel;
	U32 ret;
	
	attr &= ~0xff;
	mode &= ~HW_TRIG;
	
	for(channel=0; channel<(MAX_DMA_CHANNEL*0x10); channel+=0x10)
	{
		ret = RequestDMA(attr|channel, mode);
		if(ret!=REQUEST_DMA_FAIL)
			break;
	}
	return ret;			
}

U32 RequestDMA(U32 attr, U32 mode)
{
	U16 DevID, ReqSrc, ch;
	U32 ret=REQUEST_DMA_FAIL, r;
	
	DevID   = attr>>16;	
	ReqSrc  = attr&0xff;	
	
	if(((ReqSrc>>4)>=MAX_DMA_CHANNEL)||((ReqSrc&0xf)>4))
		return ret;
		
	EnterCritical(&r);
		
	if(DMAChannel[ReqSrc>>4].used!=DMA_IS_FREE)
	{
		U8 src = ReqSrc;			
		
		if(src==REQ_IISDI)
		{		
			if(DMAChannel[2].used!=DMA_IS_FREE)
				goto RequestDmaExit;
			else							
				ReqSrc = 0x21;											
		}
		else if(src==REQ_SDI)
		{
			if(DMAChannel[2].used!=DMA_IS_FREE)
			{
				if(DMAChannel[3].used!=DMA_IS_FREE)
					goto RequestDmaExit;
				else
					ReqSrc = 0x31;				
			}
			else
				ReqSrc = 0x22;					
		}
		else if(src==REQ_SPI)
		{
			if(DMAChannel[3].used!=DMA_IS_FREE)
				goto RequestDmaExit;
			else				
				ReqSrc = 0x32;				
		}
		else if(src==REQ_TIMER)
		{
			if(DMAChannel[2].used!=DMA_IS_FREE)
			{
				if(DMAChannel[3].used!=DMA_IS_FREE)
					goto RequestDmaExit;
				else				
					ReqSrc = 0x33;				
			}
			else				
				ReqSrc = 0x23;					
		}
		else
			goto RequestDmaExit;		
	}	
			
	ch = ReqSrc>>4;
	if(mode&HW_TRIG)
		DMAChannel[ch].used  = DMA_IS_HWTRIG;
	else
		DMAChannel[ch].used  = DMA_IS_SWTRIG;	
	DMAChannel[ch].DevID = DevID;
	DMAChannel[ch].pDMA  = (DMAReg *)(0x4b000000+(ch)*0x40);	
	DMAChannel[ch].pDMA->DMASKTRIG = 1<<2;	//stop dma
	DMAChannel[ch].pDMA->DISRCC = (attr>>8)&3;	
	DMAChannel[ch].pDMA->DIDSTC = (attr>>12)&3;	
	mode &= ~0x07000000;
	mode |= (ReqSrc&0x7)<<24;
	DMAChannel[ch].pDMA->DCON	= mode;	

//	DbgOut("Request DMA %x success\n", ReqSrc);
	ret = (DevID<<16)|ReqSrc;
	
RequestDmaExit:
	ExitCritical(&r);	
	return ret;			
}

U16 ReleaseDMA(U32 attr)
{
	U16 DevID, ReqSrc, ch;	
	
	DevID  = attr>>16;
	ReqSrc = attr&0xf;
	ch     = (attr&0xf0)>>4;
	
#if	DMA_CHECK_ATTR					
	if((ch>=MAX_DMA_CHANNEL)||(ReqSrc>4))
		return 1;
	if((DMAChannel[ch].used==DMA_IS_FREE)||(DMAChannel[ch].DevID!=DevID))
		return 1;
#endif	
		
	DMAChannel[ch].pDMA->DMASKTRIG = 0;//4;	//stop dma and channel off 
	DMAChannel[ch].used = DMA_IS_FREE;
	
	return 0;					
}

U16 StartDMA(U32 attr)
{
	U16 DevID, ReqSrc, ch;	
	
	DevID  = attr>>16;
	ReqSrc = attr&0xf;
	ch     = (attr&0xf0)>>4;		
#if	DMA_CHECK_ATTR		
	if((ch>=MAX_DMA_CHANNEL)||(ReqSrc>4))
		return 1;
	if((DMAChannel[ch].used==DMA_IS_FREE)||(DMAChannel[ch].DevID!=DevID))
		return 1;
#endif
	
	if(DMAChannel[ch].used==DMA_IS_HWTRIG)
		DMAChannel[ch].pDMA->DMASKTRIG = 2;		//channel on
	if(DMAChannel[ch].used==DMA_IS_SWTRIG)
		DMAChannel[ch].pDMA->DMASKTRIG = 3;		//sw_trig
		
	return 0;	
}

U16 StopDMA(U32 attr)
{
	U16 DevID, ReqSrc, ch;
	
	DevID  = attr>>16;
	ReqSrc = attr&0xf;
	ch     = (attr&0xf0)>>4;		
#if	DMA_CHECK_ATTR		
	if((ch>=MAX_DMA_CHANNEL)||(ReqSrc>4))
		return 1;
	if((DMAChannel[ch].used==DMA_IS_FREE)||(DMAChannel[ch].DevID!=DevID))
		return 1;
#endif	

	DMAChannel[ch].pDMA->DMASKTRIG = 1<<2;	//channel off	
		
	return 0;
}

U16 SetDMARun(U32 attr, U32 src_addr, U32 dst_addr, U32 len)
{
	U16 DevID, ReqSrc, ch;	
	
	DevID  = attr>>16;
	ReqSrc = attr&0xf;
	ch     = (attr&0xf0)>>4;		
#if	DMA_CHECK_ATTR		
	if((ch>=MAX_DMA_CHANNEL)||(ReqSrc>4))
		return 1;
	if((DMAChannel[ch].used==DMA_IS_FREE)||(DMAChannel[ch].DevID!=DevID))
		return 1;
#endif
	DMAChannel[ch].pDMA->DISRC = src_addr;
	DMAChannel[ch].pDMA->DIDST = dst_addr;
	DMAChannel[ch].pDMA->DCON &= ~0xfffff;
	DMAChannel[ch].pDMA->DCON |= len&0xfffff;
	
	if(attr&DMA_START)
	{
		if(DMAChannel[ch].used==DMA_IS_HWTRIG)
			DMAChannel[ch].pDMA->DMASKTRIG = 2;		//channel on
		if(DMAChannel[ch].used==DMA_IS_SWTRIG)
			DMAChannel[ch].pDMA->DMASKTRIG = 3;		//sw_trig
	}
	
	return 0;
}

U32 QueryDMAStat(U32 attr)
{
	U16 DevID, ReqSrc, ch;
	
	DevID  = attr>>16;
	ReqSrc = attr&0xf;
	ch     = (attr&0xf0)>>4;		
#if	DMA_CHECK_ATTR		
	if((ch>=MAX_DMA_CHANNEL)||(ReqSrc>4))
		return -1;
	if((DMAChannel[ch].used==DMA_IS_FREE)||(DMAChannel[ch].DevID!=DevID))
		return -1;
#endif	

	return DMAChannel[ch].pDMA->DSTAT;	//STAT[21:20], CURR_TC[19:0] 
}

U32 QueryDMASrc(U32 attr)
{
	U16 DevID, ReqSrc, ch;
	
	DevID  = attr>>16;
	ReqSrc = attr&0xf;
	ch     = (attr&0xf0)>>4;		
#if	DMA_CHECK_ATTR		
	if((ch>=MAX_DMA_CHANNEL)||(ReqSrc>4))
		return -1;
	if((DMAChannel[ch].used==DMA_IS_FREE)||(DMAChannel[ch].DevID!=DevID))
		return -1;
#endif	

	return DMAChannel[ch].pDMA->DCSRC;
}

U32 QueryDMADst(U32 attr)
{
	U16 DevID, ReqSrc, ch;
	
	DevID  = attr>>16;
	ReqSrc = attr&0xf;
	ch     = (attr&0xf0)>>4;		
#if	DMA_CHECK_ATTR		
	if((ch>=MAX_DMA_CHANNEL)||(ReqSrc>4))
		return -1;
	if((DMAChannel[ch].used==DMA_IS_FREE)||(DMAChannel[ch].DevID!=DevID))
		return -1;
#endif	

	return DMAChannel[ch].pDMA->DCDST;
}