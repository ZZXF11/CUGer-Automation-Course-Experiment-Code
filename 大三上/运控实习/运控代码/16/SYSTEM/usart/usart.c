#include "sys.h"
#include "usart.h"	  
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//串口1初始化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/8/18
//版本：V1.5
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//********************************************************************************
//V1.3修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
//V1.4修改说明
//1,修改串口初始化IO的bug
//2,修改了USART_RX_STA,使得串口最大接收字节数为2的14次方
//3,增加了USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
//4,修改了EN_USART1_RX的使能方式
//V1.5修改说明
//1,增加了对UCOSII的支持
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*使用microLib的方法*/
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
 
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	  
  int data[10];
	int mark = 0;
int t = 0;
int straight_xiangxian=0;
long straight_x=0,straight_y=0;//直线插补终点
int circlecent_x=0,circlecent_y=0;//圆周圆心
int circle_way = 0;//圆周运动方向，顺逆时针


int mycircle_x=0,mycircle_y=0;
int mycircle_way =0;
int mycirccle_angle =0;
int mycircle_endx=0,mycircle_endy=0;
int mycircle_getr=0;
extern long current_x;
extern long current_y;
extern int get_r;
double gx1 = 0,gy1 = 0,gx2 = 0,gy2 = 0;
int xdir=3,ydir=3;//按键向前
int anmark = 0;
void uart_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 

}

void USART1_IRQHandler(void)                	//串口1中断服务程序
	{
double temp_data ;
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
	{
		data[t] = USART_ReceiveData(USART1);
		t++;
		if(t ==1 && data[0] != 0xB1 && data[0] != 0xB2 && data[0] != 0xB3 && data[0] != 0xB4 && data[0] != 0xB5 && data[0] != 0xA1 && data[0] != 0xA2 && data[0] != 0xA3&& data[0] != 0xC3 && data[0] != 0xC4 && data[0] != 0xC5 && data[0] != 0xC6 && data[0] != 0xD4&& data[0] != 0xf4  )	
			{     //第 0 号数据不是帧头，跳过
			t = 0;
	    }
			
			
			
		if(t == 2 && data[0] == 0xB1){
		  mark = 1;//操控xy
		
		
		}
		if(t == 2 && data[0] == 0xf4){
		  mark = 4;//回家
		}
		if(t == 1 && data[0] == 0xC3){
			mark = 1;//操控xy
		 xdir = 0;//x前
		 anmark = 1;
		
		
		}
		if(t == 1&& data[0] == 0xC4){
			 mark = 1;//操控xy
		 xdir = 1;
		 anmark = 1;
		
		
		}
		if(t == 1&&data[0] == 0xC5){
			 mark = 1;//操控xy
		 ydir = 0;
		 anmark = 1;
	
		
		}
		if(t == 1&&data[0] == 0xC6){
			 mark = 1;//操控xy
		 ydir = 1;
		 anmark = 1;
	
		}
		
	
		if(t == 1 && data[0] == 0xD4){
		mark = 1;
		anmark = 0;//代表按键弹起，运动停止
		xdir=3;
			ydir=3;
		}
	
	
		
		
		
		/*
		if(t == 2 && data[0] == 0xB2){
		//  mark = 2;// 直线运动
	    	 
		}
		if(t == 2 && data[0] == 0xA1){
		//接下来的数据是straightx。straighty坐标
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
		 // mark = 3;//圆周运动
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
		  mark = 5;//圆弧插补
			mycircle_x = data[1];
			mycircle_y = data[2];
			mycircle_way = data[3];
			mycirccle_angle = data[4];
			
			mycircle_getr=sqrt(abs(mycircle_x*mycircle_x  + mycircle_y*mycircle_y -current_x*current_x - current_y*current_y ));
			
		  switch(data[5]){//象限
				case 1:
					if(mycircle_way==0){//逆时针
					
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
					if(mycircle_way==0){//逆时针
					
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
					if(mycircle_way==0){//逆时针
					
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
					if(mycircle_way==0){//逆时针
					
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
		  mark = 6;//sin三角函数
		
		}
		if(data[t-1] == 0xFF){//帧尾
		
			t = 0;
			//memset(data, 0, sizeof data);//清空数组
		}
		
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE); 
}

/*
void USART1_IRQHandler(void)                	//串口1中断服务程序
	{
double temp_data ;
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
	{
		data[t] = USART_ReceiveData(USART1);
		t++;
		if(t ==1 && data[0] != 0xA1 && data[0] != 0xA2 && data[0] != 0xA3 && data[0] != 0xA4 )	
			{     //第 0 号数据不是帧头，跳过
			t = 0;
	    }
		if(t == 2 && data[0] == 0xA1){
		  mark = 1;//圆周运动
			gx2 = data[1];
		
		}
		if(t == 3 && data[0] == 0xA1){
		  mark = 1;
			gy2 = data[2];
		
		}
		if(t == 2 && data[0] == 0xA2){
		  mark = 2;// 循迹
	    	 
		}
		
		if(t == 2 && data[0] == 0xA3){
		  mark = 3;//到达指定位置 
	    gx2 = data[1];	 
		}
		if(t == 3 && data[0] == 0xA3){
		  mark = 3;//到达指定位置 
	    gy2 = data[2];	 
		}
		if(t == 2 && data[0] == 0xA4){
		  mark = 4;//显示
	    	 
		}
		if(t == 2 && data[0] == 0xA5){
		  mark = 5;//自行
	    	 
		}
		
		if(data[t-1] == 0xFF){//帧尾
		
			t = 0;
		}
		
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE); 
} */
#endif	

