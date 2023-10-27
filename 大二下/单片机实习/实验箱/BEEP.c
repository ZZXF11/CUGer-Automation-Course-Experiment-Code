#include <reg51.h>
#include "YALI.h"
#include "temp.h"
#include "BEEP.h"
#include "motor.h"
#include "KEYLED.h"
#include "8255.h"


void Delay1()//·äÃùÆ÷×¨ÓÃÑÓÊ±
{
  unsigned char i;
  for (i=0; i<200; i++);
}