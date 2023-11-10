/****************************************************************
 NAME: MAIN.h
 DESC: 
 ****************************************************************/
 
#ifndef __MAIN_H__
#define __MAIN_H__

extern volatile unsigned char *downPt;
extern volatile U32 totalDmaCount;
extern volatile U32 downloadFileSize;
extern volatile U32 downloadAddress;
extern volatile U16 checkSum;

extern int download_run;
extern U32 tempDownloadAddress;

#endif /*__MAIN_H__*/
