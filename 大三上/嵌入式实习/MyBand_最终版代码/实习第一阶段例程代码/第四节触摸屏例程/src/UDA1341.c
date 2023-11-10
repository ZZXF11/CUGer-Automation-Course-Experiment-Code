#include "def.h"
#include "2440addr.h"
#include "2440lib.h"
#include "AudioDrv.h"
#include "Wav_source.h"
#include "drum1.h"
#include "drum2.h"
#include "drum3.h"
#include "drum4.h"
#include "drum5.h"
#include "drum6.h"
#include "drum7.h"
#include "drum8.h"

#include "LCD_TFT.h"

#define	BUF_SIZE	(16*1024)

extern U32 downloadAddress;
extern U32 downloadFileSize;
extern unsigned char cover[];

void PlayMusicTest()
{
	int size, i, j, err;
	WAVEFORMATEX fmt;
	WAVEHDR hdr[2048];
	HWAVEOUT hwo;	
	U8 pause = 0;
	U8 mute = 0;	
	U32 volume;
	unsigned char *buf;

	downloadAddress = _NONCACHE_STARTADDRESS;
	buf = (unsigned char *)downloadAddress ;
	for( i = 0; i < 243552; i++ )  buf[i] = WindowsXP_Wav[i] ;//$$$$$$$$$$$$$$$$$$$$$$$$
	downloadFileSize = 243552 ;

	size = *(U32 *)(downloadAddress+0x28);
	i = 0;							
	
	while(size>0)
	{
		hdr[i].lpData = (LPSTR)(downloadAddress+0x2c+i*BUF_SIZE);
		hdr[i].dwBufferLength = (size>BUF_SIZE)?BUF_SIZE:size;	
		size -= BUF_SIZE;
		i++;
	}
	
	fmt.wFormatTag		= WAVE_FORMAT_PCM;
	fmt.nChannels		= *(U16 *)(downloadAddress+0x16);
	fmt.nSamplesPerSec	= *(U32 *)(downloadAddress+0x18);
	fmt.nAvgBytesPerSec	= *(U32 *)(downloadAddress+0x1c);
	fmt.nBlockAlign		= *(U16 *)(downloadAddress+0x20);
	fmt.wBitsPerSample	= *(U16 *)(downloadAddress+0x22);
	Uart_Printf("\nSample Rate = %d, Channels = %d, %dBitsPerSample, size = %d\n",
			fmt.nSamplesPerSec, fmt.nChannels, fmt.wBitsPerSample, *(U32 *)(downloadAddress+0x28));
	
	hwo = 0;
	err = waveOutOpen(&hwo,
				0,
				&fmt,
				0,
				0,
				0);
	Uart_Printf("\nerr = %x\n", err);
	for(j=0;j<i;j++)
		waveOutWrite(0,	&hdr[j], 0);
		
	Uart_Printf("Now playing the file\n");
	Uart_Printf("Press 'ESC' to quit, '+' to inc volume, '-' to dec volume, 'm' to mute, 'p' to pause\n");		
	
	waveOutGetVolume(0,	&volume);
	Paint_Bmp(0, 0, 480, 272,cover);//开机显示封面
		for(i=10000;i>0;i--)
		{
			for(j=20000;j>0;j--);
		}
	/*while(1)
	{
		U8 key = Uart_Getch();
		if( key == ESC_KEY )
			break;
		if(key=='p')
		{
			pause ^= 1;
			if(pause&1)
				waveOutPause(0);
			else
				waveOutRestart(0);				
		}
		if(key=='m')
		{						
			mute ^= 1;
			if(mute&1)									
				waveOutSetVolume(0, 0);			
			else
				waveOutSetVolume(0, volume);			
		}
		if((key=='+')&&(volume<=64535))		
		{
			volume += 1000;
			waveOutSetVolume(0, volume);
		}
		if((key=='-')&&(volume>=1000))
		{
			volume -= 1000;
			waveOutSetVolume(0, volume);
		}	
					
	}	*/				
	waveOutClose(0);
}

