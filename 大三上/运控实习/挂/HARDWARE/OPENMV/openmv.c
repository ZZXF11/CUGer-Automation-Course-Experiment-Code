
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

//��usart.h�е�printf��ӡ������1
//TFMINI�ĳ�ʼ��
void openmv_init(u32 bound)
{

	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);	//ʹ��USART3ʱ��

	//PB10��PB11����ʼ������3
	//USART3_TX   GPIOB.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOA.9

	//USART3_RX	  GPIOB.11��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);// 

	//Usart3 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=4 ;//��ռ���ȼ�4
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;		//�����ȼ�4
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

	//USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	USART_Init(USART3, &USART_InitStructure); //��ʼ������3

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//����3�ж�

	USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���3

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
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
			getx1 = temp_data;//Ŀ���x������
			
			flag = 3;
		}
		else if(flag == 3)
		{
			gety1 = temp_data;//Ŀ���x������
			
			flag = 4;
		}
		else if(flag == 4)
		{
			getx2 = temp_data;//Ŀ���x������
			
			flag = 5;
		}
		else if(flag == 5)
		{
			gety2 = temp_data;//Ŀ���
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

//�����㷨
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

