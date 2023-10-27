#include <reg51.h>
#include "8255.c"
#include "KEYLED.c"
#include "YALI.c"
#include "BEEP.c"
#include "temp.c"
#include "motor.c"
#include "dianzhen.c"
#include "Bmotor.c"
#include "LCD.c"



sbit P1_0 = P1^0;
sbit P1_1 = P1^1;



unsigned char speed;//用于读取当前速度
int TT=60;//循环定时
int overspeed;
unsigned char ADResult0,ADResult1;//压力读数和温度读数

//void Setmoshi()//设置模式：道路、标载、开启温度
//{       
//        if(TestKey())
//        {            
//           switch (GetKey()& 0x0f)  // (GetKey()& 0x0f)的值就等于按键的数值
//           {
//               case 1:  initMotor=0x45;break; //可容许右起2档
//               case 2:  initMotor=0x54;break; //可容许右起3档
//               case 3:  initMotor=0x59;break; //可容许所有档                 
//           }               
//        }          
//}

void Setmoshi()//设置模式：道路、标载、开启温度
{       
        if(TestKey())
        {            
           switch (GetKey()& 0x0f)  // (GetKey()& 0x0f)的值就等于按键的数值
           {
               case 1:  {initMotor=0x45;DisplayLcd();break;} //可容许右起1档,按1
               case 2:  {initMotor=0x54;DisplayLcd();break;} //可容许右起2档,按2
               case 3:  {initMotor=0x59;DisplayLcd();break;} //可容许所有档,按3 
               case 0x0a:  {initYALI=0x07;DisplayLcd();break;}//载重5人,按a 
               case 0x0b:  {initYALI=0x15;DisplayLcd();break;}//载重7人,按b 
               case 0x0c:  {initYALI=0x25;DisplayLcd();break;}//载重9人,按c  
               case 0x00:  {--initTEMP;DisplayLcd();break;}   //下调空调开启温度,按0
               case 0x0f:  {++initTEMP;DisplayLcd();break;}   //上调空调开启温度,按F                
           }    //****暻的箱子：1档40，2档55，3档75***           
        }          
}

void DisplayS()//速度显示函数
{
	unsigned int i=0,sum=0;
	i=(speed>>4) & 0x0f;
	if(i>9) sum=16*(i-0x0a+10);
	else sum=16*i;
	i=speed & 0x0f;
	if(i>9) sum+=i-0x0a+10;
	else sum+=i;
	LEDBuf[4] = LEDMAP[sum/10];
	LEDBuf[5] = LEDMAP[sum%10];
//  LEDBuf[4] = LEDMAP[(speed>>4) & 0x0f];
//  LEDBuf[5] = LEDMAP[speed & 0x0f];
}

unsigned char SetSpeed(){
	unsigned char S,R;
	S=PortB;//开关的高4位设置速度
	if(S>=0x00&&S<=0x0f)R=0xc5;
	if(S>=0x10&&S<=0x1f)R=0xcf;
	if(S>=0x20&&S<=0x3f)R=0xdf;
	if(S>=0x40&&S<=0x7f)R=0xef;
	if(S>=0x80&&S<=0xff)R=0xff;
	return R;
}

int oil(){
	unsigned char S,Z;
	int R;
	Z=PortB;
	S = (Z & 0x0f);
	if(S==0x01){
		R=0;//油量低
	}
	else if(S==0x00){
		R=2;//没油
	}
	else R=1;
	return R;
}

void INTT0() interrupt 0 //外部中断0
{
	//需要关闭定时和计数、并将speed置0
	TR0  = 0;//关闭T0
  TH0  = 0x3c;//设置初值，50000次溢出
  TL0  = 0xb0;
	TR1  = 0;//设置计数器T1
  TH1  = 0;
  TL1  = 0;
	speed=TL1;
	TT=60;
  //以上为关闭定时器和计数器
	MOTOR=0xc5;
	PortA=0xff;
	if(oil()==0){//显示油量低
		DZO();
	}
	if(ADResult0>initYALI){//显示已超载
		DZZ();
	}
	PortA=0x00;//PA口置0
	P1_0=1;//关闭中断
	//重新打开定时器和计数器
  TR0  = 1;//打开定时器
	TR1  = 1;//打开计数器
}

void TT0() interrupt 1 //定时器T0中断
{
	if(TT!=0){
	TH0  = 0x3c;//设置初值，50000次溢出
  TL0  = 0xb0;
		TR0=1;
		--TT;
	}
	if(TT==0){
	TT=60;
	TH0  = 0x3c;//设置初值，50000次溢出
  TL0  = 0xb0;
	speed=TL1;
  TH1  = 0;
  TL1  = 0;
	TR0=1;
	TR1=1;
	}
	
}

void INTT1() interrupt 2 //外部中断1
{
	//需要关闭定时和计数、并将speed置0
	TR0  = 0;//关闭T0
  TH0  = 0x3c;//设置初值，50000次溢出
  TL0  = 0xb0;
	TR1  = 0;//设置计数器T1
  TH1  = 0;
  TL1  = 0;
	speed=TL1;
	TT=60;
  //以上为关闭定时器和计数器
	MOTOR=0x80;
	if(oil()==2){//显示请加油
			 DZOO();
		 }
	if(overspeed==1){//当速度超过设定值，进入中断0
			 DZS();
		   overspeed=0;
		 }
	PortA=0x00;//PA口置0
	MOTOR=SetSpeed();
	P1_1=1;//关闭中断
  //重新打开定时器和计数器
  TR0  = 1;//打开定时器
	TR1  = 1;//打开计数器
}

void main()  //主函数
{
   unsigned char i = 0;
	 register unsigned char dd;//档位、油量显示
   unsigned char j,OIL;
	 CAddr=mode; // 方式0，PA，PC输出，PB输入
	 IE=0x87;//中断初始化
	 TCON=0x05;//外部中断0、1均为低电平触发
	 P1=0xff;
	 readSpeed();
   DisplayLcd();
   while(1) {
		 Setmoshi();//设置模式
		 MOTOR=SetSpeed();//设置电机转速
     ADResult0 =  ReadYALI();//压力读数
		 ADResult1 =  ReadTemp();//温度读数
		 PortC = 0x00;
		 dd = PortB;     //档位、油量显示
     PortA = dd;
		 if(ADResult0>initYALI){//当压力超过设定值，进入中断0
			 P1_0=0;}
		 if(ADResult1>initTEMP&&ADResult1<0x80){//当压温度超过设定值，步进电机转动
			  PortC = 0x01;}
		 if(oil()==0){//油量低则进入中断0
			 P1_0=0; }
		 if(oil()==2){//彻底没油，进入中断1
			 P1_1=0;}
		 if(speed>initMotor&&speed<0x59){//当速度超过设定值，进入中断0
			 overspeed=1;
			 P1_1=0;}
		 DisplayT();//显示温度
		 DisplayS();//显示速度
     for(j=0; j<30; j++)DisplayLED();   // 延时
   }
}

