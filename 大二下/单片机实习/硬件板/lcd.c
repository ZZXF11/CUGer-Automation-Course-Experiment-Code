#include <reg52.h>
//#include "key-led.h"

#define PD1  61        //  122/2 分成左右两半屏(122x32)

unsigned char initMotor = 0x00;//临界直流电机转速，默认1档
unsigned char initYALI = 0x0a; //临界压力初始值
unsigned char initTEMP = 0x1e; //临界温度初始值,30度

unsigned char Column;
unsigned char Page_ ;  // 页地址寄存器 D1,DO:页地址
unsigned char Code_ ;  // 字符代码寄存器

unsigned char Command; // 指令寄存器
unsigned char LCDData; // 数据寄存器

xdata unsigned char CWADD1 _at_ 0x1cff;   // 写指令代码地址(E1)     *****地址译码接CS3*****
xdata unsigned char DWADD1 _at_ 0x1eff;   // 写显示数据地址(E1)
xdata unsigned char CRADD1 _at_ 0x1dff;   // 读状态字地址(E1)
xdata unsigned char DRADD1 _at_ 0x1fff;   // 读显示数据地址(E1)

xdata unsigned char CWADD2 _at_ 0x3cff;   // 写指令代码地址(E2)
xdata unsigned char DWADD2 _at_ 0x3eff;   // 写显示数进地址(E2)
xdata unsigned char CRADD2 _at_ 0x3dff;   // 读状态字地址(E2)
xdata unsigned char DRADD2 _at_ 0x3fff;   // 读显示数据地址(E2)


// 1.写指令代码子程序(E1)
void WriteCommandE1()
{
  while(CRADD1 & 0x80);
  CWADD1 = Command;
}

// 2.写显示数据子程序(E1)
void WriteDataE1()
{
  while(CRADD1 & 0x80);
  DWADD1 = LCDData;
}

// 3.读显示数据子程序(E1)
void ReadDataE1()
{
  while(CRADD1 & 0x80);
  LCDData = DRADD1;
}

// 4.写指令代码子程序(E2)
void WriteCommandE2()
{
  while(CRADD2 & 0x80);
  CWADD2 = Command;
}

// 5.写显示数据子程序(E2)
void WriteDataE2()
{
  while(CRADD2 & 0x80);
  DWADD2 = LCDData;
}

// 6.读显示数据子程序(E2)
void ReadDataE2()
{
  while(CRADD2 & 0x80);
  LCDData = DRADD2;
}


void Init()  // ******初始化程序******
{
  Command = 0xe2;      
  WriteCommandE1();
  WriteCommandE2();

  Command = 0xa4;
  WriteCommandE1();
  WriteCommandE2();

  Command = 0xa9;
  WriteCommandE1();
  WriteCommandE2();

  Command = 0xa0;
  WriteCommandE1();
  WriteCommandE2();

  Command = 0xc0;
  WriteCommandE1();
  WriteCommandE2();

  Command = 0xaf;
  WriteCommandE1();
  WriteCommandE2();
}


void Clear()  // *********清屏*********
{
  unsigned char i,j;

  i = 0;
  do {

    Command = (i + 0xb8); // 页地址设置
    WriteCommandE1();
    WriteCommandE2();

    Command = 0x00;      // 列地址设置为"0"
    WriteCommandE1();
    WriteCommandE2();

    j = 0x50;            // 一页清 80个字节
    do {
      LCDData = 0x00;    // 显示数据为"0"
      WriteDataE1();
      WriteDataE2();
    }while(--j !=0);     // 页内字节清零循环

  }while(++i !=4);       // 页地址暂存器加一
                         // 显示区清零循环
}


