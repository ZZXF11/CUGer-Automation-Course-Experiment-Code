/******************************************************************************

 Filename:	camproset.c

 Descriptions		
 - Camera Processor Initialization code using SCCB.
 - SCCB(Serial Camera Contol Bus) H/W dependent code.
 - Camera Processor Initialization code using IIC.

 ******************************************************************************/
#include "def.h"
#include "2440addr.h"
#include "2440lib.h"

#include "camproset.h"
#include "camdef.h"
#include "camdata.h"


#define CAMWRDATA      (1)
#define CAMRDDATA      (3)
#define CAMSETRDADDR   (4)

#define CAMIICBUFSIZE 0x20


#if USED_CAM_TYPE==CAM_OV9650
#define CAM_ID		(0x42)
#define CAM_NAME  "OV9650"
#elif USED_CAM_TYPE==CAM_S5X433
#define CAM_ID		(0x42)
#define CAM_NAME  "S5X433"
#elif USED_CAM_TYPE==CAM_S5X532
#define CAM_ID		(0x5a)
#define CAM_NAME  "S5X532"
#elif USED_CAM_TYPE==CAM_S5X3A1
#define CAM_ID		(0x5a)
#define CAM_NAME  "S5X3A1"
#elif USED_CAM_TYPE==CAM_AU70H
#define CAM_ID		(0x22)
#define CAM_NAME  "AU70H"
#endif


static U8 _CAMiicData[CAMIICBUFSIZE];
static volatile int _CAMiicDataCount;
static volatile int _CAMiicStatus;
static volatile int _CAMiicMode;
static int _CAMiicPt;

volatile U32 save_GPECON;


void * func_cammodule_test[][2]=
{								   
	//IIC 	
	(void *)Camera_WriteByte, 	"Write 1 byte data into Camera module register",
	(void *)Camera_ReadByte,  	"Read 1 byte data from Camera module register",
	(void *)Camera_WriteBlock,  	"Write a block of byte data into Camera module register",
	(void *)Camera_ReadBlock,  	"Read a block of byte data from Camera module register",
	0,0
};


void Camera_Iic_Test(void)
{
	int i;

	CameraModuleSetting();

	Uart_Printf("\n***** IIC Master Tx/Rx Test Program with %s Camera Module *****\n", CAM_NAME);

	while(1) 	{
		i=0;
		Uart_Printf("\n\n");

		while(1) {   //display menu
			Uart_Printf("%2d:%s\n", i, func_cammodule_test[i][1]);
			i++;
			if((int)(func_cammodule_test[i][0])==0) {
				Uart_Printf("\n");
				break;
			}
			if((i%4)==0)
			Uart_Printf("\n");
		}

		Uart_Printf("\nPress Enter key to exit : ");
		i = Uart_GetIntNum();

		if(i==-1) break;		// return.
		if(i>=0 && (i<((sizeof(func_cammodule_test)-1)/8)) )	// select and execute...
			( (void (*)(void)) (func_cammodule_test[i][0]) )();
	}

	Uart_Printf("\n");
   	rINTMSK |= BIT_IIC;
}


void IicPortSet(void)
{
	save_GPECON = rGPECON;
	rGPECON = rGPECON & ~(0xf<<28) | (0xa<<28);	//GPE15:IICSDA , GPE14:IICSCL 	 
}

void IicPortReturn(void)
{
	rGPECON = save_GPECON;
}

void Wr_CamIIC(U32 slvAddr, U32 addr, U8 data)
{
	_CAMiicMode      = CAMWRDATA;
	_CAMiicPt        = 0;
	_CAMiicData[0]   = (U8)addr;
	_CAMiicData[1]   = data;
	_CAMiicDataCount = 2;
    
	rIICDS        = slvAddr;            //0x5a: S5X532 Slave ID 
	rIICSTAT      = 0xf0; //Start Master TX Condition    
	rIICCON &= ~(1<<4);   //Clearing the pending bit isn't needed because the pending bit has been cleared.

	while(_CAMiicDataCount!=-1);
}

void Rd_CamIIC(U32 slvAddr,U32 addr,U8 *data)
{

	/*IIC Slave Addr Write + IIC Reg Addr Write */	
	_CAMiicMode      = CAMSETRDADDR;
	_CAMiicPt        = 0;
	_CAMiicData[0]   = (U8)addr;
	_CAMiicDataCount = 1;

	rIICDS   = slvAddr;
	rIICSTAT = 0xf0;   //Master Tx, Start
	rIICCON &= ~(1<<4);                    //Resumes IIC operation.  
	//Clearing the pending bit isn't needed because the pending bit has been cleared.
	while(_CAMiicDataCount!=-1);
    
	_CAMiicMode      = CAMRDDATA;
	_CAMiicPt        = 0;
	_CAMiicDataCount = 1;
    
	rIICDS   = slvAddr;
	rIICSTAT = 0xb0;                    //Master Rx,Start
	rIICCON &= ~(1<<4);                   //Resumes IIC operation.   
    
	while(_CAMiicDataCount!=-1);

	*data = _CAMiicData[1];
}


