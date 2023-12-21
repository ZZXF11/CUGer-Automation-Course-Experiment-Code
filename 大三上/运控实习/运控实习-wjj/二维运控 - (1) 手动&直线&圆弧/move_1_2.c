#include "move.h"
#include "support.h"

xdata unsigned char PortA _at_ 0x7c00;
xdata unsigned char PortB _at_ 0x7c01;

unsigned int i;
//�����̻�
//PortAǰ��λ����X�ķ��򣬺���λ����X�����ϵ�����
//PortBǰ��λ����Y�ķ��򣬺���λ����Y�����ϵ�����

//�ƶ�һ��
void move_onestep(unsigned char coordinate, unsigned char direction, unsigned int speed)
{
	if(coordinate == 'x')
	{
		if(direction == '+'){//�жϷ��򣬸�����λ��ֵ
		PortA=0xff;				//������������˶�һ���������ڣ���ʵ����һ���Ĺ��ܣ�
		for (i =0; i < speed; i++) _nop_();
		PortA=0xf0;
		}
		else{ 
		PortA=0x0f;				//������������˶�һ���������ڣ���ʵ����һ���Ĺ��ܣ�
		for (i =0; i < speed; i++) _nop_();
		PortA=0x00;
		}
	}
	else if(coordinate == 'y')
	{
		if(direction == '+'){//�жϷ��򣬸�����λ��ֵ
		PortB=0xff;				//������������˶�һ���������ڣ���ʵ����һ���Ĺ��ܣ�
		for (i =0; i < speed; i++) _nop_();
		PortB=0xf0;
		}
		else{ 
		PortB=0x0f;				//������������˶�һ���������ڣ���ʵ����һ���Ĺ��ܣ�
		for (i =0; i < speed; i++) _nop_();
		PortB=0x00;
		}
	}
}


//��ֱ��
void draw_line(Cdt_struct Coordinate, unsigned int speed)
{
	unsigned int all_step;//�ܲ���
	unsigned char dir_x;//����
	unsigned char dir_y;
	double f;//�б�ʽ��ֵ
	
	//�ǰ����Ϊ��ʼ����ֵ
	x_now=Coordinate.x_s;
	y_now=Coordinate.y_s;
	//�����ܲ���
	all_step=abs(Coordinate.x_end-Coordinate.x_s)+abs(Coordinate.y_end-Coordinate.y_s);
	//�б�ʽ��ʼֵ
	f=(y_now-Coordinate.y_s)*(Coordinate.x_end-Coordinate.x_s)-(x_now-Coordinate.x_s)*(Coordinate.y_end-Coordinate.y_s);
	
	
	all_step=all_step*1000;
	if(Coordinate.x_end-Coordinate.x_s>0) dir_x='+';
	else dir_x='-';
	if(Coordinate.y_end-Coordinate.y_s>0) dir_y='+';
	else dir_y='-';

	while(all_step)
	{
		f=(y_now-Coordinate.y_s)*(Coordinate.x_end-Coordinate.x_s)-(x_now-Coordinate.x_s)*(Coordinate.y_end-Coordinate.y_s);
		if(f>=0)
		{
			move_onestep('x',dir_x,speed);
			//f = f - abs(Coordinate.y_end-Coordinate.y_s);
			if(dir_x=='-')
				x_now=x_now-0.0001;
			else
				x_now=x_now+0.0001;
		}
		else
		{
			move_onestep('y',dir_y,speed);
			//f = f + abs(Coordinate.x_end-Coordinate.x_s);
			if(dir_y=='-')
				y_now=y_now-0.0001;
			else
				y_now=y_now+0.0001;
		}
		all_step--;
		//dis_count++;
//		Write_Cmd(0x80);//��һ����ʾ
//		Write_Dat('x');
//		Write_Cmd(0x80 | 0x02);
//		display_coor(x_now);
//		Write_Cmd(0xc0);	//�ڶ�����ʾ
//		Write_Dat('y');
//		Write_Cmd(0xc0 | 0x02);
//		display_coor(y_now);
//		delayms(40);
//		Write_Cmd(0x01);
	}
//	beep=~beep;		//��������ʾ
//	delayms(1000);
//	beep=~beep;
//	LED1=1;		//��ͼָʾ����
}

