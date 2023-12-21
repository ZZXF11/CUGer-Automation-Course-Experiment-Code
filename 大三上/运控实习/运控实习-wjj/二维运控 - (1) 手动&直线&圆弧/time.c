#include "time.h"

// �������ã�������ʱ����
// ��������ʱ�ĺ�����
void delayms(unsigned int tms)
{
  unsigned int i,j;		
  for(i=tms;i>0;i--)
    for(j=110;j>0;j--);	
}

// �������ã�΢����ʱ����
// ��������ʱ��΢����
void delayus(unsigned int tus)
{
  unsigned int i;		
  for(i=tus;i>0;i--)
  	_nop_();	// ��ʱһ���������ڣ�������Ƶ��Ϊ12MHzʱ����ʱ1us  	
}

//��ʼ���ж�
void inter_init()
{
	
	TMOD |= 0x02;  //��ʱ��16Ϊ��������ģʽ
	TH0 =0x00;
	TL0 =0x00; //5ms
//	TH0 =0xED;
//	TL0 =0xFF; //5ms
	ET0 = 1; //����ʱ��0�ж�
	TR0 = 1;//������ʱ��0
	EA = 1;	//�����ж�
}

void TIM1init(void)//��ʱ��0��ʼ��
{
	TMOD|=0x20;//��ʱ��1������ʽ2��TH1����װֵ��TL1�ǳ�ֵ
	TH1=0x00; //����ֵ
	TL1=0x00; //��ʼ��ֵ
	ET1=0;    //���ж�
	TR1=1;
}

//�ⲿ�жϳ�ʼ��
void EX0init(void)
{
 IT0 = 1;   //ָ���ⲿ�ж�0�½��ش�����INT0 (P3.2)
 EX0 = 1;   //ʹ���ⲿ�ж�
 EA = 1;    //�����ж�
}