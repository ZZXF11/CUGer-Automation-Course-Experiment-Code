#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "mpu6050.h"
#include "string.h"
unsigned char sign,counter=0;
unsigned char Data_Get[11];
static unsigned char Data_Rec[11];
float Pitch,Roll,Yaw;

u8 x_data[5] = {0};
u8 y_data[5] = {0};
float x_final = 0,y_final = 0;
void MPU6050_UART2(unsigned long baudrate)
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
		Data_Rec[counter] = USART_ReceiveData(USART2);   //接收数据
//		if(counter == 0 && Data_Rec[0] != 0x55)	return;      //第 0 号数据不是帧头，跳过
//		counter++; 
//		if(counter == 11) //接收到 11 个数据
//		{ 
//			memcpy(Data_Get,Data_Rec,11);
//			counter = 0; //重新赋值，准备下一帧数据的接收
//			sign = 1;
//		}
		if(counter == 0 && Data_Rec[0] != 0xE6)	return;      //第 0 号数据不是帧头，跳过
		counter++;
		if(counter == 6) //接收到 11 个数据
		{
			memcpy(Data_Get,Data_Rec,6);
			counter = 0; //重新赋值，准备下一帧数据的接收
			sign = 1;
		}		
	}
	USART_ClearITPendingBit(USART2,USART_IT_RXNE);
}

void MPU6050_Data_Get(void)
{
	if(sign)
	{
		sign = 0;
		if(Data_Get[0]==0x55)
		{
			if(Data_Get[1] == 0x53)
			{
                  Roll  = ((short)(Data_Get[3]<<8| Data_Get[2]))/32768.0*180;   //X轴滚转角（x 轴）
                  Pitch = ((short)(Data_Get[5]<<8| Data_Get[4]))/32768.0*180;   //Y轴俯仰角（y 轴）
                  Yaw   = ((short)(Data_Get[7]<<8| Data_Get[6]))/32768.0*180;   //Z轴偏航角			
			}
		}
	}
}
u8 OpenMV_Data_Get(void)
{
	if(sign)
	{
		sign = 0;
		if(Data_Get[0]==0xE6)
		{
			if(Data_Get[5] == 0xFF)
			{
          x_data[4] = Data_Get[1];
          y_data[4] = Data_Get[2];
				  x_data[4] = Data_Get[3];
          y_data[4] = Data_Get[4];
//				  x_final = ((float)(x_data[4]+x_data[3]+x_data[2]+x_data[1]+x_data[0]))/5;
//				  y_final = ((float)(y_data[4]+y_data[3]+y_data[2]+y_data[1]+y_data[0]))/5;
//				  x_data[0]=x_data[1];x_data[1]=x_data[2];x_data[2]=x_data[3];x_data[3]=x_data[4];
//				  y_data[0]=y_data[1];y_data[1]=y_data[2];y_data[2]=y_data[3];y_data[3]=y_data[4];
				  return 1;
			}
			else return 0;
		}
		else return 0;
	}
	else return 0;
}