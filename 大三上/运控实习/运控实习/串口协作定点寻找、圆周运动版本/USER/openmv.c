#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "openmv.h"
#include "string.h"
unsigned char sign,sign1,counter,counter1=0;
unsigned char Data_Get[6];
unsigned char Data_Get1[40];
double coordinate[4];
double coordinate1[38];
static unsigned char Data_Rec[6];
static unsigned char Data_Rec1[40];
unsigned char mf=0;
static unsigned char  mount=0;
void OPENMV_UART2(unsigned long baudrate)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	 
	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure); 
	USART_ITConfig(USART2, USART_IT_TXE, DISABLE);    
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	USART_ClearFlag(USART2,USART_FLAG_TC);	
	USART_Cmd(USART2, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		if(mf==0){
		Data_Rec[counter] = USART_ReceiveData(USART2);   //接收数据
		if(counter == 0 && Data_Rec[0] != 0xE6)	return;      //第 0 号数据不是帧头，跳过
		counter++;
		if(counter == 6) //接收到 11 个数据
		{
			memcpy(Data_Get,Data_Rec,6);
			counter = 0; //重新赋值，准备下一帧数据的接收
			sign = 1;
		}		
	}
		else if(mf==1){
			Data_Rec1[counter1] = USART_ReceiveData(USART2);   //接收数据
		if(counter1 == 0 && Data_Rec1[0] != 0xE6)	return;      //第 0 号数据不是帧头，跳过
		counter1++;
		if(counter1 == 40) //接收到 11 个数据
		{
			memcpy(Data_Get1,Data_Rec1,40);
			counter1 = 0; //重新赋值，准备下一帧数据的接收
			sign1 = 1;
		}	
		}
	}
	USART_ClearITPendingBit(USART2,USART_IT_RXNE);
}

void OPENMV_Data_Get(void)
{
	if(sign)
	{
		sign = 0;
		if(Data_Get[0]==0xE6)
		{
			if(Data_Get[5] == 0xFF)
			{
			 	 coordinate[0]=(double)((int)Data_Get[1]*0.43);
				 coordinate[1]=(int)Data_Get[2]*0.43;
				 coordinate[2]=(int)Data_Get[3]*0.43;
				 coordinate[3]=(int)Data_Get[4]*0.43;
//				 coordinate[0]=0.43*Data_Get[1];
//				 coordinate[1]=0.43*Data_Get[2];
//				 coordinate[2]=0.43*Data_Get[3];
//				 coordinate[3]=0.43*Data_Get[4];
			}
		}
	}
}

void OPENMV_Data(void)
{
	if(sign1)
	{
		sign1 = 0;
		if(Data_Get1[0]==0xE6)
		{
			if(Data_Get1[39] == 0xFF)
			{
					for(;mount<38;++mount){
				      coordinate1[mount]=0.43*Data_Get1[mount+1];
					}
				 mount=0;
			}
		}
	}
}
