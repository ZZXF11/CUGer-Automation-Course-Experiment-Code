#include "sys.h"
#include "usart.h"	  
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/8/18
//�汾��V1.5
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*ʹ��microLib�ķ���*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  
  
void uart_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}
unsigned char usign,ucounter=0;
unsigned char Data;
int xzuobiao;
int yzuobiao;
unsigned char yundong;
unsigned char jieshou=0;
unsigned char diandong=0;
static unsigned char Data_Rec[3];
static unsigned char Data_zuobiao[4];
static unsigned char Data_yundong[3];
void USART1_IRQHandler(void)                	//����1�жϷ������
	{
		//Data: 1:�㶯ģʽ  2������
unsigned char Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		Res = USART_ReceiveData(USART1);   //��������
		if(Res==0xe6){ //�˵�ѡ�� e6Ϊ�˵�ѡ��
			usign=1;//�˵�
		}
		else	if(Res==0xe5){ // e5Ϊȷ���趨����
			usign=2;//�趨����
		}
		else	if(Res==0xe4){ //e4Ϊ��ʼ�˶�
			usign=3;//��ʼ�˶�
		}
		else	if(Res==0xe3){ //e4Ϊ��ʼ�˶�
			usign=4;//�㶯ģʽ
			Data=0x01;
		}	
		if(usign==1){ //�˵�
		Data_Rec[ucounter]=Res;
			ucounter++;
			if(ucounter == 3 && Data_Rec[2] == 0xFF) //���յ� 3 ������
		 { 
			Data=Data_Rec[1];
			ucounter = 0; //���¸�ֵ��׼����һ֡���ݵĽ���
		 }		
		}
		
		else if(usign==2){  //��������
		Data_zuobiao[ucounter]=Res;
			ucounter++;
			if(ucounter == 4 && Data_zuobiao[3] == 0xFF ) //���յ� 4 ������
		 {
			xzuobiao=Data_zuobiao[1];
			yzuobiao=Data_zuobiao[2];
			ucounter = 0; //���¸�ֵ��׼����һ֡���ݵĽ���
			jieshou = 1; //��־λ����ʾ���Խ�����������
		 }		
		}
		
		else if(usign==3){ //��ʼ�˶�
		Data_yundong[ucounter]=Res;
			ucounter++;
			if(ucounter == 3 && Data_yundong[2] == 0xFF) //���յ� 3 ������
		 { 
			yundong=Data_yundong[1];
			ucounter = 0; //���¸�ֵ��׼����һ֡���ݵĽ���
		 }		
		}
		
		else if(usign==4){ //�㶯ģʽ
		Data_Rec[ucounter]=Res;
			ucounter++;
			if(ucounter == 3 && Data_Rec[2] == 0xFF) //���յ� 3 ������
		 { 
			diandong=Data_Rec[1];
			ucounter = 0; //���¸�ֵ��׼����һ֡���ݵĽ���
		 }		
		}
		
	}
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
} 
#endif	

