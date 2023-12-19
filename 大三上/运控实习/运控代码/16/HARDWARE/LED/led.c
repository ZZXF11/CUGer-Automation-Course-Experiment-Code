#include "led.h"
#include "delay.h"
#include <math.h>
#include <stdlib.h>
#include "usart.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
//extern const  int h;
//extern const  int l;
/*
void STEPMOTOR_Init1(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 //使能PB端口时钟
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
		
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	
	
}*/

/*
void STEPMOTOR_Init2(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PB端口时钟
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
		
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
}*/

  extern long current_x;
	extern long current_y;
	extern int speed_time;
  extern int allspeed;
	extern int mark;
	
void STEPMOTOR_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;				 //PUL1-->PB.5  DAL1 -->PB4 PUL2-->PB.7  DAL2 -->PB6端口配置

 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	
	
// GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 输出高
// GPIO_SetBits(GPIOB,GPIO_Pin_4);	
//	GPIO_SetBits(GPIOB,GPIO_Pin_7);						 //PB.5 输出高
// GPIO_SetBits(GPIOB,GPIO_Pin_6);	
//	
	
}
 


void xzz(int speed1){
	int i;
	DAL1 = 0;
	for(i=0;i<speed_time;i++){
		PUL1 = 1;
	  delay_us(speed1);
	  PUL1 = 0;
    delay_us(speed1);
	}
	current_x++;
	
	if(mark == 1 || mark == 4){
	printf("page3.t2.txt=\"%ld\"\xff\xff\xff",current_x);}
	if(mark == 2){
	printf("page1.t5.txt=\"%ld\"\xff\xff\xff",current_x);}
	if(mark == 3){
	printf("page2.t5.txt=\"%ld\"\xff\xff\xff",current_x);}
  if(mark == 5){
	printf("page4.t5.txt=\"%ld\"\xff\xff\xff",current_x);}
	if(mark == 6){
	printf("page0.t1.txt=\"%ld\"\xff\xff\xff",current_x);}
	//printf(current_x);
}


void xfz(int speed1){
	int i;
	DAL1 = 1;
	for(i=0;i<speed_time;i++){
		PUL1 = 1;
	  delay_us(speed1);
	  PUL1 = 0;
    delay_us(speed1);
	}
	current_x--;
	
	if(mark == 1||mark == 4){
	printf("page3.t2.txt=\"%ld\"\xff\xff\xff",current_x);}
	if(mark == 2){
	printf("page1.t5.txt=\"%ld\"\xff\xff\xff",current_x);}
	if(mark == 3){
	printf("page2.t5.txt=\"%ld\"\xff\xff\xff",current_x);}
	 if(mark == 5){
	printf("page4.t5.txt=\"%ld\"\xff\xff\xff",current_x);}
	if(mark == 6){
	printf("page0.t1.txt=\"%ld\"\xff\xff\xff",current_x);}
	//printf(current_x);
}

void yfz(int speed1){
	int i;
  DAL2 = 0;
	for(i=0;i<speed_time;i++){
		PUL2 = 1;
	  delay_us(speed1);
	  PUL2 = 0;
    delay_us(speed1);
	}
	current_y--;
	if(mark == 1||mark == 4){
	printf("page3.t3.txt=\"%ld\"\xff\xff\xff",current_y);}
	if(mark == 2){
	printf("page1.t7.txt=\"%ld\"\xff\xff\xff",current_y);}
	if(mark == 3){
	printf("page2.t7.txt=\"%ld\"\xff\xff\xff",current_y);}
	if(mark == 5){
	printf("page4.t7.txt=\"%ld\"\xff\xff\xff",current_y);}
	if(mark == 6){
	printf("page0.t3.txt=\"%ld\"\xff\xff\xff",current_y);}
}

void yzz(int speed1){
	int i;
	DAL2 = 1;
	for(i=0;i<speed_time;i++){
		PUL2 = 1;
	  delay_us(speed1);
	  PUL2 = 0;
    delay_us(speed1);
	}
	current_y++;
	if(mark == 1||mark == 4){
	printf("page3.t3.txt=\"%ld\"\xff\xff\xff",current_y);}
	if(mark == 2){
	printf("page1.t7.txt=\"%ld\"\xff\xff\xff",current_y);}
	if(mark == 3){
	printf("page2.t7.txt=\"%ld\"\xff\xff\xff",current_y);}
	if(mark == 5){
	printf("page4.t7.txt=\"%ld\"\xff\xff\xff",current_y);}
	if(mark == 6){
	printf("page0.t3.txt=\"%ld\"\xff\xff\xff",current_y);}
}

long lbs(long A){
	if(A<0) A=-A;
	return A;
}
int abs(int A){
	if(A<0) A=-A;
	return A;
}


