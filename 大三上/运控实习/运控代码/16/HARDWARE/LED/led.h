#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
#include "math.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
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
void STEPMOTOR_Init(void);//��ʼ��

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
void STEPMOTORV1(int time);//��
void STEPMOTORV2(int time2);//��


double leftmove(double x1,double y1,double x2,double y2);//�õ���ಽ��������߳���  ������Ϊxy��ǰ������
double rightmove(double x1,double y1,double x2,double y2);//�õ���ಽ��������߳���
void go_straight1(double x1,double y1,double x2,double y2);
void go_straight(double x1,double y1,double x2,double y2);//��ֱ��
void go_circle(double x1,double y1,double x2,double y2);//��Բ

void STEPMOTORV11(int time);
void STEPMOTORV22(int time2);

int getdirection(double x1,double y1,double x2,double y2);//�õ�����

double maichong(double x);//����λ�������������
void GO(double left_move,double right_move,int direction);//����zuoyoudianji ���ƶ�����Ӧ��������,�˶������ж�
void GO1(double left_move,double right_move,int direction);
**/
#endif
