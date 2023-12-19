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
  int data[10];
	int mark = 0;
int t = 0;
int straight_xiangxian=0;
long straight_x=0,straight_y=0;//ֱ�߲岹�յ�
int circlecent_x=0,circlecent_y=0;//Բ��Բ��
int circle_way = 0;//Բ���˶�����˳��ʱ��


int mycircle_x=0,mycircle_y=0;
int mycircle_way =0;
int mycirccle_angle =0;
int mycircle_endx=0,mycircle_endy=0;
int mycircle_getr=0;
extern long current_x;
extern long current_y;
extern int get_r;
double gx1 = 0,gy1 = 0,gx2 = 0,gy2 = 0;
int xdir=3,ydir=3;//������ǰ
int anmark = 0;
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

void USART1_IRQHandler(void)                	//����1�жϷ������
	{
double temp_data ;
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
	{
		data[t] = USART_ReceiveData(USART1);
		t++;
		if(t ==1 && data[0] != 0xB1 && data[0] != 0xB2 && data[0] != 0xB3 && data[0] != 0xB4 && data[0] != 0xB5 && data[0] != 0xA1 && data[0] != 0xA2 && data[0] != 0xA3&& data[0] != 0xC3 && data[0] != 0xC4 && data[0] != 0xC5 && data[0] != 0xC6 && data[0] != 0xD4&& data[0] != 0xf4  )	
			{     //�� 0 �����ݲ���֡ͷ������
			t = 0;
	    }
			
			
			
		if(t == 2 && data[0] == 0xB1){
		  mark = 1;//�ٿ�xy
		
		
		}
		if(t == 2 && data[0] == 0xf4){
		  mark = 4;//�ؼ�
		}
		if(t == 1 && data[0] == 0xC3){
			mark = 1;//�ٿ�xy
		 xdir = 0;//xǰ
		 anmark = 1;
		
		
		}
		if(t == 1&& data[0] == 0xC4){
			 mark = 1;//�ٿ�xy
		 xdir = 1;
		 anmark = 1;
		
		
		}
		if(t == 1&&data[0] == 0xC5){
			 mark = 1;//�ٿ�xy
		 ydir = 0;
		 anmark = 1;
	
		
		}
		if(t == 1&&data[0] == 0xC6){
			 mark = 1;//�ٿ�xy
		 ydir = 1;
		 anmark = 1;
	
		}
		
	
		if(t == 1 && data[0] == 0xD4){
		mark = 1;
		anmark = 0;//�����������˶�ֹͣ
		xdir=3;
			ydir=3;
		}
	
	
		
		
		
		/*
		if(t == 2 && data[0] == 0xB2){
		//  mark = 2;// ֱ���˶�
	    	 
		}
		if(t == 2 && data[0] == 0xA1){
		//��������������straightx��straighty����
		// mark = 2;
		 
		}*/
		if(t == 4 && data[0] == 0xA1 ){//straightx,y
		mark = 2;
		straight_xiangxian =data[1];
		if(straight_xiangxian == 1){
		 straight_x = data[2];
	   straight_y = data[3];
		}
		else if(straight_xiangxian == 2){
		 straight_x = 0-data[2];
	   straight_y = data[3];
		}
		else if(straight_xiangxian == 3){
		 straight_x = 0-data[2];
	   straight_y = 0-data[3];
		}
		else if(straight_xiangxian == 4){
		 straight_x = data[2];
	   straight_y = 0-data[3];
		}
		
		
		
		}
		
		
		
		
		
		/*
		if(t == 2 && data[0] == 0xB3){
		 // mark = 3;//Բ���˶�
	   // gx2 = data[1];	 
		}
		if(t == 3 &&  data[0] == 0xA2){
		 // mark = 3;
			
			
	    //gy2 = data[2];	 
		}
		*/
		if(t == 5  && data[0] == 0xA2){
		  mark = 3;
			circlecent_x = data[1];
			circlecent_y = data[2];
			get_r = sqrt(abs(circlecent_x*circlecent_x  + circlecent_y*circlecent_y -current_x*current_x - current_y*current_y ));
			if(data[4]==1){
			circlecent_x = data[1];
			circlecent_y = data[2];
			
			}
			else if(data[4]==2){
			
			circlecent_x = 0-data[1];
			circlecent_y = data[2];
			
			}
			else if(data[4]==3){
			circlecent_x = 0-data[1];
			circlecent_y = 0-data[2];
			
			
			}
			else if(data[4]==4){
			
			circlecent_x = data[1];
			circlecent_y = 0-data[2];
			
			}
			
			circle_way = data[3];
			
			
	    	 
		}
		if(t == 6 && data[0] == 0xA3){
		  mark = 5;//Բ���岹
			mycircle_x = data[1];
			mycircle_y = data[2];
			mycircle_way = data[3];
			mycirccle_angle = data[4];
			
			mycircle_getr=sqrt(abs(mycircle_x*mycircle_x  + mycircle_y*mycircle_y -current_x*current_x - current_y*current_y ));
			
		  switch(data[5]){//����
				case 1:
					if(mycircle_way==0){//��ʱ��
					
						if(mycirccle_angle>=90){
						  mycircle_endx = mycircle_getr*sin(3.14*mycirccle_angle/180);
							mycircle_endy = mycircle_getr + mycircle_getr*cos(3.14*(180-mycirccle_angle)/180);
						}
						else{
						  mycircle_endx = mycircle_getr*sin(3.14*mycirccle_angle/180);
						  mycircle_endy = mycircle_getr - mycircle_getr*cos(3.14*mycirccle_angle/180);
						}
						
					}
          else{
					 
						if(mycirccle_angle>=90){
						  mycircle_endy = mycircle_getr*sin(3.14*mycirccle_angle/180);
							mycircle_endx = mycircle_getr + mycircle_getr*cos(3.14*(180-mycirccle_angle)/180);
						}
						else{
						  mycircle_endy = mycircle_getr*sin(3.14*mycirccle_angle/180);
						  mycircle_endx = mycircle_getr - mycircle_getr*cos(3.14*mycirccle_angle/180);
						}
				
					}
				
					break;
				case 2:
					if(mycircle_way==0){//��ʱ��
					
						if(mycirccle_angle>=90){
						  mycircle_endy = mycircle_getr*sin(3.14*mycirccle_angle/180);
							mycircle_endx = mycircle_getr + mycircle_getr*cos(3.14*(180-mycirccle_angle)/180);
						}
						else{
						  mycircle_endy = mycircle_getr*sin(3.14*mycirccle_angle/180);
						  mycircle_endx = mycircle_getr - mycircle_getr*cos(3.14*mycirccle_angle/180);
						}
						
					}
          else{
					 
						if(mycirccle_angle>=90){
						  mycircle_endx = mycircle_getr*sin(3.14*mycirccle_angle/180);
							mycircle_endy = mycircle_getr + mycircle_getr*cos(3.14*(180-mycirccle_angle)/180);
						}
						else{
						  mycircle_endx = mycircle_getr*sin(3.14*mycirccle_angle/180);
						  mycircle_endy = mycircle_getr - mycircle_getr*cos(3.14*mycirccle_angle/180);
						}
				
					}
				  mycircle_x = 0 - mycircle_x;
					mycircle_y = mycircle_y;
				  mycircle_endx = 0-mycircle_endx;
					mycircle_endy = mycircle_endy;
				
				
					break;
			
				case 3:
					if(mycircle_way==0){//��ʱ��
					
						if(mycirccle_angle>=90){
						  mycircle_endx = mycircle_getr*sin(3.14*mycirccle_angle/180);
							mycircle_endy = mycircle_getr + mycircle_getr*cos(3.14*(180-mycirccle_angle)/180);
							
						}
						else{
						  mycircle_endx = mycircle_getr*sin(3.14*mycirccle_angle/180);
						  mycircle_endy = mycircle_getr - mycircle_getr*cos(3.14*mycirccle_angle/180);
						}
						
					}
          else{
					 
						if(mycirccle_angle>=90){
						  mycircle_endy = mycircle_getr*sin(3.14*mycirccle_angle/180);
							mycircle_endx = mycircle_getr + mycircle_getr*cos(3.14*(180-mycirccle_angle)/180);
						}
						else{
						  mycircle_endy = mycircle_getr*sin(3.14*mycirccle_angle/180);
						  mycircle_endx = mycircle_getr - mycircle_getr*cos(3.14*mycirccle_angle/180);
						}
				
					}
					mycircle_x = 0 - mycircle_x;
					mycircle_y = 0 -mycircle_y;
				  mycircle_endx = 0-mycircle_endx;
					mycircle_endy = 0-mycircle_endy;
				
					break;	
			  case 4:
					if(mycircle_way==0){//��ʱ��
					
						if(mycirccle_angle>=90){
						  mycircle_endy = mycircle_getr*sin(3.14*mycirccle_angle/180);
							mycircle_endx = mycircle_getr + mycircle_getr*cos(3.14*(180-mycirccle_angle)/180);
						}
						else{
						  mycircle_endy = mycircle_getr*sin(3.14*mycirccle_angle/180);
						  mycircle_endx = mycircle_getr - mycircle_getr*cos(3.14*mycirccle_angle/180);
						}
						
					}
          else{
					 
						if(mycirccle_angle>=90){
						  mycircle_endx = mycircle_getr*sin(3.14*mycirccle_angle/180);
							mycircle_endy = mycircle_getr + mycircle_getr*cos(3.14*(180-mycirccle_angle)/180);
						}
						else{
						  mycircle_endx = mycircle_getr*sin(3.14*mycirccle_angle/180);
						  mycircle_endy = mycircle_getr - mycircle_getr*cos(3.14*mycirccle_angle/180);
						}
				
					}
				  mycircle_x = mycircle_x;
					mycircle_y = 0-mycircle_y;
				  mycircle_endx = mycircle_endx;
					mycircle_endy = 0-mycircle_endy;
				
					break;
			
			}
			
		
		}
		
		
		
		
			if(t == 2 && data[0] == 0xB5){
		  mark = 6;//sin���Ǻ���
		
		}
		if(data[t-1] == 0xFF){//֡β
		
			t = 0;
			//memset(data, 0, sizeof data);//�������
		}
		
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE); 
}

