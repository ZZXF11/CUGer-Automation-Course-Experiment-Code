/************************************************************
File Name	: camif.c
Descriptions
 -TQ2440 camera test routines & basic libraries
*************************************************************/

#include "def.h"
#include "option.h"
#include "2440addr.h"
#include "2440lib.h"

#include "camif.h"
#include "camproset.h" // for camera setting
#include "LCD_TFT.h"


extern unsigned short LCD_BUFFER[SCR_YSIZE_TFT][SCR_XSIZE_TFT];

volatile U32 camTestMode;
volatile U32 camCodecCaptureCount;
volatile U32 camPviewCaptureCount;
volatile U32 camCodecStatus;
volatile U32 camPviewStatus;
volatile U32 amount;

U32 save_GPJCON, save_GPJDAT, save_GPJUP;

U8 flagCaptured_P = 0;
U8 flagCaptured_C = 0;

int Test_OV9650(void);

void Camera_Test(void)
{
	int i;
	
	Uart_Printf("\nCamera Preview Test\n");

	CamReset();

	// Initializing camif
	rCLKCON |= (1<<19); // enable camclk
	CamPortSet();	
	ChangeUPllValue(56, 2, 1);		// UPLL clock = 96MHz, PLL input 12MHz
	rCLKDIVN|=(1<<3); // UCLK 48MHz setting for UPLL 96MHz
	// 0:48MHz, 1:24MHz, 2:16MHz, 3:12MHz...
	// Camera clock = UPLL/[(CAMCLK_DIV+1)X2]

	SetCAMClockDivider(CAMCLK24000000); //Set Camera Clock 24MHz s5x532, OV9650

	i = Test_OV9650();
	if( i )
	{
		Uart_Printf("\nTest is failed!!!\n");
		return ;
	}

	Uart_Printf("Initializing end...\n");
	
	Test_CamPreview() ;
	
	Uart_Printf("\nCamera Preview Test End\n");

	rCLKCON &= ~(1<<19); // disable camclk
	Lcd_TFT_Init() ;		//
	
}


void CamPortSet(void)
{
	save_GPJCON = rGPJCON;
	save_GPJDAT = rGPJDAT;
	save_GPJUP = rGPJUP;

	rGPJCON = 0x2aaaaaa;
	rGPJDAT = 0;
	rGPJUP = 0;
	
	rGPGCON &= ~(3<<22);
	rGPGCON |= 1<<22;
	rGPGUP  |= 1<<11;
	rGPGDAT &= ~(1<<11);
}

void CamPortReturn(void)
{
	rGPJCON = save_GPJCON;
	rGPJDAT = save_GPJDAT;
	rGPJUP = save_GPJUP;
}

void CamPreviewIntUnmask(void)
{
    rINTSUBMSK &= ~(BIT_SUB_CAM_P);//INT CAMERA Port A ENABLE 
    rINTMSK &= ~(BIT_CAM);
}

void CamCodecIntUnmask(void)
{
    rINTSUBMSK &= ~(BIT_SUB_CAM_C);//INT CAMERA Port B ENABLE 
    rINTMSK &= ~(BIT_CAM);
}

void CamPreviewIntMask(void)
{
    rINTSUBMSK |= BIT_SUB_CAM_P;//INT CAMERA Port A ENABLE 
    rINTMSK |= (BIT_CAM);
}

void CamCodecIntMask(void)
{
    rINTSUBMSK |= BIT_SUB_CAM_C;//INT CAMERA Port B ENABLE 
    rINTMSK |= (BIT_CAM);
}


/******************************************************
 *                                                                      							*    
 *                       camera interface initialization                    		*
 *                                                                            					*     
 *******************************************************/

void CamReset(void)
{
	rCIGCTRL |= (1<<31); //camera I/F soft reset
	Delay(10);
	rCIGCTRL &= ~(1<<31);
}

void CamModuleReset(void)
{
	rCIGCTRL |= (1<<30);	  //external camera reset high
	Delay(30);
	rCIGCTRL &= ~(1<<30);	//external camera reset low
}

// 0:48MHz, 1:24MHz, 2:16MHz, 3:12MHz...
// Camera clock = UPLL/[(CAMCLK_DIV+1)X2]
void SetCAMClockDivider(int divn) 
{
	rCAMDIVN = (rCAMDIVN & ~(0xf))|(1<<4)|(divn); // CAMCLK is divided..
}