void Play_drums(int index)//drum1~8
{
	int size, i, j, err;
	WAVEFORMATEX fmt;
	WAVEHDR hdr[2048];
	HWAVEOUT hwo;	
	U8 pause = 0;
	U8 mute = 0;	
	U32 volume;
	unsigned char *buf;

	downloadAddress = _NONCACHE_STARTADDRESS;
	buf = (unsigned char *)downloadAddress ;
	for( i = 0; i < 243552; i++ )  
	{
		switch (index)
		{
			case 1:{buf[i] =drum1[i] ;break;}
			case 2:{buf[i] =drum2[i] ;break;}
			case 3:{buf[i] =drum3[i] ;break;}
			case 4:{buf[i] =drum4[i] ;break;}
			case 5:{buf[i] =drum5[i] ;break;}
			case 6:{buf[i] =drum6[i] ;break;}
			case 7:{buf[i] =drum7[i] ;break;}
			case 8:{buf[i] =drum8[i] ;break;}
		}
		
	}
	//buf[i] =drum1[i] ;//$$$$$$$$$$$$$$$$$$$$$$$$
	downloadFileSize = 243552 ;

	size = *(U32 *)(downloadAddress+0x28);
	i = 0;							
	
	while(size>0)
	{
		hdr[i].lpData = (LPSTR)(downloadAddress+0x2c+i*BUF_SIZE);
		hdr[i].dwBufferLength = (size>BUF_SIZE)?BUF_SIZE:size;	
		size -= BUF_SIZE;
		i++;
	}
	
	fmt.wFormatTag		= WAVE_FORMAT_PCM;
	fmt.nChannels		= *(U16 *)(downloadAddress+0x16);
	fmt.nSamplesPerSec	= *(U32 *)(downloadAddress+0x18);
	fmt.nAvgBytesPerSec	= *(U32 *)(downloadAddress+0x1c);
	fmt.nBlockAlign		= *(U16 *)(downloadAddress+0x20);
	fmt.wBitsPerSample	= *(U16 *)(downloadAddress+0x22);
	Uart_Printf("\nSample Rate = %d, Channels = %d, %dBitsPerSample, size = %d\n",
			fmt.nSamplesPerSec, fmt.nChannels, fmt.wBitsPerSample, *(U32 *)(downloadAddress+0x28));
	
	hwo = 0;
	err = waveOutOpen(&hwo,
				0,
				&fmt,
				0,
				0,
				0);
	Uart_Printf("\nerr = %x\n", err);
	for(j=0;j<i;j++)
		waveOutWrite(0,	&hdr[j], 0);
		
	Uart_Printf("Now playing drum1!\n");
	//Uart_Printf("Press 'ESC' to quit, '+' to inc volume, '-' to dec volume, 'm' to mute, 'p' to pause\n");		
	
	waveOutGetVolume(0,	&volume);
	//Paint_Bmp(0, 0, 480, 272, menu);//菜单背景
		switch (index)
		{
			case 1:{for(i=10000;i>0;i--){for(j=3500;j>0;j--);}break;}
			case 2:{for(i=10000;i>0;i--){for(j=2000;j>0;j--);}break;}
			case 3:{for(i=10000;i>0;i--){for(j=2000;j>0;j--);}break;}
			case 4:{for(i=10000;i>0;i--){for(j=2000;j>0;j--);}break;}
			case 5:{for(i=10000;i>0;i--){for(j=3500;j>0;j--);}break;}
			case 6:{for(i=10000;i>0;i--){for(j=2000;j>0;j--);}break;}
			case 7:{for(i=10000;i>0;i--){for(j=2000;j>0;j--);}break;}
			case 8:{for(i=10000;i>0;i--){for(j=3000;j>0;j--);}break;}
		}	
	
	
	
		
	
		
	/*while(1)
	{
		U8 key = Uart_Getch();
		if( key == ESC_KEY )
			break;
		if(key=='p')
		{
			pause ^= 1;
			if(pause&1)
				waveOutPause(0);
			else
				waveOutRestart(0);				
		}
		if(key=='m')
		{						
			mute ^= 1;
			if(mute&1)									
				waveOutSetVolume(0, 0);			
			else
				waveOutSetVolume(0, volume);			
		}
		if((key=='+')&&(volume<=64535))		
		{
			volume += 1000;
			waveOutSetVolume(0, volume);
		}
		if((key=='-')&&(volume>=1000))
		{
			volume -= 1000;
			waveOutSetVolume(0, volume);
		}	
					
	}	*/				
	waveOutClose(0);
}