//�������ܣ���ʱ�뻭Բ
void draw_circle_AW(Cdt_circle circle, unsigned int speed)
{
	//Cdt_struct_now Cdt_now;//��ǰ����
	unsigned long int count=80000;
	double f;//�б�ʽ
	double I;//x�Ĳ�ֵ 
	double J;//y�Ĳ�ֵ
	
	//��ǰ���������ʼ�㣨��Բ��Ϊԭ�㣩
	x_now=circle.x_s;///-circle.x_center;
	y_now=circle.y_s;//-circle.y_center;
	
	//�����ֵ�����ڼ����б�ʽ
	I = circle.x_s;//- circle.x_center;
	J = circle.y_s;//- circle.y_center;
	
	//��ʼ��Բ
	while(count)
	{
		f=abs(x_now*x_now)+abs(y_now*y_now)-abs(circle.radius*circle.radius);
		//��һ����
		if(x_now>=0 && y_now>0)
		{
			if(f>=0)//�б�ʽ�����㣬����Բ���棬��x-�˶�һ��
			{
				move_onestep('x','-',speed);
				x_now=x_now-0.0002;
			}
			else//�б�ʽС���㣬����Բ���棬��y+�˶�һ��
			{
				move_onestep('y','+',speed);
				y_now=y_now+0.0002;
			}
		}
		//�ڶ�����
		else if(x_now<0&&y_now>=0)
		{
			if(f>=0)
			{
				move_onestep('y','-',speed);
				y_now=y_now-0.0002;
			}
			else
			{
				move_onestep('x','-',speed);
				x_now=x_now-0.0002;
			}
		}
		//��������
		else if(x_now<=0&&y_now<0)
		{
			if(f>=0)
			{
				move_onestep('x','+',speed);
				x_now=x_now+0.0002;
			}
			else
			{
				move_onestep('y','-',speed);
				y_now=y_now-0.0002;
			}
		}
		// ��������
		else if(x_now>0&&y_now<=0)
		{
			if(f>=0)
			{
				move_onestep('y','+',speed);
				y_now=y_now+0.0002;
			}
			else
			{
				move_onestep('x','+',speed);
				x_now=x_now+0.0002;
			}
		}
		count--;
//		Write_Cmd(0x80);//��һ����ʾ
//		Write_Dat('x');
//		Write_Cmd(0x80 | 0x02);
//		display_coor(x_now);
//		Write_Cmd(0xc0);	//�ڶ�����ʾ
//		Write_Dat('y');
//		Write_Cmd(0xc0 | 0x02);
//		display_coor(y_now);
//		delayms(40);
//		Write_Cmd(0x01);
	}
//	beep=~beep;		//��������ʾ
//	delayms(1000);
//	beep=~beep;
//	LED1=1;				//��ͼָʾ����
}

//˳ʱ�뻭Բ
void draw_circle_CW(Cdt_circle circle, unsigned int speed)
{
	//Cdt_struct_now Cdt_now;//��ǰ����
	unsigned long int count=80000;
	double f;//�б�ʽ
	double I;//x�Ĳ�ֵ 
	double J;//y�Ĳ�ֵ
	
	//��ǰ���������ʼ�㣨��Բ��Ϊԭ�㣩
	x_now=circle.x_s;///-circle.x_center;
	y_now=circle.y_s;//-circle.y_center;
	
	//�����ֵ�����ڼ����б�ʽ
	I = circle.x_s;//- circle.x_center;
	J = circle.y_s;//- circle.y_center;
	
//	LED1=0;//��ͼָʾ����
	//��ʼ��Բ
	while(count)
	{
		f=abs(x_now*x_now)+abs(y_now*y_now)-abs(circle.radius*circle.radius);
		//��һ����
		if(x_now>=0 && y_now>0)
		{
			if(f>=0)//�б�ʽ�����㣬����Բ���棬��x-�˶�һ��
			{
				move_onestep('y','-',speed);
				y_now=y_now-0.0002;
			}
			else//�б�ʽС���㣬����Բ���棬��y+�˶�һ��
			{
				move_onestep('x','+',speed);
				x_now=x_now+0.0002;
			}
		}
		//�ڶ�����
		else if(x_now<0&&y_now>=0)
		{
			if(f>=0)
			{
				move_onestep('x','+',speed);
				x_now=x_now+0.0002;
			}
			else
			{
				move_onestep('y','+',speed);
				y_now=y_now+0.0002;
			}
		}
		//��������
		else if(x_now<=0&&y_now<0)
		{
			if(f>=0)
			{
				move_onestep('y','+',speed);
				y_now=y_now+0.0002;
			}
			else
			{
				move_onestep('x','-',speed);
				x_now=x_now-0.0002;
			}
		}
		// ��������
		else if(x_now>0&&y_now<=0)
		{
			if(f>=0)
			{
				move_onestep('x','-',speed);
				x_now=x_now-0.0002;
			}
			else
			{
				move_onestep('y','-',speed);
				y_now=y_now-0.0002;
			}
		}
//		count--;
//		Write_Cmd(0x80);//��һ����ʾ
//		Write_Dat('x');
//		Write_Cmd(0x80 | 0x02);
//		display_coor(x_now);
//		Write_Cmd(0xc0);	//�ڶ�����ʾ
//		Write_Dat('y');
//		Write_Cmd(0xc0 | 0x02);
//		display_coor(y_now);
//		delayms(40);
//		Write_Cmd(0x01);
	}
//	beep=~beep;		//��������ʾ
//	delayms(1000);
//	beep=~beep;
//	LED1=1;				//��ͼָʾ����
}

