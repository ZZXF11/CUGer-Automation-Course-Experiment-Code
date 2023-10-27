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

  YALI = 0;                // 起动 A/D
  for (i=0; i<0x20; i++) ;   // 延时 > 100us
  return(YALI);            // 读入结果
}







