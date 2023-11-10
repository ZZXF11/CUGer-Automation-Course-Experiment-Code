//====================================================================
// File Name : IIC.c
// Function  : TQ2440 IIC-bus Master Tx/Rx mode Test Program
//             (Interrupt / Non Interrupt (Polling))
// Version   : 1.0
//====================================================================

#include <string.h>
#include "2440addr.h"
#include "2440lib.h"
#include "def.h"
#include "IIC.h"

static U8 _iicData[IICBUFSIZE];
static volatile int _iicDataCount;
static volatile int _iicStatus;
static volatile int _iicMode;
static int _iicPt;

//===================================================================
//       TQ2440 IIC configuration
//  GPE15=IICSDA, GPE14=IICSCL
//  "Interrupt mode" for IIC block
//=================================================================== 

//******************[ Test_Iic ]**************************************
void Test_Iic(void)
{
	unsigned int i,j,save_E,save_PE;
	static U8 data[256];

	Uart_Printf("\nIIC Test(Interrupt) using AT24C02\n");

	save_E   = rGPECON;
	save_PE  = rGPEUP;
	rGPEUP  |= 0xc000;                  //Pull-up disable
	rGPECON |= 0xa00000;                //GPE15:IICSDA , GPE14:IICSCL 

	pISR_IIC = (unsigned)IicInt;
	rINTMSK &= ~(BIT_IIC);

	//Enable ACK, Prescaler IICCLK=PCLK/16, Enable interrupt, Transmit clock value Tx clock=IICCLK/16
	// If PCLK 50.7MHz, IICCLK = 3.17MHz, Tx Clock = 0.198MHz
	rIICCON = (1<<7) | (0<<6) | (1<<5) | (0xf);

	rIICADD  = 0x10;                    //2440 slave address = [7:1]
	rIICSTAT = 0x10;                    //IIC bus data output enable(Rx/Tx)
	rIICLC = (1<<2)|(1);  				// Filter enable, 15 clocks SDA output delay       added by junon
    
	Uart_Printf("Write test data into AT24C02\n");

	for(i=0;i<256;i++)
		Wr24C080(0xa0,(U8)i,i);
           
	for(i=0;i<256;i++)
		data[i] = 0;

	Uart_Printf("Read test data from AT24C02\n");
    
	for(i=0;i<256;i++)
		Rd24C080(0xa0,(U8)i,&(data[i])); 

        //Line changed 0 ~ f
	for(i=0;i<16;i++)
	{
		for(j=0;j<16;j++)
			Uart_Printf("%2x ",data[i*16+j]);
		Uart_Printf("\n");
	}
	rINTMSK |= BIT_IIC;    
	rGPEUP  = save_PE;
	rGPECON = save_E;
}


//*************************[ Wr24C080 ]****************************
void Wr24C080(U32 slvAddr,U32 addr,U8 data)
{
	_iicMode      = WRDATA;
	_iicPt        = 0;
	_iicData[0]   = (U8)addr;
	_iicData[1]   = data;
	_iicDataCount = 2;
    
	rIICDS   = slvAddr;                 //0xa0
	rIICSTAT = 0xf0;                    //MasTx,Start
	//Clearing the pending bit isn't needed because the pending bit has been cleared.
    
	while(_iicDataCount!=-1);

	_iicMode = POLLACK;

	while(1)
	{
		rIICDS     = slvAddr;
		_iicStatus = 0x100;
		rIICSTAT   = 0xf0;              //MasTx,Start
		rIICCON    = 0xaf;              //Resumes IIC operation. 
           
		while(_iicStatus==0x100);
           
		if(!(_iicStatus&0x1))
			break;                      //When ACK is received
	}
	rIICSTAT = 0xd0;                    //Stop MasTx condition 
	rIICCON  = 0xaf;                    //Resumes IIC operation. 
	Delay(1);                           //Wait until stop condtion is in effect.
	//Write is completed.
}
        
//**********************[ Rd24C080 ] ***********************************
void Rd24C080(U32 slvAddr,U32 addr,U8 *data)
{
	_iicMode      = SETRDADDR;
	_iicPt        = 0;
	_iicData[0]   = (U8)addr;
	_iicDataCount = 1;

	rIICDS   = slvAddr;
	rIICSTAT = 0xf0;                    //MasTx,Start  
	//Clearing the pending bit isn't needed because the pending bit has been cleared.
	while(_iicDataCount!=-1);

	_iicMode      = RDDATA;
	_iicPt        = 0;
	_iicDataCount = 1;
    
	rIICDS        = slvAddr;
	rIICSTAT      = 0xb0;               //MasRx,Start
	rIICCON       = 0xaf;               //Resumes IIC operation.   
	while(_iicDataCount!=-1);

	*data = _iicData[1];
}


