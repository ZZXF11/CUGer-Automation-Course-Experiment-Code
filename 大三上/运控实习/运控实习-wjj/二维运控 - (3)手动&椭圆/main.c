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

	int R;			//�뾶
	double x_st;	//x��ʼ����
	double y_st;	//y��ʼ����
	double x_end;	//x�յ�����
	double y_end;	//y�յ�����
	double coor = 0;	//���긳ֵ����
	unsigned char dir = '+';		//�����ű�־
	unsigned char model;	//��Բ���ǻ�ֱ�߱�־
	unsigned char sym = 's';	//�����յ����껹����������־λ
//	Cdt_struct Cdt_test={0.0,0.0,0.0,0.0};//ֱ����������
//	Cdt_circle circle={0.0,0.0,0.0,0.0,0.0,0.0,0};//Բ��������
	Cdt_oval oval={0,0,0,0,0,0,0,0};//tuoԲ��ʼ��
	
	int xs;
	int ys;
	int xend;
	int yend;

	int x,y;
	int keynum;
	
	int flag=0;	//����ǰλ�ñ�־flag��0�����˵���1��2��3��4����Ŀ1~4
	int flag0=0;//�����һ�θı�ǰ��flagֵ
	int confirm_sign=0;//f��ȷ����ȷ�ϼ�״̬��־��confirm_sign=n ��ʾ�Ѿ�ȷ����n��
	int retreat_sign=0;//b�����ˣ����˼�״̬��־��
	int menuCiShu=80000;
	int noTuiChu=1;

//	int indexX1=0,indexX2=0,indexX3=0,indexY1=0,indexY2=0,indexY3=0;//ȫ�ֱ������XY����ֵ
//	int indexR1=0,indexR2=0,indexR3=0;
	int indexa1=0,indexa2=0,indexa3=0,indexb1=0,indexb2=0,indexb3=0;
	unsigned int SDspeed=9;
	
	

void Moshi_1 (void)//moshi1���ֶ�
{
		Display_1(SDspeed);
		delayms(100);
		while(noTuiChu)
		{
			shoudong();
		}
		show_menu();delayms(1000);noTuiChu=1;
}

void Moshi_3 (void)//moshi3������Բ
{
		Display_3(indexa1,indexa2,indexa3,indexb1,indexb2,indexb3);//��tuoyuan
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
		if(TestKey()==0)//û������
		{
			keynum=100;
		}
		else//�м�����
		{
			keynum=keyscan() & 0x0f;	
			switch (keynum)  //keynum�͵��ڰ�������ֵ
         {    
               case 0x0f:  {Moshi_1();break;}  //
               case 0x0e:  {break;}	//  
               case 0x0d:  {Moshi_3();break;}   //
               case 0x0c:  {break;}   //        
         }				
		}
	}
	
	
	
}
