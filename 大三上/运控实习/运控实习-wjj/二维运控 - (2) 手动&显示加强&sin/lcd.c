#include <reg52.h>
#include "8x16zimo_lib.c"
#include "16x16zimo_lib.c"
#include "directionArrows.c"
#include "lcd_CUG_logo.c"

#define PD1  61        //  122/2 分成左右两半屏(122x32)

;unsigned char Column;
unsigned char Page_ ;  // 页地址寄存器 D1,DO:页地址
unsigned char Code_ ;  // 字符代码寄存器

unsigned char Command; // 指令寄存器
unsigned char LCDData; // 数据寄存器

xdata unsigned char CWADD1 _at_ 0x1cff;   // 写指令代码地址(E1)（Y8）
xdata unsigned char DWADD1 _at_ 0x1eff;   // 写显示数据地址(E1)
xdata unsigned char CRADD1 _at_ 0x1dff;   // 读状态字地址(E1)
xdata unsigned char DRADD1 _at_ 0x1fff;   // 读显示数据地址(E1)

xdata unsigned char CWADD2 _at_ 0x3cff;   // 写指令代码地址(E2) (Y9)
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

//// *******122x32显示子程序*******
//void WritePicture122x32()       //*********调用一次显示一个字*****
//{
//  unsigned char i,j,k;

//  i = 0;
//  j = 0;
//  //while(j<2) {
//	while(j<4){	//用到4页就改为4*********************************************
//    Command = ((Page_ + j) & 0x03) | 0xb8;   // 设置页地址
//    WriteCommandE1();
//    WriteCommandE2();
//    k = Column;                   // 列地址值
//    while(k < Column + 122){//*****122列******************************************
//      if (k < PD1) {              // 为左半屏显示区域(E1)
//        Command = k;
//        WriteCommandE1();         // 设置列地址值
//        LCDData = CUGlogoTAB[Code_][i]; // 取汉字字模数据/**改数组****************
//        WriteDataE1();            // 写字模数据
//      } else{                     // 为右半屏显示区域(E2)
//        Command = k-PD1;
//        WriteCommandE2();         // 设置列地址值
//        LCDData = CUGlogoTAB[Code_][i]; // 取汉字字模数据/**改数组****************
//        WriteDataE2();            // 写字模数据
//      };
//      i++;
//      if( ++k >= PD1 * 2) break;  // 列地址是否超出显示范围
//    } ;
//    j++;
//  };
//}

// *******60x24显示子程序*******
void WritePicture60x24()    //*********调用一次显示一个字模*****
{
  unsigned char i,j,k;
  i = 0;
  j = 0;
	while(j<3)//用到3页就改为3***********************************
	{	
    Command = ((Page_ + j) & 0x03) | 0xb8;   //设置页地址
    WriteCommandE1();
    WriteCommandE2();
    k = Column;			// 列地址值
    while(k < Column + 60)//*****60列***************************
		{
      if (k < PD1) // 为左半屏显示区域(E1)
			{              
        Command = k;
        WriteCommandE1();         // 设置列地址值
        LCDData = CUGlogoTAB[Code_][i]; // 取汉字字模数据
        WriteDataE1();            // 写字模数据
      } 
			else			 // 为右半屏显示区域(E2)
			{                    
        Command = k-PD1;
        WriteCommandE2();         // 设置列地址值
        LCDData = CUGlogoTAB[Code_][i]; // 取汉字字模数据
        WriteDataE2();            // 写字模数据
      }
      i++;
      if( ++k >= PD1 * 2) break;  // 列地址是否超出显示范围
    } 
    j++;
  }
}


