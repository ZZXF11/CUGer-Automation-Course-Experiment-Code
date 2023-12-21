#include <reg52.h>
#include <absacc.h>
#include "IOport.h"
#include "time.h"
#include "move.h"
//#include "support.h"
#include "lcd.c"

xdata unsigned char CAddr _at_ 0x7c03;   // 控制字地址

#define unsigned char uchar;//自定义变量类型
#define unsigned int uint; 
#define pai 3.1415926

	
	
#define mode 0x81;

	int R;			//半径
	double x_st;	//x起始坐标
	double y_st;	//y起始坐标
	double x_end;	//x终点坐标
	double y_end;	//y终点坐标
	double coor = 0;	//坐标赋值变量
	unsigned char dir = '+';		//正负号标志
	unsigned char model;	//画圆还是画直线标志
	unsigned char sym = 's';	//输入终点坐标还是起点坐标标志位
//	Cdt_struct Cdt_test={0.0,0.0,0.0,0.0};//直线坐标设置
//	Cdt_circle circle={0.0,0.0,0.0,0.0,0.0,0.0,0};//圆坐标设置
	Cdt_oval oval={0,0,0,0,0,0,0,0};//tuo圆初始化
	
	int xs;
	int ys;
	int xend;
	int yend;

	int x,y;
	int keynum;
	
	int flag=0;	//程序当前位置标志flag，0：主菜单。1，2，3，4：项目1~4
	int flag0=0;//存放上一次改变前的flag值
	int confirm_sign=0;//f键确定，确认键状态标志，confirm_sign=n 表示已经确认了n次
	int retreat_sign=0;//b键后退，后退键状态标志，
	int menuCiShu=80000;
	int noTuiChu=1;

//	int indexX1=0,indexX2=0,indexX3=0,indexY1=0,indexY2=0,indexY3=0;//全局变量存放XY坐标值
//	int indexR1=0,indexR2=0,indexR3=0;
	int indexa1=0,indexa2=0,indexa3=0,indexb1=0,indexb2=0,indexb3=0;
	unsigned int SDspeed=9;
	
	

void Moshi_1 (void)//moshi1，手动
{
		Display_1(SDspeed);
		delayms(100);
		while(noTuiChu)
		{
			shoudong();
		}
		show_menu();delayms(1000);noTuiChu=1;
}

void Moshi_3 (void)//moshi3，画椭圆
{
		Display_3(indexa1,indexa2,indexa3,indexb1,indexb2,indexb3);//画tuoyuan
		delayms(100);
		while(1)
		{
			if(TestKey())
			{
				keynum=keyscan() & 0x0f;
					if((keynum>=0&&keynum<=9)||keynum==0x0b)
					{
						switch (confirm_sign)
						{
							case 0:{ indexa1=keynum;confirm_sign=1;Display_3(indexa1,indexa2,indexa3,indexb1,indexb2,indexb3);break;}
							case 1:{ indexa2=keynum;confirm_sign=2;Display_3(indexa1,indexa2,indexa3,indexb1,indexb2,indexb3);break;}
							case 2:{ indexa3=keynum;confirm_sign=3;Display_3(indexa1,indexa2,indexa3,indexb1,indexb2,indexb3);break;}
							case 3:{ indexb1=keynum;confirm_sign=4;Display_3(indexa1,indexa2,indexa3,indexb1,indexb2,indexb3);break;}
							case 4:{ indexb2=keynum;confirm_sign=5;Display_3(indexa1,indexa2,indexa3,indexb1,indexb2,indexb3);break;}
							case 5:
										{ 
											indexb3=keynum;Display_3(indexa1,indexa2,indexa3,indexb1,indexb2,indexb3);
											confirm_sign=6;									
											oval.a=indexa1*1+indexa2*0.1+indexa3*0.01;
											oval.b=indexb1*1+indexb2*0.1+indexb3*0.01;
											oval.x_s=oval.a;
											oval.y_s=0;
											oval.x_end=oval.a;
											oval.y_end=0;
											oval.x_center=0;
											oval.y_center=0;
											darw_oval(oval,20);									
											break;
										}
							case 6: { if(keynum==0x0b){retreat_sign=1;confirm_sign=7;}break;}		
						}						
					}
			}
			if(retreat_sign==1) {retreat_sign=0;show_menu();delayms(500);break;}
		}
		indexa1=0,indexa2=0,indexa3=0,indexb1=0,indexb2=0,indexb3=0;
		confirm_sign=0;
}




void main()
{
  CAddr= mode;

	show_menu();	
	delayms(1000);
	
	while(1)
	{
		menuCiShu--;
		if(menuCiShu<0)
		{
			menuCiShu=80000;
			show_menu();
			delayms(10);
		}
		if(TestKey()==0)//没键按下
		{
			keynum=100;
		}
		else//有键按下
		{
			keynum=keyscan() & 0x0f;	
			switch (keynum)  //keynum就等于按键的数值
         {    
               case 0x0f:  {Moshi_1();break;}  //
               case 0x0e:  {break;}	//  
               case 0x0d:  {Moshi_3();break;}   //
               case 0x0c:  {break;}   //        
         }				
		}
	}
	
	
	
}
