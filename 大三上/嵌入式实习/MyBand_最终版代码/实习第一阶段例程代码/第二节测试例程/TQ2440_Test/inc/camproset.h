
#ifndef __CAMSCCB_H__
#define __CAMSCCB_H__

#ifdef __cplusplus
extern "C" {
#endif

//CAM_MODULE_XX should reserve the bit[9:5].
#define CAM_MODULE_RESERVED_BIT5	(1<<5)
#define CAM_MODULE_RESERVED_BIT6	(1<<5)
#define CAM_MODULE_RESERVED_BIT7	(1<<5)
#define CAM_MODULE_RESERVED_BIT8	(1<<5)
#define CAM_MODULE_RESERVED_BIT9	(1<<5)


void Wr_CamIIC(U32 slvAddr, U32 addr, U8 data);
void Rd_CamIIC(U32 slvAddr,U32 addr,U8 *data);
void __irq Cam_IICInt(void);

void Camera_WriteByte(void);
void Camera_ReadByte(void);
void Camera_WriteBlock(void);
void Camera_ReadBlock(void);

void Camera_Iic_Test(void);
int CameraModuleSetting(void);

#ifdef __cplusplus
}
#endif
#endif /*__CAMSCCB_H__*/

