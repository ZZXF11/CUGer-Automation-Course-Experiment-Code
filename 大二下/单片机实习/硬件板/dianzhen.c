#include <reg52.h>

#define uchar unsigned char
#define uint  unsigned int
xdata unsigned char LED _at_ 0x5cff;
sbit BEEP   = P3^5 ;
//流水灯4000，8255地址6000
//************P1控制列，列地址P1*************************
//************PA控制行，行地址PortA**********************
//列选择，行数据

xdata unsigned char PortA _at_ 0x7c00;   // PA地址

//字模   每个8x8,   8字节
code uchar Font[][8] = {

/*   4    */
0x10,0x18,0x1C,0x14,0x12,0x3E,0x10,0x38,

/*-- ! --*/
0x1C,0x1C,0x1C,0x08,0x08,0x08,0x00,0x08,

/*--  同或符  --*/
/*--  宽度x高度=8x8  --*/
0x18,0x24,0x42,0x99,0x99,0x42,0x24,0x18,

/*--  方形哭脸  --*/
/*--  宽度x高度=8x8  --*/
0xFF,0x81,0xA5,0x81,0xBD,0xA5,0x81,0xFF,
 

  };

unsigned char LEDMAP_1[8] =    //一个亮，其余暗
{
	0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f
};

void delay_1( unsigned int CNT )
{
	 unsigned char i;

	 while ( CNT-- != 0)
	 	for( i=100; i != 0; --i)
			;
}

void Delay1()//蜂鸣器专用延时
{
  unsigned char i;
  for (i=0; i<200; i++);
}
	
void delayDZ (uint t)//延时子程序
{
    uint i;
    for(i=0;i<t;++i) ;
}
void BEE(){
	
	int i;
	P2=0x5f;
	P0=~P0;
	for(i=0;i<8;++i){//LED闪烁、蜂鸣器bee
		P0 =  LEDMAP_1[i];
		BEEP=0;
		Delay1();
		BEEP=1;
		Delay1();
 }
}

//********************温度报警显示主程序**************************
void DisplayDZtemp()
{
	uchar j,i;
     uchar count;
     uchar bitmask;

     //******清屏*********
     PortA=0xff;//低电平有效
     P1=0xff;//低电平有效

//--------------------------------------------------------------------------

    for(j=3; j<4; j++){              //逐个显示所选字图。j:字模库中第j个字。

      for(count =0; count <150; count ++){//每个字显示150次
				BEE();
        bitmask = 0x01;
        for(i=0;i<8;i++){               //把第j个数逐行扫描
             
//          PortA=0xff;//低电平有效//******清屏*********
//          P1=0xff;//低电平有效
                  
          P1= ~ Font[j][i];//给第i行送值（P1能锁存）          
          PortA=bitmask;//允许第一行（点亮第一行）

          delayDZ (150);
          bitmask <<= 1;               //开启下一行
        }
      }
      P1  = 0xff;
    }
}


//*********************距离报警显示主程序*****************************
void DisplayDZdistance()
{
	uchar j,i;
     uchar count;
     uchar bitmask;

     //******清屏*********
     PortA=0xff;//低电平有效
     P1=0xff;//低电平有效

//--------------------------------------------------------------------------

    for(j=1; j<2; j++){              //逐个显示所选字图。j:字模库中第j个字。
      for(count =0; count <150; count ++){//每个字显示150次
				BEE();
        bitmask = 0x01;
        for(i=0;i<8;i++){               //把第j个数逐行扫描
             
//          PortA=0xff;//低电平有效//******清屏*********
//          P1=0xff;//低电平有效
                  
          P1= ~ Font[j][i];//给第i行送值（P1能锁存）          
          PortA=bitmask;//允许第一行（点亮第一行）

          delayDZ (150);
          bitmask <<= 1;               //开启下一行
        }
      }
      P1  = 0xff;
    }
}
