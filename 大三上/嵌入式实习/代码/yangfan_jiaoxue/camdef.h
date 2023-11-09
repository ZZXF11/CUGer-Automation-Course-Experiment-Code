	/*****************************************
  NAME: Camdef.h
  DESC: header file for Imagetest test codes 
 *****************************************/

#ifndef __CAMDEF_H__
#define __CAMDEF_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "def.h"

//Boaz Sekwang Kim
#define CAM_CCIR420					(0)
#define CAM_CCIR422					(1)
#define CAM_RGB16B					0
#define CAM_RGB24B					1

#define CAM_ITU601					(1)
#define CAM_ITU656					(0)

#define CAM_ORDER_YCBYCR				(0)
#define CAM_ORDER_YCRYCB				(1)
#define CAM_ORDER_CBYCRY				(2)
#define CAM_ORDER_CRYCBY				(3)

#define CAM_CODEC_IN_420				(0)
#define CAM_CODEC_IN_422				(1)

#define CAM_CODEC_OUT_420				(0)
#define CAM_CODEC_OUT_422				(1)

#define CAM_FLIP_NORMAL					(0)
#define CAM_FLIP_XAXIS					(1)
#define CAM_FLIP_YAXIS					(2)
#define CAM_FLIP_180					(3)

#define CAM_SCALER_BYPASS_ON				(1)
#define CAM_SCALER_BYPASS_OFF				(0)

#define CAM_CODEC_SACLER_START_BIT			(1<<15)
#define CAM_PVIEW_SACLER_START_BIT			(1<<15)

#define CAM_CAMIF_GLOBAL_CAPTURE_ENABLE_BIT		(1<<31)
#define CAM_CODEC_SCALER_CAPTURE_ENABLE_BIT		(1<<30)
#define CAM_PVIEW_SCALER_CAPTURE_ENABLE_BIT		(1<<29)

//camTestMode
#define CAM_TEST_MODE_PVIEW				(1<<0)
#define CAM_TEST_MODE_CODEC				(1<<1)

//camCodecStatus, camPviewStatus
#define CAM_STARTED					(0)
#define CAM_STOP_ISSUED					(1)
#define CAM_LAST_CAPTURING				(2)
#define CAM_STOPPED					(3)
#define CAM_CODEC_SCALER_BYPASS_STATE			(4)

//Image Size
#define XGA_XSIZE					(1024)
#define XGA_YSIZE					(768)
#define SVGA_XSIZE					(800)
#define SVGA_YSIZE					(600)
#define VGA_XSIZE					(640)
#define VGA_YSIZE					(480)
#define QVGA_XSIZE					(320)
#define QVGA_YSIZE					(240)
#define PQVGA_XSIZE					(240)
#define PQVGA_YSIZE					(320)
#define CIF_XSIZE					(352)
#define CIF_YSIZE					(288)
#define QCIF_XSIZE					(176)
#define QCIF_YSIZE					(144)

#define CAMCLK48000000					(0)
#define CAMCLK24000000					(1)
#define CAMCLK16000000					(2)
#define CAMCLK12000000					(3)
#define CAMCLK9600000					(4)
#define CAMCLK8000000					(5)

#define C16_BLUE 					(0x1f<<0)
#define C16_GREEN 					(0x3f<<5)
#define C16_RED 					(0x1f<<11)
#define C16_BLACK 					(0x0)
#define C16_WHITE 					(0xffff)

#define C18_BLUE					(0xfc)
#define C18_GREEN					(0xfc00)
#define C18_RED 					(0xfc0000)
#define C18_BLACK					(0x0)
#define C18_WHITE					(0xfcfcfc)

//camera type
#define CAM_OV9650					(0)	// 640X480 VGA, 
#define CAM_S5X433					(1)	// VGA,
#define CAM_S5X532					(2)	// VGA,
#define CAM_AU70H					(3) 	//1152x864 MegaPixel Camera, max 19.3MHz 
#define CAM_S5X3A1					(4)	// Mega pixel,

#define	YCbCrtoR(Y,Cb,Cr)				(1000*Y + 1371*(Cr-128))/1000
#define 	YCbCrtoG(Y,Cb,Cr)				(1000*Y - 336*(Cb-128) - 698*(Cr-128))/1000
#define	YCbCrtoB(Y,Cb,Cr)				(1000*Y + 1732*(Cb-128))/1000

#define CAM_FRAMEBUFFER_C		_NONCACHE_STARTADDRESS+0x1000000// Adjusting is needed..
#define CAM_FRAMEBUFFER_P		_NONCACHE_STARTADDRESS// Max buffer size of Port : 0x1000000 (2048*2048*4)

// Current modes
//#define USED_CAM_TYPE					CAM_S5X532
#define USED_CAM_TYPE					CAM_OV9650	//use OV9650
#define USED_LCD_TYPE  					MODE_TFT_16BIT_240320  // refer to Lcdlib.h 
//AU70H camera resolution
#define AU70H_VIDEO_SIZE				(1152)	  // 1152:(1152x864) or 640:(640x480)	
//#define CAM_CODEC_OUTPUT				CAM_CCIR420
#define CAM_CODEC_OUTPUT				CAM_CCIR422		//directly CCIR422
//#define CAM_PVIEW_OUTPUT				CAM_RGB24B
#define CAM_PVIEW_OUTPUT				CAM_RGB16B		//use 16B

#define CAM_CODEC_4PP					(0) // 0:all equal, 1:4 pingpong
#define CAM_PVIEW_4PP					(0) // 0:all equal, 1:4 pingpong

#if USED_CAM_TYPE==CAM_AU70H && AU70H_VIDEO_SIZE==1152
#define CAM_SRC_HSIZE					(1152)
#define CAM_SRC_VSIZE					(864)
#elif USED_CAM_TYPE==CAM_S5X3A1
#define CAM_SRC_HSIZE					(1280)
#define CAM_SRC_VSIZE					(1024)
#else
#define CAM_SRC_HSIZE					(640)
#define CAM_SRC_VSIZE					(480)
#endif


#ifdef __cplusplus
}
#endif

#endif /*__CAMDEF_H__*/
