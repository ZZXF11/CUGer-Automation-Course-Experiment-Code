#include "driver.h"
#include "delay.h"
#include "usart.h"

long current_pos[2]={0,0}; //�з��ŷ���
DIR_Type motor_dir2=0;  //����
DIR_Type motor_dir3=0;
u16 count[2]={0,0};
extern double xdistance;
extern double ydistance;
/************** �����������ź��߳�ʼ�� ****************/
void Driver_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��PA�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_11;	//PC0.2 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//�����趨������ʼ��GPIOA
	GPIO_SetBits(GPIOA,GPIO_Pin_6);						 	//PA6����� ˳ʱ�뷽��  DRIVER_DIR
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);						//PA5����� ʹ�����  DRIVER_OE
	GPIO_SetBits(GPIOA,GPIO_Pin_8);						 	//PA8����� ˳ʱ�뷽��  DRIVER_DIR
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);						//PA11����� ʹ�����  DRIVER_OE
}

/***********************************************
//TIM2_CH2(PA1) ���������+�ظ��������ܳ�ʼ�� y��
//TIM2 ʱ��Ƶ�� 72MHz
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
************************************************/
void TIM2_Init(u16 arr,u16 psc)
{		 					 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 	//TIM2ʱ��ʹ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //ʹ��GPIOA����ʱ��ʹ��	                                                                     	

  //���ø�����Ϊ�����������,���TIM2 CH2��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				//TIM2_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr;					//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ,���ü��������ֵ�Ͳ������	 
	TIM_TimeBaseStructure.TIM_Prescaler =psc;				//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 			//����ʱ�ӷָ�:TDTS = Tck_tim,�Ǹı������벶��ʱ�˲��õĲ����Ƕ�ʱ���ķ�Ƶ��
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 		//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);				//�������һЩ�жϱ�־λ

	TIM_UpdateRequestConfig(TIM2,TIM_UpdateSource_Regular); //TIM_UpdateSource_Regular ���ɵ�һ�����壺����������һ�������¼�ֹͣ�����ر�    
	TIM_SelectOnePulseMode(TIM2,TIM_OPMode_Single);			//������ģʽ 
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;		//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2[1]
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����2ʹ��
	TIM_OCInitStructure.TIM_Pulse = arr>>1; 				//���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�[2]
	//----[1][2]���������һ��Ȼ����ֲ���Եõ�->����ʱ��ֵС�ڱȽ����趨ֵʱ��TIMX����Ŵ�ʱ�����Ч�͵�λ��
	TIM_OC2Init(TIM2, &TIM_OCInitStructure); 				//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx

	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  		//CH2Ԥװ��ʹ��	 
	TIM_ARRPreloadConfig(TIM2, ENABLE); 					//ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_ITConfig(TIM2, TIM_IT_Update ,ENABLE);  			//TIM2ʹ�ܻ���ʧ��ָ����TIM�ж�
 
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  		//TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 		//�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  						//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  			//���TIMx���жϴ�����λ:TIM �ж�Դ
	TIM_Cmd(TIM2, DISABLE);  								//ʹ��TIM2									  
}
/******* TIM2�����жϷ������ *********/
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_FLAG_Update)!=RESET)//�����ж�
	{
		TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);//��������жϱ�־λ		
		count[0]++; 
		TIM_GenerateEvent(TIM2,TIM_EventSource_Update);//����һ�������¼� ���³�ʼ����������
		//�������һ�������͵���������õ����תһ��������������ϸ�ֵ�����£�һ�㲽�����ת1.8��
		//��ʱ����ʼ���У����õ�����ģʽ���ü���������һ�������¼�ֹͣ�����رգ���ֹ����жϻ�û������
		//��һ��������ʱ���Ѿ�����ʹ�ж����ң�Ҳ���ǽ����жϺ󣬶�ʱ���Զ��رա�			
		TIM_Cmd(TIM2, ENABLE);  					   //ʹ��TIM2,�ö�ʱ����ʼ��һ��������������	
		if(count[0]==lpwmcount(xdistance))  //800һȦ4.05cm
		{
			if(motor_dir2==CW) 						   //�������Ϊ˳ʱ��   
				current_pos[0]+=count[0];
			else          							   //������Ϊ��ʱ��
				current_pos[0]-=count[0];
			TIM_Cmd(TIM2, DISABLE);  				   //�ر�TIM2			
			printf("motor2��ǰλ��=%ld\r\n",current_pos[0]);//��ӡ���
			//count[0]=0;
		}
	
	}
}

