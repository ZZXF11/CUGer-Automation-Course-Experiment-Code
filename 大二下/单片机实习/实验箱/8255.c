#include <reg51.h>
#include "YALI.h"
#include "temp.h"
#include "BEEP.h"
#include "motor.h"
#include "KEYLED.h"
#include "8255.h"

#define mode 0x82   // 方式0，PA，PC输出，PB输入
xdata unsigned char PortA _at_ 0x8000 ; // Port A
xdata unsigned char PortB _at_ 0x8001 ; // Port B
xdata unsigned char PortC _at_ 0x8002 ; // Port C
xdata unsigned char CAddr _at_ 0x8003 ; // 控制字地址

//void main()
//{
//  register unsigned char i, dd;

//  CAddr = mode;     // 方式0, PA,PC输出, PB输入
//  while(1){
//    dd = 0x80;
//    for(i = 0; i<8; i++)
//    {
//      PortA = dd;   // 输出到PA
//      dd >>= 1;     // 移位
//      delay(1);     // 延时
//    };

//    dd = PortB;     // PB输入
//    PortA = dd;     // 再输出到PA
//    delay(2);
//  }
//}
