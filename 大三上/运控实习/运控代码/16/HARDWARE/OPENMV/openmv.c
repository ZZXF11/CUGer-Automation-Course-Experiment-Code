
#include "delay.h"
#include "usart2.h"
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"	 
#include "timer.h"	  
#include "stm32f10x_tim.h"

#include "stm32f10x_rcc.h"

#include "openmv.h"
double getx1 = 0,gety1 = 0,getx2 = 0,gety2 = 0;
uint8_t flag = 0;
//u16 distance[5] ={0,0,0,0,0};
//int cnt;

//用usart.h中的printf打印到串口1
//TFMINI的初始化
void openmv_init(u32 bound)
{

	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);	//使能USART3时钟

	//PB10，PB11，初始化串口3
	//USART3_TX   GPIOB.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOA.9

	//USART3_RX	  GPIOB.11初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);// 

	//Usart3 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=4 ;//抢占优先级4
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;		//子优先级4
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

	//USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART3, &USART_InitStructure); //初始化串口3

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//串口3中断

	USART_Cmd(USART3, ENABLE);                    //使能串口3

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
}

void USART3_IRQHandler(void)
{
	double temp_data ;
	if(USART_GetITStatus(USART3,USART_IT_RXNE) != RESET)
	{
		temp_data = USART_ReceiveData(USART3);
		
		if((temp_data == 0xB3) && (flag == 0))
		{
			flag = 1;
		}
		else if((temp_data == 0xC3) && (flag == 1))
		{
			flag = 2;
		}
		else if(flag == 2)
		{
			getx1 = temp_data;//目标的x轴坐标
			
			flag = 3;
		}
		else if(flag == 3)
		{
			gety1 = temp_data;//目标的x轴坐标
			
			flag = 4;
		}
		else if(flag == 4)
		{
			getx2 = temp_data;//目标的x轴坐标
			
			flag = 5;
		}
		else if(flag == 5)
		{
			gety2 = temp_data;//目标的
//			if(cnt==5)
//	{cnt=0;}	
			
			flag = 6;
		}
		else if((temp_data == 0xFF) && (flag == 6)){
		  flag = 7;
		
		}
		else if((temp_data == 0xFF) && (flag == 7)){
	   	flag = 0;
		
		} 
	}
	USART_ClearITPendingBit(USART3, USART_IT_RXNE);
}

//排序算法
//float openmv_sort(void)
//{
//	int i,j,t,sum;
//	float aver;
//	for(j=0;j<4;j++)
//		for(i=0;i<4-j;i++)
//	    if(distance[i]>distance[i+1])
//		{t=distance[i];distance[i]=distance[i+1];distance[i+1]=t;}		
//	sum=distance[1]+distance[2]+distance[3];
//	aver=sum/3.0;
//	return aver;
//}