void TIM3_Init(u16 arr,u16 psc) //x��
{		 					 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  	                                                                     	


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr; 	 
	TIM_TimeBaseStructure.TIM_Prescaler =psc;  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);

	TIM_UpdateRequestConfig(TIM3,TIM_UpdateSource_Regular); 
	TIM_SelectOnePulseMode(TIM3,TIM_OPMode_Single);
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = arr>>1; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  	 
	TIM_ARRPreloadConfig(TIM3, ENABLE); 
	
	TIM_ITConfig(TIM3, TIM_IT_Update ,ENABLE);  
 
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);  
	
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update); 
	TIM_Cmd(TIM3, DISABLE);  							  
}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_FLAG_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_FLAG_Update);	
		count[1]++; 
		TIM_GenerateEvent(TIM3,TIM_EventSource_Update);
		TIM_Cmd(TIM3, ENABLE);  		
		
		if(count[1]==rpwmcount(ydistance))
		{
			if(motor_dir3==CW) 						//�������Ϊ˳ʱ��   
				current_pos[1]+=count[1];
			else          							//������Ϊ��ʱ��
				current_pos[1]-=count[1];
			TIM_Cmd(TIM3, DISABLE);  				
			printf("motor3��ǰλ��=%ld\r\n",current_pos[1]);
			//count[1]=0;
		}	
	}
}

/***************** ����TIM8 *****************/
void TIM2_Startup(u32 frequency)   //������ʱ��2
{
	u16 temp_arr=1000000/frequency-1; //frequency=500,1999 0.002=2ms
	TIM_SetAutoreload(TIM2,temp_arr);//�趨�Զ���װֵ	
	TIM_SetCompare2(TIM2,temp_arr>>1); //ƥ��ֵ2������װֵһ�룬����ռ�ձ�Ϊ50%�������һ��ߵ�ƽ��һ��͵�ƽ��
	//��ʱ����������߻���;��ǲ���һ�����壬��������﷢�͵�PA1��TIM2_CH2	����ռ�ձ�Խ������ĵ�ѹԽ��
	TIM_SetCounter(TIM2,0);//����������
	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIM2
}
void TIM3_Startup(u32 frequency)   
{
	u16 temp_arr=1000000/frequency-1; 
	TIM_SetAutoreload(TIM3,temp_arr);
	TIM_SetCompare2(TIM3,temp_arr>>1); 
	TIM_SetCounter(TIM3,0);
	TIM_Cmd(TIM3, ENABLE);  
}
/********************************************
//��Զ�λ���� 
//num 0��2147483647
//frequency: 20Hz~100KHz
//dir: CW(˳ʱ�뷽��)  CCW(��ʱ�뷽��)
*********************************************/
void Locate_Rle2(u32 frequency,DIR_Type dir) //��Զ�λ����
{
	
	if(TIM2->CR1&0x01)//��һ�����廹δ�������  ֱ�ӷ��أ�TIM2->CR1=0x01��ʹ�ܶ�ʱ����
		//�����ж�2��������󣬲���һ�����壬Ȼ��ʱ���Զ��رգ��ٳ����п�������TIM2->CR1=0x01
	{
		//printf("\r\nThe last time pulses is not send finished,wait please!\r\n");
		return;
	}
	if((frequency<20)||(frequency>100000))//����Ƶ�ʲ��ڷ�Χ�� ֱ�ӷ���
	{
		//printf("\r\nThe frequency is out of range! please reset it!!(range:20Hz~100KHz)\r\n");
		return;
	}
	motor_dir2=dir;//��ö������ΪDIR_Type��dir��ֵ��ֵ����һ��ö������motor_dir2���������ж����ж�motor_dir2�Ƿ�Ϊ��
	//Ȼ�����ж��е�current_pos[0]�����ܺͼ������ǰ��λ��
	DRIVER_DIR2=motor_dir2;				 //����ת����ֵ��DRIVER_DIR2������Ľӿ�
	TIM2_Startup(frequency);				 //����TIM2
}
void Locate_Rle3(u32 frequency,DIR_Type dir) //��Զ�λ����
{
	
	if(TIM3->CR1&0x01)
	{
		//printf("\r\nThe last time pulses is not send finished,wait please!\r\n");
		return;
	}
	if((frequency<20)||(frequency>100000))
	{
		//printf("\r\nThe frequency is out of range! please reset it!!(range:20Hz~100KHz)\r\n");
		return;
	}
	motor_dir3=dir;
	DRIVER_DIR3=motor_dir3;
	TIM3_Startup(frequency);
}

