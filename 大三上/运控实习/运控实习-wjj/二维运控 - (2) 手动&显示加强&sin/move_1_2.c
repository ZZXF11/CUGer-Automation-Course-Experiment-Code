#include "move.h"
#include "support.h"

xdata unsigned char PortA _at_ 0x7c00;
xdata unsigned char PortB _at_ 0x7c01;

unsigned int i;
//蓝红绿黄
//PortA前四位控制X的方向，后四位控制X方向上的运行
//PortB前四位控制Y的方向，后四位控制Y方向上的运行

//移动一步
void move_onestep(unsigned char coordinate, unsigned char direction, unsigned int speed)
{
	if(coordinate == 'x')
	{
		if(direction == '+'){//判断方向，给方向位赋值
		PortA=0xff;				//启动电机让其运动一个机器周期（即实现走一步的功能）
		for (i =0; i < speed; i++) _nop_();
		PortA=0xf0;
		}
		else{ 
		PortA=0x0f;				//启动电机让其运动一个机器周期（即实现走一步的功能）
		for (i =0; i < speed; i++) _nop_();
		PortA=0x00;
		}
	}
	else if(coordinate == 'y')
	{
		if(direction == '+'){//判断方向，给方向位赋值
		PortB=0xff;				//启动电机让其运动一个机器周期（即实现走一步的功能）
		for (i =0; i < speed; i++) _nop_();
		PortB=0xf0;
		}
		else{ 
		PortB=0x0f;				//启动电机让其运动一个机器周期（即实现走一步的功能）
		for (i =0; i < speed; i++) _nop_();
		PortB=0x00;
		}
	}
}


//画直线
void draw_line(Cdt_struct Coordinate, unsigned int speed)
{
	unsigned int all_step;//总步数
	unsigned char dir_x;//方向
	unsigned char dir_y;
	double f;//判别式的值
	
	//令当前坐标为起始坐标值
	x_now=Coordinate.x_s;
	y_now=Coordinate.y_s;
	//计算总步数
	all_step=abs(Coordinate.x_end-Coordinate.x_s)+abs(Coordinate.y_end-Coordinate.y_s);
	//判别式初始值
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
//		Write_Cmd(0x80);//第一行显示
//		Write_Dat('x');
//		Write_Cmd(0x80 | 0x02);
//		display_coor(x_now);
//		Write_Cmd(0xc0);	//第二行显示
//		Write_Dat('y');
//		Write_Cmd(0xc0 | 0x02);
//		display_coor(y_now);
//		delayms(40);
//		Write_Cmd(0x01);
	}
//	beep=~beep;		//蜂鸣器提示
//	delayms(1000);
//	beep=~beep;
//	LED1=1;		//画图指示灯灭
}

//函数功能：逆时针画圆
void draw_circle_AW(Cdt_circle circle, unsigned int speed)
{
	//Cdt_struct_now Cdt_now;//当前坐标
	unsigned long int count=80000;
	double f;//判别式
	double I;//x的差值 
	double J;//y的差值
	
	//当前坐标等于起始点（以圆心为原点）
	x_now=circle.x_s;///-circle.x_center;
	y_now=circle.y_s;//-circle.y_center;
	
	//坐标差值，用于计算判别式
	I = circle.x_s;//- circle.x_center;
	J = circle.y_s;//- circle.y_center;
	
	//开始画圆
	while(count)
	{
		f=abs(x_now*x_now)+abs(y_now*y_now)-abs(circle.radius*circle.radius);
		//第一象限
		if(x_now>=0 && y_now>0)
		{
			if(f>=0)//判别式大于零，点在圆外面，向x-运动一步
			{
				move_onestep('x','-',speed);
				x_now=x_now-0.0002;
			}
			else//判别式小于零，点在圆里面，向y+运动一步
			{
				move_onestep('y','+',speed);
				y_now=y_now+0.0002;
			}
		}
		//第二象限
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
		//第三象限
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
		// 第四象限
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
//		Write_Cmd(0x80);//第一行显示
//		Write_Dat('x');
//		Write_Cmd(0x80 | 0x02);
//		display_coor(x_now);
//		Write_Cmd(0xc0);	//第二行显示
//		Write_Dat('y');
//		Write_Cmd(0xc0 | 0x02);
//		display_coor(y_now);
//		delayms(40);
//		Write_Cmd(0x01);
	}
//	beep=~beep;		//蜂鸣器提示
//	delayms(1000);
//	beep=~beep;
//	LED1=1;				//画图指示灯灭
}

