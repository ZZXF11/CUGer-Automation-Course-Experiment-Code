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
		int cishu=500;
		while(TestKey())
		{
			if(noTuiChu==0) break;
						keynum=keyscan2() & 0x0f;	
						switch (keynum)  //keynum就等于按键的数值
						{
								 case 5:  {								 
										move_onestep('x','+',SDspeed);
									 cishu--;
									 if(cishu<0) {cishu=500;Display_1(SDspeed,keynum);}	 
								 break;} 
								 case 7:  {							
									 move_onestep('x','-',SDspeed);
									 cishu--;
									 if(cishu<0) {cishu=500;Display_1(SDspeed,keynum);}	 
								 break;} 
								 case 0x0a:  {							 
									 move_onestep('y','+',SDspeed);
									 cishu--;
									 if(cishu<0) {cishu=500;Display_1(SDspeed,keynum);}	 
								 break;} 
								 case 2: {
									 move_onestep('y','-',SDspeed);
									 cishu--;
									 if(cishu<0) {cishu=500;Display_1(SDspeed,keynum);}	 
								 break;}
								 case 1: {
									 move_onestep('x','+',SDspeed);
									 move_onestep('y','-',SDspeed);
									 cishu--;
									 if(cishu<0) {cishu=500;Display_1(SDspeed,keynum);}	 
								 break;}
								 case 3: {
									 move_onestep('x','-',SDspeed);
									 move_onestep('y','-',SDspeed);
									 cishu--;
									 if(cishu<0) {cishu=500;Display_1(SDspeed,keynum);}	 
								 break;}
								 case 9: {
									 move_onestep('x','+',SDspeed);
									 move_onestep('y','+',SDspeed);
									 cishu--;
									 if(cishu<0) {cishu=500;Display_1(SDspeed,keynum);}	 
								 break;}
								 case 0x0b: {
									 move_onestep('x','-',SDspeed);
									 move_onestep('y','+',SDspeed);
									 cishu--;
									 if(cishu<0) {cishu=500;Display_1(SDspeed,keynum);}	 
								 break;}
								 case 0x0c: //c键加速
										{
											SDspeed-=1;
											Display_1(SDspeed,keynum);
											do{Delaykey(10);}while((keyscan2())==0x0c);
											break;
										}
								 case 0x08: //8键减速	
										{
											SDspeed+=1;
											Display_1(SDspeed,keynum);
											do{Delaykey(10);}while((keyscan2())==0x08);
											break;
										}							 
								 case 0x00: {noTuiChu=0;do{Delaykey(10);}while((keyscan2())==0x00);break;}
						}
				
	 }
}


//画直线
//void draw_line(Cdt_struct Coordinate, unsigned int speed)
//{
//	unsigned int all_step;//总步数
//	unsigned char dir_x;//方向
//	unsigned char dir_y;
//	double f;//判别式的值
//	
//	//令当前坐标为起始坐标值
//	x_now=Coordinate.x_s;
//	y_now=Coordinate.y_s;
//	//计算总步数
//	all_step=abs(Coordinate.x_end-Coordinate.x_s)+abs(Coordinate.y_end-Coordinate.y_s);
//	//判别式初始值
//	f=(y_now-Coordinate.y_s)*(Coordinate.x_end-Coordinate.x_s)-(x_now-Coordinate.x_s)*(Coordinate.y_end-Coordinate.y_s);
//	
//	
//	//all_step=all_step*1000;
//	all_step=all_step*5000;	
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
//			//f = f - abs(Coordinate.y_end-Coordinate.y_s);
//			if(dir_x=='-')
//				x_now=x_now-0.0001;
//			else
//				x_now=x_now+0.0001;
//		}
//		else
//		{
//			move_onestep('y',dir_y,speed);
//			//f = f + abs(Coordinate.x_end-Coordinate.x_s);
//			if(dir_y=='-')
//				y_now=y_now-0.0001;
//			else
//				y_now=y_now+0.0001;
//		}
//		all_step--;

//	}
////	beep=~beep;		//蜂鸣器提示
////	delayms(1000);
////	beep=~beep;
////	LED1=1;		//画图指示灯灭
//}




//函数功能：画一个圆
//void draw_circle_AW(Cdt_circle circle, unsigned int speed)
//{
//	//Cdt_struct_now Cdt_now;//当前坐标
//	long int count=8*circle.radius*5000;
//	//unsigned long int count=circle.radius*8*5000;
//	double f;//判别式
//	double I;//x的差值 
//	double J;//y的差值
//	
//	int keynum;
//	
//	//当前坐标等于起始点（以圆心为原点）
//	x_now=circle.x_s-circle.x_center;
//	y_now=circle.y_s-circle.y_center;
//	
//	//坐标差值，用于计算判别式
//	I = circle.x_s;//- circle.x_center;
//	J = circle.y_s;//- circle.y_center;
//	
//	//开始画圆
//	while(count>0)
//	{
//		f=abs(x_now*x_now)+abs(y_now*y_now)-abs(circle.radius*circle.radius);
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
//		if(TestKey())
//		{
//			keynum=keyscan() & 0x0f;	
//			if(keynum==0x0b) { count=-1;}
//		}
//	}
////	beep=~beep;		//蜂鸣器提示
////	delayms(1000);
////	beep=~beep;
////	LED1=1;				//画图指示灯灭
//}