/* Description of Parameters
CoDstWidth: Destination Width of Codec Path
CoDstHeight: Destination Height of Codec Path
PrDstWidth: Destination Width of Preview Path
PrDstHeight: Destination Height of Preview Path
WinHorOffset: Size of Window Offset for Horizontal Direction
WinVerOffset: Size of Window Offset for Vertical Direction
CoFrameBuffer: Start Address for Codec DMA
PrFrameBuffer: Start Address for Previe DMA
*/
void CamInit(U32 CoDstWidth, U32 CoDstHeight, U32 PrDstWidth, U32 PrDstHeight, 
			U32 WinHorOffset, U32 WinVerOffset,  U32 CoFrameBuffer, U32 PrFrameBuffer)
{
	U32 WinOfsEn;
	U32 divisor, multiplier;
	U32 MainBurstSizeY, RemainedBurstSizeY, MainBurstSizeC, RemainedBurstSizeC, MainBurstSizeRGB, RemainedBurstSizeRGB;
	U32 H_Shift, V_Shift, PreHorRatio, PreVerRatio, MainHorRatio, MainVerRatio;
	U32 SrcWidth, SrcHeight;
	U32 ScaleUp_H_Co, ScaleUp_V_Co, ScaleUp_H_Pr, ScaleUp_V_Pr;

	//constant for calculating codec dma address
	if(CAM_CODEC_OUTPUT)
		divisor=2; //CCIR-422
	else
		divisor=4; //CCIR-420
		
	//constant for calculating preview dma address
	if(CAM_PVIEW_OUTPUT)
		multiplier=4;
	else
		multiplier=2;
	
	if(WinHorOffset==0 && WinVerOffset==0)
		WinOfsEn=0;
	else
		WinOfsEn=1;

	SrcWidth=CAM_SRC_HSIZE-WinHorOffset*2;
	SrcHeight=CAM_SRC_VSIZE-WinVerOffset*2;

	if(SrcWidth>=CoDstWidth) ScaleUp_H_Co=0; //down
	else ScaleUp_H_Co=1;		//up

	if(SrcHeight>=CoDstHeight) ScaleUp_V_Co=0;
	else ScaleUp_V_Co=1;		

	if(SrcWidth>=PrDstWidth) ScaleUp_H_Pr=0; //down
	else ScaleUp_H_Pr=1;		//up

	if(SrcHeight>=PrDstHeight) ScaleUp_V_Pr=0;   // edited 040225
	else ScaleUp_V_Pr=1;		

	////////////////// common control setting
	rCIGCTRL |= (1<<26)|(0<<27); // inverse PCLK, test pattern

	//rCIGCTRL |= (0<<26)|(0<<27); // don't inverse PCLK, test pattern
	//---
	rCIWDOFST = (1<<30)|(0xf<<12); // clear overflow 
	rCIWDOFST = 0;	
	rCIWDOFST=(WinOfsEn<<31)|(WinHorOffset<<16)|(WinVerOffset);
	rCISRCFMT=(CAM_ITU601<<31)|(0<<30)|(0<<29)|(CAM_SRC_HSIZE<<16)|(CAM_ORDER_YCBYCR<<14)|(CAM_SRC_VSIZE);

	//rCISRCFMT=(CAM_ITU601<<31)|(1<<30)|(0<<29)|(CAM_SRC_HSIZE<<16)|(CAM_ORDER_YCBYCR<<14)|(CAM_SRC_VSIZE);
	//---

	////////////////// codec port setting
	if (CAM_CODEC_4PP)
	{
		rCICOYSA1=CoFrameBuffer;
		rCICOYSA2=rCICOYSA1+CoDstWidth*CoDstHeight+2*CoDstWidth*CoDstHeight/divisor;
		rCICOYSA3=rCICOYSA2+CoDstWidth*CoDstHeight+2*CoDstWidth*CoDstHeight/divisor;
		rCICOYSA4=rCICOYSA3+CoDstWidth*CoDstHeight+2*CoDstWidth*CoDstHeight/divisor;
		
		rCICOCBSA1=rCICOYSA1+CoDstWidth*CoDstHeight;
		rCICOCBSA2=rCICOYSA2+CoDstWidth*CoDstHeight;
		rCICOCBSA3=rCICOYSA3+CoDstWidth*CoDstHeight;
		rCICOCBSA4=rCICOYSA4+CoDstWidth*CoDstHeight;

		rCICOCRSA1=rCICOCBSA1+CoDstWidth*CoDstHeight/divisor;
		rCICOCRSA2=rCICOCBSA2+CoDstWidth*CoDstHeight/divisor;
		rCICOCRSA3=rCICOCBSA3+CoDstWidth*CoDstHeight/divisor;
		rCICOCRSA4=rCICOCBSA4+CoDstWidth*CoDstHeight/divisor;
	}
	else
	{
		rCICOYSA1=CoFrameBuffer;
		rCICOYSA2=rCICOYSA1;
		rCICOYSA3=rCICOYSA1;
		rCICOYSA4=rCICOYSA1;
		
		rCICOCBSA1=rCICOYSA1+CoDstWidth*CoDstHeight;
		rCICOCBSA2=rCICOCBSA1;
		rCICOCBSA3=rCICOCBSA1;
		rCICOCBSA4=rCICOCBSA1;
		
		rCICOCRSA1=rCICOCBSA1+CoDstWidth*CoDstHeight/divisor;
		rCICOCRSA2=rCICOCRSA1;
		rCICOCRSA3=rCICOCRSA1;
		rCICOCRSA4=rCICOCRSA1;
	}
	rCICOTRGFMT=(CAM_CODEC_IN_422<<31)|(CAM_CODEC_OUTPUT<<30)|(CoDstWidth<<16)|(CAM_FLIP_180<<14)|(CoDstHeight);

	CalculateBurstSize(CoDstWidth, &MainBurstSizeY, &RemainedBurstSizeY);
	CalculateBurstSize(CoDstWidth/2, &MainBurstSizeC, &RemainedBurstSizeC);
	rCICOCTRL=(MainBurstSizeY<<19)|(RemainedBurstSizeY<<14)|(MainBurstSizeC<<9)|(RemainedBurstSizeC<<4);

	CalculatePrescalerRatioShift(SrcWidth, CoDstWidth, &PreHorRatio, &H_Shift);
	CalculatePrescalerRatioShift(SrcHeight, CoDstHeight, &PreVerRatio, &V_Shift);
	MainHorRatio=(SrcWidth<<8)/(CoDstWidth<<H_Shift);
	MainVerRatio=(SrcHeight<<8)/(CoDstHeight<<V_Shift);
    			
	rCICOSCPRERATIO=((10-H_Shift-V_Shift)<<28)|(PreHorRatio<<16)|(PreVerRatio);
	rCICOSCPREDST=((SrcWidth/PreHorRatio)<<16)|(SrcHeight/PreVerRatio); 
	rCICOSCCTRL=(CAM_SCALER_BYPASS_OFF<<31)|(ScaleUp_H_Co<<30)|(ScaleUp_V_Co<<29)|(MainHorRatio<<16)|(MainVerRatio);

	rCICOTAREA=CoDstWidth*CoDstHeight;

	///////////////// preview port setting
	if (CAM_PVIEW_4PP) // codec view mode
	{
		rCIPRCLRSA1=PrFrameBuffer;
		rCIPRCLRSA2=rCIPRCLRSA1+PrDstWidth*PrDstHeight*multiplier;
		rCIPRCLRSA3=rCIPRCLRSA2+PrDstWidth*PrDstHeight*multiplier;
		rCIPRCLRSA4=rCIPRCLRSA3+PrDstWidth*PrDstHeight*multiplier;
	}	
	else // direct preview mode
	{
		rCIPRCLRSA1 = (U32)LCD_BUFFER;
		rCIPRCLRSA2 = (U32)LCD_BUFFER;
		rCIPRCLRSA3 = (U32)LCD_BUFFER;
		rCIPRCLRSA4 = (U32)LCD_BUFFER;
	}	

	rCIPRTRGFMT=(PrDstWidth<<16)|(CAM_FLIP_180<<14)|(PrDstHeight);

	if (CAM_PVIEW_OUTPUT==CAM_RGB24B)
		CalculateBurstSize(PrDstWidth*2, &MainBurstSizeRGB, &RemainedBurstSizeRGB);
	else // RGB16B
		CalculateBurstSize(PrDstWidth*2, &MainBurstSizeRGB, &RemainedBurstSizeRGB);
   	rCIPRCTRL=(MainBurstSizeRGB<<19)|(RemainedBurstSizeRGB<<14);

	CalculatePrescalerRatioShift(SrcWidth, PrDstWidth, &PreHorRatio, &H_Shift);
	CalculatePrescalerRatioShift(SrcHeight, PrDstHeight, &PreVerRatio, &V_Shift);
	MainHorRatio=(SrcWidth<<8)/(PrDstWidth<<H_Shift);
	MainVerRatio=(SrcHeight<<8)/(PrDstHeight<<V_Shift);
	rCIPRSCPRERATIO=((10-H_Shift-V_Shift)<<28)|(PreHorRatio<<16)|(PreVerRatio);		 
	rCIPRSCPREDST=((SrcWidth/PreHorRatio)<<16)|(SrcHeight/PreVerRatio);
	rCIPRSCCTRL=(1<<31)|(CAM_PVIEW_OUTPUT<<30)|(ScaleUp_H_Pr<<29)|(ScaleUp_V_Pr<<28)|(MainHorRatio<<16)|(MainVerRatio);
    
	rCIPRTAREA= PrDstWidth*PrDstHeight;
}



