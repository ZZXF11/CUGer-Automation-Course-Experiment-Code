#include <reg51.h>
#include "YALI.h"
#include "temp.h"
#include "BEEP.h"
#include "motor.h"
#include "KEYLED.h"
#include "8255.h"

#define DC_P 1
#define mode 0x82   // ��ʽ0��PA��PC�����PB����
xdata unsigned char PortA _at_ 0x8000 ; // Port A
xdata unsigned char PortB _at_ 0x8001 ; // Port B
xdata unsigned char PortC _at_ 0x8002 ; // Port C
xdata unsigned char CAddr _at_ 0x8003 ; // �����ֵ�ַ
xdata unsigned char MOTOR _at_ 0xd000;
sbit P1_3=P1^3;

unsigned int count;


void delaymotor()
{
  unsigned int ddd;

  ddd = 50000;            // ��6MHzԼ��ʱ1��
  while(ddd--);
}



void readSpeed()
{
	int i=0;
  TMOD = 0x51; // T0��ʱ��T1����
  TR0  = 0;//�ر�T0
  TH0  = 0x3c;//���ó�ֵ��50000�����
  TL0  = 0xb0;
	TR1  = 0;//���ü�����T1
  TH1  = 0;
  TL1  = 0;
	TR0  = 1;//�򿪶�ʱ��
	TR1  = 1;//�򿪼�����
}

