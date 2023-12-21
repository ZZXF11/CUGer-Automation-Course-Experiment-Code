#include <math.h>
#include "move.h"
#include "support.h"
#include "lcd.h"

#define pai 3.1415926

xdata unsigned char PortA _at_ 0x7c00;
xdata unsigned char PortB _at_ 0x7c01;
xdata unsigned char PortC _at_ 0x7c02;   // PC硬件地址,键盘
xdata unsigned char INC _at_ 0x6002 ; //$$$$$$$$$
xdata unsigned char IN _at_ 0x6002 ;

extern int flag;
extern int confirm_sign;//f键确定，确认键状态标志
extern int retreat_sign;
extern unsigned int SDspeed;
extern int noTuiChu;

code unsigned char KeyTable[] = //键值表
{	
	0x0c,0x08,0x04,0x00,
	0x0d,0x09,0x05,0x01,
	0x0e,0x0a,0x06,0x02,
	0x0f,0x0b,0x07,0x03
};

void Delaykey(int CNT)
{
  unsigned char i;

  while (CNT-- !=0)
    for (i=100; i !=0; i--);
}


unsigned char TestKey()	//有无键按下检测，有就返回非零
{
   PortC = 0x0f;            // 输出PC4~PC6置为0，四列一起扫描
   return (~INC & 0x0f);   //读回四行状态（PC0~PC3），被按下的被拉成0，取反为1
}


unsigned char keyscan()	//键盘扫描函数，返回键值
{
  unsigned char Pos;
  unsigned char i;
  unsigned char k;
  i = 4;
  Pos = 0x80;     // 1000 0000，扫描用
  do {
    PortC = ~ Pos;
    Pos >>= 1;
    k = ~IN & 0x0f;
  } while ((--i != 0) && (k == 0));

  if (k != 0) {//如果有键按下
    i *= 4;
    if (k & 2)
      i += 1;
    else if (k & 4)
      i += 2;
    else if (k & 8)
      i += 3;
			do {Delaykey(10);} 
			while (TestKey());  // deng键松开	
    return(KeyTable[i]);  //有键按下返回键值
  } 
	else return(0xff);//无键按下，则返回0xff  ￥￥￥￥￥￥￥￥￥￥￥￥
}