/********************************************************
 CalculateBurstSize - Calculate the busrt lengths
 
 Description:	
 - dstHSize: the number of the byte of H Size.
 
*/
void CalculateBurstSize(U32 hSize,U32 *mainBurstSize,U32 *remainedBurstSize)
{
	U32 tmp;	
	tmp=(hSize/4)%16;
	switch(tmp) {
		case 0:
			*mainBurstSize=16;
			*remainedBurstSize=16;
			break;
		case 4:
			*mainBurstSize=16;
			*remainedBurstSize=4;
			break;
		case 8:
			*mainBurstSize=16;
			*remainedBurstSize=8;
			break;
		default: 
			tmp=(hSize/4)%8;
			switch(tmp) {
				case 0:
					*mainBurstSize=8;
					*remainedBurstSize=8;
					break;
				case 4:
					*mainBurstSize=8;
					*remainedBurstSize=4;
				default:
					*mainBurstSize=4;
					tmp=(hSize/4)%4;
					*remainedBurstSize= (tmp) ? tmp: 4;
					break;
			}
			break;
	}		    	    		
}



/********************************************************
 CalculatePrescalerRatioShift - none
 
 Description:	
 - none
 
*/
void CalculatePrescalerRatioShift(U32 SrcSize, U32 DstSize, U32 *ratio,U32 *shift)
{
	if(SrcSize>=64*DstSize) {
		Uart_Printf("ERROR: out of the prescaler range: SrcSize/DstSize = %d(< 64)\n",SrcSize/DstSize);
		while(1);
	}
	else if(SrcSize>=32*DstSize) {
		*ratio=32;
		*shift=5;
	}
	else if(SrcSize>=16*DstSize) {
		*ratio=16;
		*shift=4;
	}
	else if(SrcSize>=8*DstSize) {
		*ratio=8;
		*shift=3;
	}
	else if(SrcSize>=4*DstSize) {
		*ratio=4;
		*shift=2;
	}
	else if(SrcSize>=2*DstSize) {
		*ratio=2;
		*shift=1;
	}
	else {
		*ratio=1;
		*shift=0;
	}    
	
}


