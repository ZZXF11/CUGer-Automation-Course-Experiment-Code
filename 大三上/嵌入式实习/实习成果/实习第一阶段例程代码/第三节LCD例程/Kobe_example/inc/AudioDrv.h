#ifndef	AUDIO_DRV_H
#define	AUDIO_DRV_H

#include "def.h"

#define	HWAVEOUT	U32
#define	LPHWAVEOUT	HWAVEOUT *
#define	HWAVEIN		HWAVEOUT
#define	LPHWAVEIN	HWAVEIN *

#define	LPDWORD	U32 *
#define	MMRESULT	U32

#define MMSYSERR_BASE 	0
#define WAVERR_BASE 	32
#define	MMSYSERR_NOERROR 		(MMSYSERR_BASE+0) 
#define	MMSYSERR_BADDEVICEID 	(MMSYSERR_BASE+2)
#define	MMSYSERR_INVALHANDLE 	(MMSYSERR_BASE+5)
#define	MMSYSERR_NOMEM 			(MMSYSERR_BASE+7) 
#define	MMSYSERR_NOTSUPPORTED 	(MMSYSERR_BASE+8)
#define	WAVERR_BADFORMAT 		(WAVERR_BASE+0) 
#define	WAVERR_STILLPLAYING 	(WAVERR_BASE+1)
#define	WAVERR_UNPREPARED 		(WAVERR_BASE+2) 
#define	WAVERR_SYNC 			(WAVERR_BASE+3) 

typedef struct tWAVEFORMATEX{
	WORD wFormatTag;
	WORD nChannels;
	DWORD nSamplesPerSec;
	DWORD nAvgBytesPerSec;
	WORD nBlockAlign;
	WORD wBitsPerSample;
	WORD cbSize;
}WAVEFORMATEX, *LPWAVEFORMATEX;

typedef struct wavehdr_tag{
	LPSTR lpData;
	DWORD dwBufferLength;
	DWORD dwBytesRecorded;
	DWORD dwUser;
	DWORD dwFlags;
	DWORD dwLoops;
	struct wavehdr_tag *lpNext;
	DWORD reserved;
}WAVEHDR, *LPWAVEHDR;

MMRESULT waveOutOpen(
	LPHWAVEOUT phwo,
	UINT uDeviceID,
	LPWAVEFORMATEX pwfx,
	DWORD dwCallback,
	DWORD dwCallbackInstance,
	DWORD fdwOpen
);
MMRESULT waveOutClose(HWAVEOUT hwo);
MMRESULT waveOutPrepareHeader(HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh);
MMRESULT waveOutUnprepareHeader(HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh);
MMRESULT waveOutWrite(HWAVEOUT hwo,	LPWAVEHDR pwh, UINT cbwh);
MMRESULT waveOutSetVolume(HWAVEOUT hwo,	DWORD dwVolume);
MMRESULT waveOutGetVolume(HWAVEOUT hwo, LPDWORD pdwVolume);
MMRESULT waveOutPause (HWAVEOUT hwo);
MMRESULT waveOutRestart(HWAVEOUT hwo);
MMRESULT waveOutReset (HWAVEOUT hwo);

/*******************************************************************/
MMRESULT waveInOpen(
	LPHWAVEIN phwi,
	UINT uDeviceID,
	LPWAVEFORMATEX pwfx,
	DWORD dwCallback,
	DWORD dwCallbackInstance,
	DWORD fdwOpen
);
MMRESULT waveInClose(HWAVEOUT hwi);
MMRESULT waveInStart(HWAVEIN hwi);
MMRESULT waveInStop(HWAVEIN hwi);
MMRESULT waveInPrepareHeader(HWAVEIN hwi, LPWAVEHDR pwh, UINT cbwh);
MMRESULT waveInUnprepareHeader(HWAVEIN hwi, LPWAVEHDR pwh, UINT cbwh);
MMRESULT waveInAddBuffer(HWAVEIN hwi, LPWAVEHDR pwh, UINT cbwh);
MMRESULT waveInReset(HWAVEOUT hwi);