void __irq Cam_IICInt(void)
{
	U32 iicSt,i;

	ClearPending(BIT_IIC);
	iicSt   = rIICSTAT; 
	rINTMSK |= BIT_IIC;

	if(iicSt & 0x8){}           //When bus arbitration is failed.
	if(iicSt & 0x4){}           //When a slave address is matched with IICADD
	if(iicSt & 0x2){}           //When a slave address is 0000000b
	if(iicSt & 0x1){}           //When ACK isn't received

	switch(_CAMiicMode) {
		case CAMRDDATA:
			if((_CAMiicDataCount--)==0) {
				_CAMiicData[_CAMiicPt++] = rIICDS;
            
				rIICSTAT = 0x90;      //Stop MasRx condition 
				rIICCON  &= ~(1<<4);      //Resumes IIC operation.
				Delay(1);                 //Wait until stop condtion is in effect., Too long time...  # need the time 2440:Delay(1), 24A0: Delay(2)
								//The pending bit will not be set after issuing stop condition.
				break;    
			}      
			_CAMiicData[_CAMiicPt++] = rIICDS;     //The last data has to be read with no ack.

			if((_CAMiicDataCount)==0)
				rIICCON &= ~((1<<7)|(1<<4));      //Resumes IIC operation with NOACK in case of S5X532 Cameara  
//				rIICCON = 0x6f;			//Resumes IIC operation with NOACK in case of S5X532 Cameara	
			else 
				rIICCON &= ~(1<<4);      //Resumes IIC operation with ACK
			break;
		case CAMWRDATA:
			if((_CAMiicDataCount--)==0) {
				rIICSTAT = 0xd0;                //stop MasTx condition 
				rIICCON  &= ~(1<<4);                //resumes IIC operation.
				Delay(1);                       //wait until stop condtion is in effect. # need the time 2440:Delay(1), 24A0: Delay(2)
					//The pending bit will not be set after issuing stop condition.
				break;    
			}
			rIICDS = _CAMiicData[_CAMiicPt++];        //_iicData[0] has dummy.
			for(i=0;i<10;i++);                  //for setup time until rising edge of IICSCL
				rIICCON &= ~(1<<4);                     //resumes IIC operation.
			break;
		case CAMSETRDADDR: //Uart_Printf("[S%d]",_iicDataCount);
			if((_CAMiicDataCount--)==0) {
				rIICSTAT = 0xd0;                //stop MasTx condition 
				rIICCON  &= ~(1<<4);                //resumes IIC operation.
				Delay(1);      //wait until stop condtion is in effect.

				break;                  //IIC operation is stopped because of IICCON[4]    
			}
			rIICDS = _CAMiicData[_CAMiicPt++];
			for(i=0;i<10;i++);          //for setup time until rising edge of IICSCL
				rIICCON &= ~(1<<4);             //resumes IIC operation.
			break;
		default:
			break;      
	}

	rINTMSK &= ~BIT_IIC;
}


void Camera_WriteByte(void)
{
	unsigned int RegAddr, RegData;
      	
#if (USED_CAM_TYPE==CAM_S5X532)||(USED_CAM_TYPE==CAM_S5X3A1)
	Uart_Printf("Input Write Page No of %s\n=>", CAM_NAME);
	pageNo = (U8)Uart_GetIntNum();
#endif

	Uart_Printf("Input Write Register Address of %s\n=>", CAM_NAME);
	RegAddr = (U8)Uart_GetIntNum();
    
	Uart_Printf("Input Write Transfer Data into %s\n=>", CAM_NAME);
	RegData = (U8)Uart_GetIntNum();

#if (USED_CAM_TYPE==CAM_S5X532)||(USED_CAM_TYPE==CAM_S5X3A1)
	Wr_CamIIC(CAM_ID, (U8)0xec, pageNo);  // set Page no
#endif
	Wr_CamIIC(CAM_ID, (U8)RegAddr, RegData); // set register after setting page number
}


void Camera_ReadByte(void)
{
	unsigned int RegAddr;
	static U8 rdata[8];
      	
#if (USED_CAM_TYPE==CAM_S5X532)||(USED_CAM_TYPE==CAM_S5X3A1)
	Uart_Printf("Input Write Page No of %s\n=>", CAM_NAME);
	pageNo = (U8)Uart_GetIntNum();
	Wr_CamIIC(CAM_ID, (U8)0xec, pageNo);  // set Page no
#endif

	Uart_Printf("Input Read Register Address of %s\n=>", CAM_NAME);
	RegAddr = (U8)Uart_GetIntNum();
	Rd_CamIIC(CAM_ID, RegAddr, &rdata[0]); 
	Uart_Printf("Register Addr: 0x%2x, data: 0x%2x\n", RegAddr,rdata[0]);
}


