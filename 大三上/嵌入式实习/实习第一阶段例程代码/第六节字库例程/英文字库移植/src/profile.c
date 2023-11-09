/**************************************************************
 NAME: profile.c
 DESC: To measuure the USB download speed, the WDT is used.
       To measure up to large time, The WDT interrupt is used.
 **************************************************************/
#include "def.h"
#include "option.h"
#include "2440addr.h"
#include "2440lib.h"
#include "2440slib.h" 

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/************************* Timer ********************************/
static int intCount;

void __irq IsrWatchdog(void);

void Timer_InitEx(void)
{
	intCount=0;	
	pISR_WDT_AC97=(U32)IsrWatchdog;
	ClearPending(BIT_WDT_AC97);
	rSUBSRCPND=BIT_SUB_WDT;
	rINTMSK&=~(BIT_WDT_AC97);
	rINTSUBMSK&=~(BIT_SUB_WDT);
}


void Timer_StartEx(void)
{
	int divider=0;
	rWTCON=((PCLK/1000000-1)<<8)|(0<<3)|(1<<2);	// 16us
	rWTDAT=0xffff;
	rWTCNT=0xffff;   

	// 1/16/(65+1),interrupt enable,reset disable,watchdog enable
	rWTCON=((PCLK/1000000-1)<<8)|(0<<3)|(1<<2)|(0<<0)|(1<<5);   
}



float Timer_StopEx(void)
{
	int count;
	rWTCON=((PCLK/1000000-1)<<8);
	rINTMSK|=BIT_WDT_AC97;
	rINTSUBMSK|=BIT_SUB_WDT;
	count=(0xffff-rWTCNT)+(intCount*0xffff);
	return ((float)count*(16e-6));
}


void __irq IsrWatchdog(void)
{
	 rINTSUBMSK|=BIT_SUB_WDT;
	 rSRCPND = BIT_WDT_AC97;	//Clear pending bit
	 rINTPND = BIT_WDT_AC97;
	 rINTPND;	//Prevent an double interrupt pending
	 rSUBSRCPND=BIT_SUB_WDT;
	 intCount++;   	
	 rINTSUBMSK&=~BIT_SUB_WDT;
}



