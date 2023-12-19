#include <lcd.h>
#include <init.h>

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
//数字&标点符号字模库    8x16 点阵
code unsigned char DIGTAB[][16]={
/*--  文字:  0  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,

/*--  文字:  1  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,

/*--  文字:  2  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x70,0x08,0x08,0x08,0x08,0xF0,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00,

/*--  文字:  3  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x30,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x18,0x20,0x21,0x21,0x22,0x1C,0x00,

/*--  文字:  4  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x80,0x40,0x30,0xF8,0x00,0x00,0x00,0x06,0x05,0x24,0x24,0x3F,0x24,0x24,

/*--  文字:  5  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0xF8,0x88,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x20,0x20,0x20,0x11,0x0E,0x00,

/*--  文字:  6  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0xE0,0x10,0x88,0x88,0x90,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x20,0x1F,0x00,

/*--  文字:  7  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x18,0x08,0x08,0x88,0x68,0x18,0x00,0x00,0x00,0x00,0x3E,0x01,0x00,0x00,0x00,

/*--  文字:  8  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00,

/*--  文字:  9  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0xF0,0x08,0x08,0x08,0x10,0xE0,0x00,0x00,0x01,0x12,0x22,0x22,0x11,0x0F,0x00,

/*--  文字:  A  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0xC0,0x38,0xE0,0x00,0x00,0x00,0x20,0x3C,0x23,0x02,0x02,0x27,0x38,0x20,

/*--  文字:  B  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x08,0xF8,0x88,0x88,0x88,0x70,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x11,0x0E,0x00,

/*--  文字:  C  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0xC0,0x30,0x08,0x08,0x08,0x08,0x38,0x00,0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00,

/*--  文字:  D  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,0x20,0x3F,0x20,0x20,0x20,0x10,0x0F,0x00,

/*--  文字:  E  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x20,0x23,0x20,0x18,0x00,

/*--  文字:  F  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x00,0x03,0x00,0x00,0x00,

/*--  文字:  S  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x70,0x88,0x08,0x08,0x08,0x38,0x00,0x00,0x38,0x20,0x21,0x21,0x22,0x1C,0x00,

/*--  文字:  X  --18*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x08,0x18,0x68,0x80,0x80,0x68,0x18,0x08,0x20,0x30,0x2C,0x03,0x03,0x2C,0x30,0x20,

/*--  文字:  Y  --19*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x08,0x38,0xC8,0x00,0xC8,0x38,0x08,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,
 };


// 中文字模库   16x16点阵
code unsigned char CCTAB[][32] ={
/*--  文字:  牛  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x40,0x20,0x1E,0x10,0x10,0x10,0xFF,0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x00,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0xFF,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x00,

/*--  文字:  马  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x02,0x02,0xF2,0x82,0x82,0x82,0x82,0x82,0x82,0xFE,0x80,0x80,0x80,0x00,0x00,
0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x48,0x80,0x40,0x3F,0x00,0x00,

/*--  文字:  小  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x20,0x40,0x80,0x00,0x00,
0x08,0x04,0x03,0x00,0x00,0x40,0x80,0x7F,0x00,0x00,0x00,0x00,0x00,0x01,0x0E,0x00,

/*--  文字:  分  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x80,0x40,0x20,0x90,0x88,0x86,0x80,0x80,0x80,0x83,0x8C,0x10,0x20,0x40,0x80,0x00,
0x00,0x80,0x40,0x20,0x18,0x07,0x00,0x40,0x80,0x40,0x3F,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  队  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0xFE,0x02,0x22,0xDA,0x06,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xFF,0x08,0x10,0x88,0x47,0x20,0x18,0x07,0x00,0x07,0x18,0x20,0x40,0x80,0x00,

/*--  文字:  选  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x40,0x40,0x42,0xCC,0x00,0x50,0x4E,0xC8,0x48,0x7F,0xC8,0x48,0x48,0x40,0x00,0x00,
0x00,0x40,0x20,0x1F,0x20,0x50,0x4C,0x43,0x40,0x40,0x4F,0x50,0x50,0x5C,0x40,0x00,

/*--  文字:  择  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x10,0xFF,0x10,0x00,0x82,0x86,0x4A,0x52,0xA2,0x52,0x4A,0x86,0x80,0x80,0x00,
0x42,0x82,0x7F,0x01,0x00,0x10,0x12,0x12,0x12,0xFF,0x12,0x12,0x12,0x10,0x00,0x00,

/*--  文字:  项  --*/
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

/*--  文字:  手  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x24,0x24,0x24,0x24,0x24,0xFC,0x22,0x22,0x22,0x23,0x22,0x00,0x00,0x00,
0x02,0x02,0x02,0x02,0x02,0x42,0x82,0x7F,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x00,

/*--  文字:  动  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x40,0x44,0xC4,0x44,0x44,0x44,0x40,0x10,0x10,0xFF,0x10,0x10,0x10,0xF0,0x00,0x00,
0x10,0x3C,0x13,0x10,0x14,0xB8,0x40,0x30,0x0E,0x01,0x40,0x80,0x40,0x3F,0x00,0x00,

/*--  文字:  控  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x10,0x10,0xFF,0x90,0x20,0x98,0x48,0x28,0x09,0x0E,0x28,0x48,0xA8,0x18,0x00,
0x02,0x42,0x81,0x7F,0x00,0x40,0x40,0x42,0x42,0x42,0x7E,0x42,0x42,0x42,0x40,0x00,

/*--  文字:  制  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x40,0x50,0x4E,0x48,0x48,0xFF,0x48,0x48,0x48,0x40,0xF8,0x00,0x00,0xFF,0x00,0x00,
0x00,0x00,0x3E,0x02,0x02,0xFF,0x12,0x22,0x1E,0x00,0x0F,0x40,0x80,0x7F,0x00,0x00,

/*--  文字:  模  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x10,0xD0,0xFF,0x90,0x14,0xE4,0xAF,0xA4,0xA4,0xA4,0xAF,0xE4,0x04,0x00,0x00,
0x04,0x03,0x00,0xFF,0x00,0x89,0x4B,0x2A,0x1A,0x0E,0x1A,0x2A,0x4B,0x88,0x80,0x00,

/*--  文字:  式  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x10,0x90,0x90,0x90,0x90,0x90,0x10,0x10,0xFF,0x10,0x10,0x11,0x16,0x10,0x00,
0x00,0x20,0x60,0x20,0x3F,0x10,0x10,0x10,0x00,0x03,0x0C,0x10,0x20,0x40,0xF8,0x00,

/*--  文字:  退  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x40,0x40,0x42,0xCC,0x00,0x00,0xFF,0x49,0x49,0xC9,0x49,0x49,0x7F,0x80,0x00,0x00,
0x00,0x40,0x20,0x1F,0x20,0x40,0x5F,0x48,0x44,0x40,0x41,0x42,0x45,0x58,0x40,0x00,

/*--  文字:  出  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x7C,0x40,0x40,0x40,0x40,0xFF,0x40,0x40,0x40,0x40,0xFC,0x00,0x00,0x00,
0x00,0x7C,0x40,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x40,0xFC,0x00,0x00,

/*--  文字:  直  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x04,0x04,0xF4,0x94,0x94,0x94,0x9F,0x94,0x94,0x94,0xF4,0x04,0x04,0x00,0x00,
0x40,0x40,0x40,0x7F,0x4A,0x4A,0x4A,0x4A,0x4A,0x4A,0x4A,0x7F,0x40,0x40,0x40,0x00,

/*--  文字:  线  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x20,0x30,0xAC,0x63,0x20,0x18,0x80,0x90,0x90,0xFF,0x90,0x49,0x4A,0x48,0x40,0x00,
0x22,0x67,0x22,0x12,0x12,0x12,0x40,0x40,0x20,0x13,0x0C,0x14,0x22,0x41,0xF8,0x00,

/*--  文字:  模  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x10,0xD0,0xFF,0x90,0x14,0xE4,0xAF,0xA4,0xA4,0xA4,0xAF,0xE4,0x04,0x00,0x00,
0x04,0x03,0x00,0xFF,0x00,0x89,0x4B,0x2A,0x1A,0x0E,0x1A,0x2A,0x4B,0x88,0x80,0x00,

/*--  文字:  式  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x10,0x90,0x90,0x90,0x90,0x90,0x10,0x10,0xFF,0x10,0x10,0x11,0x16,0x10,0x00,
0x00,0x20,0x60,0x20,0x3F,0x10,0x10,0x10,0x00,0x03,0x0C,0x10,0x20,0x40,0xF8,0x00,

/*--  文字:  圆  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0xFE,0x02,0x82,0xBA,0xAA,0xAA,0xAA,0xAA,0xAA,0xBA,0x82,0x02,0xFE,0x00,0x00,
0x00,0xFF,0x40,0x4F,0x60,0x50,0x48,0x46,0x48,0x50,0x60,0x4F,0x40,0xFF,0x00,0x00,

/*--  文字:  弧  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x02,0xE2,0x22,0x22,0x3E,0x00,0xFC,0x04,0xFC,0x04,0x02,0xFE,0x03,0x02,0x00,0x00,
0x00,0x43,0x82,0x42,0xBE,0x60,0x1F,0x00,0x7F,0x28,0x10,0x61,0x0E,0x30,0x40,0x00,

/*--  文字:  模  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x10,0xD0,0xFF,0x90,0x14,0xE4,0xAF,0xA4,0xA4,0xA4,0xAF,0xE4,0x04,0x00,0x00,
0x04,0x03,0x00,0xFF,0x00,0x89,0x4B,0x2A,0x1A,0x0E,0x1A,0x2A,0x4B,0x88,0x80,0x00,

/*--  文字:  式  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x10,0x90,0x90,0x90,0x90,0x90,0x10,0x10,0xFF,0x10,0x10,0x11,0x16,0x10,0x00,
0x00,0x20,0x60,0x20,0x3F,0x10,0x10,0x10,0x00,0x03,0x0C,0x10,0x20,0x40,0xF8,0x00,
 };

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
  Code_ = 0x00;
  WriteCHN16x16();   //“牛 ”

  Page_ = 0x02; 
  Column = 0x10;
  Code_ = 0x01;
  WriteCHN16x16();   //“马 ”

  Page_ = 0x02;    
  Column = 0x20;
  Code_ = 0x02;
  WriteCHN16x16();   //“小”

  Page_ = 0x02;    
  Column = 0x30;
  Code_ = 0x03;
  WriteCHN16x16();   //“分 ”

  Page_ = 0x02;     
  Column = 0x40;
  Code_ = 0x04;
  WriteCHN16x16();   //“队 ”

}

//作者显示函数
void Show_select()
{
  Init();        //初始化  
  Clear();       //清屏
   //****************************选择项目************************************
//------------------------------------上排--------------------------------------------------  
  Page_ = 0x02; //（上排 ）    
  Column = 0x00;//列位置
  Code_ = 0x05;
  WriteCHN16x16();   //“选 ”

  Page_ = 0x02; 
  Column = 0x10;
  Code_ = 0x06;
  WriteCHN16x16();   //“择 ”

  Page_ = 0x02;    
  Column = 0x20;
  Code_ = 0x07;
  WriteCHN16x16();   //“项”

  Page_ = 0x02;    
  Column = 0x30;
  Code_ = 0x08;
  WriteCHN16x16();   //“目 ”

  Page_ = 0x02;     
  Column = 0x40;
  Code_ = 0x09;
  WriteCHN16x16();   //“： ”


//----------------------------------------------------------------------------
  Page_ = 0x00; //（下排 ）    
  Column = 0x00;
  Code_ = 0x10;
  WriteNUM8x16();   //“s ”

   Page_ = 0x00;  
  Column = 0x08;
  Code_ = 0x02;
  WriteNUM8x16();   //“2”

  Page_ = 0x04;     
  Column = 0x20;
  Code_ = 0x10;
  WriteNUM8x16();   //“s ”

  Page_ = 0x04;     
  Column = 0x28;
  Code_ = 0x06;
  WriteNUM8x16();   //“6 ”
	
	Page_ = 0x04;     
  Column = 0x40;
  Code_ = 0x10;
  WriteNUM8x16();   //“s ”
	
	Page_ = 0x04;     
  Column = 0x48;
  Code_ = 0x01;
  WriteNUM8x16();   //“1 ”
	
	Page_ = 0x04;     
  Column = 0x50;
  Code_ = 0x00;
  WriteNUM8x16();   //“0”
	
	Page_ = 0x04;     
  Column = 0x60;
  Code_ = 0x10;
  WriteNUM8x16();   //“s”
	
	Page_ = 0x04;     
  Column = 0x68;
  Code_ = 0x01;
  WriteNUM8x16();   //“1”
	
	Page_ = 0x04;     
  Column = 0x70;
  Code_ = 0x04;
  WriteNUM8x16();   //“4”
  
}

//显示手动控制
void Show_head()
{
  Init();        //初始化  
  Clear();       //清屏
   //****************************选择项目************************************
//------------------------------------上排--------------------------------------------------  
  Page_ = 0x02; //（上排 ）    
  Column = 0x00;//列位置
  Code_ = 0x0a;
  WriteCHN16x16();   
	
	Page_ = 0x02; //（上排 ）    
  Column = 0x10;//列位置
  Code_ = 0x0b;
  WriteCHN16x16();   
	
	Page_ = 0x02; //（上排 ）    
  Column = 0x20;//列位置
  Code_ = 0x0c;
  WriteCHN16x16();   
	
	Page_ = 0x02; //（上排 ）    
  Column = 0x30;//列位置
  Code_ = 0x0d;
  WriteCHN16x16();   
	
	Page_ = 0x02; //（上排 ）    
  Column = 0x40;//列位置
  Code_ = 0x0e;
  WriteCHN16x16();  
	
	Page_ = 0x02; //（上排 ）    
  Column = 0x50;//列位置
  Code_ = 0x0f;
  WriteCHN16x16();  
	
	Page_ = 0x04;     
  Column = 0x10;
  Code_ = 0x10;
  WriteNUM8x16();   //“s”
	
	Page_ = 0x04;     
  Column = 0x18;
  Code_ = 0x05;
  WriteNUM8x16();   //“5”
	
	Page_ = 0x04; //（上排 ）    
  Column = 0x28;//列位置
  Code_ = 0x10;
  WriteCHN16x16();

	Page_ = 0x04; //（上排 ）    
  Column = 0x38;//列位置
  Code_ = 0x11;
  WriteCHN16x16();  
}

//显示直线模式
void Show_str()
{
  Init();        //初始化  
  Clear();       //清屏
   //****************************选择项目************************************
//------------------------------------上排--------------------------------------------------  
  Page_ = 0x02; //（上排 ）    
  Column = 0x00;//列位置
  Code_ = 0x12;
  WriteCHN16x16();   
	
	Page_ = 0x02; //（上排 ）    
  Column = 0x10;//列位置
  Code_ = 0x13;
  WriteCHN16x16();   
	
	Page_ = 0x02; //（上排 ）    
  Column = 0x20;//列位置
  Code_ = 0x14;
  WriteCHN16x16();   
	
	Page_ = 0x02; //（上排 ）    
  Column = 0x30;//列位置
  Code_ = 0x15;
  WriteCHN16x16();     
	
	Page_ = 0x04;     
  Column = 0x00;
  Code_ = 0x11;
  WriteNUM8x16();   //“X”
	
	Page_ = 0x04;     
  Column = 0x08;
  Code_ = 0x09;
  WriteCHN16x16();   //“:”
	
	Page_ = 0x04;     
  Column = 0x18;
  Code_ = 0x00;
  WriteNUM8x16();   //“0”
	
	Page_ = 0x04;     
  Column = 0x20;
  Code_ = 0x00;
  WriteNUM8x16();   //“0”
	
	Page_ = 0x04;     
  Column = 0x28;
  Code_ = 0x00;
  WriteNUM8x16();   //“0”
	
//	Page_ = 0x04; //（上排 ）    
//  Column = 0x28;//列位置
//  Code_ = 0x10;
//  WriteCHN16x16();

//	Page_ = 0x04; //（上排 ）    
//  Column = 0x38;//列位置
//  Code_ = 0x11;
//  WriteCHN16x16();  
}

//显示圆模式
void Show_yh()
{
  Init();        //初始化  
  Clear();       //清屏
   //****************************选择项目************************************
//------------------------------------上排--------------------------------------------------  
  Page_ = 0x02; //（上排 ）    
  Column = 0x00;//列位置
  Code_ = 0x16;
  WriteCHN16x16();   
	
	Page_ = 0x02; //（上排 ）    
  Column = 0x10;//列位置
  Code_ = 0x17;
  WriteCHN16x16();   
	
	Page_ = 0x02; //（上排 ）    
  Column = 0x20;//列位置
  Code_ = 0x18;
  WriteCHN16x16();   
	
	Page_ = 0x02; //（上排 ）    
  Column = 0x30;//列位置
  Code_ = 0x19;
  WriteCHN16x16();     
	
	Page_ = 0x04;     
  Column = 0x10;
  Code_ = 0x10;
  WriteNUM8x16();   //“s”
	
	Page_ = 0x04;     
  Column = 0x18;
  Code_ = 0x05;
  WriteNUM8x16();   //“5”
	
	Page_ = 0x04; // 
  Column = 0x28;//列位置
  Code_ = 0x10;
  WriteCHN16x16();

	Page_ = 0x04; //  
  Column = 0x38;//列位置
  Code_ = 0x11;
  WriteCHN16x16();  
}