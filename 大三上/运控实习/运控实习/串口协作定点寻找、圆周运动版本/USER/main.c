#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "key.h"
#include "led.h"	 
#include "usmart.h"	
#include "driver.h"
#include "openmv.h"
#include <math.h>
/*
�������1���ɰ���PA.0����
Pluse+->PA.1��Pluse-��GND
DIR+->PA.8��DIR-��GND
EN+->PA.11��EN-��GND
�������2���ɰ���PA.4����
Pluse+->PA.7��Pluse-��GND
DIR+->PA.6��DIR-��GND
EN+->PA.5��EN-��GND
*/
double xdistance;
double ydistance;
double y;
double x;
double j=0;
int ci=0;
double lb=0,rb=0,la=0,ra=0,dl=0,dr=0;
double L;
double R;
extern u16 count[2];
extern double coordinate[4];  //1��x���� 2:y���� 3:x���� 4:����
extern double coordinate1[38]; 
extern int xzuobiao;
extern int yzuobiao;
extern unsigned char yundong;
extern unsigned char Data;
extern unsigned char jieshou;
extern unsigned char diandong;
extern unsigned char mf;
void GPIO_Config(void)
{ 
		GPIO_InitTypeDef GPIO_InitStructure; 

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE , ENABLE); //ʹ��IOA
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE); //ʹ��IOC
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //ͨ���������ģʽ
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //ָ��GPIO���ſ���������Ƶ��Ϊ50MHZ
		GPIO_Init(GPIOE, &GPIO_InitStructure); 

	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	    		 //LED1-->PC.6 �˿�����, �������  ����
    GPIO_Init(GPIOC, &GPIO_InitStructure);	  
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	    		 //LED1-->PC.7 �˿�����, �������   ����
    GPIO_Init(GPIOC, &GPIO_InitStructure);	  
//		GPIO_ResetBits(GPIOA, GPIO_Pin_2);//ָ����������͵�ƽ����ʱ��ȫ��	ʹ��
//		GPIO_SetBits(GPIOA, GPIO_Pin_11);//ָ����������͵�ƽ����ʱ��ȫ�𣬷���
}
void diandongmoshi(void){
	//diandong: 1:X+ 2:X- 1:Y+ 1:Y-
	if(diandong == 0x01){   //X+
			while(1){
					TIM_Cmd(TIM3, ENABLE); 
					Locate_Rle3(3000,CCW);   
						 if(Data==0x05) {
							TIM_Cmd(TIM3, DISABLE);  
							 diandong=0;
							 break;
						 }
					 }
				}
				else if(diandong == 0x02){ //X-
			while(1){
				TIM_Cmd(TIM3, ENABLE); 
					Locate_Rle3(3000,CW); 
						 if(Data==0x05) {
							TIM_Cmd(TIM3, DISABLE);  
							  diandong=0;
							 break;
						 }
					 }
				}
				else if(diandong == 0x03){ //Y+
				while(1){
					TIM_Cmd(TIM2, ENABLE); 
					Locate_Rle2(3000,CCW); 
						 if(Data==0x05) {
							TIM_Cmd(TIM2, DISABLE);  
							  diandong=0;
							 break;
						 }
					 }
				}
				else if(diandong == 0x04){ //Y-
			while(1){
				TIM_Cmd(TIM2, ENABLE); 
				Locate_Rle2(3000,CW); 
						 if(Data==0x05) {
							TIM_Cmd(TIM2, DISABLE);  
							  diandong=0;
							 break;
						 }
					 }
				}
}

