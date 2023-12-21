#include "driver.h"
#include "delay.h"
#include "usart.h"

long current_pos[2]={0,0}; //有符号方向
DIR_Type motor_dir2=0;  //方向
DIR_Type motor_dir3=0;
u16 count[2]={0,0};
extern double xdistance;
extern double ydistance;
/************** 驱动器控制信号线初始化 ****************/
void Driver_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能PA端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_11;	//PC0.2 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//根据设定参数初始化GPIOA
	GPIO_SetBits(GPIOA,GPIO_Pin_6);						 	//PA6输出高 顺时针方向  DRIVER_DIR
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);						//PA5输出低 使能输出  DRIVER_OE
	GPIO_SetBits(GPIOA,GPIO_Pin_8);						 	//PA8输出高 顺时针方向  DRIVER_DIR
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);						//PA11输出低 使能输出  DRIVER_OE
}

/***********************************************
//TIM2_CH2(PA1) 单脉冲输出+重复计数功能初始化 y轴
//TIM2 时钟频率 72MHz
//arr：自动重装值
//psc：时钟预分频数
************************************************/
void TIM2_Init(u16 arr,u16 psc)
{		 					 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 	//TIM2时钟使能
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //使能GPIOA外设时钟使能	                                                                     	

  //设置该引脚为复用输出功能,输出TIM2 CH2的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				//TIM2_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			//复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr;					//设置在下一个更新事件装入活动的自动重装载寄存器周期的值,设置计数到这个值就产生溢出	 
	TIM_TimeBaseStructure.TIM_Prescaler =psc;				//设置用来作为TIMx时钟频率除数的预分频值  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 			//设置时钟分割:TDTS = Tck_tim,是改变作输入捕获时滤波用的并不是定时器的分频器
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 		//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);				//清除的是一些中断标志位

	TIM_UpdateRequestConfig(TIM2,TIM_UpdateSource_Regular); //TIM_UpdateSource_Regular 生成单一的脉冲：计数器在下一个更新事件停止，即关闭    
	TIM_SelectOnePulseMode(TIM2,TIM_OPMode_Single);			//单脉冲模式 
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;		//选择定时器模式:TIM脉冲宽度调制模式2[1]
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出2使能
	TIM_OCInitStructure.TIM_Pulse = arr>>1; 				//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高[2]
	//----[1][2]这两个配合一起然后查手册可以得到->当计时器值小于比较器设定值时则TIMX输出脚此时输出有效低电位。
	TIM_OC2Init(TIM2, &TIM_OCInitStructure); 				//根据TIM_OCInitStruct中指定的参数初始化外设TIMx

	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  		//CH2预装载使能	 
	TIM_ARRPreloadConfig(TIM2, ENABLE); 					//使能TIMx在ARR上的预装载寄存器
	
	TIM_ITConfig(TIM2, TIM_IT_Update ,ENABLE);  			//TIM2使能或者失能指定的TIM中断
 
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  		//TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 		//从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  						//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  			//清除TIMx的中断待处理位:TIM 中断源
	TIM_Cmd(TIM2, DISABLE);  								//使能TIM2									  
}
/******* TIM2更新中断服务程序 *********/
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_FLAG_Update)!=RESET)//更新中断
	{
		TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);//清除更新中断标志位		
		count[0]++; 
		TIM_GenerateEvent(TIM2,TIM_EventSource_Update);//产生一个更新事件 重新初始化计数器，
		//这里产生一个脉冲送到步进电机让电机运转一个脉冲数，即不细分的情况下，一般步进电机转1.8°
		//定时器初始化中，设置单脉冲模式是让计数器在下一个更新事件停止，即关闭，防止这次中断还没结束，
		//下一个计数器时间已经到了使中断紊乱，也就是进入中断后，定时器自动关闭。			
		TIM_Cmd(TIM2, ENABLE);  					   //使能TIM2,让定时器开始下一个脉冲计数后输出	
		if(count[0]==lpwmcount(xdistance))  //800一圈4.05cm
		{
			if(motor_dir2==CW) 						   //如果方向为顺时针   
				current_pos[0]+=count[0];
			else          							   //否则方向为逆时针
				current_pos[0]-=count[0];
			TIM_Cmd(TIM2, DISABLE);  				   //关闭TIM2			
			printf("motor2当前位置=%ld\r\n",current_pos[0]);//打印输出
			//count[0]=0;
		}
	
	}
}

void TIM3_Init(u16 arr,u16 psc) //x轴
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
			if(motor_dir3==CW) 						//如果方向为顺时针   
				current_pos[1]+=count[1];
			else          							//否则方向为逆时针
				current_pos[1]-=count[1];
			TIM_Cmd(TIM3, DISABLE);  				
			printf("motor3当前位置=%ld\r\n",current_pos[1]);
			//count[1]=0;
		}	
	}
}

