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
    //如果温度低于零度,显示'-'号
    LEDBuf[0] = 0x40;
    T = - T;
  } else LEDBuf[0] = 0;
  //显示温度十位数
  LEDBuf[1] = LEDMAP[T / 10];
  //显示温度个位数
  LEDBuf[2] = LEDMAP[T % 10];

  LEDBuf[3] = 0;

}

unsigned char ReadAD()
{
  unsigned int i;

  // 启动A/D变换
  TEMP = 0;
  //延时100us,
  for (i=0; i<20; i++);
  //得到A/D采样值
  return (0xff - TEMP);
}

signed char ReadTemp()
{
  unsigned char i;
  signed int Temp;

  Temp = 0;
  //采样16次,取平均数
  for (i=0; i<16; i++) {
    Temp += ReadAD();
  };
  //AD采样值转换为实际温度
  CurTemp = (Temp >> 4) * (HighTemp-LowTemp) / 256 + LowTemp;
	return CurTemp;
}


//void main()
//{
//  unsigned char dtimer;

//  while (1) {
//    for(dtimer=15; dtimer>0; dtimer--){
//      // 当前温度和设定温度送显示缓冲
//      DisplayT();
//      // 显示当前温度和设定温度
//      DisplayLED();
//    };
//    // 读入当前温度
//    ReadTemp();
//  }
//}
