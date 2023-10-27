#include <reg51.h>
#include "YALI.h"
#include "temp.h"
#include "BEEP.h"
#include "motor.h"
#include "KEYLED.h"
#include "8255.h"

#define uchar unsigned char
#define uint  unsigned int
sbit BEEP = P1^2;

//LED16x16的片选信号接主板CS3,其它数据信号,地址信号,写信号接主板的相应信号.
xdata unsigned char RowLow  _at_ 0xc002;   //行低八位地址    *绝对位置变量*
xdata unsigned char RowHigh _at_ 0xc003;   //行高八位地址
xdata unsigned char ColLow  _at_ 0xc000;   //列低八位地址
xdata unsigned char ColHigh _at_ 0xc001;   //列高八位地址

//数字字模   每个8x8点阵汉字为: 8位x1x8 = 64位, 8字节
code uchar NUMFont[][16] = {

{0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00,0x00},/*"0",0*/
{0x00,0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x38,0x08,0x00,0x00,0x00},/*"1",1*/
{0x00,0x00,0x7E,0x42,0x20,0x10,0x08,0x04,0x02,0x42,0x42,0x42,0x3C,0x00,0x00,0x00},/*"2",2*/
{0x00,0x00,0x3C,0x42,0x42,0x02,0x04,0x18,0x04,0x02,0x42,0x42,0x3C,0x00,0x00,0x00},/*"3",3*/
{0x00,0x00,0x1F,0x04,0x04,0x7F,0x44,0x24,0x24,0x14,0x0C,0x0C,0x04,0x00,0x00,0x00},/*"4",4*/
{0x00,0x00,0x38,0x44,0x42,0x02,0x02,0x44,0x78,0x40,0x40,0x40,0x7E,0x00,0x00,0x00},/*"5",5*/
{0x00,0x00,0x1C,0x22,0x42,0x42,0x42,0x62,0x5C,0x40,0x40,0x24,0x18,0x00,0x00,0x00},/*"6",6*/
{0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x08,0x08,0x04,0x04,0x42,0x7E,0x00,0x00,0x00},/*"7",7*/
{0x00,0x00,0x3C,0x42,0x42,0x42,0x24,0x18,0x24,0x42,0x42,0x42,0x3C,0x00,0x00,0x00},/*"8",8*/
{0x00,0x00,0x18,0x24,0x02,0x02,0x3A,0x46,0x42,0x42,0x42,0x44,0x38,0x00,0x00,0x00},/*"9",9*/

  };


