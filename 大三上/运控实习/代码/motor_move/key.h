#include <reg52.h>


extern xdata unsigned char PortA; // Port A
extern xdata unsigned char PortB; // Port B
extern xdata unsigned char PortC; // Port C
extern xdata unsigned char INC; 
extern xdata unsigned char IN;
extern xdata unsigned char CAddr; // ¿ØÖÆ×ÖµØÖ·
extern xdata unsigned char LED;
extern xdata unsigned char LED_Y0;




void Delay(unsigned char CNT);

unsigned char TestKey();

unsigned char KeyScan();

void KeyPro();