#ifndef __LED_H
#define __LED_H

#include <reg52.h>

void WriteCommandE1(void);
void WriteDataE1(void);
void ReadDataE1(void);
void WriteCommandE2(void);
void WriteDataE2(void);
void ReadDataE2(void);
void Init(void);
void Clear(void);
//void WritePicture32x32(void);	
//void WritePicture122x32();
void WriteCHN16x16(void);
void WriteNUM8x16(void); 

//void show_author(void);
void show_menu(void);

void Display_1(int SDspeed);
void Display_2(int indexX1,int indexX2,int indexX3,int indexY1,int indexY2,int indexY3);	//»­Ö±Ïß
//void Display_3(int index_x,int index_y);//»­¾ØÐÎ	
void Display_4(int indexR1,int indexR2,int indexR3,int indexAng1,int indexAng2,int indexAng3);//»­Ô²



#endif