// *******32x32显示子程序*******
void WritePicture32x32()       //*********调用一次显示一个字*****
{
  unsigned char i,j,k;
  i = 0;
  j = 0;
	while(j<4){	//用到4页就改为4*********************************************
    Command = ((Page_ + j) & 0x03) | 0xb8;   // 设置页地址
    WriteCommandE1();
    WriteCommandE2();
    k = Column;                   // 列地址值
    while(k < Column + 32)//*****32列******************************************
		{
      if (k < PD1) // 为左半屏显示区域(E1)
			{              
        Command = k;
        WriteCommandE1();         // 设置列地址值
        LCDData = ArrowsTAB[Code_][i]; // 取汉字字模数据
        WriteDataE1();            // 写字模数据
      } 
			else				// 为右半屏显示区域(E2)
			{                     
        Command = k-PD1;
        WriteCommandE2();         // 设置列地址值
        LCDData = ArrowsTAB[Code_][i]; // 取汉字字模数据
        WriteDataE2();            // 写字模数据
      };
      i++;
      if( ++k >= PD1 * 2) break;  // 列地址是否超出显示范围
    } 
    j++;
  }
}



// *******16×16显示子程序*******
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
      }

      i++;
      if( ++k >= PD1 * 2) break;  // 列地址是否超出显示范围
    } 
    j++;
  }
}

// *******8×16字模显示子程序*******
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

void show_CUGlogo()
{
  Init();        //初始化  
  Clear();       //清屏
	
//  Page_ = 0x02;     
//  Column = 0x00;
//  Code_ = 0x00;
//  WritePicture122x32();   //“中国地质大学”

  Page_ = 0x02;     
  Column = 0x00;
  Code_ = 0x00;	
	WritePicture60x24();

  Page_ = 0x02;     
  Column = 0x3a;
  Code_ = 0x01;	
	WritePicture60x24();
		
}


//作者显示函数
//void show_author()
//{
//  Init();        //初始化  
//  Clear();       //清屏
//	
//  Page_ = 0x02; //（上排 ）    
//  Column = 0x00;//列位置
//  Code_ = 0x00;
//  WriteCHN16x16();   //“作 ”

//  Page_ = 0x02; 
//  Column = 0x10;
//  Code_ = 0x01;
//  WriteCHN16x16();   //“者 ”
//	
//  Page_ = 0x02; 
//  Column = 0x20;
//  Code_ = 0x02;
//  WriteCHN16x16();   //“: ”	

//  Page_ = 0x00; 	//下排
//  Column = 0x10;
//  Code_ = 0x03;
//  WriteCHN16x16();   //“茁 ”
//	
//	Page_ = 0x00; 	
//  Column = 0x20;
//  Code_ = 0x04;
//  WriteCHN16x16();   //“壮 ”

//	Page_ = 0x00; 	
//  Column = 0x30;
//  Code_ = 0x05;
//  WriteCHN16x16();   //“成· ”

//	Page_ = 0x00; 	
//  Column = 0x40;
//  Code_ = 0x06;
//  WriteCHN16x16();   //“长 ”


//	Page_ = 0x00; 	
//  Column = 0x50;
//  Code_ = 0x07;
//  WriteCHN16x16();   //“小”
//	
//	Page_ = 0x00; 	
//  Column = 0x60;
//  Code_ = 0x08;
//  WriteCHN16x16();   //“队 ”
//  
//}


void show_menu()
{
  Init();        //初始化  
  Clear();       //清屏
	
  Page_ = 0x02;     
  Column = 0x00;
  Code_ = 0x09;
  WriteCHN16x16();   //“选”

  Page_ = 0x02; 
  Column = 0x10;
  Code_ = 0x0a;
  WriteCHN16x16();   //“择”
	
  Page_ = 0x02; 
  Column = 0x20;
  Code_ = 0x0b;
  WriteCHN16x16();   //“操”
	
  Page_ = 0x02; 
  Column = 0x30;
  Code_ = 0x0c;
  WriteCHN16x16();   //“作”

  Page_ = 0x02; 
  Column = 0x40;
  Code_ = 0x02;
  WriteCHN16x16();   //“：”

	Page_ = 0x00;     
  Column = 0x07;
  Code_ = 0x0d;
  WriteCHN16x16();   //“①”
	
	Page_ = 0x00;     
  Column = 0x25;
  Code_ = 0x0e;
  WriteCHN16x16();   //“②”
	
	Page_ = 0x00;     
  Column = 0x43;
  Code_ = 0x0f;
  WriteCHN16x16();   //“③”
	
	Page_ = 0x00;     
  Column = 0x61;
  Code_ = 0x10;
  WriteCHN16x16();   //“④”
	
}