/********************************************************
 CamCaptureStart - Start camera capture operation.
 
 Description:	
 - mode= CAM_CODEC_CAPTURE_ENABLE_BIT or CAM_PVIEW_CAPTURE_ENABLE_BIT or both
  
*/
void CamCaptureStart(U32 mode)
{ 
    
	if(mode&CAM_CODEC_SCALER_CAPTURE_ENABLE_BIT) {
		camCodecStatus=CAM_STARTED;
		rCICOSCCTRL|=CAM_CODEC_SACLER_START_BIT;
	}
	
	if(mode&CAM_PVIEW_SCALER_CAPTURE_ENABLE_BIT) {
		camPviewStatus=CAM_STARTED;
		rCIPRSCCTRL|=CAM_PVIEW_SACLER_START_BIT;
	}

	if(mode&CAM_CAMIF_GLOBAL_CAPTURE_ENABLE_BIT) {
		camCodecStatus=CAM_STARTED;
		rCICOSCCTRL|=CAM_CAMIF_GLOBAL_CAPTURE_ENABLE_BIT;
	}
	
	rCIIMGCPT|=CAM_CAMIF_GLOBAL_CAPTURE_ENABLE_BIT|mode;
}


void CamCaptureStop(void)
{
	camCodecStatus=CAM_STOP_ISSUED;
	camPviewStatus=CAM_STOP_ISSUED;
}