void RecordTest(void)
{
	int size, i, j, err;
	WAVEFORMATEX fmt;
	WAVEHDR hdr[2048];
	HWAVEIN hwi = 1;	
	
	Uart_Printf( "\nThe Frequency of record is 48KHz\n" );
	fmt.nSamplesPerSec = 48000;		//采样频率为48KHz
	fmt.wBitsPerSample = 16;

	fmt.wFormatTag		= WAVE_FORMAT_PCM;
	fmt.nChannels		= 2;
	fmt.nBlockAlign     = fmt.wBitsPerSample*fmt.nChannels/8;	
	fmt.nAvgBytesPerSec	= fmt.nSamplesPerSec*fmt.nBlockAlign;
	
	downloadAddress  = 0x30800000;//_NONCACHE_STARTADDRESS;
	downloadFileSize = size = 16*1024*1024;	
	i = 0;
	
	while(size>0)
	{
		hdr[i].lpData = (LPSTR)(downloadAddress+0x2c+i*BUF_SIZE);
		hdr[i].dwBufferLength = (size>BUF_SIZE)?BUF_SIZE:size;	
		size -= BUF_SIZE;
		i++;
	}	
	
	*(U16 *)(downloadAddress+0x14) = fmt.wFormatTag;
	*(U16 *)(downloadAddress+0x16) = fmt.nChannels;
	*(U32 *)(downloadAddress+0x18) = fmt.nSamplesPerSec;
	*(U32 *)(downloadAddress+0x1c) = fmt.nAvgBytesPerSec;
	*(U16 *)(downloadAddress+0x20) = fmt.nBlockAlign;
	*(U16 *)(downloadAddress+0x22) = fmt.wBitsPerSample;
	*(U32 *)(downloadAddress+0x28) = downloadFileSize;
	
	err = waveInOpen(&hwi,
				0,
				&fmt,
				0,
				0,
				0);
	Uart_Printf("\nerr = %x\n", err);
	
	for(j=0;j<i;j++)
		if(waveInAddBuffer(hwi, &hdr[j], 0))
			Uart_Printf("Add buffer error!");
			
	Uart_Printf("Added %d buffer for record\n", i);
	Uart_Printf("Press any to Record\n");
	Uart_Getch();
	
	Uart_Printf("Now begin recording, Press 'ESC' to quit\n");	
	waveInStart(hwi);
	
	while(1)
	{
		U8 key;
		
		key = Uart_GetKey();
		if( key == ESC_KEY )
			break;
			
//		Uart_Printf("%x,%x,%x,%x,%x,%x,%x\n", rDISRC2, rDISRCC2, rDIDST2, rDIDSTC2, rDCON2, rDSTAT2, rDMASKTRIG2);		
//		Uart_Printf("%x,%x,%x,%x\n", rIISCON, rIISMOD, rIISPSR, rIISFCON);
	}		
	waveInClose(hwi);
}

void RecordChannelOnOff(void)
{
	static int ChannelOn = 0;
	int err;
	WAVEFORMATEX fmt;
	WAVEHDR hdr;
	HWAVEIN hwi = 1;
	
	fmt.nSamplesPerSec  = 22050;
	fmt.wBitsPerSample  = 16;
	fmt.wFormatTag		= WAVE_FORMAT_PCM;
	fmt.nChannels		= 2;
	fmt.nBlockAlign     = fmt.wBitsPerSample*fmt.nChannels/8;	
	fmt.nAvgBytesPerSec	= fmt.nSamplesPerSec*fmt.nBlockAlign;
	
	hdr.lpData = (LPSTR)0x30800000;//_NONCACHE_STARTADDRESS;
	hdr.dwBufferLength = BUF_SIZE;
	
	if(!ChannelOn)
	{
		err = waveInOpen(&hwi,
					0,
					&fmt,
					0,
					0,
					0);
		Uart_Printf("\nerr = %x\n", err);
		if(!err)
		{
			waveInAddBuffer(hwi, &hdr, 0);
			waveInStart(hwi);
			Uart_Printf("Record channel on\n");
			ChannelOn = 1;
		}
	}
	else
	{
		waveInClose(hwi);
		Uart_Printf("Record channel off\n");
		ChannelOn = 0;
	}
}
