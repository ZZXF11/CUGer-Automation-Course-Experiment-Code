//====================================================================
// File Name : RTC.c
// Function  : TQ2440 RTC Test 
// Version   : 1.0
//====================================================================

#include "def.h"
#include "option.h"
#include "2440addr.h"
#include "2440lib.h"
#include "2440slib.h" 

//==================================================================================		
void RTC_Time_Set( void )
{
	rRTCCON = 1 ;		//RTC read and write enable

	rBCDYEAR = 0x08 ;		//年
	rBCDMON  = 0x11 ;		//月
	rBCDDATE = 0x07 ;		//日	
	rBCDDAY  = 0x05 ;		//星期
	rBCDHOUR = 0x12 ;		//小时
	rBCDMIN  = 0x00 ;			//分
	rBCDSEC  = 0x00 ;		//秒
	
	rRTCCON &= ~1 ;		//RTC read and write disable
}

//==================================================================================
void RTC_Display(void) 
{
	U16 year ;
	U8 month, day ;		// week
	U8 hour, minute, second ;

	RTC_Time_Set() ;
	   
   	Uart_Printf( "\nRTC TIME Display, press ESC key to exit !\n" ) ;

	while( Uart_GetKey() != ESC_KEY )
	{
		rRTCCON = 1 ;		//RTC read and write enable

		year = 0x2000+rBCDYEAR  ;		//年
		month = rBCDMON  ;		//月
		day = rBCDDATE  ;		//日	
//		week = rBCDDAY  ;		//星期
		hour = rBCDHOUR  ;		//小时
		minute = rBCDMIN  ;		//分
		second = rBCDSEC  ;		//秒
		
		rRTCCON &= ~1 ;		//RTC read and write disable

		Uart_Printf( "RTC time : %04x-%02x-%02x %02x:%02x:%02x\n", year, month, day, hour, minute, second );
		Delay( 900 ) ;
	}
}