int zhixianchabu(long x,long y){//输入x，y为目标位置
	int xm=0,ym=0;//当前位置与初始位置差
	int xe,ye;//判断是否到达
	
	long f=0;
	unsigned int n;//n判断x,y是否都靠近目标值
	int speed=2;
	
	xe=x-current_x;//目标与初始差
	ye=y-current_y;
	n=abs(xe)+abs(ye);
	while(n)
	{
		
		
		
		
		
		f=lbs((long)ym*xe)-lbs((long)xm*ye);
		if(f>=0){
			if(xe>xm){
				xzz(speed);//电机正转
				xm++;
				n--;
			}
			else if(xe<xm){
				xfz(speed);//电机反转
				xm--;
				n--;
			}
			else if(xe==xm){
				f=-1;
			}
		}
		else if(f<0){
			if(ye>ym){
				yzz(speed);
				ym++;
				n--;
			}
			else if(ye<ym){
				yfz(speed);
				ym--;
				n--;
			}	
		}
		//printf(current_x,current_y);
		}	
	xm=0;
	ym=0;
	return 1;
}



/*unsigned char get_xiang(int x,int,y){
	if(x>=0&&y>=0)return 1;//第一象限
	else if(x<0&&y>0)return 2;
	else if(x<0&&y<0)return 3;
	else return 4;
}*/

void circle1(int xm,int ym,int xe,int ye,int r){//xm，ym当前位置与初始值，xe,ye当前位置与终点位置
	int f;
	int speed=10;
	if(xm<xe || ym>ye){//顺
		while(xm<xe || ym>ye)//判断有无到达Xe,ye
		{
			f=xm*xm+ym*ym-r*r;
			if(f<=0)//圆内
			{
				xzz(speed);
				xm++;
				ym=ym;
			}
			else//圆外
			{
				yfz(speed);
				ym--;
				xm=xm;
			}
		}
	}
	else//逆时针
	{
		while(xm>xe || ym<ye){//判断有无过第二
			f=xm*xm+ym*ym-r*r;
			if(f<=0)//圆内
			{
				yzz(speed);
				ym++;
				xm=xm;
			}
			else
			{
				xfz(speed);
				xm--;
				ym=ym;
			}
			}
		}
	}
	
	void circle2(int xm,int ym,int xe,int ye,int r){//xm，ym当前位置与初始值，xe,ye当前位置与终点位置
	int f;
	int speed=10;
	if(xm<xe || ym<ye){//顺
		while(xm<xe || ym<ye)//判断有没有到第一象限
		{
			f=xm*xm+ym*ym-r*r;
			if(f<=0)//圆内
			{
				yzz(speed);
				ym++;
				xm=xm;
			}
			else//圆外
			{
				xzz(speed);
				xm++;
				ym=ym;
			}
		}
	}
	else//逆
	{
		while(xm>xe || ym>ye)//判断是否到第三
		{
			f=xm*xm+ym*ym-r*r;
			if(f<=0)//圆内
			{
				xfz(speed);
				xm--;
				ym=ym;
			}
			else//圆外
			{
				yfz(speed);
				ym--;
				xm=xm;
			}
		}
	}
}
void circle3(int xm,int ym,int xe,int ye,int r){//xm，ym当前位置与初始值，xe,ye当前位置与终点位置
	int f;
	int speed=10;
	if(xm>xe || ym<ye){//顺
		while(xm>xe || ym<ye)//判断有没有到第一象限
		{
			f=xm*xm+ym*ym-r*r;
			if(f<=0)//圆内
			{
				xfz(speed);
				xm--;
				ym=ym;
			}
			else//圆外
			{
				yzz(speed);
				ym++;
				xm=xm;
			}
		}
	}
	else//逆
	{
		while(xm<xe || ym>ye)//判断是否到第三
		{
			f=xm*xm+ym*ym-r*r;
			if(f<=0)//圆内
			{
				yfz(speed);
				ym--;
				xm=xm;
			}
			else//圆外
			{
				xzz(speed);
				xm++;
				ym=ym;
			}
		}
	}
}
void circle4(int xm,int ym,int xe,int ye,int r){//xm，ym当前位置与初始值，xe,ye当前位置与终点位置
	int f;
	int speed=10;
	if(xm>xe || ym>ye){//顺
		while(xm>xe || ym>ye)//判断有没有到第一象限
		{
			f=xm*xm+ym*ym-r*r;
			if(f<=0)//圆内
			{
				yfz(speed);
				ym--;
				xm=xm;
			}
			else//圆外
			{
				xfz(speed);
				xm--;
				ym=ym;
			}
			
		}
	}
	else//逆
	{
		while(xm<xe || ym<ye)//判断是否到第三
		{
			f=xm*xm+ym*ym-r*r;
			if(f<=0)//圆内
			{
				xzz(speed);
				xm++;
				ym=ym;
			}
			else//圆外
			{
				yzz(speed);
				ym++;
				xm=xm;
			}
		}
	}
}

