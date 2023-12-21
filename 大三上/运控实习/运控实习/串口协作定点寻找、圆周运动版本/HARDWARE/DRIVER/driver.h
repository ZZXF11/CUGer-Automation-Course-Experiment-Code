#ifndef __DRIVER_H
#define __DRIVER_H
#include "sys.h"
#include "stdlib.h"	


/********** ������ �˿ڶ��� **************
//DRIVER_DIR   PA8 
//DRIVER_OE    PA11 
//STEP_PULSE   PA1 (TIM2_CH2)
******************************************/
#define DRIVER_DIR2   PAout(8) // ��ת���� 
//#define DRIVER_OE2    PAout(11) // ʹ�ܽ� �͵�ƽ��Ч
#define DRIVER_DIR3   PAout(6) // ��ת���� 
//#define DRIVER_OE3    PAout(5) // ʹ�ܽ� �͵�ƽ��Ч

typedef enum
{
	CW = 1,//�ߵ�ƽ˳ʱ��
	CCW = 0,//�͵�ƽ��ʱ��
}DIR_Type;  //����ö������ΪDIR_Type �ɿ���Ϊu16���֣����� DIR_Type dir,����CW,CCW���ǳ�����
//���ܶ����Ǹ�ֵ��ֻ�ܽ����ǵ�ֵ���������ı�����

extern long current_pos[2];//�з��ŷ���

void Driver_Init(void);//��������ʼ��
void TIM2_Init(u16 arr,u16 psc);//TIM2_CH2 
void TIM3_Init(u16 arr,u16 psc);//TIM3_CH2 
void TIM2_Startup(u32 frequency);   //������ʱ��2
void TIM3_Startup(u32 frequency);   //������ʱ��3
void Locate_Rle2(u32 frequency,DIR_Type dir); //��Զ�λ����2
void Locate_Rle3(u32 frequency,DIR_Type dir); //��Զ�λ����3
void Locate_Abs(long num,u32 frequency);//���Զ�λ����
void TIM4_PWM_Init(u16 arr,u16 psc); //��� ��ʱ��4��ʼ��
u16 lpwmcount(double distance); //����������ת��
u16 rpwmcount(double distance);

#endif