//**************汉字字模*******************
code uchar CHNFont[][32] = {
//code uchar CHNFont[] = {
0x00,0x00,0xFC,0x1F,0x04,0x20,0x04,0x20,0x04,0x20,0x00,0x20,0x00,0x20,0x00,0x20,
0xF0,0x3F,0x10,0x20,0x10,0x20,0x10,0x00,0x10,0x00,0x10,0x00,0xF0,0x3F,0x00,0x00,/*"已",1*/
/* (16 X 16 , 宋体 )*/
0x00,0x80,0xFE,0x4F,0x00,0x58,0x00,0x28,0xFC,0x28,0x84,0x2E,0x84,0x28,0x84,0x28,
0xFC,0x08,0x08,0xFF,0x94,0x08,0x44,0x08,0x44,0x7E,0x44,0x08,0xFC,0x09,0x00,0x08,/*"超",2*/
/* (16 X 16 , 宋体 )*/
0x82,0x08,0x46,0x08,0x2A,0xF8,0x12,0x0F,0x10,0x08,0x28,0x7F,0x28,0x48,0x24,0x20,
0x24,0xFF,0x24,0x10,0x20,0x10,0xFE,0xFF,0x20,0x08,0x24,0x7F,0x28,0x08,0x20,0x08,/*"载",3*/
/* (16 X 16 , 宋体 )*/
0x00,0x00,0xFC,0x1F,0x04,0x20,0x04,0x20,0x04,0x20,0x00,0x20,0x00,0x20,0x00,0x20,
0xF0,0x3F,0x10,0x20,0x10,0x20,0x10,0x00,0x10,0x00,0x10,0x00,0xF0,0x3F,0x00,0x00,/*"已",4*/
/* (16 X 16 , 宋体 )*/

0x00,0x80,0xFE,0x4F,0x00,0x58,0x00,0x28,0xFC,0x28,0x84,0x2E,0x84,0x28,0x84,0x28,
0xFC,0x08,0x08,0xFF,0x94,0x08,0x44,0x08,0x44,0x7E,0x44,0x08,0xFC,0x09,0x00,0x08,/*"超",5*/
/* (16 X 16 , 宋体 )*/

0x00,0x00,0xFE,0x47,0x00,0x28,0x40,0x10,0x44,0x14,0x48,0x12,0x50,0x11,0xE0,0x10,
0xF8,0x13,0x48,0xF2,0x48,0x02,0xF8,0x03,0x40,0x10,0xFC,0x17,0x40,0x20,0x40,0x00,/*"速",6*/
/* (16 X 16 , 宋体 )*/

0x04,0x04,0xFC,0x27,0x44,0x24,0x44,0x24,0x44,0x24,0x44,0xE4,0xFC,0x27,0x44,0x14,
0x44,0x14,0x44,0x44,0x44,0x44,0xFC,0x87,0x40,0x10,0x40,0x10,0x40,0x20,0x40,0x00,/*"油",7*/
/* (16 X 16 , 宋体 )*/

0xFC,0x7F,0x00,0x01,0xF0,0x1F,0x00,0x01,0xF0,0x1F,0x10,0x11,0xF0,0x1F,0x10,0x11,
0xF0,0x1F,0x00,0x00,0xFE,0xFF,0x10,0x10,0xF0,0x1F,0x10,0x10,0xF0,0x1F,0x00,0x00,/*"量",8*/
/* (16 X 16 , 宋体 )*/

0x12,0x12,0x26,0x13,0x8A,0x12,0x0A,0x12,0x12,0x12,0x10,0x12,0x10,0x12,0x20,0x92,
0xFE,0x53,0x20,0x32,0x20,0x32,0x20,0x12,0x20,0x12,0xE0,0x0B,0x3C,0x08,0x08,0x08,/*"低",9*/
/* (16 X 16 , 宋体 )*/

0x10,0x02,0x28,0x22,0x08,0x32,0xF8,0x2B,0x08,0x22,0xF8,0x23,0x08,0x22,0xF8,0x23,
0x00,0x20,0xFE,0xE7,0x40,0x00,0xF8,0x03,0x40,0x20,0xFC,0x27,0x40,0x40,0x40,0x00,/*"请",10*/
0x00,0x84,0x44,0x4A,0x7C,0x22,0x44,0x22,0x44,0x12,0x44,0x12,0x44,0x12,0x44,0x12,
0x44,0x12,0x44,0x12,0x44,0x12,0x44,0xFE,0x7C,0x10,0x00,0x10,0x00,0x10,0x00,0x10,/*"加",11*/
0x04,0x04,0xFC,0x27,0x44,0x24,0x44,0x24,0x44,0x24,0x44,0xE4,0xFC,0x27,0x44,0x14,
0x44,0x14,0x44,0x44,0x44,0x44,0xFC,0x87,0x40,0x10,0x40,0x10,0x40,0x20,0x40,0x00,/*"油",12*/

  };
//*************************/
	

void delayDZ(uchar t)
{
   uchar i,j;

   for(i= t; i>0; i--){
     for(j=0; j<100; j++);
   }
}

void BEE(){
	int i;
	PortA=~PortA;
	for(i=10;i!=0;--i){//LED闪烁、蜂鸣器bee
		BEEP=0;
		Delay1();
		BEEP=1;
		Delay1();
 }
}
void DZS()//显示已超速
{
  uchar i,j;
  uchar count;
  uint bitmask;

  //清屏
  ColLow = 0xff;  //行驱动低有效
  ColHigh= 0xff;
  RowLow = 0x00;  //列驱动高有效
  RowHigh= 0x00;


    for(j=3; j<6; j++){        //j:第几个。逐个显示所有数字
      for(count =0; count <50; count ++){  //每个字显示50次
        bitmask = 0x01;
				BEE();
        for(i=0;i<16;i++){//把第j个数逐行扫描
          
          RowLow  = 0x00;    //首先清屏
          RowHigh = 0x00;

          ColLow  = ~ CHNFont[j][i*2  ];  //写出一行数据（Col送数据）//      
          ColHigh = ~ CHNFont[j][i*2+1];       
          
          RowLow  = bitmask & 0xff;    //点亮此行**显示一半屏** （Row控制点亮）
          RowHigh = bitmask >> 8;    //**显示另一半屏**

          bitmask <<= 1;               //左移位,指向下一行
          delayDZ(1);
        }
      }
      ColLow  = 0xff;
      ColHigh = 0xff;
      
    }
  
}

