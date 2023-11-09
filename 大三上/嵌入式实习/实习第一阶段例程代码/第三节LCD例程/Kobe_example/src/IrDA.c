#include "def.h"
#include "2440addr.h"
#include "2440lib.h"

#define IrDA_BUFLEN 0x100

void IrDA_Port_Set(void);
void IrDA_Port_Return(void);

void __irq IrDA_TxInt(void);
void __irq IrDA_RxOrErr(void);

volatile U8 *IrDAdataPt;
volatile U8 *IrDAdataFl;
volatile U32 IrDA_cnt,IrDA_end,IrDA_err,IrDA_BAUD;
volatile U32 sirda_rGPBCON,sirda_rGPBDAT,sirda_rGPBUP;
volatile U32 sirda_rGPHCON,sirda_rGPHDAT,sirda_rGPHUP;
volatile U32 sirda_ULCON2,sirda_UCON2,sirda_UFCON2,sirda_UMCON2,sirda_UBRDIV2;

void IrDA_Port_Set(void)
{
    //Push UART GPIO port configuration
    sirda_rGPBCON=rGPBCON; 
    sirda_rGPBDAT=rGPBDAT;
    sirda_rGPBUP=rGPBUP;
    sirda_rGPHCON=rGPHCON; 
    sirda_rGPHDAT=rGPHDAT;
    sirda_rGPHUP=rGPHUP;
    //Configure IrDA port
    rGPBDAT|=(1<<1);	
    rGPBCON&=0x3ffff3;
    rGPBCON|=(1<<2);	// Output(nIrDATXDEN)
    rGPBUP|=(1<<1);	//Uart port pull-up disable
    rGPHCON&=0x3c0fff;
    rGPHCON|=0x2a000;	// TXD2,RXD2
    rGPHUP|=0x1c0;	//Uart port pull-up disable
    //Push Uart control registers 
    sirda_ULCON2=rULCON2;		
    sirda_UCON2 =rUCON2;		
    sirda_UFCON2=rUFCON2;		
    sirda_UMCON2=rUMCON2;
    sirda_UBRDIV2=rUBRDIV2;
}       
        
void IrDA_Port_Return(void)
{       
    //Pop UART GPIO port configuration
    rGPBCON=sirda_rGPBCON;
    rGPBDAT=sirda_rGPBDAT;
    rGPBUP =sirda_rGPBUP;
    rGPHCON=sirda_rGPHCON;
    rGPHDAT=sirda_rGPHDAT;
    rGPHUP =sirda_rGPHUP;
    //Pop Uart control registers 
    rULCON2=sirda_ULCON2;		
    rUCON2 =sirda_UCON2;	
    rUFCON2=sirda_UFCON2;		
    rUMCON2=sirda_UMCON2;
    rUBRDIV2=sirda_UBRDIV2;
}

void __irq IrDA_TxInt(void)
{
    rINTSUBMSK|=(BIT_SUB_RXD2|BIT_SUB_TXD2|BIT_SUB_ERR2);
    if(IrDA_cnt < (IrDA_BUFLEN))
    {
	Uart_Printf("%d,",*IrDAdataPt);
	WrUTXH2(*IrDAdataPt++);
	IrDA_cnt++;
	ClearPending(BIT_UART2);
        rSUBSRCPND=(BIT_SUB_TXD2);
        rINTSUBMSK&=~(BIT_SUB_TXD2);
    }
    else
    {
	IrDA_end=1;
	while(rUFSTAT2 & 0x2f0);	//Until FIFO is empty
	while(!(rUTRSTAT2 & 0x4));	//Until Tx shifter is empty
        ClearPending(BIT_UART2);
	rINTMSK|=BIT_UART2;
    }
}

void __irq IrDA_RxOrErr(void)
{
    DisableSubIrq(BIT_SUB_RXD2|BIT_SUB_TXD2|BIT_SUB_ERR2);	// Just for the safety
    if(rSUBSRCPND&BIT_SUB_RXD2) {
    	if(rUTRSTAT2&1)		//has data, non-fifo mode
			WrUTXH1(rURXH2);
    }
    else {
   	    switch(rUERSTAT2) {	//to clear and check the status of register bits
		case '1':
		    Uart_Printf("Overrun error\n");
	    	break;
		case '2':
		    Uart_Printf("Parity error\n");
	    	break;
		case '4':
		    Uart_Printf("Frame error\n");
	    	break;
		case '8':
		    Uart_Printf("Breake detect\n");
	    	break;
		default :
		    break;
    	}
    }
    ClearSubPending(BIT_SUB_RXD2|BIT_SUB_TXD2|BIT_SUB_ERR2);
    EnableSubIrq(BIT_SUB_RXD2|BIT_SUB_ERR2);
    ClearPending(BIT_UART2);
}

extern U32 PCLK;

