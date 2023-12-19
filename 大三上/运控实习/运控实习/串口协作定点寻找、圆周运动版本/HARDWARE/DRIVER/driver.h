#ifndef __DRIVER_H
#define __DRIVER_H
#include "sys.h"
#include "stdlib.h"	


/********** 驱动器 端口定义 **************
//DRIVER_DIR   PA8 
//DRIVER_OE    PA11 
//STEP_PULSE   PA1 (TIM2_CH2)
******************************************/
#define DRIVER_DIR2   PAout(8) // 旋转方向 
//#define DRIVER_OE2    PAout(11) // 使能脚 低电平有效
#define DRIVER_DIR3   PAout(6) // 旋转方向 
//#define DRIVER_OE3    PAout(5) // 使能脚 低电平有效

typedef enum
{
	CW = 1,//高电平顺时针
	CCW = 0,//低电平逆时针
}DIR_Type;  //定义枚举类型为DIR_Type 可看作为u16这种，例如 DIR_Type dir,上面CW,CCW都是常量，
//不能对它们赋值，只能将它们的值赋给其他的变量。

extern long current_pos[2];//有符号方向

void Driver_Init(void);//驱动器初始化
void TIM2_Init(u16 arr,u16 psc);//TIM2_CH2 
void TIM3_Init(u16 arr,u16 psc);//TIM3_CH2 
void TIM2_Startup(u32 frequency);   //启动定时器2
void TIM3_Startup(u32 frequency);   //启动定时器3
void Locate_Rle2(u32 frequency,DIR_Type dir); //相对定位函数2
void Locate_Rle3(u32 frequency,DIR_Type dir); //相对定位函数3
void Locate_Abs(long num,u32 frequency);//绝对定位函数
void TIM4_PWM_Init(u16 arr,u16 psc); //舵机 定时器4初始化
u16 lpwmcount(double distance); //距离脉冲数转换
u16 rpwmcount(double distance);

#endif


