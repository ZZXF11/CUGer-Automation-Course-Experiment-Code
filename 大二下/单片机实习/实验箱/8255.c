#include <reg51.h>
#include "YALI.h"
#include "temp.h"
#include "BEEP.h"
#include "motor.h"
#include "KEYLED.h"
#include "8255.h"

#define mode 0x82   // ��ʽ0��PA��PC�����PB����
xdata unsigned char PortA _at_ 0x8000 ; // Port A
xdata unsigned char PortB _at_ 0x8001 ; // Port B
xdata unsigned char PortC _at_ 0x8002 ; // Port C
xdata unsigned char CAddr _at_ 0x8003 ; // �����ֵ�ַ

//void main()
//{
//  register unsigned char i, dd;

//  CAddr = mode;     // ��ʽ0, PA,PC���, PB����
//  while(1){
//    dd = 0x80;
//    for(i = 0; i<8; i++)
//    {
//      PortA = dd;   // �����PA
//      dd >>= 1;     // ��λ
//      delay(1);     // ��ʱ
//    };

//    dd = PortB;     // PB����
//    PortA = dd;     // �������PA
//    delay(2);
//  }
//}