//顺时针画圆
void draw_circle_CW(Cdt_circle circle, unsigned int speed)
{
	//Cdt_struct_now Cdt_now;//当前坐标
	unsigned long int count=80000;
	double f;//判别式
	double I;//x的差值 
	double J;//y的差值
	
	//当前坐标等于起始点（以圆心为原点）
	x_now=circle.x_s;///-circle.x_center;
	y_now=circle.y_s;//-circle.y_center;
	
	//坐标差值，用于计算判别式
	I = circle.x_s;//- circle.x_center;
	J = circle.y_s;//- circle.y_center;
	
//	LED1=0;//画图指示灯亮
	//开始画圆
	while(count)
	{
		f=abs(x_now*x_now)+abs(y_now*y_now)-abs(circle.radius*circle.radius);
		//第一象限
		if(x_now>=0 && y_now>0)
		{
			if(f>=0)//判别式大于零，点在圆外面，向x-运动一步
			{
				move_onestep('y','-',speed);
				y_now=y_now-0.0002;
			}
			else//判别式小于零，点在圆里面，向y+运动一步
			{
				move_onestep('x','+',speed);
				x_now=x_now+0.0002;
			}
		}
		//第二象限
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
		//第三象限
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
		// 第四象限
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
//		Write_Cmd(0x80);//第一行显示
//		Write_Dat('x');
//		Write_Cmd(0x80 | 0x02);
//		display_coor(x_now);
//		Write_Cmd(0xc0);	//第二行显示
//		Write_Dat('y');
//		Write_Cmd(0xc0 | 0x02);
//		display_coor(y_now);
//		delayms(40);
//		Write_Cmd(0x01);
	}
//	beep=~beep;		//蜂鸣器提示
//	delayms(1000);
//	beep=~beep;
//	LED1=1;				//画图指示灯灭
}

void darw_oval(Cdt_oval oval,unsigned int speed){
	//Cdt_struct_now Cdt_now;//当前坐标
	unsigned long int count=80000;
	double f;//判别式
	double I;//x的差值 
	double J;//y的差值
	double a1;
	double b1;
	
	//当前坐标等于起始点（以圆心为原点）
	x_now=oval.x_s;///-circle.x_center;
	y_now=oval.y_s;//-circle.y_center;
	a1=oval.a;
	b1=oval.a;
	
	//坐标差值，用于计算判别式
	I = oval.x_s;//- circle.x_center;
	J = oval.y_s;//- circle.y_center;
	
	//开始画圆
	while(count)
	{
	//	f=((oval.b*oval.b*oval.x_end*oval_x.end)+(oval.a*oval.a*oval.y_end*oval.y_end))-((oval.b*oval.b*oval.x_s*oval_x.s)+(oval.a*oval.a*oval.y_s*oval.y_s));
		f=abs(x_now*x_now)+abs(y_now*y_now)-abs(a1*a1*b1*b1);
		//第一象限
		if(x_now>=0 && y_now>0)
		{
			if(f>=0)//判别式大于零，点在圆外面，向x-运动一步
			{
				move_onestep('x','-',speed);
				x_now=x_now-0.0002;
			}
			else//判别式小于零，点在圆里面，向y+运动一步
			{
				move_onestep('y','+',speed);
				y_now=y_now+0.0002;
			}
		}
		//第二象限
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
		//第三象限
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
		// 第四象限
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
//		Write_Cmd(0x80);//第一行显示
//		Write_Dat('x');
//		Write_Cmd(0x80 | 0x02);
//		display_coor(x_now);
//		Write_Cmd(0xc0);	//第二行显示
//		Write_Dat('y');
//		Write_Cmd(0xc0 | 0x02);
//		display_coor(y_now);
//		delayms(40);
//		Write_Cmd(0x01);
	}
//	beep=~beep;		//蜂鸣器提示
//	delayms(1000);
//	beep=~beep;
//	LED1=1;				//画图指示灯灭
}