void _CamCodecStopHw(void)
{
	rCICOSCCTRL &= ~CAM_CODEC_SACLER_START_BIT; //stop codec scaler.
	rCIIMGCPT &= ~CAM_CODEC_SCALER_CAPTURE_ENABLE_BIT; //stop capturing for codec scaler.
	if(!(rCIIMGCPT & CAM_PVIEW_SCALER_CAPTURE_ENABLE_BIT))
		rCIIMGCPT &= ~CAM_CAMIF_GLOBAL_CAPTURE_ENABLE_BIT; //stop capturing for preview scaler if needed.
	rCICOCTRL |= (1<<2); //Enable last IRQ at the end of frame capture.
		       //NOTE:LastIrqEn bit should be set after clearing CAPTURE_ENABLE_BIT & SCALER_START_BIT
}

void _CamPviewStopHw(void)
{
	rCIPRSCCTRL &= ~CAM_PVIEW_SACLER_START_BIT; //stop preview scaler.
	rCIIMGCPT &= ~CAM_PVIEW_SCALER_CAPTURE_ENABLE_BIT; //stop capturing for preview scaler.
	if(!(rCIIMGCPT&CAM_CODEC_SCALER_CAPTURE_ENABLE_BIT))
		rCIIMGCPT &= ~CAM_CAMIF_GLOBAL_CAPTURE_ENABLE_BIT; //stop capturing for codec scaler if needed.
	rCIPRCTRL |= (1<<2); //Enable last IRQ at the end of frame capture.
       	//NOTE:LastIrqEn bit should be set after clearing CAPTURE_ENABLE_BIT & SCALER_START_BIT
}


void __irq CamIsr(void)
{

	U32 completedFrameIndex;

	if (rSUBSRCPND&BIT_SUB_CAM_C)
	{
		//Uart_Printf("[C]");
		rGPFDAT ^= 1<<5;
		CamCodecIntMask();
		rSUBSRCPND |= BIT_SUB_CAM_C;
		ClearPending(BIT_CAM);
		switch(camCodecStatus) {
			case CAM_STOP_ISSUED:
				_CamCodecStopHw();
				camCodecStatus=CAM_LAST_CAPTURING;
				Uart_Printf("cr=%x\n", rCICOCTRL);
				//Uart_Printf("cS1\n");
				break;
			case CAM_LAST_CAPTURING:
				camCodecStatus=CAM_STOPPED;
				CamCodecIntMask();			
				//Uart_Printf("cS2\n");
				return;
			case CAM_STARTED:
				flagCaptured_C = 1;
//				_CamCodecStopHw();
				if(camTestMode&CAM_TEST_MODE_CODEC)	{
					if(camCodecCaptureCount>0) 
						completedFrameIndex=(((rCICOSTATUS>>26)&0x3)+4-2)%4;   
					//Uart_Printf("FrameIndex:%d\n",completedFrameIndex);
				}
				else {
					//Uart_Printf("Just Capturing without display");
				}
				break;
			case CAM_CODEC_SCALER_BYPASS_STATE:
				//Uart_Printf("cBP\n");
				break;
			default:
				break;
		}
			
		CamCodecIntUnmask();
	    camCodecCaptureCount++;	 
	}
	else
	{
		//Uart_Printf("[P]");
		rGPFDAT ^= 1<<4;
		CamPreviewIntMask();
		rSUBSRCPND |= BIT_SUB_CAM_P;
		ClearPending(BIT_CAM) ;
		switch(camPviewStatus) {
			case CAM_STOP_ISSUED:
				_CamPviewStopHw();
				camPviewStatus=CAM_LAST_CAPTURING;	 
				Uart_Printf("pr=%x\n", rCIPRCTRL);
				//Uart_Printf("pS1\n");
				break;
			case CAM_LAST_CAPTURING:
				camPviewStatus=CAM_STOPPED;
				CamPreviewIntMask();
				//Uart_Printf("pS2\n"); 	
				return;
			case CAM_STARTED:
				flagCaptured_P = 1;
				if(camTestMode&CAM_TEST_MODE_PVIEW) {
					if(camPviewCaptureCount >0) 
						completedFrameIndex=(((rCIPRSTATUS>>26)&0x3)+4-2)%4;
					//Uart_Printf("FrameIndex:%d\n",completedFrameIndex);
				}
				else {
					//Uart_Printf("Preview Image Captured\n");
				} 		
			default:
				break;			
		} 	
		
		CamPreviewIntUnmask();
		camPviewCaptureCount++;
	}
}