int main(void)
{	 
	delay_init();	    	    //��ʱ������ʼ��	  
	GPIO_Config();
	LED_Init();			     //LED�˿ڳ�ʼ��
	KEY_Init();          //��ʼ���밴�����ӵ�Ӳ���ӿ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	     	//���ڳ�ʼ��Ϊ115200
	Driver_Init();			    //��������ʼ��
	TIM4_PWM_Init(9999,143);//�����arr��ֵ��psc��ֵ�����޸ģ�ֻҪ�ڲ���Ƶ�����Ϊ72MHZ  20ms
	TIM2_Init(999,72-1);        //1MHz����Ƶ��,��һ�������Զ�װ��ֵ�ں���TIM2_Startup�����лᱻ�ı�
	TIM3_Init(999,72-1); //T=(arr+1)/10^6=1/frequency
	OPENMV_UART2(9600);    //
	GPIO_ResetBits(GPIOE, GPIO_Pin_1); //openmv��������õ�
	GPIO_SetBits(GPIOC, GPIO_Pin_6);   //z������
	GPIO_SetBits(GPIOC, GPIO_Pin_7);   //z�᷽��
	GPIO_ResetBits(GPIOC, GPIO_Pin_6);
	GPIO_ResetBits(GPIOC, GPIO_Pin_7);
	mf=2;
	printf("page �˵�\xff\xff\xff"); 

	while(1) 
	{
		if(Data==0x01){   //�㶯ģʽ  
			diandongmoshi();			
		}
		if(Data==0x02){   //����
			while(1){
			TIM_Cmd(TIM3, ENABLE); 
			TIM_Cmd(TIM2, ENABLE); 
			Locate_Rle2(3000,CCW); 
			Locate_Rle3(3000,CCW); 
				if(Data==0x05){
					TIM_Cmd(TIM2, DISABLE); 
					TIM_Cmd(TIM3, DISABLE); 
					GPIO_ResetBits(GPIOB, GPIO_Pin_5); //������
					break;
				}
			}
		}
//		if(Data==0x01){ //Բ���˶�
//		   while(1){
//				  mf=0;
//			    GPIO_SetBits(GPIOC, GPIO_Pin_6);
//			    GPIO_ResetBits(GPIOC, GPIO_Pin_7);
//				 while(jieshou==0){
//					 if(Data==0x05) break;
//				 }
//				 jieshou=0;
//				 while(yundong!=0x11){
//					 if(Data==0x05) break;
//		}
//				 if(Data==0x05) break;
//					crun(xzuobiao,yzuobiao);
//		      yundong=0;
//	}
// }	
//		
//		else	if(Data==0x02){ //�趨�˶�
//			 mf=0;
//			 GPIO_ResetBits(GPIOC, GPIO_Pin_6);
//			 GPIO_SetBits(GPIOC, GPIO_Pin_7);
//			 delay_ms(100);
//			while(1){
//			 while(yundong!=0x21){
//				 if(Data==0x05) break;
//		}
//			 if(Data==0x05) break;
//			 srun(10,50);
//		   yundong=0;
//	    }
//		}
//		
//		else	if(Data==0x03){ //��ָ�������
//			 mf=0;
//			 GPIO_SetBits(GPIOC, GPIO_Pin_6);
//			 GPIO_ResetBits(GPIOC, GPIO_Pin_7);
//			while(1){
//			while(jieshou==0){//�ȴ����ݷ���	
//	    OPENMV_Data_Get();
//		  delay_ms(100);
//	   	printf("t2.txt=\"%d\"\xff\xff\xff",(int)coordinate[0]); 
//		  printf("t3.txt=\"%d\"\xff\xff\xff",(int)coordinate[1]); 
//		  delay_ms(100);					
//				 if(Data==0x05) break;
//			}				
//			jieshou=0;
//			while(yundong!=0x31){
//					OPENMV_Data_Get();
//		      delay_ms(100);
//		      printf("t2.txt=\"%d\"\xff\xff\xff",(int)coordinate[0]); 
//		      printf("t3.txt=\"%d\"\xff\xff\xff",(int)coordinate[1]); 
//		      delay_ms(100);	
//				 if(Data==0x05) break;
//			}
//			  if(Data==0x05) break;
//				OPENMV_Data_Get();
//				lb = leftlencon(coordinate[0],coordinate[1]);
//				rb = rightlencon(coordinate[0],coordinate[1]);
//				la = leftlencon(xzuobiao,yzuobiao);
//				ra = rightlencon(xzuobiao,yzuobiao);
//			if(yzuobiao>50){
//			yzuobiao=yzuobiao*0.9;
//			}
//				dl = la-lb;
//				dr = ra-rb;
//				if(dl>0){
//					xdistance=dl;
//					Locate_Rle2(1500,CW);  //y��  CCW=0 ���
//				}
//				else{
//					xdistance=(0-dl);
//					Locate_Rle2(1500,CCW);  //y��  CW=1 ��ǰ
//				}
//				if(dr>0) {
//					ydistance=dr;
//					Locate_Rle3(1500,CCW);  //x��  CCW=0 ���
//				}
//				else {
//					ydistance=(0-dr);
//					Locate_Rle3(1500,CW);  //x��  CW=1 ����(��)
//				}	
//			yundong=0;
//		}
//	}
//		
//		 else	if(Data==0x04){ //Ѱ��
//			 		mf=1;
//			 	  GPIO_SetBits(GPIOC, GPIO_Pin_6);
//			    GPIO_SetBits(GPIOC, GPIO_Pin_7);
//			    ci=0;
//					delay_ms(1000);
//			 		OPENMV_Data();
//			    for(;ci<18;++ci){
//						if(ci<10){
//						 lb = leftlencon(coordinate1[0+2*ci],coordinate1[1+2*ci]);
//			       rb = rightlencon(coordinate1[0+2*ci],coordinate1[1+2*ci]);
//						 la = leftlencon(coordinate1[2+2*ci],coordinate1[3+2*ci]);
//			       ra = rightlencon(coordinate1[2+2*ci],coordinate1[3+2*ci]);
//             dl = la-lb;
//						 dr = ra-rb;
//						}
//						else{
//						 lb = leftlencon(coordinate1[0+2*ci]-0.7,coordinate1[1+2*ci]-0.5);
//			       rb = rightlencon(coordinate1[0+2*ci]-0.7,coordinate1[1+2*ci]-0.5);
//						 la = leftlencon(coordinate1[2+2*ci],coordinate1[3+2*ci]);
//			       ra = rightlencon(coordinate1[2+2*ci],coordinate1[3+2*ci]);
//             dl = la-lb;
//						 dr = ra-rb;
//						}
//						if(dl>0){
//							xdistance=dl;
//							Locate_Rle2(500,CW);  //y��  CCW=0 ���
//						}
//						else{
//							xdistance=(0-dl);
//							Locate_Rle2(500,CCW);  //y��  CW=1 ��ǰ
//						}
//						if(dr>0) {
//							ydistance=dr;
//							Locate_Rle3(500,CCW);  //x��  CCW=0 ���
//						}
//						else {
//							ydistance=(0-dr);
//							Locate_Rle3(500,CW);  //x��  CW=1 ����(��)
//						}	
//			 while(1){
//			  if(count[0]==lpwmcount(xdistance) && count[1]==rpwmcount(ydistance)){						
//			     count[0]=0;
//			     count[1]=0;
//				break;
//			}
//			else
//				;
//			}
//					}
//		    Data=0x05;
//		}
//		else delay_ms(10); 		
	}	
	
}

