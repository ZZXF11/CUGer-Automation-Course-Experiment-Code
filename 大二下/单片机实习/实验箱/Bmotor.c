#include <reg51.h>
#include "YALI.h"
#include "temp.h"
#include "BEEP.h"
#include "motor.h"
#include "KEYLED.h"
#include "8255.h"

#define Astep 0x01
#define Bstep 0x02
#define Cstep 0x04
#define Dstep 0x08

unsigned char dly_c;

void delay()
{
   unsigned char tt,cc,yy;

   cc = dly_c;
   tt = 0x0;
   do{
     do {
       yy = 1;
       while(yy--);
     }while(--tt);
   }while(--cc);
}

void BJmotor()
{
   PortC = 0;
   dly_c = 0x01;

      PortC = Astep+Bstep;
      delay();
      PortC = Bstep+Cstep;
      delay();
      PortC = Cstep+Dstep;
      delay();
      PortC = Dstep+Astep;
      delay();
}