#define	WAVE_FORMAT_UNKNOWN 				0x0000	//Microsoft Corporation
#define	WAVE_FORMAT_PCM 					0x0001	//PCM data format 
#define	WAVE_FORMAT_ADPCM 					0x0002	//Microsoft Corporation 
#define	WAVE_FORMAT_IEEE_FLOAT 				0x0003	//Microsoft Corporation 
#define	WAVE_FORMAT_IBM_CVSD 				0x0005	//IBM Corporation 
#define	WAVE_FORMAT_ALAW 					0x0006	//Microsoft Corporation 
#define	WAVE_FORMAT_MULAW 					0x0007	//Microsoft Corporation 
#define	WAVE_FORMAT_OKI_ADPCM 				0x0010	//OKI 
#define	WAVE_FORMAT_DVI_ADPCM 				0x0011	//Intel Corporation 
#define	WAVE_FORMAT_IMA_ADPCM 				0x0011 	//Intel Corporation 
#define	WAVE_FORMAT_MEDIASPACE_ADPCM 		0x0012	//Videologic 
#define	WAVE_FORMAT_SIERRA_ADPCM 			0x0013 	//Sierra Semiconductor Corp 
#define	WAVE_FORMAT_G723_ADPCM 				0x0014	//Antex Electronics Corporation 
#define	WAVE_FORMAT_DIGISTD 				0x0015	//DSP Solutions, Inc. 
#define	WAVE_FORMAT_DIGIFIX 				0x0016	//DSP Solutions, Inc. 
#define	WAVE_FORMAT_DIALOGIC_OKI_ADPCM 		0x0017 	//Dialogic Corporation 
#define	WAVE_FORMAT_MEDIAVISION_ADPCM 		0x0018 	//Media Vision, Inc. 
#define	WAVE_FORMAT_YAMAHA_ADPCM 			0x0020	//Yamaha Corporationof America 
#define	WAVE_FORMAT_SONARC 					0x0021	//Speech Compression 
#define	WAVE_FORMAT_DSPGROUP_TRUESPEECH 	0x0022 	//DSP Group, Inc 
#define	WAVE_FORMAT_ECHOSC1 				0x0023 	//Echo Speech Corporation 
#define	WAVE_FORMAT_AUDIOFILE_AF36 			0x0024
#define	WAVE_FORMAT_APTX 					0x0025	//Audio Processing Technology 
#define	WAVE_FORMAT_AUDIOFILE_AF10 			0x0026
#define	WAVE_FORMAT_DOLBY_AC2 				0x0030	//Dolby Laboratories 
#define	WAVE_FORMAT_GSM610 					0x0031	//Microsoft Corporation 
#define	WAVE_FORMAT_MSNAUDIO 				0x0032 	//Microsoft Corporation 
#define	WAVE_FORMAT_ANTEX_ADPCME 			0x0033	//Antex Electronics Corporation 
#define	WAVE_FORMAT_CONTROL_RES_VQLPC		0x0034 	//Control Resources Limited
#define	WAVE_FORMAT_DIGIREAL 				0x0035	//DSP Solutions, Inc. 
#define	WAVE_FORMAT_DIGIADPCM 				0x0036	//DSP Solutions, Inc. 
#define	WAVE_FORMAT_CONTROL_RES_CR10 		0x0037 	//Control Resources Limited 
#define	WAVE_FORMAT_NMS_VBXADPCM 			0x0038	//Natural MicroSystems 
#define	WAVE_FORMAT_CS_IMAADPCM 			0x0039	//Crystal Semiconductor IMA ADPCM 
#define	WAVE_FORMAT_ECHOSC3 				0x003A	//Echo Speech Corporation 
#define	WAVE_FORMAT_ROCKWELL_ADPCM 			0x003B	//Rockwell International
#define	WAVE_FORMAT_ROCKWELL_DIGITALK		0x003C 	//Rockwell International
#define	WAVE_FORMAT_XEBEC 					0x003D	//Xebec Multimedia Solutions Limited 
#define	WAVE_FORMAT_G721_ADPCM 				0x0040	//Antex Electronics Corporation 
#define	WAVE_FORMAT_G728_CELP 				0x0041	//Antex Electronics Corporation 
#define	WAVE_FORMAT_MPEG 					0x0050	//Microsoft Corporation 
#define	WAVE_FORMAT_MPEGLAYER3 				0x0055	//ISO/MPEG Layer3 Format Tag 
#define	WAVE_FORMAT_CIRRUS 					0x0060	//Cirrus Logic
#define	WAVE_FORMAT_ESPCM 					0x0061	//ESS Technology
#define	WAVE_FORMAT_VOXWARE 				0x0062	//Voxware Inc
#define	WAVEFORMAT_CANOPUS_ATRAC 			0x0063	//Canopus, co., Ltd. 
#define	WAVE_FORMAT_G726_ADPCM 				0x0064	//APICOM
#define	WAVE_FORMAT_G722_ADPCM 				0x0065	//APICOM 
#define	WAVE_FORMAT_DSAT 					0x0066	//Microsoft Corporation
#define	WAVE_FORMAT_DSAT_DISPLAY 			0x0067	//Microsoft Corporation
#define	WAVE_FORMAT_SOFTSOUND 				0x0080	//Softsound, Ltd. 
#define	WAVE_FORMAT_RHETOREX_ADPCM 			0x0100	//Rhetorex Inc
#define	WAVE_FORMAT_CREATIVE_ADPCM 			0x0200	//Creative Labs, Inc 
#define	WAVE_FORMAT_CREATIVE_FASTSPEECH8	0x0202	//Creative Labs, Inc 
#define	WAVE_FORMAT_CREATIVE_FASTSPEECH10	0x0203 	//Creative Labs, Inc 
#define	WAVE_FORMAT_QUARTERDECK				0x0220 	//Quarterdeck Corporation 
#define	WAVE_FORMAT_FM_TOWNS_SND 			0x0300	//Fujitsu Corp. 
#define	WAVE_FORMAT_BTV_DIGITAL 			0x0400	//Brooktree Corporation 
#define	WAVE_FORMAT_OLIGSM 					0x1000 	//Ing C. Olivetti & C., S.p.A. 
#define	WAVE_FORMAT_OLIADPCM 				0x1001	//Ing C. Olivetti & C., S.p.A. 
#define	WAVE_FORMAT_OLICELP 				0x1002	//Ing C. Olivetti & C., S.p.A. 
#define	WAVE_FORMAT_OLISBC 					0x1003 	//Ing C. Olivetti & C., S.p.A. 
#define	WAVE_FORMAT_OLIOPR 					0x1004	//Ing C. Olivetti & C., S.p.A. 
#define	WAVE_FORMAT_LH_CODEC 				0x1100	//Lernout & Hauspie 
#define	WAVE_FORMAT_NORRIS 					0x1400 	//Norris Communications, Inc. 
#define	WAVE_FORMAT_DEVELOPMENT 			(0xFFFF)//development a new wave forma

typedef void (*CallBackProc)(HWAVEOUT handle, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);

#endif	/* AUDIO_DRV_H */