/********************************************
//���Զ�λ���� 
//num   -2147483648��2147483647
//frequency: 20Hz~100KHz
*********************************************/
/*void Locate_Abs(long num,u32 frequency)//���Զ�λ����
{
	if(TIM8->CR1&0x01)//��һ�����廹δ������� ֱ�ӷ���
	{
		printf("\r\nThe last time pulses is not send finished,wait please!\r\n");
		return;
	}
	if((frequency<20)||(frequency>100000))//����Ƶ�ʲ��ڷ�Χ�� ֱ�ӷ���
	{
		printf("\r\nThe frequency is out of range! please reset it!!(range:20Hz~100KHz)\r\n");
		return;
	}
	target_pos=num;//����Ŀ��λ��
	if(target_pos!=current_pos)//Ŀ��͵�ǰλ�ò�ͬ
	{
		if(target_pos>current_pos)
			motor_dir=CW;//˳ʱ��
		else
			motor_dir=CCW;//��ʱ��
		DRIVER_DIR=motor_dir;//���÷���
		
		rcr_integer=abs(target_pos-current_pos)/(RCR_VAL+1);//�ظ�������������
		rcr_remainder=abs(target_pos-current_pos)%(RCR_VAL+1);//�ظ�������������
		is_rcr_finish=0;//�ظ�������δ�������
		TIM8_Startup(frequency);//����TIM8
	}
}*/

void TIM4_PWM_Init(u16 arr,u16 psc)
{
       
        GPIO_InitTypeDef GPIO_InitStructure;
        TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstruct;
        TIM_OCInitTypeDef TIM_OCInitStructure;
       
       
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//�ı���Ӧ�����źź�ʱ�Ӻţ������в�ͬ������PWM������˴���PA.7��TIM3_CH1û����ӳ��
        //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //�Ƿ�������ӳ��
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
       
       
        GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
        GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
        GPIO_Init(GPIOB,&GPIO_InitStructure);
  //GPIO_SetBits(GPIOA,GPIO_Pin_1);//��ʼΪ�͵�ƽ�����п���
       
        //GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);//�Ƿ�������ӳ��
       

        TIM_TimeBaseInitstruct.TIM_ClockDivision=TIM_CKD_DIV1;
        TIM_TimeBaseInitstruct.TIM_CounterMode=TIM_CounterMode_Up;
        TIM_TimeBaseInitstruct.TIM_Period=arr;
        TIM_TimeBaseInitstruct.TIM_Prescaler=psc;
        TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitstruct);
       

        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ�� PWM ģʽ 1
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //������Ը�
        TIM_OC2Init(TIM4, &TIM_OCInitStructure); //��ʼ�� TIM3 OC1
       
        TIM_Cmd(TIM4, ENABLE);
       
        TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
}

u16 lpwmcount(double distance){ //����������ת��
 u16 a;
 a=(u16)500*distance; // distance mmΪ��λ aΪ��Ӧ����������
	if (a==0)
			a=10;
 return a;
}

u16 rpwmcount(double distance){ //����������ת��
 u16 a;
 a=(u16)500*distance; // distance cmΪ��λ aΪ��Ӧ����������
  if (a==0)
		a=10;
 return a;
}


