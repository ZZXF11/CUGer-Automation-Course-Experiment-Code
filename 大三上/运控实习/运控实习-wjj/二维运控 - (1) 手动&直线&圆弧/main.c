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

//	int R;			//半径
//	double x_st;	//x起始坐标
//	double y_st;	//y起始坐标
//	double x_end;	//x终点坐标
//	double y_end;	//y终点坐标
	double coor = 0;	//坐标赋值变量
	unsigned char dir = '+';		//正负号标志
	unsigned char model;	//画圆还是画直线标志
	unsigned char sym = 's';	//输入终点坐标还是起点坐标标志位
	Cdt_struct Cdt_test={0.0,0.0,0.0,0.0};//直线坐标设置
	Cdt_circle circle={0,0,0,0,0,0,0,0};//圆坐标设置
//	Cdt_oval oval={0,0,0,0,0,0,0,0};//tuo圆初始化

	int x,y;
	int keynum;
	
	int flag=0;	//程序当前位置标志flag，0：主菜单。1，2，3，4：项目1~4
	int flag0=0;//存放上一次改变前的flag值
	int confirm_sign=0;//f键确定，确认键状态标志，confirm_sign=n 表示已经确认了n次
	int retreat_sign=0;//b键后退，后退键状态标志，
	int menuCiShu=80000;
	int noTuiChu=1;

	int indexX1=0,indexX2=0,indexX3=0,indexY1=0,indexY2=0,indexY3=0;//全局变量存放XY坐标值
	int indexR1=0,indexR2=0,indexR3=0, indexAng1=0, indexAng2=0,indexAng3=0;

	unsigned int SDspeed=9,CIRCLEspeed=20;
	
	

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

void Moshi_2 (void)//moshi2，画直线
{
		Display_2(indexX1,indexX2,indexX3,indexY1,indexY2,indexY3);
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
							case 0:{ if(keynum!=0x0b){indexX1=keynum;confirm_sign=1;Display_2(indexX1,indexX2,indexX3,indexY1,indexY2,indexY3);}break;}
							case 1:{ if(keynum!=0x0b){indexX2=keynum;confirm_sign=2;Display_2(indexX1,indexX2,indexX3,indexY1,indexY2,indexY3);}break;}
							case 2:{ if(keynum!=0x0b){indexX3=keynum;confirm_sign=3;Display_2(indexX1,indexX2,indexX3,indexY1,indexY2,indexY3);}break;}
							case 3:{ if(keynum!=0x0b){indexY1=keynum;confirm_sign=4;Display_2(indexX1,indexX2,indexX3,indexY1,indexY2,indexY3);}break;}
							case 4:{ if(keynum!=0x0b){indexY2=keynum;confirm_sign=5;Display_2(indexX1,indexX2,indexX3,indexY1,indexY2,indexY3);}break;}
							case 5:
										{ if(keynum!=0x0b)
											{
												indexY3=keynum;Display_2(indexX1,indexX2,indexX3,indexY1,indexY2,indexY3);
												confirm_sign=6;									
												Cdt_test.x_end= indexX1*1+indexX2*0.1+indexX3*0.01;
												Cdt_test.y_end= indexY1*1+indexY2*0.1+indexY3*0.01;
												draw_line(Cdt_test, SDspeed);
										  }
											break;
										}
							case 6: { if(keynum==0x0b){retreat_sign=1;confirm_sign=7;}break;}		
						}						
					}
			}
			if(retreat_sign==1) {retreat_sign=0;show_menu();delayms(500);break;}
		}
		indexX1=0,indexX2=0,indexX3=0,indexY1=0,indexY2=0,indexY3=0;
		confirm_sign=0;
}

