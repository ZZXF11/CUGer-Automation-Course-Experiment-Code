//====================================================================
// File Name : IIC.h
// Function  : TQ2440 IIC Test Program Head file
// Version   : 1.0
//====================================================================

#ifndef __IIC_H__
#define __IIC_H__

#define WRDATA      (1)
#define POLLACK     (2)
#define RDDATA      (3)
#define SETRDADDR   (4)

#define IICBUFSIZE 0x20

void Test_Iic(void);
void Test_Iic2(void);
void Wr24C080(U32 slvAddr,U32 addr,U8 data);    
void Rd24C080(U32 slvAddr,U32 addr,U8 *data);   
void _Wr24C080(U32 slvAddr,U32 addr,U8 data);   
void _Rd24C080(U32 slvAddr,U32 addr,U8 *data);  

void __irq IicInt(void);
void IicPoll(void);
void Run_IicPoll(void);
void Iic_Test(void);


#endif    //__IIC_H__
