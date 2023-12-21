#include <reg52.h>
#include <absacc.h>
#include "IOport.h"
#include "time.h"
#include "move.h"
//#include "support.h"
#include "lcd.c"

xdata unsigned char CAddr _at_ 0x7c03;   // �����ֵ�ַ

#define unsigned char uchar;//�Զ����������
#define unsigned int uint; 
#define pai 3.1415926

	
	
#define mode 0x81;

//	int R;			//�뾶
//	double x_st;	//x��ʼ����
//	double y_st;	//y��ʼ����
//	double x_end;	//x�յ�����
//	double y_end;	//y�յ�����
//	double coor = 0;	//���긳ֵ����
	unsigned char dir = '+';		//�����ű�־
	unsigned char model;	//��Բ���ǻ�ֱ�߱�־
	unsigned char sym = 's';	//�����յ����껹����������־λ

//int x,y;
	int keynum;
	
	int flag=0;	//����ǰλ�ñ�־flag��0�����˵���1��2��3��4����Ŀ1~4
	int flag0=0;//�����һ�θı�ǰ��flagֵ
	int confirm_sign=0;//f��ȷ����ȷ�ϼ�״̬��־��confirm_sign=n ��ʾ�Ѿ�ȷ����n��
	int retreat_sign=0;//b�����ˣ����˼�״̬��־��
	int menuCiShu=80000;
	int noTuiChu=1;

//	int indexX1=0,indexX2=0,indexX3=0,indexY1=0,indexY2=0,indexY3=0;//ȫ�ֱ������XY����ֵ
//	int indexR1=0,indexR2=0,indexR3=0;
	int index=0;
	int indexA1=0,indexA2=0,indexA3=0,indexW1=0,indexW2=0,indexW3=0;
	
	
	unsigned int SDspeed=6;
	
	

void Moshi_1 (void)//moshi1���ֶ�
{
		Display_1(SDspeed,index);
		delayms(100);
		while(noTuiChu)
		{
			shoudong();
		}
		show_menu();delayms(1000);noTuiChu=1;
}



void Moshi_3 (void)//moshi3����sin
{
		Display_3(indexA1,indexA2,indexA3,indexW1,indexW2,indexW3);
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
							case 0:{ indexA1=keynum;confirm_sign=1;Display_3(indexA1,indexA2,indexA3,indexW1,indexW2,indexW3);break;}
							case 1:{ indexA2=keynum;confirm_sign=2;Display_3(indexA1,indexA2,indexA3,indexW1,indexW2,indexW3);break;}
							case 2:{ indexA3=keynum;confirm_sign=3;Display_3(indexA1,indexA2,indexA3,indexW1,indexW2,indexW3);break;}
							case 3:{ indexW1=keynum;confirm_sign=4;Display_3(indexA1,indexA2,indexA3,indexW1,indexW2,indexW3);break;}
							case 4:{ indexW2=keynum;confirm_sign=5;Display_3(indexA1,indexA2,indexA3,indexW1,indexW2,indexW3);break;}
							case 5:
										{ 
											indexW3=keynum;Display_3(indexA1,indexA2,indexA3,indexW1,indexW2,indexW3);
											confirm_sign=6;									
											draw_sin((indexA1*1+indexA2*0.1+indexA3*0.01),(indexW1*1+indexW2*0.1+indexW3*0.01),0,SDspeed);										
											break;
										}
							case 6: { if(keynum==0x0b){retreat_sign=1;confirm_sign=7;}break;}		
						}						
					}
			}
			if(retreat_sign==1) {retreat_sign=0;show_menu();delayms(500);break;}
		}
		indexA1=0,indexA2=0,indexA3=0,indexW1=0,indexW2=0,indexW3=0;
		confirm_sign=0;
}

//void Moshi_4 (void)//moshi4����Բ
//{
//		Display_4(indexR1,indexR2,indexR3);
//		delayms(100);
//		while(1)
//		{
//			if(TestKey())
//			{
//				keynum=keyscan() & 0x0f;	
//				if(keynum>=0 && keynum<=9)//���µ���0~9ʱ������indexY��ֵ
//				{
//					switch (confirm_sign)
//					{
//						case 0:{ indexR1=keynum;confirm_sign=1;Display_4(indexR1,indexR2,indexR3);break;}
//						case 1:{ indexR2=keynum;confirm_sign=2;Display_4(indexR1,indexR2,indexR3);break;}
//						case 2:{ indexR3=keynum;confirm_sign=3;Display_4(indexR1,indexR2,indexR3);break;}
//					}
//				}
//				if (keyscan()==0x0b) {show_menu();delayms(500);break;}//�˳�ģʽ2				
//			}
//			if(confirm_sign==3) 
//			{
//				confirm_sign=0;
//				circle.radius=indexR1*1+indexR2*0.1+indexR3*0.01;
//				circle.x_s=circle.radius;
//				circle.x_end=circle.radius;
//				draw_circle_AW(circle, CIRCLEspeed);
//				break;
//			}
//		}
//	indexR1=0;indexR2=0;indexR3=0;//��������
//	confirm_sign=0;
//	retreat_sign=0;
//}


void main()
{
  CAddr= mode;
//	Cdt_test.x_s=0;
//	Cdt_test.y_s=0;
//	Cdt_test.x_end= 2;
//	Cdt_test.y_end= 4;
	

//	circle.x_center=0;
//	circle.y_center=0;
//	circle.radius=Radius;
//	circle.x_s=circle.radius;
//	circle.y_s=0;
//	circle.x_end=circle.radius;
//	circle.y_end=0;

	//draw_line(Cdt_test, 10);
	//draw_circle_AW(circle, CIRCLEspeed);

//	xs=0;
//	ys=0;
//	xend=3;
//	yend=6;


	
	//show_author();
	show_CUGlogo();
	delayms(1000);
	show_menu();	
	delayms(1000);
	
//	circle.radius=0.5;
//	circle.x_s=circle.radius;
//	circle.x_end=circle.radius;
//	draw_circle_AW(circle, CIRCLEspeed);

//	oval.a=4;
//	oval.b=3;
//	oval.x_s=oval.a;
//	oval.y_s=0;
//	oval.x_end=oval.a;
//	oval.y_end=0;
//	oval.x_center=0;
//	oval.y_center=0;
	
	//darw_oval(oval,20);
	
	while(1)
	{
		menuCiShu--;
		if(menuCiShu<0)
		{
			menuCiShu=80000;
			show_menu();
			delayms(10);
		}
		if(TestKey()==0)//û������
		{
			keynum=100;
		}
		else//�м�����
		{
			keynum=keyscan() & 0x0f;	
			switch (keynum)  //keynum�͵��ڰ�������ֵ
         {    
               case 0x0f:  {Moshi_1();break;} //ģʽһ���ֶ���λ
               case 0x0e:  {break;}	//ģʽ������ֱ��  
							 case 0x0d:  {Moshi_3();break;} //ģʽ��������Բ
               case 0x0c:  {break;} //ģʽ�ģ�������Բ��
							 //case 0x0b:	 {Moshi_5();break;}	//ģʽ�壺��sin
         }				
		}
	}

}