unsigned char get_xiang(int x,int y){
	if(x>0&&y>=0)return 0;//第一象限
	else if(x<=0&&y>0)return 1;
	else if(x<0&&y<=0)return 2;
	else if(x>=0&&y<0)return 3;
}

int yuanhuchabu(int point_x,int point_y,int end_x,int end_y,int r,unsigned char direction){//direction,1表示顺，0表示逆
	int xm=current_x-point_x;//当前位置与圆心位置距离
	int ym=current_y-point_y;//
	int xe=end_x-point_x;//终点位置距离与圆心距离
	int ye=end_y-point_y;
	unsigned char end_wei=get_xiang(xe,ye);//判断终点位置位于哪个象限
	unsigned char current_wei=get_xiang(xm,ym);//当前位置位于哪个象限
	if (r - abs(xe) - abs(ye) > 10 || abs(xe) - r > 10 || abs(ye) - r > 10 || r - abs(xm) - abs(ym) > 10 || abs(xm) - r > 10 || abs(ym) - r > 10 )
	{
	 return 0;
	}
	if(direction){//顺时针
		while(current_wei!=end_wei){//不在同一象限
			switch(current_wei)
			{
				case 0:circle1(xm,ym,r,0,r);xm=r;ym=0;break;
				case 1:circle2(xm,ym,0,r,r);xm=0;ym=r;break;
				case 2:circle3(xm,ym,-r,0,r);xm=-r;ym=0;break;
				case 3:circle4(xm,ym,0,-r,r);xm=0;ym=-r;break;
			}
			current_wei=(current_wei-1)&3;//按位与，每循环一次象限减一
		}
	}
	else //逆时针
	{
		while(current_wei!=end_wei)//不在同一象限
		{
			switch(current_wei)
			{
				case 0:circle1(xm,ym,0,r,r);xm=0;ym=r;break;
				case 1:circle2(xm,ym,-r,0,r);xm=-r;ym=0;break;
				case 2:circle3(xm,ym,0,-r,r);xm=0;ym=-r;break;
				case 3:circle4(xm,ym,r,0,r);xm=r;ym=0;break;
			}
			current_wei=(current_wei+1)&3;//按位与，每循环一次象限减一
		}
	}
	switch(current_wei)//在同一象限
	{
		case 0:circle1(xm,ym,xe,ye,r);break;
		case 1:circle2(xm,ym,xe,ye,r);break;
		case 2:circle3(xm,ym,xe,ye,r);break;
		case 3:circle4(xm,ym,xe,ye,r);break;		
	}
	return 1;
}
int yuan(int point_x,int point_y,int r,int direction)
{
	int x=current_x;
	int y=current_y;
	
	if(yuanhuchabu(point_x, point_y, 2 * point_x - current_x, 2 * point_y - current_y, r, direction) == 0)
	{
		return 0;
	}
	/*long lenth_1=0,lenth=0;
	int x=current_x;
	int y=current_y;
	long sin_yuan=0,cos_yuan=0;//初始与圆弧最左端角度
	int x_zhi=0;
	int x_1;
	lenth_1=(long)(point_x-r)*(point_x-r)+(long)point_y*+point_y;
	lenth=sqrt(lenth_1);//初始与圆最左端距离
	sin_yuan=(point_x-r)/lenth;
	cos_yuan=point_y/lenth;
	x_1=(int)(point_x-lenth*sin_yuan);//圆弧最左端x位置
	
	zhixianchabu(x_1,point_y);//直线运动到圆弧最左端*/
	yuanhuchabu(point_x,point_y,x,y,r,direction);//作圆运动
	
	if(current_x >x){//避免画圆后没到原出发点
			while(current_x != x){	
			xfz(allspeed);
			}
	}
	if(current_x <x){
			while(current_x != x){	
			xzz(allspeed);
			}
	
	}
	
	if(current_y >y){
			while(current_y != y){	
			yfz(allspeed);
			}
	}
	if(current_y <y){
			while(current_y != y){	
			yzz(allspeed);
			}
	}
	
	
	
	return 1;
}
//画小车程序
void draw_car()
{	
	//zhixianchabu(0,0);
	zhixianchabu(40,0);
	yuan(40,-15,15,1);
	zhixianchabu(110,0);
	yuan(110,-15,15,1);
	zhixianchabu(150,0);
	zhixianchabu(150,31);
	zhixianchabu(110,30);
	yuanhuchabu(80,12,50,30,34,0);
	zhixianchabu(0,15);
	yuanhuchabu(50,7,0,0,50,0);
	return;
}