void Moshi_4 (void)//moshi4，画圆
{
		Display_4(indexR1,indexR2,indexR3,indexAng1,indexAng2,indexAng3);
		delayms(100);
		while(1)
		{
			if(TestKey())
			{
				keynum=keyscan() & 0x0f;	
				if(keynum>=0 && keynum<=9)//按下的是0~9时，更新indexY的值
				{
					switch (confirm_sign)
					{
						case 0:{ indexR1=keynum;confirm_sign=1;Display_4(indexR1,indexR2,indexR3,indexAng1,indexAng2,indexAng3);break;}
						case 1:{ indexR2=keynum;confirm_sign=2;Display_4(indexR1,indexR2,indexR3,indexAng1,indexAng2,indexAng3);break;}
						case 2:{ indexR3=keynum;confirm_sign=3;Display_4(indexR1,indexR2,indexR3,indexAng1,indexAng2,indexAng3);break;}
						case 3:{ indexAng1=keynum;confirm_sign=4;Display_4(indexR1,indexR2,indexR3,indexAng1,indexAng2,indexAng3);break;}
						case 4:{ indexAng2=keynum;confirm_sign=5;Display_4(indexR1,indexR2,indexR3,indexAng1,indexAng2,indexAng3);break;}
						case 5:{ indexAng3=keynum;confirm_sign=6;Display_4(indexR1,indexR2,indexR3,indexAng1,indexAng2,indexAng3);break;}
					}
				}
				if (keyscan()==0x0b) {show_menu();delayms(500);break;}//退出模式2				
			}
			if(confirm_sign==6) 
			{
				confirm_sign=0;
				circle.angle=indexAng1*100+indexAng2*10+indexAng3*1;
				circle.radius=indexR1*1+indexR2*0.1+indexR3*0.01;
				circle.x_s=circle.radius;
				circle.y_s=0;
				circle.x_end=circle.radius;
				circle.y_end=0;
				circle.x_center=0;
				circle.y_center=0;
				draw_circle_AW(circle, CIRCLEspeed);
				break;
			}
		}
	indexR1=0,indexR2=0,indexR3=0,indexAng1=0,indexAng2=0,indexAng3=0;//参数清零
	confirm_sign=0;
	retreat_sign=0;
}

//void Moshi_4(void)
//{
//		Display_4(indexR1,indexR2,indexR3,indexAng1,indexAng2,indexAng3);
//		delayms(100);
//		while(1)
//		{
//			if(TestKey())
//			{
//				keynum=keyscan() & 0x0f;
//					if((keynum>=0&&keynum<=9)||keynum==0x0b)
//					{
//						switch (confirm_sign)
//						{
//							case 0:{ if(keynum!=0x0b){indexR1=keynum;confirm_sign=1;Display_4(indexR1,indexR2,indexR3,indexAng1,indexAng2,indexAng3);}break;}
//							case 1:{ if(keynum!=0x0b){indexR2=keynum;confirm_sign=2;Display_4(indexR1,indexR2,indexR3,indexAng1,indexAng2,indexAng3);}break;}
//							case 2:{ if(keynum!=0x0b){indexR3=keynum;confirm_sign=3;Display_4(indexR1,indexR2,indexR3,indexAng1,indexAng2,indexAng3);}break;}
//							case 3:{ if(keynum!=0x0b){indexAng1=keynum;confirm_sign=4;Display_4(indexR1,indexR2,indexR3,indexAng1,indexAng2,indexAng3);}break;}
//							case 4:{ if(keynum!=0x0b){indexAng2=keynum;confirm_sign=5;Display_4(indexR1,indexR2,indexR3,indexAng1,indexAng2,indexAng3);}break;}
//							case 5:
//										{ if(keynum!=0x0b)
//											{
//												indexAng3=keynum;Display_4(indexR1,indexR2,indexR3,indexAng1,indexAng2,indexAng3);
//												confirm_sign=6;										
//												circle.angle=indexAng1*1+indexAng2*0.1+indexAng3*0.01;
//												circle.radius=indexR1*1+indexR2*0.1+indexR3*0.01;
//												circle.x_s=circle.radius;
//												circle.y_s=0;
//												circle.x_end=circle.radius;
//												circle.y_end=0;
//												circle.x_center=0;
//												circle.y_center=0;
//												draw_circle_AW(circle, CIRCLEspeed);	
//											}
//											break;
//										}
//							case 6: { if(keynum==0x0b){retreat_sign=1;confirm_sign=7;}break;}		
//						}						
//					}
//			}
//			if(retreat_sign==1) {retreat_sign=0;show_menu();delayms(500);break;}
//		}
//		indexR1=0,indexR2=0,indexR3=0,indexAng1=0,indexAng2=0,indexAng3=0;
//		confirm_sign=0;	
//	
//}

void main()
{
  CAddr= mode;
//	Cdt_test.x_s=0;
//	Cdt_test.y_s=0;


//	circle.x_center=0;
//	circle.y_center=0;
//	circle.radius=Radius;
//	circle.x_s=circle.radius;
//	circle.y_s=0;
//	circle.x_end=circle.radius;
//	circle.y_end=0;

	show_menu();	
	delayms(1000);


//	oval.a=4;
//	oval.b=3;
//	oval.x_s=oval.a;
//	oval.y_s=0;
//	oval.x_end=oval.a;
//	oval.y_end=0;
//	oval.x_center=0;
//	oval.y_center=0;
//	
//	darw_oval(oval,20);
	
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
               case 0x0e:  {Moshi_2();break;}	//  
               //case 0x0d:  {darw_oval(oval,8);break;}   //
							 //case 0x0d:  {draw_sin(2,1,0,10);break;}   //
               case 0x0c:  {Moshi_4();break;}   //        
         }				
		}
	}
	
	
	
}