//void DisplayTest(void)	
//{  
//  Init();        //初始化  (移到主函数)
//  Clear();       //清屏
//	
//	Page_ = 0x02;     
//  Column = 0x00;
//  Code_ = 0x0d;
//  WriteCHN16x16();   //“①”
//}

//void DisplayTest2(void)	
//{  
//  Init();        //初始化  (移到主函数)
//  Clear();       //清屏
//	
//	Page_ = 0x02;     
//  Column = 0x00;
//  Code_ = 0x0e;
//  WriteCHN16x16();   //“”
//}
//void DisplayTest3(void)	//
//{  
//  Init();        //初始化  (移到主函数)
//  Clear();       //清屏
//	
//	Page_ = 0x02;     
//  Column = 0x00;
//  Code_ = 0x0f;
//  WriteCHN16x16();   //“”
//}

void Display_1(int SDspeed,int index)	//显示手动
{  
  Init();        //初始化  (移到主函数)
  Clear();       //清屏
	
	Page_ = 0x02;     
  Column = 0x00;
  Code_ = 0x0d;
  WriteCHN16x16();   //“①”
	
	Page_ = 0x02; 
  Code_ = 0x17;    
  Column = 0x10;
  WriteCHN16x16();   //“手”
	
	Page_ = 0x02;     
  Column = 0x20;
  Code_ = 0x18;
  WriteCHN16x16();   //“动”	
	
	Page_ = 0x00;     
  Column = 0x28;
  Code_ = ((106-SDspeed)/10);
  WriteNUM8x16();   //“”
	
	Page_ = 0x00;     
  Column = 0x30;
  Code_ = ((106-SDspeed)%10);
  WriteNUM8x16();   //“”

	Page_ = 0x02;     
  Column = 0x50;//*******图像右沿最多到62列，之后就输出不了**************
  switch(index)
	{
		case 0: {Code_ = 0;break;}//还没按下过
		case 2: {Code_ = 3;break;}//y-
		case 5: {Code_ = 2;break;}//x+
		case 7: {Code_ = 4;break;}//x-
		case 0x0a: {Code_ = 1;break;}//y+
		default: {Code_ = 0;break;}//按倒其他键显示无键按下图
	}
  WritePicture32x32();   //“无操作”
	
}


//void Display_2(int indexX1,int indexX2,int indexX3,int indexY1,int indexY2,int indexY3)	//画直线
//{  
//  Init();        //初始化  (移到主函数)
//  Clear();       //清屏
//	
//	Page_ = 0x02;     
//  Column = 0x00;
//  Code_ = 0x0e;
//  WriteCHN16x16();   //“②”
//		
//	Page_ = 0x02;     
//  Column = 0x10;
//  Code_ = 0x11;
//  WriteCHN16x16();   //“画”
//	
//	Page_ = 0x02;     
//  Column = 0x20;
//  Code_ = 0x12;
//  WriteCHN16x16();   //“直”
//	
//	Page_ = 0x02;     
//  Column = 0x30;
//  Code_ = 0x13;
//  WriteCHN16x16();   //“线”
//	
//	Page_ = 0x00;     
//  Column = 0x00;
//  Code_ = 0x0a;
//  WriteNUM8x16();   //“X”
//	
//	Page_ = 0x00;     
//  Column = 0x08;
//  Code_ = 0x11;
//  WriteNUM8x16();   //“=”
//	
//	Page_ = 0x00;     
//  Column = 0x10;
//	Code_ = indexX1;  //百位数字
//  WriteNUM8x16();   //
//	
//	Page_ = 0x00;     
//  Column = 0x18;
//  Code_ = indexX2;	//十位数字
//  WriteNUM8x16();   //
//	
//	Page_ = 0x00;     
//  Column = 0x20;
//  Code_ = indexX3;	//个位数字
// 	WriteNUM8x16();   //
//	
//	Page_ = 0x00;     
//  Column = 0x3c;
//  Code_ = 0x0b;
//  WriteNUM8x16();   //“Y”
//	
//	Page_ = 0x00;     
//  Column = 0x44;
//  Code_ = 0x11;
//  WriteNUM8x16();   //“=”