void sanjiao(int A,int w,int b){

	int xm,ym;
	int xe1=-1,ye1=-1;//存放之前的坐标
	int flag=1;//判断斜率
	int ye;
	A=1;
	w=1;
	b=0;
	
	while(current_x!=100){
	xm=current_x;
	ym=A*sin(w*xm+b);
	ye=current_y;
	flag=(ym-ye1)/(xm-xe1);
	if(flag>=0){
	if(ym>ye){//正向
		yzz(2);
	}
	if(ym<=ye){
		xzz(2);
	}
	}
	else{
	if(ye>ym){
		yfz(2);
	}
	if(ye<ym){
		xzz(2);
	}
	}
	xe1=xm;
	ye1=ym;
	}	
}















































//void STEPMOVE(int time1,int time2){

//int time;
//int case1;
//	if(time1>=time2){
//		case1 =1;
//		time = time2;
//	}
//	else{
//	time= time1;
//	case1 = 2;
//	}
//	for(;time>0;time--){
//  PUL1 = 1;
//	PUL2 = 1;
//	delay_us(700);
//	PUL1 = 0;
//	PUL2 = 0;
//  delay_us(700);
//  }
//	if(case1 == 1){
//	time = time1-time2;
//	for(;time>0;time--){
//  PUL1 = 1;
//	delay_us(700);
//	PUL1 = 0;
//  delay_us(700);
//  //GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5);
//	
//}
//	}
//	else{
//	time = time2-time1;
//	for(;time>0;time--){
//  PUL1 = 1;
//	delay_us(700);
//	PUL1 = 0;
//  delay_us(700);
//  //GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5);
//	
//}
//	
//	}
//}





