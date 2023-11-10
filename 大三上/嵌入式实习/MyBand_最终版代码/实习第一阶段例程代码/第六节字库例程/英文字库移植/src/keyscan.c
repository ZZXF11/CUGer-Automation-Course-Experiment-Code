/**************************************************************
4 Key Scan
**************************************************************/

#include "def.h"
#include "option.h"
#include "2440addr.h"
#include "2440lib.h"
#include "2440slib.h" 

#define LED1		(1<<5)		// rGPB[5] =1 ;
#define LED2		(1<<6)		// rGPB[5] =1 ;
#define LED3		(1<<7)		// rGPB[5] =1 ;
#define LED4		(1<<8)		// rGPB[5] =1 ;

/******************************************************************************
	4 个用户按键
四个输入引脚：
				EINT0 -----( GPF0  )----INPUT---K4
				EINT2 -----( GPF2  )----INPUT---K3
				EINT4 -----( GPF4  )----INPUT---K2
				EINT1 -----( GPF1  )----INPUT---K1
				 
				
******************************************************************************/
U8 Key_Scan( void )
{
	Delay( 80 ) ;
	if(      (rGPFDAT&(1<< 0)) == 0 )
	{
		rGPBDAT = rGPBDAT & ~(LED4);			//亮LED4

		return 4 ;
	}
	else if( (rGPFDAT&(1<< 2)) == 0 )
	{
		rGPBDAT = rGPBDAT & ~(LED3);			//亮LED3

		return 3;
	}
	else if( (rGPFDAT&(1<<4)) == 0 )
	{
		rGPBDAT = rGPBDAT & ~(LED2);			//亮LED2

		return 2 ;
	}
	else if( (rGPFDAT&(1<< 1)) == 0 )
	{
		rGPBDAT = rGPBDAT & ~(LED1);			//亮LED1

		return 1 ;
	}
	else
	{
		rGPBDAT = rGPBDAT & ~0x1e0|0x1e0;   //LED[8:5] => 1;

		return 0xff;
	}

}

static void __irq Key_ISR(void)
{
	U8 key;
	U32 r;

	EnterCritical(&r);
	if(rINTPND==BIT_EINT1)
	{
		//Uart_Printf("eint1\n");
		ClearPending(BIT_EINT1);
	}
	if(rINTPND==BIT_EINT4_7)
	{
		ClearPending(BIT_EINT4_7);
		if(rEINTPEND&(1<<4))
		{
			//Uart_Printf("eint4\n");
			rEINTPEND |= 1<< 4;
		}
	}
	if(rINTPND==BIT_EINT0)
	{
		//Uart_Printf("eint0\n");
		ClearPending(BIT_EINT0);
	}
	if(rINTPND==BIT_EINT2)
	{
		//Uart_Printf("eint2\n");
		ClearPending(BIT_EINT2);
	}

	key=Key_Scan();
	if( key == 0xff )
		Uart_Printf( "Interrupt occur... Key is released!\n") ;
	else
		Uart_Printf( "Interrupt occur... K%d is pressed!\n", key) ;

	ExitCritical(&r);
}

void KeyScan_Test(void)
{
	Uart_Printf("\nKey Scan Test, press ESC key to exit !\n");	

	rGPBUP = rGPBUP & ~0x03f0|0x03f0;			//  LED [8:5] => PU En
	rGPBCON = rGPBCON & ~0x3d57fc|0x3d57fc;		//LED[8:5] => OUTPUT;
	rGPFCON = rGPFCON & (~((3<<4)|(3<<0)|(3<<8)|(3<<2))) | ((2<<4)|(2<<0)|(2<<8)|(2<<2)) ;		//GPF4,2,1,0 set EINT
	
	rEXTINT0 &= ~(7|(7<<4)|(7<<8)|(7<<16));	
	rEXTINT0 |= (0|(0<<4)|(0<<8)|(0<<16));		//set eint0,1,2,4 falling edge int


	rEINTPEND |= (1<<4);							//clear eint 4
	rEINTMASK &= ~(1<<4);						//enable eint 4
	ClearPending(BIT_EINT0|BIT_EINT1|BIT_EINT2|BIT_EINT4_7);
	pISR_EINT0 = pISR_EINT1 = pISR_EINT2 = pISR_EINT4_7 = (U32)Key_ISR;
	EnableIrq(BIT_EINT0|BIT_EINT1|BIT_EINT2|BIT_EINT4_7);	

	 while( Uart_GetKey() != ESC_KEY ) ;
	 DisableIrq(BIT_EINT0|BIT_EINT1|BIT_EINT2|BIT_EINT4_7);	
}
