#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
#include "math.h"
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
#define PUL1 PBout(5)// PB5
#define DAL1 PBout(7)// PB4	
#define PUL2 PBout(8)// PB8
#define DAL2 PBout(6)// PB6	

//void STEPMOTOR_Init1(void);
//void move_quickl(double x1,double y1,double x2,double y2);
//void STEPMOTOR_Init2(void);
//void STEPMOTORV(int timel,int timer);
void STEPMOTOR_Init(void);//初始化

void xzz(int speed);
void xfz(int speed);
void yzz(int speed);
void yfz(int speed);
long lbs(long A);
int abs(int A);
int zhixianchabu(long x,long y);
void circle1(int xm,int ym,int xe,int ye,int r);
void circle2(int xm,int ym,int xe,int ye,int r);
void circle3(int xm,int ym,int xe,int ye,int r);
void circle4(int xm,int ym,int xe,int ye,int r);

unsigned char get_xiang(int x,int y);
int yuanhuchabu(int point_x,int point_y,int end_x,int end_y,int r,unsigned char direction);
int yuan(int point_x,int point_y,int r,int direction);
void draw_car();

void sanjiao(int A,int w,int b);





/**
void STEPMOVE(int time1,int time2);
void STEPMOTORV1(int time);//左
void STEPMOTORV2(int time2);//右


double leftmove(double x1,double y1,double x2,double y2);//得到左侧步进电机放线长度  输入量为xy的前后坐标
double rightmove(double x1,double y1,double x2,double y2);//得到左侧步进电机放线长度
void go_straight1(double x1,double y1,double x2,double y2);
void go_straight(double x1,double y1,double x2,double y2);//走直线
void go_circle(double x1,double y1,double x2,double y2);//走圆

void STEPMOTORV11(int time);
void STEPMOTORV22(int time2);

int getdirection(double x1,double y1,double x2,double y2);//得到方向

double maichong(double x);//根据位移量换算得脉冲
void GO(double left_move,double right_move,int direction);//传递zuoyoudianji 的移动量对应脉冲数量,运动方向判定
void GO1(double left_move,double right_move,int direction);
**/
#endif