//画椭圆
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

//画sin曲线
void draw_sin(double A,double w,double fai,unsigned int speed)
{
	unsigned long int count=(pai/w+2*A)*2*5000;//计算总步数（总脉冲数）
	double f;//判别式
	//设置当前坐标
	x_now=0;
	y_now=A*sin(w*x_now+fai);	
	
	//开始画sin
	move_onestep('y','+',speed);
	y_now=y_now+0.0002;

	while(count>0)
	{
		f=y_now-A*sin(w*x_now+fai);
		if(x_now <= (pai/(2*w)))	//0~pai/2w
		{
			if(f>=0)	{move_onestep('x','+',speed);x_now=x_now+0.0002;}
			else	{move_onestep('y','+',speed);y_now=y_now+0.0002;}
		}
		else if(x_now <= 2*(pai/(2*w)))	//pai/2w ~ pai/w
		{
			if(f>=0)	{move_onestep('y','-',speed);y_now=y_now-0.0002;}
			else	{move_onestep('x','+',speed);x_now=x_now+0.0002;}
		}	
		else if(x_now <= 3*(pai/(2*w)))	//pai/w ~ 3pai/2w
		{
			if(f>=0)	{move_onestep('y','-',speed);y_now=y_now-0.0002;}
			else	{move_onestep('x','+',speed);x_now=x_now+0.0002;}
		}		
		else if(x_now <= 4*(pai/(2*w)) )	// 3pai/2w ~ 2pai/w
		{
			if(f>=0)	{move_onestep('x','+',speed);x_now=x_now+0.0002;}
			else	{move_onestep('y','+',speed);y_now=y_now+0.0002;}
		}
		count--;
	}
}
/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/
//	//sin曲线进阶版（任意初相）
//	void draw_sin2(double A,double w,double fai,unsigned int speed)
//	{
//	unsigned long int count=(pai/w+2*A)*2*5000;//计算总步数（总脉冲数）
//	double f;//判别式
//	//设置当前坐标
//	x_now=0;
//	y_now=A*sin(w*x_now+fai);	

//	//开始画sin
//	move_onestep('y','+',speed);
//	y_now=y_now+0.0002;

//	while(count>0)
//	{
//		f=y_now-A*sin(w*x_now+fai);
//		
//		if(cos(w*x_now+fai)>0)	//上升段
//		{
//			if(f>=0)	{move_onestep('x','+',speed);x_now=x_now+0.0002;}
//			else	{move_onestep('y','+',speed);y_now=y_now+0.0002;}			
//		}
//		else if(cos(w*x_now+fai)<0)	//下降段
//		{
//			if(f>=0)	{move_onestep('y','-',speed);y_now=y_now-0.0002;}
//			else	{move_onestep('x','+',speed);x_now=x_now+0.0002;}			
//		}
//		else	{ move_onestep('x','+',speed);x_now=x_now+0.0002;}	//波峰波谷
//		count--;
//	}
//	}

//double myfunc(double x)	//把待绘制函数封装成“函数”
//{
//	double value=0;
//	value=sin(x);		//待绘制的函数，以sin为例
//	return value;
//}

//double differentiate(double x0)	//求导函数
//{
//	double dx,dd1,dd2;
//	dx=0.01;    //设 dx 初值
//	do{
//			dd1=(myfunc(x0) - myfunc(x0+dx))/dx;    //计算导数dd1
//			dx = 0.5 * dx;  // 减小步长
//			dd2=(myfunc(x0) - myfunc(x0+dx))/dx;    //计算导数dd2
//	}while(abs(dd1-dd2) >= 1e-06); //判断新旧导数值之差是否满足精度
//	return dd2;
//}

////任意函数曲线绘制
//void draw_random_func(double x1,double x2,unsigned int speed)	//起点x、终点x、速度
//{
//	//这里用当前x值x_now来判断插补终点，不再用计算总脉冲数的办法
//	double F;//判别式
//	//设置当前坐标
//	x_now=x1;
//	y_now=myfunc(x_now);	
//	
//	//开始画绘制
//	while(x_now<=x2)	//只要x_now还没到达终点x2便继续运动
//	{
//		F=y_now-myfunc(x_now);	//任意函数的判别函数F的表达式
//		if(differentiate(x_now)>0)	//上升段
//		{
//			if(F>=0)	{move_onestep('x','+',speed);x_now=x_now+0.0002;}
//			else	{move_onestep('y','+',speed);y_now=y_now+0.0002;}			
//		}
//		else if(differentiate(x_now)<0)	//下降段
//		{
//			if(F>=0)	{move_onestep('y','-',speed);y_now=y_now-0.0002;}
//			else	{move_onestep('x','+',speed);x_now=x_now+0.0002;}			
//		}
//		else	{ move_onestep('x','+',speed);x_now=x_now+0.0002;}	//波峰波谷
//	}
//}
/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/

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