unsigned char keyscan2()	//键盘扫描函数，返回键值
{
  unsigned char Pos;
  unsigned char i;
  unsigned char k;
  i = 4;
  Pos = 0x80;     // 1000 0000，扫描用
  do {
    PortC = ~ Pos;
    Pos >>= 1;
    k = ~IN & 0x0f;
  } while ((--i != 0) && (k == 0));

  if (k != 0) {//如果有键按下
    i *= 4;
    if (k & 2)
      i += 1;
    else if (k & 4)
      i += 2;
    else if (k & 8)
      i += 3;
//		if(flag!=1)//如果不处于模式1手动
//		{
//			do {Delaykey(10);} 
//			while (TestKey());  // deng键松开			
//		}
//			do {Delaykey(10);} 
//			while (TestKey());  // deng键松开	
    return(KeyTable[i]);  //有键按下返回键值
  } 
	else return(0xff);//无键按下，则返回0xff  ￥￥￥￥￥￥￥￥￥￥￥￥
}

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
		else{ //如果-向
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


void shoudong()	//手动模式扫描按键、执行操作函数
{
		unsigned char keynum;
		unsigned char TuiChu=0;
		while(TestKey())
		{
			if(noTuiChu==0) break;
						keynum=keyscan2() & 0x0f;	
						switch (keynum)  //keynum就等于按键的数值
						{
								 case 5:  {		move_onestep('x','+',SDspeed);	break;} 
								 case 7:  {		move_onestep('x','-',SDspeed);break;} 
								 case 0x0a: {	move_onestep('y','+',SDspeed);break;} 
								 case 2: 	{		move_onestep('y','-',SDspeed);break;}
								 case 1: {	//1键右下
									 move_onestep('x','+',SDspeed);
									 move_onestep('y','-',SDspeed);
								 break;}
								 case 3: {	//3键左下
									 move_onestep('x','-',SDspeed);
									 move_onestep('y','-',SDspeed);
								 break;}
								 case 9: {	//9键右上
									 move_onestep('x','+',SDspeed);
									 move_onestep('y','+',SDspeed);
								 break;}
								 case 0x0b: {//b键左上
									 move_onestep('x','-',SDspeed);
									 move_onestep('y','+',SDspeed);
								 break;}
								 case 0x0c: {//c键加速
										SDspeed-=1;
										Display_1(SDspeed);
										do{Delaykey(10);}while((keyscan2())==0x0c);
										break;}
								 case 0x08: {//8键减速
										SDspeed+=1;
										Display_1(SDspeed);
										do{Delaykey(10);}while((keyscan2())==0x08);
										break;}								 
								 case 0x00: {//0键退出
										noTuiChu=0;
										do{Delaykey(10);}while((keyscan2())==0x00);
										break;}
						}			
	 }
}


////画直线
//void draw_line(Cdt_struct Coordinate, unsigned int speed)
//{
//	unsigned int all_step;//总步数
//	unsigned char dir_x;//方向
//	unsigned char dir_y;
//	double f;//判别式的值
//	
//	//令当前坐标=起始坐标值
//	x_now=Coordinate.x_s;
//	y_now=Coordinate.y_s;
//	//计算总步数
//	all_step=abs(Coordinate.x_end-Coordinate.x_s)+abs(Coordinate.y_end-Coordinate.y_s);
//	all_step=all_step*5000;	
//	//判别式初始值
//	f=(y_now-Coordinate.y_s)*(Coordinate.x_end-Coordinate.x_s)-(x_now-Coordinate.x_s)*(Coordinate.y_end-Coordinate.y_s);
//	

//	if(Coordinate.x_end-Coordinate.x_s>0) dir_x='+';
//	else dir_x='-';
//	if(Coordinate.y_end-Coordinate.y_s>0) dir_y='+';
//	else dir_y='-';

//	while(all_step)
//	{
//		f=(y_now-Coordinate.y_s)*(Coordinate.x_end-Coordinate.x_s)-(x_now-Coordinate.x_s)*(Coordinate.y_end-Coordinate.y_s);
//		if(f>=0)
//		{
//			move_onestep('x',dir_x,speed);		
//			if(dir_x=='-')
//				x_now=x_now-0.0001;
//			else
//				x_now=x_now+0.0001;
//		}
//		else
//		{
//			move_onestep('y',dir_y,speed);
//			if(dir_y=='-')
//				y_now=y_now-0.0001;
//			else
//				y_now=y_now+0.0001;
//		}
//		all_step--;
//	}
//}


//画直线（修改版）
void draw_line(Cdt_struct Coordinate, unsigned int speed)
{
	unsigned int all_step;//总步数
	unsigned char dir_x;//方向
	unsigned char dir_y;
	double f;//判别式的值
	
	//令当前坐标=起始坐标值
	x_now=Coordinate.x_s;
	y_now=Coordinate.y_s;
	//计算总步数
	all_step=abs(Coordinate.x_end-Coordinate.x_s)+abs(Coordinate.y_end-Coordinate.y_s);
	all_step=all_step*5000;	
	//判别式初始值
	f=(y_now-Coordinate.y_s)*(Coordinate.x_end-Coordinate.x_s)-(x_now-Coordinate.x_s)*(Coordinate.y_end-Coordinate.y_s);
	
	if(Coordinate.x_end-Coordinate.x_s>0) dir_x='+';
	else dir_x='-';
	if(Coordinate.y_end-Coordinate.y_s>0) dir_y='+';
	else dir_y='-';

	while(all_step)
	{
		f=(y_now-Coordinate.y_s)*(Coordinate.x_end-Coordinate.x_s)-(x_now-Coordinate.x_s)*(Coordinate.y_end-Coordinate.y_s);
		if(dir_x=='+' && dir_y=='+')//第一象限
		{
			if(f>=0)	{ move_onestep('x','+',speed); x_now=x_now+0.0001; }
			else { move_onestep('y','+',speed); y_now=y_now+0.0001;}
		}
		if(dir_x=='-' && dir_y=='+')//第二象限
		{
			if(f>=0)	{ move_onestep('x','-',speed); x_now=x_now-0.0001; }
			else { move_onestep('y','+',speed); y_now=y_now+0.0001;}
		}
		if(dir_x=='-' && dir_y=='-')//第三象限
		{
			if(f>=0)	{ move_onestep('x','-',speed); x_now=x_now-0.0001; }
			else { move_onestep('y','-',speed); y_now=y_now-0.0001;}
		}
		if(dir_x=='+' && dir_y=='-')//第四象限
		{
			if(f>=0)	{ move_onestep('x','+',speed); x_now=x_now+0.0001; }
			else { move_onestep('y','-',speed); y_now=y_now-0.0001;}
		}
		all_step--;
	}
}


//画一个任意圆心角、任意半径的弧/圆
void draw_circle_AW(Cdt_circle circle,unsigned int speed)
{
	long int count=8*circle.radius*5000*(circle.angle/360.0);
	double f;//判别式
	int keynum;
	//当前坐标等于起始点（以圆心为原点）
	x_now=circle.x_s-circle.x_center;
	y_now=circle.y_s-circle.y_center;

	//开始画圆
	move_onestep('y','+',speed);
	y_now=y_now+0.0002;
	
	while(count>0)
	{
		f=x_now*x_now+y_now*y_now-circle.radius*circle.radius;	
		if(x_now>=0 && y_now>0)	//第一象限
		{
			if(f>=0)	{move_onestep('x','-',speed);x_now=x_now-0.0002;}
			else	{move_onestep('y','+',speed);y_now=y_now+0.0002;}
		}
		else if(x_now<0&&y_now>=0)		//第二象限
		{
			if(f>=0) {move_onestep('y','-',speed);y_now=y_now-0.0002;}
			else	{move_onestep('x','-',speed);x_now=x_now-0.0002;}
		}
		else if(x_now<=0&&y_now<0)	//第三象限
		{
			if(f>=0)	{move_onestep('x','+',speed);x_now=x_now+0.0002;}
			else	{move_onestep('y','-',speed);y_now=y_now-0.0002;}
		}
		else if(x_now>0&&y_now<=0)	// 第四象限
		{
			if(f>=0)	{move_onestep('y','+',speed);y_now=y_now+0.0002;}
			else	{move_onestep('x','+',speed);x_now=x_now+0.0002;}
		}
		count--;
		if(TestKey())
		{
			keynum=keyscan() & 0x0f;	
			if(keynum==0x0b) { count=-1;}	//b键做退出键，按下后剩余步数直接置为-1
		}
	}
}



////画椭圆
//void darw_oval(Cdt_oval oval,unsigned int speed){
//	unsigned long int count=(oval.a+oval.b)*4*5000;
//	double f;//判别式
//	double I;//x的差值 
//	double J;//y的差值
//	
//	//当前坐标等于起始点（以圆心为原点）
//	x_now=oval.x_s-oval.x_center;
//	y_now=oval.y_s-oval.y_center;
//	
//	//坐标差值，用于计算判别式
//	I = oval.x_s;//- circle.x_center;
//	J = oval.y_s;//- circle.y_center;
//	
//	//开始画椭圆
//	move_onestep('y','+',speed);
//	y_now=y_now+0.0002;
//	
//	while(count>0)
//	{
//		//f=1.0-( (x_now*x_now)/(oval.a*oval.a) + (y_now*y_now)/(oval.b*oval.b) );
//		f=(x_now*x_now*oval.b*oval.b)+(y_now*y_now*oval.a*oval.a)-(oval.a*oval.a*oval.b*oval.b);
//		//第一象限
//		if(x_now>=0 && y_now>0)
//		{
//			if(f>=0)//判别式大于零，点在圆外面，向x-运动一步
//			{
//				move_onestep('x','-',speed);
//				x_now=x_now-0.0002;
//			}
//			else//判别式小于零，点在圆里面，向y+运动一步
//			{
//				move_onestep('y','+',speed);
//				y_now=y_now+0.0002;
//			}
//		}
//		//第二象限
//		else if(x_now<0&&y_now>=0)
//		{
//			if(f>=0)
//			{
//				move_onestep('y','-',speed);
//				y_now=y_now-0.0002;
//			}
//			else
//			{
//				move_onestep('x','-',speed);
//				x_now=x_now-0.0002;
//			}
//		}
//		//第三象限
//		else if(x_now<=0&&y_now<0)
//		{
//			if(f>=0)
//			{
//				move_onestep('x','+',speed);
//				x_now=x_now+0.0002;
//			}
//			else
//			{
//				move_onestep('y','-',speed);
//				y_now=y_now-0.0002;
//			}
//		}
//		// 第四象限
//		else if(x_now>0&&y_now<=0)
//		{
//			if(f>=0)
//			{
//				move_onestep('y','+',speed);
//				y_now=y_now+0.0002;
//			}
//			else
//			{
//				move_onestep('x','+',speed);
//				x_now=x_now+0.0002;
//			}
//		}
//		count--;
//	}
//}

//void draw_sin(double A,double w,double fai,unsigned int speed)
//{
//	unsigned long int count=(3.1415926+2*A)*2*5000;
//	double f;//判别式
//	//设置当前坐标
//	x_now=0;
//	y_now=A*sin(w*x_now+fai);	
//	
//	//开始画sin
//	move_onestep('x','+',speed);
//	x_now=x_now+0.0002;	
//	move_onestep('y','+',speed);
//	y_now=y_now+0.0002;

//	while(count>0)
//	{
//		f=y_now-A*sin(w*x_now+fai);
//		
//		//0~pai/2w
//		if(x_now<=(pai/2*w) && y_now>0)
//		{
//			if(f>=0)//判别式大于零，点在圆外面，向x+运动一步
//			{
//				move_onestep('x','+',speed);
//				x_now=x_now+0.0002;
//			}
//			else//判别式小于零，点在圆里面，向y+运动一步
//			{
//				move_onestep('y','+',speed);
//				y_now=y_now+0.0002;
//			}
//		}
//		//pai/2w ~ pai/w
//		else if(x_now<=pai/w &&y_now>=0)
//		{
//			if(f>=0)
//			{
//				move_onestep('y','-',speed);
//				y_now=y_now-0.0002;
//			}
//			else
//			{
//				move_onestep('x','+',speed);
//				x_now=x_now+0.0002;
//			}
//		}
//		//pai/w ~ 3pai/2w
//		else if(x_now<=(3*pai/2*w) && y_now<0)
//		{
//			if(f>=0)
//			{
//				move_onestep('y','-',speed);
//				y_now=y_now-0.0002;
//			}
//			else
//			{
//				move_onestep('x','+',speed);
//				x_now=x_now+0.0002;
//			}
//		}
//		// 3pai/2w ~ 2pai/w
//		else if(x_now<=(2*pai/w) && y_now<=0)
//		{
//			if(f>=0)
//			{
//				move_onestep('x','+',speed);
//				x_now=x_now+0.0002;
//			}
//			else
//			{
//				move_onestep('y','+',speed);
//				y_now=y_now+0.0002;
//			}
//		}
//		count--;
//	}
//}

////******************进阶版sin，任意初相**************************
//void draw_sin(double A,double w,double fai,unsigned int speed)
//{
//	unsigned long int count=(3.1415926/w+2*A)*2*5000;
//	double f;//判别式
//	int Q,P;
//	//设置当前坐标
//	x_now=0;
//	y_now=A*sin(w*x_now+fai);	
//	
//	Q=(2*pai/w-fai)/(pai/(2*w));
//	
//	//开始画sin
////	move_onestep('x','+',speed);
////	x_now=x_now+0.0002;	
//	move_onestep('y','+',speed);
//	y_now=y_now+0.0002;

//	while(count>0)
//	{
//		f=y_now-A*sin(w*x_now+fai);
//		for(P=4;P<=8;P++)
//		{
//			if(x_now>((pai/(2*w))*(P-Q-1)-fai) && x_now<=((pai/(2*w))*(P-Q)-fai))
//			{
//				switch (((P-Q)%4)+1)
//				{
//					case 1:
//					{
//							if(f>=0)//判别式大于零，点在圆外面，向x+运动一步
//							{
//								move_onestep('x','+',speed);
//								x_now=x_now+0.0002;
//							}
//							else//判别式小于零，点在圆里面，向y+运动一步
//							{
//								move_onestep('y','+',speed);
//								y_now=y_now+0.0002;
//							}
//						count--;
//						break;
//					}
//					case 2:
//					{
//							if(f>=0)
//							{
//								move_onestep('y','-',speed);
//								y_now=y_now-0.0002;
//							}
//							else
//							{
//								move_onestep('x','+',speed);
//								x_now=x_now+0.0002;
//							}	
//						count--;							
//						break;
//					}
//					case 3:
//					{
//							if(f>=0)
//							{
//								move_onestep('y','-',speed);
//								y_now=y_now-0.0002;
//							}
//							else
//							{
//								move_onestep('x','+',speed);
//								x_now=x_now+0.0002;
//							}	
//						count--;							
//						break;
//					}
//					case 4:
//					{
//							if(f>=0)
//							{
//								move_onestep('x','+',speed);
//								x_now=x_now+0.0002;
//							}
//							else
//							{
//								move_onestep('y','+',speed);
//								y_now=y_now+0.0002;
//							}
//						count--;							
//						break;
//					}					
//				}
//			}
//		}
//	}
//}

