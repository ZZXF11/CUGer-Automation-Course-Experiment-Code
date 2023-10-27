#include <reg51.h>
#include "8255.h"
#include "KEYLED.h"
#include "YALI.h"
#include "BEEP.h"
#include "temp.h"
#include "motor.h"

#define LEDLen 6

xdata unsigned char OUTBIT _at_ 0x9002;   // λ���ƿ�
xdata unsigned char OUTSEG _at_ 0x9004;   // �ο��ƿ�
xdata unsigned char IN     _at_ 0x9001;   // ���̶����

unsigned char LEDBuf[LEDLen];    // ��ʾ����
code unsigned char LEDMAP[] = {  // �˶ι���ʾ��
  0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
  0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71
};


void Delay(unsigned char CNT)
{
  unsigned char i;

  while (CNT-- !=0)
    for (i=100; i !=0; i--);
}

void DisplayLED()
{
  unsigned char i;
  unsigned char Pos;
  unsigned char LED;

  Pos = 0x20;       // ����߿�ʼ��ʾ
  for (i = 0; i < LEDLen; i++) {
    OUTBIT = 0;     // �����а˶ι�
    LED = LEDBuf[i];
    OUTSEG = LED;
    OUTBIT = Pos;   // ��ʾһλ�˶ι�
    Delay(1);
    Pos >>= 1;      // ��ʾ��һλ
  }
}

code unsigned char KeyTable[] = {   // ���붨��
  0x16, 0x15, 0x14, 0xff,
  0x13, 0x12, 0x11, 0x10,
  0x0d, 0x0c, 0x0b, 0x0a,
  0x0e, 0x03, 0x06, 0x09,
  0x0f, 0x02, 0x05, 0x08,
  0x00, 0x01, 0x04, 0x07
};

unsigned char TestKey()
{
   OUTBIT = 0;            // �������Ϊ0
   return (~IN & 0x0f);   // �����״̬(����λ����)
}

unsigned char GetKey()
{
  unsigned char Pos;
  unsigned char i;
  unsigned char k;

  i = 6;
  Pos = 0x20;     // �ҳ���������
  do {
    OUTBIT = ~ Pos;
    Pos >>= 1;
    k = ~IN & 0x0f;
  } while ((--i != 0) && (k == 0));

  // ��ֵ = �� x 4 + ��
  if (k != 0) {
    i *= 4;
    if (k & 2)
      i += 1;
    else if (k & 4)
      i += 2;
    else if (k & 8)
      i += 3;

    OUTBIT = 0;
    do Delay(10); while (TestKey());  // �ȼ��ͷ�

    return(KeyTable[i]);  // ȡ������
  } else return(0xff);
}


