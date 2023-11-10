/**************************************************************
 NAME: option.h
 DESC: To measuure the USB download speed, the WDT is used.
       To measure up to large time, The WDT interrupt is used.
 **************************************************************/
 
#ifndef __OPTION_H__
#define __OPTION_H__

#define MEGA	(1000000)

#define FIN 	(12000000)	

//use variable
#ifdef GLOBAL_CLK
	U32 FCLK;
	U32 HCLK;
	U32 PCLK;
	U32 UCLK;
#else
	extern unsigned int FCLK;
	extern unsigned int HCLK;
	extern unsigned int PCLK;
	extern unsigned int UCLK;
#endif

// BUSWIDTH : 16,32
#define BUSWIDTH    (32)

//64MB
// 0x30000000 ~ 0x30ffffff : Download Area (16MB) Cacheable
// 0x31000000 ~ 0x33feffff : Non-Cacheable Area
// 0x33ff0000 ~ 0x33ff47ff : Heap & RW Area
// 0x33ff4800 ~ 0x33ff7fff : FIQ ~ User Stack Area
// 0x33ff8000 ~ 0x33fffeff : Not Useed Area
// 0x33ffff00 ~ 0x33ffffff : Exception & ISR Vector Table

#define _RAM_STARTADDRESS 	0x30000000
#define _ISR_STARTADDRESS 	0x33ffff00     
#define _MMUTT_STARTADDRESS	0x33ff8000
#define _STACK_BASEADDRESS	0x33ff8000
#define HEAPEND		  	0x33ff0000
#define _NONCACHE_STARTADDRESS	0x31000000

//If you use ADS1.x, please define ADS10
#define ADS10 1

//USB Device Options
#define USBDMA		1	//1->0
#define USBDMA_DEMAND 	0	//the downloadFileSize should be (64*n)
#define BULK_PKT_SIZE	64

// note: makefile,option.a should be changed

#endif /*__OPTION_H__*/