//-------------------------------------------------------------------------
void __irq IicInt(void)
{
	U32 iicSt,i;
    
	rSRCPND = BIT_IIC;          //Clear pending bit
	rINTPND = BIT_IIC;
	iicSt   = rIICSTAT; 
    
	if(iicSt & 0x8){}           //When bus arbitration is failed.
	if(iicSt & 0x4){}           //When a slave address is matched with IICADD
	if(iicSt & 0x2){}           //When a slave address is 0000000b
	if(iicSt & 0x1){}           //When ACK isn't received

	switch(_iicMode)
	{
		case POLLACK:
			_iicStatus = iicSt;
			break;

		case RDDATA:
			if((_iicDataCount--)==0)
			{
				_iicData[_iicPt++] = rIICDS;
            
				rIICSTAT = 0x90;                 //Stop MasRx condition 
				rIICCON  = 0xaf;                 //Resumes IIC operation.
				Delay(1);                        //Wait until stop condtion is in effect.
                                                //Too long time... 
                                                //The pending bit will not be set after issuing stop condition.
				break;    
			}      
			_iicData[_iicPt++] = rIICDS;         //The last data has to be read with no ack.

			if((_iicDataCount)==0)
				rIICCON = 0x2f;                  //Resumes IIC operation with NOACK.  
			else 
				rIICCON = 0xaf;                  //Resumes IIC operation with ACK
			break;

		case WRDATA:
			if((_iicDataCount--)==0)
			{
				rIICSTAT = 0xd0;                //Stop MasTx condition 
				rIICCON  = 0xaf;                //Resumes IIC operation.
				Delay(1);                       //Wait until stop condtion is in effect.
				//The pending bit will not be set after issuing stop condition.
				break;    
			}
			rIICDS = _iicData[_iicPt++];        //_iicData[0] has dummy.
			for(i=0;i<10;i++);                  //for setup time until rising edge of IICSCL
              
			rIICCON = 0xaf;                     //resumes IIC operation.
			break;

		case SETRDADDR:
 			if((_iicDataCount--)==0)
			break;                          //IIC operation is stopped because of IICCON[4]    
			rIICDS = _iicData[_iicPt++];
			for(i=0;i<10;i++);                  //For setup time until rising edge of IICSCL
			rIICCON = 0xaf;                     //Resumes IIC operation.
			break;

		default:
			break;      
	}
}


//===================================================================
//       TQ2440 IIC configuration
//  GPE15=IICSDA, GPE14=IICSCL
//  "Non-Interrupt" mode for IIC block
//=================================================================== 

//*********************[ Test_Iic2 ]*********************************
void Test_Iic2(void)
{
	unsigned int i,j,save_E,save_PE;
	static U8 data[256];
    
	Uart_Printf("[ IIC Test(Polling) using KS24C080 ]\n");

	save_E   = rGPECON;
	save_PE  = rGPEUP;

	rGPEUP  |= 0xc000;                  //Pull-up disable
	rGPECON |= 0xa00000;                //GPE15:IICSDA , GPE14:IICSCL    

	//Enable ACK, Prescaler IICCLK=PCLK/16, Enable interrupt, Transmit clock value Tx clock=IICCLK/16
	rIICCON  = (1<<7) | (0<<6) | (1<<5) | (0xf);

	rIICADD  = 0x10;                    //2440 slave address = [7:1]
	rIICSTAT = 0x10;                    //IIC bus data output enable(Rx/Tx)
	//rIICLC = (1<<2)|(3);  // Filter enable, 15 clocks SDA output delay     added by junon
    
	Uart_Printf("Write test data into KS24C080\n");

	for(i=0;i<256;i++)
		_Wr24C080(0xa0,(U8)i,255-i);
	for(i=0;i<256;i++)
		data[i] = 0;

	Uart_Printf("Read test data from KS24C080\n");
	for(i=0;i<256;i++)
		_Rd24C080(0xa0,(U8)i,&(data[i])); 

	for(i=0;i<16;i++)
	{
		for(j=0;j<16;j++)
			Uart_Printf("%2x ",data[i*16+j]);
		Uart_Printf("\n");
	}
    
	rGPEUP  = save_PE;
	rGPECON = save_E;
}