void Test_IrDA_Tx(void)
{
	char dat;

	Uart_Printf("\nIrDA test\n");	// Select IrDA baud rate
	
	IrDA_cnt = 0;
	IrDA_end = 0;
	IrDA_Port_Set();
	
	IrDA_BAUD = 19200;
	Uart_Printf("Select baudrate = %d\n", IrDA_BAUD);
	
	rUBRDIV2 = ((int)(PCLK/16./IrDA_BAUD)-1);
	//Uart_Printf("rUBRDIV2 = %d\n", rUBRDIV2);
	rGPBDAT &= 0x7fd;	// Enable nIrDATXDEN    
	rUFCON2  = (1<<6)|(0<<4)|(1<<2)|(1<<1)|0;
	//Tx and Rx FIFO Trigger Level = 4byte,Tx and Rx FIFO Reset,FIFO disable
	rUCON2 = (0<<10)|(1<<9)|(1<<8)|(0<<7)|(1<<6)|(0<<5)|(0<<4)|(0<<2)|(0);
	//Use PCLK,Tx&RxLevel interrupt,Rx timeout disable,Rx err interrupt enable,Non-loopback,Tx&Rx disable
	rULCON2 = (1<<6)|(0<<3)|(0<<2)|(3);	//IrDA,No parity,One stop bit,8bits
	
	rUCON2 = (0<<10)|(1<<9)|(1<<8)|(0<<7)|(1<<6)|(0<<5)|(0<<4)|(1<<2)|(1);
	//Use PCLK,Tx&RxLevel interrupt,Rx timeout disable,Rx err interrupt enable,Non-loopback,Tx&Rx disable
	Uart_Printf("Now start UART IrDA Tx&Rx test, check data[a~z]\n");

	pISR_UART2 = (U32)IrDA_RxOrErr;
	EnableSubIrq(BIT_SUB_RXD2|BIT_SUB_ERR2);	
	EnableIrq(BIT_UART2);

	dat = 'a';
    while(1) {
		Delay(5);
		WrUTXH0(dat);
		Delay(5);
		WrUTXH2(dat);
		while(!(rUTRSTAT2&0x2));   //Wait until THR is empty.    	
		dat++;
		if(dat>'z')
			break;
	}
	
	DisableSubIrq(BIT_SUB_RXD2|BIT_SUB_TXD2|BIT_SUB_ERR2);
	EnableIrq(BIT_UART2);
//	rUFCON2 = (3<<6)|(2<<4)|(1<<2)|(1<<1)|(0);
	rGPBDAT |= (1<<1);	// Disable nIrDATXDEN
//	IrDA_Port_Return();
	Uart_Printf("\nEnd Tx&Rx\n");
}

void Test_IrDA_Rx(void)
{
    unsigned int i;
    
    IrDA_cnt=0;
    IrDA_end=0;
    IrDA_err=0;
    IrDA_Port_Set();    
    
	pISR_UART2 = (U32)IrDA_RxOrErr;
	Uart_Printf("\nSelect the baud rate\n");	// Select IrDA baud rate
	Uart_Printf("1)9600    2)19200    3)38400    4)57600    5)115200\n");
	i = Uart_Getch();
    switch(i) {
	case '1':
            IrDA_BAUD=9600;
        break;
	
	case '2':
            IrDA_BAUD=19200;
        break;
	
	case '3':
            IrDA_BAUD=38400;
        break;
	
	case '4':
            IrDA_BAUD=57600;
        break;
	
	case '5':
            IrDA_BAUD=115200;
        break;
	
	default:
	break;
    }
    rUBRDIV2=( (int)(PCLK/16./IrDA_BAUD) -1 );
    Uart_Printf("rUBRDIV2=%d\n", rUBRDIV2);
    Uart_Printf("[UART IrDA Rx Test]\n");
    Uart_Printf("This test should be configured two boards.\n");
    Uart_Printf("Press any key to start Rx and then Start Tx....\n");
    Uart_Getch();
    Uart_Printf("Now... Rx with IrDA\n");
    rUFCON2=(1<<6)|(0<<4)|(1<<2)|(1<<1)|(1);
    //Tx and Rx FIFO Trigger Level:4byte,Tx and Rx Reset,FIFO En
    rUCON2=(0<<10)|(1<<9)|(1<<8)|(0<<7)|(1<<6)|(0<<5)|(0<<4)|(0<<2)|(0); // From H/W
    rULCON2=(1<<6)|(0<<3)|(0<<2)|(3);	// IrDA,No parity,One stop bit, 8bit
    Delay(1); // From H/W
    rUCON2=(0<<10)|(1<<9)|(1<<8)|(0<<7)|(1<<6)|(0<<5)|(0<<4)|(0<<2)|(1);
    // PCLK,Tx&Rx:Level,Rx timeout:x,Rx error int:o,Loop-back:x,Send break:x,Tx:x,Rx:int
    rINTMSK=~(BIT_UART2);
    rINTSUBMSK=~(BIT_SUB_RXD2|BIT_SUB_ERR2);

    while(!IrDA_end);
    
    rINTSUBMSK|=(BIT_SUB_RXD2|BIT_SUB_TXD2|BIT_SUB_ERR2);
    rUFCON2=(3<<6)|(2<<4)|(1<<2)|(1<<1)|(0);
    Uart_Printf("\nEnd Rx, receive data count=%d\n",IrDA_cnt);
    for(i=0;i<IrDA_BUFLEN;i++)
    {
	if(i-(*IrDAdataFl++))
	{
	    Uart_Printf("i=%d,",i);
	    IrDA_err++;
	}
    }
    if(IrDA_err)
    	Uart_Printf("IrDA test fail!! Error count=%d\n",IrDA_err);
    else
    	Uart_Printf("IrDA test is good!!\n");
    IrDA_Port_Return();
}