/******************************************************************************
 *                                                                            *    
 *                   camera interface interrupts & controls                   *
 *                                                                            *     
 ******************************************************************************/


U32 Conv_YCbCr_Rgb(U8 y0, U8 y1, U8 cb0, U8 cr0)  // second solution... by junon
{
	// bit order is
	// YCbCr = [Cr0 Y1 Cb0 Y0], RGB=[R1,G1,B1,R0,G0,B0].
	
	int r0, g0, b0, r1, g1, b1;
	U32 rgb0, rgb1, rgb;
 
	#if 1 // 4 frames/s @192MHz, 12MHz ; 6 frames/s @450MHz, 12MHz
	r0 = YCbCrtoR(y0, cb0, cr0);
	g0 = YCbCrtoG(y0, cb0, cr0);
	b0 = YCbCrtoB(y0, cb0, cr0);
	r1 = YCbCrtoR(y1, cb0, cr0);
	g1 = YCbCrtoG(y1, cb0, cr0);
	b1 = YCbCrtoB(y1, cb0, cr0);
	#endif

	if (r0>255 ) r0 = 255;
	if (r0<0) r0 = 0;
	if (g0>255 ) g0 = 255;
	if (g0<0) g0 = 0;
	if (b0>255 ) b0 = 255;
	if (b0<0) b0 = 0;

	if (r1>255 ) r1 = 255;
	if (r1<0) r1 = 0;
	if (g1>255 ) g1 = 255;
	if (g1<0) g1 = 0;
	if (b1>255 ) b1 = 255;
	if (b1<0) b1 = 0;
	
	// 5:6:5 16bit format
	rgb0 = (((U16)r0>>3)<<11) | (((U16)g0>>2)<<5) | (((U16)b0>>3)<<0);	//RGB565.
	rgb1 = (((U16)r1>>3)<<11) | (((U16)g1>>2)<<5) | (((U16)b1>>3)<<0);	//RGB565.

	rgb = (rgb1<<16) | rgb0;

	return(rgb);
}


void Display_Cam_Image(U32 size_x, U32 size_y)
{
	U8 *buffer_y, *buffer_cb, *buffer_cr;
	U32 rgb_data0; 
	U32 x, y;
	int temp;

	if (CAM_CODEC_4PP)
		temp = (((rCICOSTATUS>>26)&0x3)+4-2)%4; // current frame memory block
	else
		temp = 4;
	//Uart_Printf("Current Frame memory %d\n", temp);

	switch (temp) // current frame mem - 2
	{
	case 0:
		buffer_y = (U8 *)rCICOYSA1;
		buffer_cb = (U8 *)rCICOCBSA1;
		buffer_cr = (U8 *)rCICOCRSA1;
		break;
	case 1:
		buffer_y = (U8 *)rCICOYSA2;
		buffer_cb = (U8 *)rCICOCBSA2;
		buffer_cr = (U8 *)rCICOCRSA2;
		break;
	case 2:
		buffer_y = (U8 *)rCICOYSA3;
		buffer_cb = (U8 *)rCICOCBSA3;
		buffer_cr = (U8 *)rCICOCRSA3;
		break;
	case 3:
		buffer_y = (U8 *)rCICOYSA4;
		buffer_cb = (U8 *)rCICOCBSA4;
		buffer_cr = (U8 *)rCICOCRSA4;
		break;
	default :
		buffer_y = (U8 *)rCICOYSA1;
		buffer_cb = (U8 *)rCICOCBSA1;
		buffer_cr = (U8 *)rCICOCRSA1;
		break;
	}

	//Uart_Printf("End setting : Y-0x%x, Cb-0x%x, Cr-0x%x\n", buffer_y, buffer_cb, buffer_cr);	

#if CAM_CODEC_OUTPUT==CAM_CCIR420
	for (y=0;y<size_y;y++) // YCbCr 4:2:0 format
	{
		for (x=0;x<size_x;x+=2)
		{		
			rgb_data0 = Conv_YCbCr_Rgb(*buffer_y++, *buffer_y++, *buffer_cb++, *buffer_cr++);
			frameBuffer16BitTft240320[y][x/2] = rgb_data0;

			if ( (x==(size_x-2)) && ((y%2)==0) ) // when x is last pixel & y is even number
			{
				buffer_cb -= size_x/2;
				buffer_cr -= size_x/2;
			} 	
		}
	}	
#else
	for (y=0;y<size_y;y++) // YCbCr 4:2:2 format
	{
		for (x=0;x<size_x;x+=2)
		{ 	
			rgb_data0 = Conv_YCbCr_Rgb(*buffer_y++, *buffer_y++, *buffer_cb++, *buffer_cr++);
			LCD_BUFFER[y][x/2] = rgb_data0;
			//Uart_Printf("%08x\n", rgb_data0);
		//---
		}
	} 
#endif

}