//**************[ _Wr24C080 ]*****************************************
void _Wr24C080(U32 slvAddr,U32 addr,U8 data)
{
	_iicMode      = WRDATA;
	_iicPt        = 0;
	_iicData[0]   = (U8)addr;
	_iicData[1]   = data;
	_iicDataCount = 2;
    
	rIICDS = slvAddr;            //0xa0
	//Master Tx mode, Start(Write), IIC-bus data output enable
	//Bus arbitration sucessful, Address as slave status flag Cleared,
	//Address zero status flag cleared, Last received bit is 0
	rIICSTAT      = 0xf0;      
	//Clearing the pending bit isn't needed because the pending bit has been cleared.
	while(_iicDataCount!=-1)
		Run_IicPoll();

	_iicMode = POLLACK;

	while(1)
	{
		rIICDS     = slvAddr;
		_iicStatus = 0x100;             //To check if _iicStatus is changed 
		rIICSTAT   = 0xf0;              //Master Tx, Start, Output Enable, Sucessful, Cleared, Cleared, 0
		rIICCON    = 0xaf;              //Resumes IIC operation. 
		while(_iicStatus==0x100)  
			Run_IicPoll();
              
		if(!(_iicStatus & 0x1))
			break;                      //When ACK is received
	}
	rIICSTAT = 0xd0;                    //Master Tx condition, Stop(Write), Output Enable
	rIICCON  = 0xaf;                    //Resumes IIC operation. 
	Delay(1);                           //Wait until stop condtion is in effect.
	//Write is completed.
}
        
//************************[ _Rd24C080 ]********************************
void _Rd24C080(U32 slvAddr,U32 addr,U8 *data)
{
	_iicMode      = SETRDADDR;
	_iicPt        = 0;
	_iicData[0]   = (U8)addr;
	_iicDataCount = 1;

	rIICDS   = slvAddr;
	rIICSTAT = 0xf0;                    //MasTx,Start  
	//Clearing the pending bit isn't needed because the pending bit has been cleared.
	while(_iicDataCount!=-1)
		Run_IicPoll();

	_iicMode      = RDDATA;
	_iicPt        = 0;
	_iicDataCount = 1;
    
	rIICDS   = slvAddr;
	rIICSTAT = 0xb0;                    //Master Rx,Start
	rIICCON  = 0xaf;                    //Resumes IIC operation.   
	while(_iicDataCount!=-1)
		Run_IicPoll();

	*data = _iicData[1];
}

//**********************[ Run_IicPoll ]*********************************
void Run_IicPoll(void)
{
	if(rIICCON & 0x10)                  //Tx/Rx Interrupt Enable
		IicPoll();
}       
    
//**********************[IicPoll ]**************************************
void IicPoll(void)
{
	U32 iicSt,i;
    
	iicSt = rIICSTAT; 
	if(iicSt & 0x8){}                   //When bus arbitration is failed.
	if(iicSt & 0x4){}                   //When a slave address is matched with IICADD
	if(iicSt & 0x2){}                   //When a slave address is 0000000b
	if(iicSt & 0x1){}                   //When ACK isn't received

	switch(_iicMode)
	{
		case POLLACK:
			_iicStatus = iicSt;
			break;

		case RDDATA:
			if((_iicDataCount--)==0)
			{
				_iicData[_iicPt++] = rIICDS;
            
				rIICSTAT = 0x90;                //Stop MasRx condition 
				rIICCON  = 0xaf;                //Resumes IIC operation.
				Delay(1);                       //Wait until stop condtion is in effect.
                                                //Too long time... 
                                                //The pending bit will not be set after issuing stop condition.
				break;    
			}      
			_iicData[_iicPt++] = rIICDS;
							//The last data has to be read with no ack.
			if((_iicDataCount)==0)
				rIICCON = 0x2f;                 //Resumes IIC operation with NOACK.  
		else 
			rIICCON = 0xaf;                 //Resumes IIC operation with ACK
			break;

		case WRDATA:
			if((_iicDataCount--)==0)
			{
				rIICSTAT = 0xd0;                //stop MasTx condition 
				rIICCON  = 0xaf;                //resumes IIC operation.
				Delay(1);                       //wait until stop condtion is in effect.
				//The pending bit will not be set after issuing stop condition.
				break;    
			}
			rIICDS = _iicData[_iicPt++];        //_iicData[0] has dummy.
			for(i=0;i<10;i++);                  //for setup time until rising edge of IICSCL
			rIICCON = 0xaf;                     //resumes IIC operation.
			break;

		case SETRDADDR:
			if((_iicDataCount--)==0)
			{
				break;                  //IIC operation is stopped because of IICCON[4]    
			}
			rIICDS = _iicData[_iicPt++];
			for(i=0;i<10;i++);          //for setup time until rising edge of IICSCL
			rIICCON = 0xaf;             //resumes IIC operation.
			break;

		default:
			break;      
	}
}
