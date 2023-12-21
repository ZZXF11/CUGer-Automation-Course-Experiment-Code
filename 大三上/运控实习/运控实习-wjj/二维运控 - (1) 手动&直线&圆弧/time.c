#include "time.h"

// 函数作用：毫秒延时函数
// 参数：延时的毫秒数
void delayms(unsigned int tms)
{
  unsigned int i,j;		
  for(i=tms;i>0;i--)
    for(j=110;j>0;j--);	
}

// 函数作用：微秒延时函数
// 参数：延时的微秒数
void delayus(unsigned int tus)
{
  unsigned int i;		
  for(i=tus;i>0;i--)
  	_nop_();	// 延时一个机器周期，当晶振频率为12MHz时，延时1us  	
}

//初始化中断
void inter_init()
{
	
	TMOD |= 0x02;  //定时器16为计数工作模式
	TH0 =0x00;
	TL0 =0x00; //5ms
//	TH0 =0xED;
//	TL0 =0xFF; //5ms
	ET0 = 1; //开定时器0中断
	TR0 = 1;//启动定时器0
	EA = 1;	//开总中断
}

void TIM1init(void)//定时器0初始化
{
	TMOD|=0x20;//定时器1工作方式2，TH1是重装值，TL1是初值
	TH1=0x00; //重载值
	TL1=0x00; //初始化值
	ET1=0;    //开中断
	TR1=1;
}

//外部中断初始化
void EX0init(void)
{
 IT0 = 1;   //指定外部中断0下降沿触发，INT0 (P3.2)
 EX0 = 1;   //使能外部中断
 EA = 1;    //开总中断
}