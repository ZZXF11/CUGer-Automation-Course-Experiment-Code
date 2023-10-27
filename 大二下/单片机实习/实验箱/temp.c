#include <reg51.h>
#include "YALI.h"
#include "temp.h"
#include "BEEP.h"
#include "motor.h"
#include "KEYLED.h"
#include "8255.h"

#define LowTemp   (-99)   // A/D 0
#define HighTemp  99      // A/D 255
#define LEDLen 6

xdata unsigned char TEMP _at_ 0xa001;

signed char CurTemp;

void DisplayT()
{
  signed char T;
  T = CurTemp;
	
  if (T < 0) {
    //����¶ȵ������,��ʾ'-'��
    LEDBuf[0] = 0x40;
    T = - T;
  } else LEDBuf[0] = 0;
  //��ʾ�¶�ʮλ��
  LEDBuf[1] = LEDMAP[T / 10];
  //��ʾ�¶ȸ�λ��
  LEDBuf[2] = LEDMAP[T % 10];

  LEDBuf[3] = 0;

}

unsigned char ReadAD()
{
  unsigned int i;

  // ����A/D�任
  TEMP = 0;
  //��ʱ100us,
  for (i=0; i<20; i++);
  //�õ�A/D����ֵ
  return (0xff - TEMP);
}

signed char ReadTemp()
{
  unsigned char i;
  signed int Temp;

  Temp = 0;
  //����16��,ȡƽ����
  for (i=0; i<16; i++) {
    Temp += ReadAD();
  };
  //AD����ֵת��Ϊʵ���¶�
  CurTemp = (Temp >> 4) * (HighTemp-LowTemp) / 256 + LowTemp;
	return CurTemp;
}


//void main()
//{
//  unsigned char dtimer;

//  while (1) {
//    for(dtimer=15; dtimer>0; dtimer--){
//      // ��ǰ�¶Ⱥ��趨�¶�����ʾ����
//      DisplayT();
//      // ��ʾ��ǰ�¶Ⱥ��趨�¶�
//      DisplayLED();
//    };
//    // ���뵱ǰ�¶�
//    ReadTemp();
//  }
//}
