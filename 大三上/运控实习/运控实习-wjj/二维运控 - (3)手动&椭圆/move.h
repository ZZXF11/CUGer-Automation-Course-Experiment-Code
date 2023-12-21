#ifndef __MOVE_H
#define __MOVE_H

#include <IOport.h>

//ֱ��������
typedef struct Cdt_line
{
	double x_s;
	double y_s;
	double x_end;
	double y_end;
}Cdt_struct;//ֱ�����������ͱ���

//������
typedef struct Cdt_coordinate
{
	double x;
	double y;
}Cdt_struct_now;//���������ͱ���

//Բ��
typedef struct
{
	double x_s;
	double y_s;
	double x_end;
	double y_end;
	double x_center;
	double y_center;
	double radius;
}Cdt_circle;//Բ�����ͱ���

//��Բ��
typedef struct
{
	double x_s;
	double y_s;
	double x_end;
	double y_end;
	double x_center;
	double y_center;	
	double a;
	double b;
}Cdt_oval;

void move_onestep(unsigned char coordinate, unsigned char direction, unsigned int speed);
void draw_line(Cdt_struct Coordinate, unsigned int speed);
void draw_circle_AW(Cdt_circle circle, unsigned int speed);//AW��ʱ�뻭Բ
void draw_circle_CW(Cdt_circle circle, unsigned int speed);//CW˳ʱ�뻭Բ

void darw_oval(Cdt_oval oval,unsigned int speed);//��Բ
void draw_sin(double A,double w,double fai,unsigned int speed);//sin
#endif