void Test_CamPreview(void)
{
	Uart_Printf("\nNow Start Camera Preview\n");

	//camera global variables
	camTestMode=CAM_TEST_MODE_PVIEW;
	camCodecCaptureCount=0;
	camPviewCaptureCount=0;
	camPviewStatus=CAM_STOPPED;
	camCodecStatus=CAM_STOPPED;
	flagCaptured_P=0;

	Lcd_Init();
	Lcd_PowerEnable(0, 1);
	Lcd_EnvidOnOff(1);		//turn on vedio


	Uart_Printf( "preview sc control = %x\n" , rCIPRSCCTRL ) ;

	// Initialize Camera interface
	if(LCD_Type == LCDT35)
		CamInit(240, 320, 240, 320, 0, 0,  CAM_FRAMEBUFFER_C, CAM_FRAMEBUFFER_P);
	else if((LCD_Type == LCDW35)||(LCD_Type == LCDS35))
		CamInit(320, 240, 320, 240, 100, 100,  CAM_FRAMEBUFFER_C, CAM_FRAMEBUFFER_P);		
	else if(LCD_Type == VGA)
		CamInit(640, 480, 640, 480, 100, 100,  CAM_FRAMEBUFFER_C, CAM_FRAMEBUFFER_P);		
	else if(LCD_Type == LCDA70)
		CamInit(800, 480, 800, 480, 100, 100,  CAM_FRAMEBUFFER_C, CAM_FRAMEBUFFER_P);		
	Uart_Printf("preview sc control = %x\n", rCIPRSCCTRL);

	// Start Capture	
	rSUBSRCPND |= BIT_SUB_CAM_C|BIT_SUB_CAM_P;
	ClearPending(BIT_CAM);
	pISR_CAM = (U32)CamIsr;    
	CamPreviewIntUnmask();
	CamCaptureStart(CAM_PVIEW_SCALER_CAPTURE_ENABLE_BIT);
	Uart_Printf("Press 'ESC' key to exit!\n");
	while (1)
	{
		if (flagCaptured_P)
		{
			flagCaptured_P = 0;
//			Uart_Printf("Enter Cam A port, count = %d\n",camCodecCaptureCount);
		}
		if ( Uart_GetKey() == ESC_KEY ) break;			
	}
    
	CamCaptureStop();

	Uart_Printf("\nWait until the current frame capture is completed.\n");
	while(camPviewStatus!=CAM_STOPPED)
		if (Uart_GetKey()== '\r') break;			

	Uart_Printf("CIS format = %x\n", rCISRCFMT);
	Uart_Printf("image cap = %x\n", rCIIMGCPT);
	Uart_Printf("preview sc control = %x\n", rCIPRSCCTRL);
	Uart_Printf("preview control = %x\n", rCIPRCTRL);
	Uart_Printf("codec sc control = %x\n", rCICOSCCTRL);
	Uart_Printf("codec control = %x\n", rCICOCTRL);
	Uart_Printf("pr addr1 = %x\n", rCIPRCLRSA1);
	Uart_Printf("pr addr2 = %x\n", rCIPRCLRSA2);

	Uart_Printf("camCodecCaptureCount=%d\n",camCodecCaptureCount);
	Uart_Printf("camPviewCaptureCount=%d\n",camPviewCaptureCount);
//	CamPreviewIntMask();
}

