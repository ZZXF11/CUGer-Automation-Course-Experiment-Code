#include <reg51.h>
#include "YALI.h"
#include "temp.h"
#include "BEEP.h"
#include "motor.h"
#include "KEYLED.h"
#include "8255.h"
xdata unsigned char YALI _at_ 0xa000;

unsigned char ReadYALI()
{
  unsigned char i;

  YALI = 0;                // �� A/D
  for (i=0; i<0x20; i++) ;   // ��ʱ > 100us
  return(YALI);            // ������
}







