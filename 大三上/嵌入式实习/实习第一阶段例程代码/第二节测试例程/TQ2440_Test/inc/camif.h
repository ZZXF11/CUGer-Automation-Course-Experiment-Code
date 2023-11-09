/******************************************************************************

 Filename:	camif.h

 Descriptions		
 - header file of camif.c

 ******************************************************************************/

 
#ifndef __CAMIF_H__
#define __CAMIF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "camdef.h"

void CalculateBurstSize(U32 dstHSize,U32 *mainBurstSize,U32 *RemainedBurstSize);
void CalculatePrescalerRatioShift(U32 srcWidth, U32 dstWidth, U32 *ratio,U32 *shift);

void __irq CamPviewIsr(void);
void __irq CamCodecIsr(void);
void __irq CamIsr(void);


void CamPortSet(void);
void CamPortReturn(void);
void CamPreviewIntUnmask(void);
void CamCodecIntUnmask(void);
void CamPreviewIntMask(void);
void CamCodecIntMask(void);
void CamReset(void);
void CamModuleReset(void);
void SetCAMClockDivider(int divn);

void CamCaptureStart(U32 mode);
void CamCaptureStop(void);
void _CamPviewStopHw(void);
void _CamCodecStopHw(void);


void Test_CamPreview(void);
void Test_CamCodec(void);
void Test_YCbCr_to_RGB(void);
void Camera_Test(void);


#ifdef __cplusplus
}
#endif

#endif /*__CAMIF_H__*/