//数字&标点符号字模库    8x16 点阵
code unsigned char DIGTAB[][16]={
/*--  00文字:  0  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,

/*--  01文字:  1  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,

/*--  02文字:  2  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x70,0x08,0x08,0x08,0x08,0xF0,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00,

/*--  03文字:  3  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x30,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x18,0x20,0x21,0x21,0x22,0x1C,0x00,

/*--  04文字:  4  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x80,0x40,0x30,0xF8,0x00,0x00,0x00,0x06,0x05,0x24,0x24,0x3F,0x24,0x24,

/*--  05文字:  5  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0xF8,0x88,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x20,0x20,0x20,0x11,0x0E,0x00,

/*--  06文字:  6  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0xE0,0x10,0x88,0x88,0x90,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x20,0x1F,0x00,

 /*--  07文字:  7  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x18,0x08,0x08,0x88,0x68,0x18,0x00,0x00,0x00,0x00,0x3E,0x01,0x00,0x00,0x00,

 /*--  08文字:  8  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00,

 /*--  09文字:  9  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0xF0,0x08,0x08,0x08,0x10,0xE0,0x00,0x00,0x01,0x12,0x22,0x22,0x11,0x0F,0x00,
 
/*--  0a文字:  :  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,
 
/*--  0b文字:  ；  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x5B,0x3B,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

 };


// 中文字模库   16x16点阵
code unsigned char CCTAB[][32] ={
/*--  00文字:  道  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x40,0x40,0x42,0xCC,0x00,0x08,0xE9,0xAA,0xB8,0xA8,0xA8,0xAA,0xE9,0x08,0x00,0x00,
0x00,0x40,0x20,0x1F,0x20,0x40,0x5F,0x4A,0x4A,0x4A,0x4A,0x4A,0x5F,0x40,0x40,0x00,

/*--  01文字:  路  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x3E,0x22,0xE2,0x22,0x3E,0x00,0x10,0x88,0x57,0x24,0x54,0x8C,0x00,0x00,0x00,
0x40,0x7E,0x40,0x3F,0x22,0x22,0x00,0x01,0xFE,0x42,0x42,0x42,0xFE,0x01,0x01,0x00,

/*--  02文字:  城  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x20,0x20,0xFF,0x20,0x20,0xF8,0x88,0x88,0x88,0x08,0xFF,0x08,0x09,0xCA,0x08,0x00,
0x10,0x30,0x1F,0x88,0x68,0x1F,0x10,0x20,0x9F,0x40,0x27,0x18,0x26,0x41,0xF0,0x00,

/*--  03文字:  公  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x80,0x40,0x20,0x18,0x06,0x80,0x00,0x07,0x18,0x20,0x40,0x80,0x00,0x00,0x00,
0x01,0x00,0x20,0x70,0x28,0x26,0x21,0x20,0x20,0x24,0x38,0x60,0x00,0x01,0x01,0x00,

/*--  04文字:  高  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x04,0x04,0x04,0x04,0xF4,0x94,0x95,0x96,0x94,0x94,0xF4,0x04,0x04,0x04,0x04,0x00,
0x00,0xFE,0x02,0x02,0x7A,0x4A,0x4A,0x4A,0x4A,0x4A,0x7A,0x02,0x82,0xFE,0x00,0x00,

/*--  05文字:  市  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x08,0x88,0x88,0x88,0x88,0x89,0xFA,0x88,0x88,0x88,0x88,0x88,0x08,0x00,0x00,
0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x10,0x20,0x1F,0x00,0x00,0x00,

/*--  06文字:  路  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x3E,0x22,0xE2,0x22,0x3E,0x00,0x10,0x88,0x57,0x24,0x54,0x8C,0x00,0x00,0x00,
0x40,0x7E,0x40,0x3F,0x22,0x22,0x00,0x01,0xFE,0x42,0x42,0x42,0xFE,0x01,0x01,0x00,

/*--  07文字:  速  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x40,0x40,0x42,0xCC,0x00,0x04,0xF4,0x94,0x94,0xFF,0x94,0x94,0xF4,0x04,0x00,0x00,
0x00,0x40,0x20,0x1F,0x20,0x48,0x44,0x42,0x41,0x5F,0x41,0x42,0x44,0x48,0x40,0x00,
//-----------------------------------------------------------------------------------------
/*--  08文字:  限  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0xFE,0x22,0x5A,0x86,0x00,0xFE,0x92,0x92,0x92,0x92,0x92,0xFE,0x00,0x00,0x00,
0x00,0xFF,0x04,0x08,0x07,0x00,0xFF,0x40,0x20,0x03,0x0C,0x14,0x22,0x41,0x40,0x00,

/*--  09文字:  人  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x3F,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x80,0x40,0x20,0x10,0x0C,0x03,0x00,0x00,0x00,0x03,0x0C,0x10,0x20,0x40,0x80,0x00,

//******************************LCD下排*******************************************
/*--  10文字:  ℃  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x06,0x09,0x09,0xE6,0xF8,0x0C,0x04,0x02,0x02,0x02,0x02,0x02,0x04,0x1E,0x00,0x00,
0x00,0x00,0x00,0x07,0x1F,0x30,0x20,0x40,0x40,0x40,0x40,0x40,0x20,0x10,0x00,0x00,

/*--  11文字:  开  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x80,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x80,0x00,
0x00,0x80,0x40,0x30,0x0F,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,

/*--  12文字:  启  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x00,0xFC,0x44,0x44,0x44,0x45,0x46,0x44,0x44,0x44,0x44,0x7C,0x00,0x00,
0x40,0x20,0x18,0x07,0x00,0xFC,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0xFC,0x00,0x00,

/*--  13文字:  空  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x0C,0x44,0x24,0x14,0x04,0x05,0x06,0x04,0x04,0x14,0x24,0x44,0x14,0x0C,0x00,
0x00,0x40,0x40,0x41,0x41,0x41,0x41,0x7F,0x41,0x41,0x41,0x41,0x40,0x40,0x00,0x00,

/*--  14文字:  调  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x40,0x42,0xCC,0x00,0x00,0xFE,0x82,0x92,0x92,0xFE,0x92,0x92,0x82,0xFE,0x00,0x00,
0x00,0x00,0x3F,0x10,0x88,0x7F,0x00,0x1E,0x12,0x12,0x12,0x5E,0x80,0x7F,0x00,0x00,

//-------------------------------------------------------------------------
//******************************************************************************************************
/*--  15文字:  项  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x08,0x08,0x08,0xF8,0x08,0x08,0x00,0xF2,0x12,0x1A,0xD6,0x12,0x12,0xF2,0x02,0x00,
0x10,0x30,0x10,0x0F,0x08,0x08,0x80,0x4F,0x20,0x18,0x07,0x10,0x20,0x4F,0x80,0x00,

/*--  文字:  目  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0xFE,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0xFE,0x00,0x00,0x00,
0x00,0x00,0xFF,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0xFF,0x00,0x00,0x00,

/*--  文字:  ：  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  车  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x08,0x88,0x48,0x28,0x18,0x0F,0xE8,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,
0x08,0x08,0x09,0x09,0x09,0x09,0x09,0xFF,0x09,0x09,0x09,0x09,0x09,0x08,0x08,0x00,

/*--  文字:  辆  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0xC8,0xB8,0x8F,0xE8,0x88,0x88,0xE2,0x22,0x22,0xFE,0x22,0xFE,0x22,0x22,0xE2,0x00,
0x08,0x18,0x08,0xFF,0x04,0x04,0xFF,0x08,0x06,0x01,0x06,0x01,0x42,0x84,0x7F,0x00,

/*--  文字:  状  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x08,0x30,0x00,0xFF,0x20,0x20,0x20,0x20,0xFF,0x20,0x20,0x22,0x2C,0x20,0x00,
0x04,0x04,0x02,0x01,0xFF,0x80,0x40,0x30,0x0E,0x01,0x06,0x18,0x20,0x40,0x80,0x00,

/*--  文字:  况  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x02,0x0C,0xC0,0x00,0x7E,0x42,0xC2,0x42,0x42,0xC2,0x42,0x7E,0x00,0x00,0x00,
0x02,0x02,0x7F,0x80,0x40,0x20,0x18,0x07,0x00,0x00,0x3F,0x40,0x40,0x40,0x70,0x00,

/*--  文字:  监  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x7E,0x00,0x00,0xFF,0x00,0x40,0x30,0x0F,0x04,0x14,0x64,0x04,0x00,0x00,
0x40,0x40,0x7E,0x42,0x42,0x7E,0x42,0x42,0x42,0x7E,0x42,0x42,0x7E,0x40,0x40,0x00,

/*--  文字:  控  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x10,0x10,0xFF,0x90,0x20,0x98,0x48,0x28,0x09,0x0E,0x28,0x48,0xA8,0x18,0x00,
0x02,0x42,0x81,0x7F,0x00,0x40,0x40,0x42,0x42,0x42,0x7E,0x42,0x42,0x42,0x40,0x00,

/*--  文字:  系  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x22,0x32,0x2A,0xA6,0xA2,0x62,0x21,0x11,0x09,0x81,0x01,0x00,0x00,0x00,
0x00,0x42,0x22,0x13,0x0B,0x42,0x82,0x7E,0x02,0x02,0x0A,0x12,0x23,0x46,0x00,0x00,

/*--  16文字:  统  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x20,0x30,0xAC,0x63,0x30,0x00,0x88,0xC8,0xA8,0x99,0x8E,0x88,0xA8,0xC8,0x88,0x00,
0x22,0x67,0x22,0x12,0x12,0x80,0x40,0x30,0x0F,0x00,0x00,0x3F,0x40,0x40,0x71,0x00,

//-------------------------------------------------------------------------------------------------------------
/*--  25文字:  作  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x80,0x60,0xF8,0x07,0x40,0x30,0x0F,0xF8,0x88,0x88,0x88,0x88,0x08,0x08,0x00,
0x01,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0xFF,0x08,0x08,0x08,0x08,0x08,0x00,0x00,

/*--  26文字:  者  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x20,0x20,0x24,0x24,0x24,0x24,0xBF,0x64,0x24,0x34,0x28,0x24,0x22,0x20,0x20,0x00,
0x10,0x08,0x04,0x02,0xFF,0x49,0x49,0x49,0x49,0x49,0x49,0xFF,0x00,0x00,0x00,0x00,

/*--  文字:  ：  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  张  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x02,0xE2,0x22,0x22,0x3E,0x80,0x80,0xFF,0x80,0xA0,0x90,0x88,0x86,0x80,0x80,0x00,
0x00,0x43,0x82,0x42,0x3E,0x00,0x00,0xFF,0x40,0x21,0x06,0x08,0x10,0x20,0x40,0x00,

/*--  文字:  宇  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x0C,0x24,0x24,0x24,0x24,0x25,0xE6,0x24,0x24,0x24,0x24,0x24,0x14,0x0C,0x00,
0x02,0x02,0x02,0x02,0x02,0x42,0x82,0x7F,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x00,

/*-- 30 文字:  一  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  31文字:  王  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x02,0x82,0x82,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x82,0x82,0x02,0x00,0x00,
0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,

/*--  文字:  珺  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x04,0x44,0x44,0xFC,0x44,0x44,0x10,0x92,0x92,0xFE,0x92,0x92,0x92,0xFE,0x10,0x00,
0x10,0x10,0x10,0x1F,0x10,0x10,0x08,0x04,0xFF,0x44,0x44,0x44,0x44,0xFC,0x00,0x00,

/*--  文字:  璟  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x04,0x44,0x44,0xFC,0x44,0x44,0x80,0xBE,0xAA,0xAA,0xEA,0xAA,0xAA,0xBE,0x80,0x00,
0x10,0x10,0x10,0x1F,0x10,0x10,0x40,0x2E,0x0A,0x8A,0xFA,0x0A,0x0A,0x2E,0x40,0x00,



 };

// *******中文显示子程序*******
void WriteCHN16x16()       //*********调用一次显示一个字*****
{
  unsigned char i,j,k;

  i = 0;
  j = 0;
  while(j<2) {
    Command = ((Page_ + j) & 0x03) | 0xb8;   // 设置页地址
    WriteCommandE1();
    WriteCommandE2();
    k = Column;                   // 列地址值
    while(k < Column + 16){
      if (k < PD1) {              // 为左半屏显示区域(E1)
        Command = k;
        WriteCommandE1();         // 设置列地址值
        LCDData = CCTAB[Code_][i]; // 取汉字字模数据
        WriteDataE1();            // 写字模数据
      } else{                     // 为右半屏显示区域(E2)
        Command = k-PD1;
        WriteCommandE2();         // 设置列地址值
        LCDData = CCTAB[Code_][i]; // 取汉字字模数据
        WriteDataE2();            // 写字模数据
      };

      i++;
      if( ++k >= PD1 * 2) break;  // 列地址是否超出显示范围
    } ;
    j++;
  };
}

// *******标点符号显示子程序*******
void WriteNUM8x16()       //*********调用一次显示一个字*****
{
  unsigned char i,j,k;
  i = 0;
  j = 0;
  while(j<2) { //***********page的数量，16行对应2个page*********
    Command = ((Page_ + j) & 0x03) | 0xb8;   // 设置页地址
    WriteCommandE1();
    WriteCommandE2();
    k = Column;                   // 列地址值
    while(k < Column + 8){        //*******取模8x16，列变成8了*******
      if (k < PD1) {              // 为左半屏显示区域(E1)
        Command = k;
        WriteCommandE1();         // 设置列地址值
        LCDData = DIGTAB[Code_][i]; // 取数字字模数据
        WriteDataE1();            // 写字模数据
      } else{                     // 为右半屏显示区域(E2)
        Command = k-PD1;
        WriteCommandE2();         // 设置列地址值
        LCDData = DIGTAB[Code_][i]; // 取数字字模数据
        WriteDataE2();            // 写字模数据
      };
      i++;
      if( ++k >= PD1 * 2) break;  // 列地址是否超出显示范围
    } ;
    j++;
  };
}


//  显示主程序
void DisplayLcd()
{  
  unsigned int A=0x03;
  Init();        //初始化  (移到主函数)
  Clear();       //清屏

//****************************LCD上排*************************************
//----------------------以下是道路部分-----------------------------------
  Page_ = 0x02; //（上排 ）    
  Column = 0x00;//列位置
  Code_ = 0x00;
  WriteCHN16x16();   //“道”

  Page_ = 0x02;      
  Column = 0x10;
  Code_ = 0x01;
  WriteCHN16x16();    //“路”

  Page_ = 0x02;       
  Column = 0x20;
  Code_ = 0x0a;
  WriteNUM8x16();     //“：”


  Page_ = 0x02;       
  Column = 0x28;
  switch (initMotor)
  {
     case 0x00:    Code_ = 0x02;break;  //1档，“城”
     case 0x01:    Code_ = 0x03;break;  //2档，“公”
     case 0x02:    Code_ = 0x04;break;  //3档，“高”
  }
  WriteCHN16x16();    //“城”、“公”、“高”


  Page_ = 0x02;       
  Column = 0x38;
  switch (initMotor)
  {
     case 0x00:    Code_ = 0x05;break;  //1档，“市”
     case 0x01:    Code_ = 0x06;break;  //2档，“路”
     case 0x02:    Code_ = 0x07;break;  //3档，“速”
  }
  WriteCHN16x16();    //“市”、“路”、“速”
 
  Page_ = 0x02;       
  Column = 0x48;
  Code_ = 0x0b;
  WriteNUM8x16();     //“ ”


//----------------------以下是载重部分-----------------------------------
  Page_ = 0x02;       
  Column = 0x50;
  Code_ = 0x08;
  WriteCHN16x16();     //“限”

  Page_ = 0x02;       
  Column = 0x60;
  switch (initYALI)
  {
     case 0x0a:    Code_ = 0x05;break;  //“5”
     case 0x0b:    Code_ = 0x07;break;  //“7”
     case 0x0c:    Code_ = 0x09;break;  //“9”
  }
  WriteNUM8x16();     //“5”、“7”、“9”

  Page_ = 0x02;       
  Column = 0x68;
  Code_ = 0x09;
  WriteCHN16x16();     //“人”



//****************************LCD下排*************************************
  Page_ = 0x00; //下排       
  Column = 0x00;
  Code_ = (initTEMP/10);
  WriteNUM8x16();       //“x”温度的十位数字

  Page_ = 0x00;        
  Column = 0x08;
  Code_ = (initTEMP%10);
  WriteNUM8x16();       //“x”温度的个位数字


  Page_ = 0x00;      
  Column = 0x10;       
  Code_ = 0x0a;
  WriteCHN16x16();       //"℃"

  Page_ = 0x00;        
  Column = 0x20;
  Code_ = 0x0b;
  WriteCHN16x16();       //"开"

   Page_ = 0x00;        
  Column = 0x30;
  Code_ = 0x0c;
  WriteCHN16x16();       //"启"

  Page_ = 0x00;     
  Column =0x40;
  Code_ = 0x0d;
   WriteCHN16x16();      //"空"

  Page_ = 0x00;      
  Column =0x50;
  Code_ = 0x0e;
  WriteCHN16x16();       //"调"
 
}

//项目名显示函数
void ShowXiangmu()
{
  unsigned int A=0x03;
  Init();        //初始化  
  Clear();       //清屏

//****************************项目：车辆状况    监控系统************************************
//-------------------------上排-----------------------------------
  Page_ = 0x02; //（上排 ）    
  Column = 0x00;//列位置
  Code_ = 0x0f;
  WriteCHN16x16();   //“项 ”

  Page_ = 0x02; 
  Column = 0x10;
  Code_ = 0x10;
  WriteCHN16x16();   //“目 ”

  Page_ = 0x02;    
  Column = 0x20;
  Code_ = 0x11;
  WriteCHN16x16();   //“：”

  Page_ = 0x02;    
  Column = 0x30;
  Code_ = 0x12;
  WriteCHN16x16();   //“车 ”

  Page_ = 0x02;     
  Column = 0x40;
  Code_ = 0x13;
  WriteCHN16x16();   //“辆 ”

    Page_ = 0x02;    
  Column = 0x50;
  Code_ = 0x14;
  WriteCHN16x16();   //“状 ”

  Page_ = 0x02;     
  Column = 0x60;
  Code_ = 0x15;
  WriteCHN16x16();   //“况 ”

//----------------------------------------------------------------------------
  Page_ = 0x00; //（下排 ）    
  Column = 0x30;
  Code_ = 0x16;
  WriteCHN16x16();   //“监 ”

   Page_ = 0x00;  
  Column = 0x40;
  Code_ = 0x17;
  WriteCHN16x16();   //“测 ”

  Page_ = 0x00;     
  Column = 0x50;
  Code_ = 0x18;
  WriteCHN16x16();   //“系 ”

  Page_ = 0x00;   
  Column = 0x60;
  Code_ = 0x19;
  WriteCHN16x16();   //“统 ”

}

//作者显示函数
void ShowZuozhe()
{
  Init();        //初始化  
  Clear();       //清屏
   //****************************作者：张宇一   王珺璟************************************
//------------------------------------上排--------------------------------------------------  
  Page_ = 0x02; //（上排 ）    
  Column = 0x00;//列位置
  Code_ = 0x1a;
  WriteCHN16x16();   //“作 ”

  Page_ = 0x02; 
  Column = 0x10;
  Code_ = 0x1b;
  WriteCHN16x16();   //“者 ”

  Page_ = 0x02;    
  Column = 0x20;
  Code_ = 0x1c;
  WriteCHN16x16();   //“：”

  Page_ = 0x02;    
  Column = 0x38;
  Code_ = 0x1d;
  WriteCHN16x16();   //“张 ”

  Page_ = 0x02;     
  Column = 0x48;
  Code_ = 0x1e;
  WriteCHN16x16();   //“宇 ”

    Page_ = 0x02;    
  Column = 0x58;
  Code_ = 0x1f;
  WriteCHN16x16();   //“一 ”

//----------------------------------------------------------------------------
  Page_ = 0x00; //（下排 ）    
  Column = 0x38;
  Code_ = 0x20;
  WriteCHN16x16();   //“王 ”

   Page_ = 0x00;  
  Column = 0x48;
  Code_ = 0x21;
  WriteCHN16x16();   //“珺 ”

  Page_ = 0x00;     
  Column = 0x58;
  Code_ = 0x22;
  WriteCHN16x16();   //“璟 ”


  
}