//	Page_ = 0x00;     
//  Column = 0x4c;
//	Code_ = indexY1;//百位数字
//	WriteNUM8x16();   //
//	//Code_ = 0xb5;//Code_>b4就全黑,b5=181；
//	
//	Page_ = 0x00;     
//  Column = 0x54;
//  Code_ = indexY2;	//十位数字
//  WriteNUM8x16();   //
//	
//	Page_ = 0x00;     
//  Column = 0x5c;
//  Code_ = 0x03;
//  Code_ = indexY3;	//个位数字
//  WriteNUM8x16();   //
//}

void Display_3(int indexA1,int indexA2,int indexA3,int indexW1,int indexW2,int indexW3)//画sin
{  
  Init();        //初始化  (移到主函数)
  Clear();       //清屏
	
	Page_ = 0x02;     
  Column = 0x00;
  Code_ = 0x0f;
  WriteCHN16x16();   //“③”
		
	Page_ = 0x02;     
  Column = 0x10;
  Code_ = 0x11;
  WriteCHN16x16();   //“画”
	
	Page_ = 0x02;     
  Column = 0x20;
  Code_ = 0x12;
 WriteNUM8x16(); //“s”
	
	Page_ = 0x02;     
  Column = 0x28;
  Code_ = 0x13;
  WriteNUM8x16();   //“i”
	
	Page_ = 0x02;     
  Column = 0x30;
  Code_ = 0x14;
  WriteNUM8x16();  //“n”
	
	Page_ = 0x00;     
  Column = 0x00;
  Code_ = 0x0e;
  WriteNUM8x16();   //“A”
	
	Page_ = 0x00;     
  Column = 0x08;
	Code_ = 0x11;			//"="
  WriteNUM8x16();   
	
	Page_ = 0x00;     
  Column = 0x10;
  Code_ = indexA1;	//
  WriteNUM8x16();   //
	
	Page_ = 0x00;     
  Column = 0x18;
  Code_ = indexA2;	//
 	WriteNUM8x16();   //
	
	Page_ = 0x00;     
  Column = 0x20;
  Code_ = indexA3;	//
 	WriteNUM8x16();   //	
	
	Page_ = 0x00;     
  Column = 0x3c;
  Code_ = 0x0f;
  WriteNUM8x16();   //“w”
	
	Page_ = 0x00;     
  Column = 0x44;
  Code_ = 0x11;
  WriteNUM8x16();   //“=”
	
	Page_ = 0x00;     
  Column = 0x4c;
	Code_ = indexW1;//
	WriteNUM8x16();   //

	Page_ = 0x00;     
  Column = 0x54;
  Code_ = indexW2;	//
  WriteNUM8x16();   //
	
	Page_ = 0x00;     
  Column = 0x5c;
  Code_ = 0x03;
  Code_ = indexW3;	//
  WriteNUM8x16();   //

}

//void Display_4(int indexR1,int indexR2,int indexR3)//画圆
//{  
//  Init();        //初始化  (移到主函数)
//  Clear();       //清屏
//	
//	Page_ = 0x02;     
//  Column = 0x00;
//  Code_ = 0x10;
//  WriteCHN16x16();   //“④”
//		
//	Page_ = 0x02;     
//  Column = 0x10;
//  Code_ = 0x11;
//  WriteCHN16x16();   //“画”
//	
//	Page_ = 0x02;     
//  Column = 0x20;
//  Code_ = 0x16;
//  WriteCHN16x16();   //“圆”
//	
//	Page_ = 0x00;     
//  Column = 0x20;
//  Code_ = 0x10;
//  WriteNUM8x16();   //“R”
//	
//	Page_ = 0x00;     
//  Column = 0x28;
//  Code_ = 0x11;
//  WriteNUM8x16();   //“=”
//	
//	Page_ = 0x00;     
//  Column = 0x4c;
//	Code_ = indexR1;//
//	WriteNUM8x16();   //
//	
//	Page_ = 0x00;     
//  Column = 0x54;
//  Code_ = indexR2;	//
//  WriteNUM8x16();   //
//	
//	Page_ = 0x00;     
//  Column = 0x5c;
//  Code_ = indexR3;	//
//  WriteNUM8x16();   //	

//}