void Camera_WriteBlock(void)
{
	unsigned int i;

#if USED_CAM_TYPE==CAM_OV9650
	for(i=0; i<(sizeof(OV9650_YCbCr8bit)/2); i++)
		Wr_CamIIC(CAM_ID, OV9650_YCbCr8bit[i][0], OV9650_YCbCr8bit[i][1]);
#elif USED_CAM_TYPE==CAM_S5X532
	for(i=0; i<(sizeof(S5X532_YCbCr8bit)/2); i++)
		Wr_CamIIC(CAM_ID, S5X532_YCbCr8bit[i][0], S5X532_YCbCr8bit[i][1]);
#elif USED_CAM_TYPE==CAM_S5X3A1
		for(i=0; i<(sizeof(S5X3A1_YCbCr8bit)/2); i++)
			Wr_CamIIC(CAM_ID, S5X3A1_YCbCr8bit[i][0], S5X3A1_YCbCr8bit[i][1]);
#elif USED_CAM_TYPE==CAM_AU70H
	for(i=0; i<(sizeof(Au70h)/2); i++)
		Wr_CamIIC(CAM_ID, Au70h[i][0], Au70h[i][1]);
#endif
	
   Uart_Printf("\nBlock TX Ended...\n");	
}


void Camera_ReadBlock(void)
{
	unsigned int i;
	static U8 rdata[256]; 

#if USED_CAM_TYPE==CAM_OV9650
	for(i=0; i<(sizeof(OV9650_YCbCr8bit)/2);i++)
		Rd_CamIIC(CAM_ID, OV9650_YCbCr8bit[i][0], &rdata[i]); 
	for(i=0; i<(sizeof(OV9650_YCbCr8bit)/2);i++)
		Uart_Printf("Addr: 0x%2x, W: 0x%2x, R: 0x%2x\n", OV9650_YCbCr8bit[i][0], OV9650_YCbCr8bit[i][1], rdata[i]);
#elif USED_CAM_TYPE==CAM_S5X532
	for(i=0; i<(sizeof(S5X532_YCbCr8bit)/2);i++)
	{     
		if(S5X532_YCbCr8bit[i][0] == 0xec)
			Wr_CamIIC(CAM_ID, S5X532_YCbCr8bit[i][0], S5X532_YCbCr8bit[i][1]);
		else
			Rd_CamIIC(CAM_ID, S5X532_YCbCr8bit[i][0], &rdata[i]); 
	}
  	for(i=0; i<(sizeof(S5X532_YCbCr8bit)/2);i++)
	{
	  	if(S5X532_YCbCr8bit[i][0] == 0xec)
			Uart_Printf("Page: 0x%2x\n",  S5X532_YCbCr8bit[i][1]);
		else
	 		Uart_Printf("Addr: 0x%2x, W: 0x%2x, R: 0x%2x\n", S5X532_YCbCr8bit[i][0], S5X532_YCbCr8bit[i][1], rdata[i]);
  	}      
#elif USED_CAM_TYPE==CAM_S5X3A1
	for(i=0; i<(sizeof(S5X3A1_YCbCr8bit)/2);i++)
	{ 		
	if(S5X3A1_YCbCr8bit[i][0] == 0xec)
		Wr_CamIIC(CAM_ID, S5X3A1_YCbCr8bit[i][0], S5X3A1_YCbCr8bit[i][1]);
	else
		Rd_CamIIC(CAM_ID, S5X3A1_YCbCr8bit[i][0], &rdata[i]); 
	}
	for(i=0; i<(sizeof(S5X3A1_YCbCr8bit)/2);i++)
{
		if(S5X3A1_YCbCr8bit[i][0] == 0xec)
			 Uart_Printf("Page: 0x%2x\n",  S5X3A1_YCbCr8bit[i][1]);
	else
			Uart_Printf("Addr: 0x%2x, W: 0x%2x, R: 0x%2x\n", S5X3A1_YCbCr8bit[i][0], S5X3A1_YCbCr8bit[i][1], rdata[i]);
	} 		 
#elif USED_CAM_TYPE==CAM_AU70H
	for(i=0; i<(sizeof(Au70h)/2);i++)
		Rd_CamIIC(CAM_ID, Au70h[i][0], &rdata[i]); 
	for(i=0; i<(sizeof(Au70h)/2);i++)
		Uart_Printf("Addr: 0x%2x, W: 0x%2x, R: 0x%2x\n", Au70h[i][0], Au70h[i][1], rdata[i]);
#endif

}


int CameraModuleSetting(void)
{
	int donestatus;
      	
	IicPortSet();

	// for camera init, added by junon
	pISR_IIC = (unsigned)Cam_IICInt; 
	rINTMSK &= ~(BIT_IIC);

	//Enable ACK, Prescaler IICCLK=PCLK/512, Enable interrupt, Transmit clock value Tx clock=IICCLK/16
	rIICCON  = (1<<7) | (1<<6) | (1<<5) | (0x3);

	rIICADD  = 0x10;                    //24A0 slave address = [7:1]
	rIICSTAT = 0x10;                    //IIC bus data output enable(Rx/Tx)
    rIICLC = (1<<2)|(3);   			// SDAOUT has 5clock cycle delay

	donestatus=1;

	Camera_WriteBlock();
//	Camera_ReadBlock();
	
	return donestatus;
}