void darw_oval(Cdt_oval oval,unsigned int speed){
	//Cdt_struct_now Cdt_now;//��ǰ����
	unsigned long int count=80000;
	double f;//�б�ʽ
	double I;//x�Ĳ�ֵ 
	double J;//y�Ĳ�ֵ
	double a1;
	double b1;
	
	//��ǰ���������ʼ�㣨��Բ��Ϊԭ�㣩
	x_now=oval.x_s;///-circle.x_center;
	y_now=oval.y_s;//-circle.y_center;
	a1=oval.a;
	b1=oval.a;
	
	//�����ֵ�����ڼ����б�ʽ
	I = oval.x_s;//- circle.x_center;
	J = oval.y_s;//- circle.y_center;
	
	//��ʼ��Բ
	while(count)
	{
	//	f=((oval.b*oval.b*oval.x_end*oval_x.end)+(oval.a*oval.a*oval.y_end*oval.y_end))-((oval.b*oval.b*oval.x_s*oval_x.s)+(oval.a*oval.a*oval.y_s*oval.y_s));
		f=abs(x_now*x_now)+abs(y_now*y_now)-abs(a1*a1*b1*b1);
		//��һ����
		if(x_now>=0 && y_now>0)
		{
			if(f>=0)//�б�ʽ�����㣬����Բ���棬��x-�˶�һ��
			{
				move_onestep('x','-',speed);
				x_now=x_now-0.0002;
			}
			else//�б�ʽС���㣬����Բ���棬��y+�˶�һ��
			{
				move_onestep('y','+',speed);
				y_now=y_now+0.0002;
			}
		}
		//�ڶ�����
		else if(x_now<0&&y_now>=0)
		{
			if(f>=0)
			{
				move_onestep('y','-',speed);
				y_now=y_now-0.0002;
			}
			else
			{
				move_onestep('x','-',speed);
				x_now=x_now-0.0002;
			}
		}
		//��������
		else if(x_now<=0&&y_now<0)
		{
			if(f>=0)
			{
				move_onestep('x','+',speed);
				x_now=x_now+0.0002;
			}
			else
			{
				move_onestep('y','-',speed);
				y_now=y_now-0.0002;
			}
		}
		// ��������
		else if(x_now>0&&y_now<=0)
		{
			if(f>=0)
			{
				move_onestep('y','+',speed);
				y_now=y_now+0.0002;
			}
			else
			{
				move_onestep('x','+',speed);
				x_now=x_now+0.0002;
			}
		}
		count--;
//		Write_Cmd(0x80);//��һ����ʾ
//		Write_Dat('x');
//		Write_Cmd(0x80 | 0x02);
//		display_coor(x_now);
//		Write_Cmd(0xc0);	//�ڶ�����ʾ
//		Write_Dat('y');
//		Write_Cmd(0xc0 | 0x02);
//		display_coor(y_now);
//		delayms(40);
//		Write_Cmd(0x01);
	}
//	beep=~beep;		//��������ʾ
//	delayms(1000);
//	beep=~beep;
//	LED1=1;				//��ͼָʾ����
}