/***************** 启动TIM8 *****************/
void TIM2_Startup(u32 frequency)   //启动定时器2
{
	u16 temp_arr=1000000/frequency-1; //frequency=500,1999 0.002=2ms
	TIM_SetAutoreload(TIM2,temp_arr);//设定自动重装值	
	TIM_SetCompare2(TIM2,temp_arr>>1); //匹配值2等于重装值一半，是以占空比为50%，这个是一半高电平，一半低电平，
	//定时器计数到最高或最低就是产生一个脉冲，脉冲从这里发送到PA1（TIM2_CH2	），占空比越大，输出的电压越大。
	TIM_SetCounter(TIM2,0);//计数器清零
	TIM_Cmd(TIM2, ENABLE);  //使能TIM2
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
//相对定位函数 
//num 0～2147483647
//frequency: 20Hz~100KHz
//dir: CW(顺时针方向)  CCW(逆时针方向)
*********************************************/
void Locate_Rle2(u32 frequency,DIR_Type dir) //相对定位函数
{
	
	if(TIM2->CR1&0x01)//上一次脉冲还未发送完成  直接返回，TIM2->CR1=0x01是使能定时器，
		//上面中断2函数进入后，产生一个脉冲，然后定时器自动关闭，再程序中开启，即TIM2->CR1=0x01
	{
		//printf("\r\nThe last time pulses is not send finished,wait please!\r\n");
		return;
	}
	if((frequency<20)||(frequency>100000))//脉冲频率不在范围内 直接返回
	{
		//printf("\r\nThe frequency is out of range! please reset it!!(range:20Hz~100KHz)\r\n");
		return;
	}
	motor_dir2=dir;//将枚举类型为DIR_Type的dir的值赋值给另一个枚举类型motor_dir2，方便在中断中判断motor_dir2是否为正
	//然后在中断中的current_pos[0]进行总和计算出当前的位置
	DRIVER_DIR2=motor_dir2;				 //将旋转方向赋值给DRIVER_DIR2所定义的接口
	TIM2_Startup(frequency);				 //开启TIM2
}
void Locate_Rle3(u32 frequency,DIR_Type dir) //相对定位函数
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
//绝对定位函数 
//num   -2147483648～2147483647
//frequency: 20Hz~100KHz
*********************************************/
/*void Locate_Abs(long num,u32 frequency)//绝对定位函数
{
	if(TIM8->CR1&0x01)//上一次脉冲还未发送完成 直接返回
	{
		printf("\r\nThe last time pulses is not send finished,wait please!\r\n");
		return;
	}
	if((frequency<20)||(frequency>100000))//脉冲频率不在范围内 直接返回
	{
		printf("\r\nThe frequency is out of range! please reset it!!(range:20Hz~100KHz)\r\n");
		return;
	}
	target_pos=num;//设置目标位置
	if(target_pos!=current_pos)//目标和当前位置不同
	{
		if(target_pos>current_pos)
			motor_dir=CW;//顺时针
		else
			motor_dir=CCW;//逆时针
		DRIVER_DIR=motor_dir;//设置方向
		
		rcr_integer=abs(target_pos-current_pos)/(RCR_VAL+1);//重复计数整数部分
		rcr_remainder=abs(target_pos-current_pos)%(RCR_VAL+1);//重复计数余数部分
		is_rcr_finish=0;//重复计数器未设置完成
		TIM8_Startup(frequency);//开启TIM8
	}
}*/

void TIM4_PWM_Init(u16 arr,u16 psc)
{
       
        GPIO_InitTypeDef GPIO_InitStructure;
        TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstruct;
        TIM_OCInitTypeDef TIM_OCInitStructure;
       
       
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//改变相应的引脚号和时钟号，就能有不同的引脚PWM输出，此处是PA.7，TIM3_CH1没有重映射
        //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //是否启用重映射
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
       
       
        GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
        GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
        GPIO_Init(GPIOB,&GPIO_InitStructure);
  //GPIO_SetBits(GPIOA,GPIO_Pin_1);//初始为低电平，可有可无
       
        //GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);//是否启用重映射
       

        TIM_TimeBaseInitstruct.TIM_ClockDivision=TIM_CKD_DIV1;
        TIM_TimeBaseInitstruct.TIM_CounterMode=TIM_CounterMode_Up;
        TIM_TimeBaseInitstruct.TIM_Period=arr;
        TIM_TimeBaseInitstruct.TIM_Prescaler=psc;
        TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitstruct);
       

        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择 PWM 模式 1
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性高
        TIM_OC2Init(TIM4, &TIM_OCInitStructure); //初始化 TIM3 OC1
       
        TIM_Cmd(TIM4, ENABLE);
       
        TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
}

u16 lpwmcount(double distance){ //距离脉冲数转换
 u16 a;
 a=(u16)500*distance; // distance mm为单位 a为对应距离脉冲数
	if (a==0)
			a=10;
 return a;
}

u16 rpwmcount(double distance){ //距离脉冲数转换
 u16 a;
 a=(u16)500*distance; // distance cm为单位 a为对应距离脉冲数
  if (a==0)
		a=10;
 return a;
}