/*****

void STEPMOTORV1(int time){

for(;time>0;time--){
  PUL1 = 1;
	delay_us(300);
	PUL1 = 0;
  delay_us(300);
  //GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5);
	
}
}


void STEPMOTORV2(int time2){

for(;time2>0;time2--){
	PUL2 = 1;
	delay_us(300);
	PUL2 = 0;
  delay_us(300);
}
}




void STEPMOTORV11(int time){

for(;time>0;time--){
  PUL1 = 1;
	delay_us(700);
	PUL1 = 0;
  delay_us(700);
  //GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5);
	
}
}


void STEPMOTORV22(int time2){

for(;time2>0;time2--){
	PUL2 = 1;
	delay_us(1000);
	PUL2 = 0;
  delay_us(1000);
}
}





















double maichong(double x){//根据位移量换算得脉冲

	double maic = 0;
	maic = (1000/11.9)*x;
	return maic;
}

int getdirection(double x1,double y1,double x2,double y2){
	int dir;
	if(((x2+10)*(x2+10)+(h+10-y2)*(h+10-y2)-(x1+10)*(x1+10)-(h+10-y1)*(h+10-y1))>= 0){//左侧放线
		
	   if(((l-x2+10)*(l-x2+10)+(h+10-y2)*(h+10-y2)-(h+10-y1)*(h+10-y1)-(l-x1+10)*(l-x1+10))>=0){//右侧放线
	
				dir = 1;//左放右放
			}
	
	  else{
		
		    dir = 2;//左放右收
			}
	
	
		
	}

	else {//左侧收线
	
			if(((l-x2+10)*(l-x2+10)+(h+10-y2)*(h+10-y2)-(h+10-y1)*(h+10-y1)-(l-x1+10)*(l-x1+10))>=0){//右侧放线
	
				dir = 3;//左收右方
			}
	
	    else{
		
		    dir = 4;//左收右收
			}
	}
	
  return dir;
}



//void STEPMOTORV(int timel,int timer){
//	int min;
//	int biaozhi=0;
//	int next;
//	if(timel>=timer){
//		min = timer;
//		biaozhi = 1;
//	}
//	else {
//		min = timel;
//		biaozhi = 2;
//	}
//for(;min>0;min--){
//  PUL1 = 1;
//	PUL2 = 1;
//	delay_us(300);
//	PUL1 = 0;
//	PUL2 = 0;
//  delay_us(300);
//  //GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5);
//}

//if(biaozhi == 1){
//	next = timel - min;
//	for(;next>0;next--){
//  PUL1 = 1;
//	delay_us(300);
//	PUL1 = 0;
//  delay_us(300);
//  //GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5);
//}
//	if(biaozhi == 2){
//	next = timer - min;
//	for(;next>0;next--){
//  PUL2 = 1;
//	delay_us(300);
//	PUL2 = 0;
//  delay_us(300);
//  //GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5);
//}

//}
//}
//}
void GO1(double left_move,double right_move,int direction){

if(direction == 1){//左放右放
		DAL2 = 0;
	  DAL1 = 1;
	  STEPMOTORV11(left_move);
	  STEPMOTORV22(right_move);
	}
	else if(direction == 2){//左放右收
		
		DAL2 = 1;
	  DAL1 = 1;
	  STEPMOTORV11(left_move);
	  STEPMOTORV22(right_move);
	
	
	}
	else if(direction == 3){//左收右方
		
		DAL2 = 0;
	  DAL1 = 0;
	  STEPMOTORV11(left_move);
	  STEPMOTORV22(right_move);
	
	
	}
	else if(direction == 4){//左收右收
		DAL2 = 1;
	  DAL1 = 0;
	  STEPMOTORV11(left_move);
	  STEPMOTORV22(right_move);
	
	}





}

void GO(double left_move,double right_move,int direction){
	
	if(direction == 1){//左放右放
		DAL2 = 0;
	  DAL1 = 1;
	  STEPMOTORV1(left_move);
	  STEPMOTORV2(right_move);
	}
	else if(direction == 2){//左放右收
		
		DAL2 = 1;
	  DAL1 = 1;
	  STEPMOTORV1(left_move);
	  STEPMOTORV2(right_move);
	
	
	}
	else if(direction == 3){//左收右方
		
		DAL2 = 0;
	  DAL1 = 0;
	  STEPMOTORV1(left_move);
	  STEPMOTORV2(right_move);
	
	
	}
	else if(direction == 4){//左收右收
		DAL2 = 1;
	  DAL1 = 0;
	  STEPMOTORV1(left_move);
	  STEPMOTORV2(right_move);
	
	}
}

double leftmove(double x1,double y1,double x2,double y2){
	double i;	
	i = sqrt((x2+10)*(x2+10)+(h+10-y2)*(h+10-y2))-sqrt((x1+10)*(x1+10)+(h+10-y1)*(h+10-y1));
	if(i>=0){return i;}
	else{return -i;}
	
}
double rightmove(double x1,double y1,double x2,double y2){
	double i;	
	i = sqrt((l-x2+10)*(l-x2+10)+(h+10-y2)*(h+10-y2))-sqrt((h+10-y1)*(h+10-y1)+(l-x1+10)*(l-x1+10));
	if(i>=0){return i;}
	else{return -i;}
	
}
void go_straight1(double x1,double y1,double x2,double y2){

  double q,w,e,r;
	int diec;
	double lef1;
	double rig1;
	int j = 0;
	double left_maichong,right_maichong;
	int i;
	int n;
	i = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
	n = i/20;
	q = x1;
	w = y1;
	for(;j <n;j++){
		e = x1+(j+1)*(x2-x1)/n;
		r = y1+(j+1)*(y2-y1)/n;
		//((y2-y1)/(x2-x1))*(x1+(j+1)*(x2-x1)/100)+(x2*y1-x1*y2)/(x2-x1);  
		diec = getdirection(q,w,e,r);
		lef1 = leftmove(q,w,e,r);
		rig1 = rightmove(q,w,e,r);
		
		left_maichong = maichong(lef1);
		right_maichong = maichong(rig1);
		GO(left_maichong,right_maichong,diec);
	//printf("zuomaichong%f\r\n",left_maichong);
   // printf("youmaichong%f\r\n",right_maichong);
		printf("q:%.1f\r\n",q);
		printf("w:%.1f\r\n",w);
		//printf("youmaichong%f\r\n",q);
		q = e;
		w = r;
	}
    delay_ms(3000);

}
void go_straight(double x1,double y1,double x2,double y2){//直线行驶
  double q,w,e,r;
	int diec;
	double lef1;
	double rig1;
	int j = 0;
	double left_maichong,right_maichong;
	int i;
	int n;
	i = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
	n = i/20;
	q = x1;
	w = y1;
  
	for(;j <n;j++){
		
		e = x1+(j+1)*(x2-x1)/n;
		r = y1+(j+1)*(y2-y1)/n;
		//((y2-y1)/(x2-x1))*(x1+(j+1)*(x2-x1)/100)+(x2*y1-x1*y2)/(x2-x1);  
		diec = getdirection(q,w,e,r);
		lef1 = leftmove(q,w,e,r);
		rig1 = rightmove(q,w,e,r);
		
		left_maichong = maichong(lef1);
		right_maichong = maichong(rig1);
		GO(left_maichong,right_maichong,diec);
	//printf("zuomaichong%f\r\n",left_maichong);
   // printf("youmaichong%f\r\n",right_maichong);
		printf("q:%.1f\r\n",q);
		printf("w:%.1f\r\n",w);
		//printf("youmaichong%f\r\n",q);
		q = e;
		w = r;
	}
	
	while(1);

}



 void move_quickl(double x1,double y1,double x2,double y2){
	int diec;
	double lef1;
	double rig1;
	double left_maichong,right_maichong;
	lef1 = leftmove(x1,y1,x2,y2);
  rig1 = rightmove(x1,y1,x2,y2);
	diec = getdirection(x1,y1,x2,y2);
	left_maichong = maichong(lef1);
	right_maichong = maichong(rig1);
	GO(left_maichong,right_maichong,diec);
}



void go_circle(double x1,double y1,double x2,double y2){
double q,w,e,r;
	int diec;
	double lef1;
	double rig1;
	int j =1;
	int k =1;
  double left_maichong,right_maichong;

  go_straight1(x1,y1,x2-25,y2);
    
	q =x2-25;
	w = y2;

for(;j<=400;j++){//step2    前1cm
		
		e = x2 - 25 + j*50/400;
	  r = y2 + sqrt(abs(625 - (j*50/400-25)*(j*50/400-25)));
		
		diec = getdirection(q,w,e,r);
		lef1 = leftmove(q,w,e,r);
		rig1 = rightmove(q,w,e,r);
		
		left_maichong = maichong(lef1);
		right_maichong = maichong(rig1);
	
		GO1(left_maichong,right_maichong,diec);
		
		q = e;
		w = r;
	}



















}













//////void go_circle(double x1,double y1,double x2,double y2){

//////  //第一步，走到目标圆最左侧点
//////	//第二步，走上半圆到达最右侧
//////	//第三步，走下半圆回到最左侧
//////	double q,w,e,r;
//////	int diec;
//////	double lef1;
//////	double rig1;
//////	int j =1;
//////	int k =1;
//////	int j1 =1;
//////	int k1 =1;
//////	int j2 =1;
//////	int k2 =1;
//////	int j3 =1;
//////	int k3 =1;
//////	int j4 =1;
//////	int k4 =1;
//////	int j5 =1;
//////	int k5 =1;
//////	
//////	
//////	int p =1;
//////	int p1 = 1;
//////	double left_maichong,right_maichong;
//////	
//////	q = x2-25;
//////	w = y2;
//////	
//////	go_straight1(x1,y1,x2-25,y2);
////////	diec = getdirection(x1,y1,x2-25,y2);
////////	lef1 = leftmove(x1,y1,x2-25,y2);
////////	rig1 = rightmove(x1,y1,x2-25,y2);	
////////	left_maichong = maichong(lef1);
////////	right_maichong = maichong(rig1);
////////	GO(left_maichong,right_maichong,diec);//step1
//////	//delay_ms(1000);delay_ms(1000);delay_ms(1000);
//////	for(;j<=100;j++){//step2    前1cm
//////		
//////		e = x2 - 25 + j*1/100;
//////	  r = y2 + sqrt(abs(625 - (j*1/100-25)*(j*1/100-25)));
//////		
//////		diec = getdirection(q,w,e,r);
//////		lef1 = leftmove(q,w,e,r);
//////		rig1 = rightmove(q,w,e,r);
//////		
//////		left_maichong = maichong(lef1);
//////		right_maichong = maichong(rig1);
//////	
//////		GO1(left_maichong,right_maichong,diec);
//////		
//////		q = e;
//////		w = r;
//////	}
//////			
//////		for(;j1<=100;j1++){//step2    1-5
//////		
//////		e = x2 - 24 + j1*4/100;
//////	  r = y2 + sqrt(abs(625 - (j1*4/100-24)*(j1*4/100-24)));
//////		
//////		diec = getdirection(q,w,e,r);
//////		lef1 = leftmove(q,w,e,r);
//////		rig1 = rightmove(q,w,e,r);
//////		
//////		left_maichong = maichong(lef1);
//////		right_maichong = maichong(rig1);
//////		
//////		
//////		GO1(left_maichong,right_maichong,diec);
//////		
//////		q = e;
//////		w = r;
//////	}
//////		for(;j2<=100;j2++){//step2    5-10
//////		
//////		e = x2 - 20 + j2*5/100;
//////	  r = y2 + sqrt(abs(625 - (j2*5/100-20)*(j2*5/100-20)));
//////		
//////		diec = getdirection(q,w,e,r);
//////		lef1 = leftmove(q,w,e,r);
//////		rig1 = rightmove(q,w,e,r);
//////		
//////		left_maichong = maichong(lef1);
//////		right_maichong = maichong(rig1);
//////		
//////		
//////		GO1(left_maichong,right_maichong,diec);
//////		
//////		q = e;
//////		w = r;
//////	}
//////		for(;p<=250;p++){//step2    10-40
//////		
//////		e = x2 - 15 + j2*30/250;
//////	  r = y2 + sqrt(abs(625 - (j2*30/250-15)*(j2*30/250-15)));
//////		
//////		diec = getdirection(q,w,e,r);
//////		lef1 = leftmove(q,w,e,r);
//////		rig1 = rightmove(q,w,e,r);
//////		
//////		left_maichong = maichong(lef1);
//////		right_maichong = maichong(rig1);
//////		
//////		
//////		GO1(left_maichong,right_maichong,diec);
//////		
//////		q = e;
//////		w = r;
//////	}
//////	  for(;j3<=100;j3++){//step2    40-45
//////		
//////		e = x2 + 15 + j3*5/100;
//////	  r = y2 + sqrt(abs(625 - (j3*5/100+15)*(j3*5/100+15)));
//////		
//////		diec = getdirection(q,w,e,r);
//////		lef1 = leftmove(q,w,e,r);
//////		rig1 = rightmove(q,w,e,r);
//////		
//////		left_maichong = maichong(lef1);
//////		right_maichong = maichong(rig1);
//////		
//////		
//////		GO1(left_maichong,right_maichong,diec);
//////		
//////		q = e;
//////		w = r;
//////	}
//////	for(;j4<=100;j4++){//step2    45-49
//////		
//////		e = x2 + 20 + j4*4/100;
//////	  r = y2 + sqrt(abs(625 - (20 + j4*4/100)*(20 + j4*4/100)));
//////		
//////		diec = getdirection(q,w,e,r);
//////		lef1 = leftmove(q,w,e,r);
//////		rig1 = rightmove(q,w,e,r);
//////		
//////		left_maichong = maichong(lef1);
//////		right_maichong = maichong(rig1);
//////		
//////		
//////		GO1(left_maichong,right_maichong,diec);
//////		
//////		q = e;
//////		w = r;
//////	}
//////	for(;j5<=100;j5++){//step2    last
//////		
//////		e = x2 +29 + j5*1/100;
//////	  r = y2 + sqrt(abs(625 - (29 + j5*1/100)*(29 + j5*1/100)));
//////		
//////		diec = getdirection(q,w,e,r);
//////		lef1 = leftmove(q,w,e,r);
//////		rig1 = rightmove(q,w,e,r);
//////		
//////		left_maichong = maichong(lef1);
//////		right_maichong = maichong(rig1);
//////	
//////		GO1(left_maichong,right_maichong,diec);
//////		
//////		q = e;
//////		w = r;
//////	}
//////	
//////	
//////	
//////	delay_ms(1000);delay_ms(1000);
//////	
//////	
//////	
//////	
//////	
//////	
//////	
//////	
//////	
//////	
//////	
//////	for(;k<=100;k++){//step3   //50-49
//////		
//////		
//////		
//////		
//////	  e = x2 + 25- k/100;
//////	  r = y2 - sqrt(abs(625 - (25-k/100)*(25-k/100)));
//////		
//////		diec = getdirection(q,w,e,r);
//////		lef1 = leftmove(q,w,e,r);
//////		rig1 = rightmove(q,w,e,r);
//////		
//////		left_maichong = maichong(lef1);
//////		right_maichong = maichong(rig1);
//////		
//////		
//////		GO1(left_maichong,right_maichong,diec);
//////		
//////		q = e;
//////		w = r;
//////	
//////	}
//////	
//////	
//////	for(;k1<=100;k1++){//step3   //49-45
//////		
//////		
//////	  e = x2 + 24 - k1*4/100;
//////	  r = y2 - sqrt(abs(625 - (25-k1*4/100)*(25-k1*4/100)));
//////		
//////		diec = getdirection(q,w,e,r);
//////		lef1 = leftmove(q,w,e,r);
//////		rig1 = rightmove(q,w,e,r);
//////		
//////		left_maichong = maichong(lef1);
//////		right_maichong = maichong(rig1);
//////		
//////		
//////		GO1(left_maichong,right_maichong,diec);
//////		
//////		q = e;
//////		w = r;
//////	
//////	}
//////	for(;k2<=100;k2++){//step3   //45-40
//////		
//////		
//////	  e = x2 + 20- k2*5/100;
//////	  r = y2 - sqrt(abs(625 - (20-k2*5/100)*(20-k2*5/100)));
//////		
//////		diec = getdirection(q,w,e,r);
//////		lef1 = leftmove(q,w,e,r);
//////		rig1 = rightmove(q,w,e,r);
//////		
//////		left_maichong = maichong(lef1);
//////		right_maichong = maichong(rig1);
//////		
//////		
//////		GO1(left_maichong,right_maichong,diec);
//////		
//////		q = e;
//////		w = r;
//////	
//////	}
//////	for(;k3<=250;k3++){//step3   //40-10
//////		
//////		
//////	  e = x2 + 15 - k3*30/250;
//////	  r = y2 - sqrt(abs(625 - (15 - k3*30/250)*(15 - k3*30/250)));
//////		
//////		diec = getdirection(q,w,e,r);
//////		lef1 = leftmove(q,w,e,r);
//////		rig1 = rightmove(q,w,e,r);
//////		
//////		left_maichong = maichong(lef1);
//////		right_maichong = maichong(rig1);
//////		
//////		
//////		GO1(left_maichong,right_maichong,diec);
//////		
//////		q = e;
//////		w = r;
//////	
//////	}
//////	for(;k4<=100;k4++){//step3   //10-5
//////		
//////		
//////	  e = x2 - 15 - k4*5/100;
//////	  r = y2 - sqrt(abs(625 - (15 - k4*5/100)*(15 - k4*5/100)));
//////		
//////		diec = getdirection(q,w,e,r);
//////		lef1 = leftmove(q,w,e,r);
//////		rig1 = rightmove(q,w,e,r);
//////		
//////		left_maichong = maichong(lef1);
//////		right_maichong = maichong(rig1);
//////		
//////		GO1(left_maichong,right_maichong,diec);
//////		
//////		q = e;
//////		w = r;
//////	
//////	}
//////	
//////	for(;k5<=100;k5++){//step3   //5-1
//////		
//////		
//////	  e = x2 - 20 - k5*4/100;
//////	  r = y2 - sqrt(abs(625 - (20+k5*4/100)*(20+k5*4/100)));
//////		
//////		diec = getdirection(q,w,e,r);
//////		lef1 = leftmove(q,w,e,r);
//////		rig1 = rightmove(q,w,e,r);
//////		
//////		left_maichong = maichong(lef1);
//////		right_maichong = maichong(rig1);
//////		
//////		GO1(left_maichong,right_maichong,diec);
//////		
//////		q = e;
//////		w = r;
//////	
//////	}
//////	for(;p1<=100;p1++){//step3   //5-1
//////		
//////		
//////	  e = x2 - 24 - p1*1/100;
//////	  r = y2 - sqrt(abs(625 - (24 + p1*1/100)*(24 + p1*1/100)));
//////		
//////		diec = getdirection(q,w,e,r);
//////		lef1 = leftmove(q,w,e,r);
//////		rig1 = rightmove(q,w,e,r);
//////		
//////		left_maichong = maichong(lef1);
//////		right_maichong = maichong(rig1);
//////		
//////		GO1(left_maichong,right_maichong,diec);
//////		
//////		q = e;
//////		w = r;
//////	
//////	}
//////	
//////	
//////	
//////  while(1);


//////}
	
	
//			
//	 e = x2 - 25 + j/8;
//	  r = y2 + sqrt(abs(625 - (j/8-25)*(j/8-25) ));
//		
//		diec = getdirection(q,w,e,r);
//		lef1 = leftmove(q,w,e,r);
//		rig1 = rightmove(q,w,e,r);
//		
//		left_maichong = maichong(lef1);
//		right_maichong = maichong(rig1);
//		
//		
//		GO(left_maichong,right_maichong,diec);
//		
//		q = e;
	//	w = r;
	
	
	





//u16 *getmove(u16 x_move,u16 y_move){
//	
//	static u16 a1[2];
//	u16 x,y;
//	x = y =0;
//if(x_move >= 0&& y_move >= 0){//向右上
//  DAL1 = 1;
//	DAL2 = 1;
//	
//	//这里写通过移动值计算脉冲数
//	
//	a1[0]= x;
//	a1[1]=y;
//	
//	
//}

//else if(x_move >= 0&& y_move <= 0){//向右下

//  DAL1 = 0;
//	DAL2 = 1;
//	
//	//这里写通过移动值计算脉冲数
//	
//	a1[0]= x;
//	a1[1]=y;
//}
//else if(x_move <= 0&& y_move >= 0){//向左上

//  DAL1 = 1;
//	DAL2 = 0;
//	
//	//这里写通过移动值计算脉冲数
//	
//	a1[0]= x;
//	a1[1]=y;
//}

//else if(x_move <= 0&& y_move <= 0){//向左下

//  DAL1 = 0;
//	DAL2 = 0;
//	
//	//这里写通过移动值计算脉冲数
//	
//	a1[0]= x;
//	a1[1]=y;
//}
//return a1;

//}

**/

