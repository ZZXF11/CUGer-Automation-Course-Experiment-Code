#ifndef __USART3_H
#define __USART3_H	 
#include "sys.h"  

#define USART2_MAX_RECV_LEN		600					//�����ջ����ֽ���
#define USART2_MAX_SEND_LEN		600					//����ͻ����ֽ���
#define USART2_RX_EN 			1					//0,������;1,����.

extern u8  USART2_RX_BUF[USART2_MAX_RECV_LEN]; 		//���ջ���,���USART2_MAX_RECV_LEN�ֽ�
extern u8  USART2_TX_BUF[USART2_MAX_SEND_LEN]; 		//���ͻ���,���USART2_MAX_SEND_LEN�ֽ�
extern vu16 USART2_RX_STA;   						//��������״̬

extern double gx1 ,gy1 ,gx2,gy2 ;
extern int mark;
void HMI_Send_End();
void usart2_init(u32 bound);				//����2��ʼ�� 
void u2_printf(char* fmt,...);
#endif













