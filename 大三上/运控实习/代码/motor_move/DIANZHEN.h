#include <reg52.h>

#define uchar unsigned char
#define uint  unsigned int
xdata unsigned char LED _at_ 0x5cff;
sbit BEEP   = P3^5 ;
xdata unsigned char PortA _at_ 0x6000 ; // Port A
unsigned char LEDMAP_1[8] =    //“ª∏ˆ¡¡£¨∆‰”‡∞µ
{
	0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f
};

void delay_1( unsigned int CNT );
void Delay1();
void delayDZ (uint t);
void BEE();
void DisplayDZtemp();
void DisplayDZdistance();