void DZZ()//显示已超载
{
  uchar i,j;
  uchar count;
  uint bitmask;

  //清屏
  ColLow = 0xff;  //行驱动低有效
  ColHigh= 0xff;
  RowLow = 0x00;  //列驱动高有效
  RowHigh= 0x00;


    for(j=0; j<3; j++){        //j:第几个。逐个显示所有数字
      for(count =0; count <50; count ++){  //每个字显示50次
        bitmask = 0x01;
				BEE();
        for(i=0;i<16;i++){//把第j个数逐行扫描
          
          RowLow  = 0x00;    //首先清屏
          RowHigh = 0x00;

          ColLow  = ~ CHNFont[j][i*2  ];  //写出一行数据（Col送数据）//      
          ColHigh = ~ CHNFont[j][i*2+1];       
          
          RowLow  = bitmask & 0xff;    //点亮此行**显示一半屏** （Row控制点亮）
          RowHigh = bitmask >> 8;    //**显示另一半屏**

          bitmask <<= 1;               //左移位,指向下一行
          delayDZ(1);
        }
      }
      ColLow  = 0xff;
      ColHigh = 0xff;
      
    }
  
}

void DZO()//显示油量低
{
  uchar i,j;
  uchar count;
  uint bitmask;

  //清屏
  ColLow = 0xff;  //行驱动低有效
  ColHigh= 0xff;
  RowLow = 0x00;  //列驱动高有效
  RowHigh= 0x00;


    for(j=6; j<9; j++){        //j:第几个。逐个显示所有数字
      for(count =0; count <50; count ++){  //每个字显示50次
        bitmask = 0x01;
				BEE();
        for(i=0;i<16;i++){//把第j个数逐行扫描
          
          RowLow  = 0x00;    //首先清屏
          RowHigh = 0x00;

          ColLow  = ~ CHNFont[j][i*2  ];  //写出一行数据（Col送数据）//      
          ColHigh = ~ CHNFont[j][i*2+1];       
          
          RowLow  = bitmask & 0xff;    //点亮此行**显示一半屏** （Row控制点亮）
          RowHigh = bitmask >> 8;    //**显示另一半屏**

          bitmask <<= 1;               //左移位,指向下一行
          delayDZ(1);
        }
      }
      ColLow  = 0xff;
      ColHigh = 0xff;
      
    }
  
}

void DZOO()//显示请加油
{
  uchar i,j;
  uchar count;
  uint bitmask;

  //清屏
  ColLow = 0xff;  //行驱动低有效
  ColHigh= 0xff;
  RowLow = 0x00;  //列驱动高有效
  RowHigh= 0x00;


    for(j=9; j<12; j++){        //j:第几个。逐个显示所有数字
      for(count =0; count <50; count ++){  //每个字显示50次
        bitmask = 0x01;
				BEE();
        for(i=0;i<16;i++){//把第j个数逐行扫描
          
          RowLow  = 0x00;    //首先清屏
          RowHigh = 0x00;

          ColLow  = ~ CHNFont[j][i*2  ];  //写出一行数据（Col送数据）//      
          ColHigh = ~ CHNFont[j][i*2+1];       
          
          RowLow  = bitmask & 0xff;    //点亮此行**显示一半屏** （Row控制点亮）
          RowHigh = bitmask >> 8;    //**显示另一半屏**

          bitmask <<= 1;               //左移位,指向下一行
          delayDZ(1);
        }
      }
      ColLow  = 0xff;
      ColHigh = 0xff;
      
    }
  
}