/*
void USART1_IRQHandler(void)                	//����1�жϷ������
	{
double temp_data ;
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
	{
		data[t] = USART_ReceiveData(USART1);
		t++;
		if(t ==1 && data[0] != 0xA1 && data[0] != 0xA2 && data[0] != 0xA3 && data[0] != 0xA4 )	
			{     //�� 0 �����ݲ���֡ͷ������
			t = 0;
	    }
		if(t == 2 && data[0] == 0xA1){
		  mark = 1;//Բ���˶�
			gx2 = data[1];
		
		}
		if(t == 3 && data[0] == 0xA1){
		  mark = 1;
			gy2 = data[2];
		
		}
		if(t == 2 && data[0] == 0xA2){
		  mark = 2;// ѭ��
	    	 
		}
		
		if(t == 2 && data[0] == 0xA3){
		  mark = 3;//����ָ��λ�� 
	    gx2 = data[1];	 
		}
		if(t == 3 && data[0] == 0xA3){
		  mark = 3;//����ָ��λ�� 
	    gy2 = data[2];	 
		}
		if(t == 2 && data[0] == 0xA4){
		  mark = 4;//��ʾ
	    	 
		}
		if(t == 2 && data[0] == 0xA5){
		  mark = 5;//����
	    	 
		}
		
		if(data[t-1] == 0xFF){//֡β
		
			t = 0;
		}
		
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE); 
} */
#endif	

