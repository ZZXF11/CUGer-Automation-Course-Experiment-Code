#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "usart2.h"
#include "openmv.h"
#include "math.h"
#include "stdio.h"
/************************************************
 ALIENTEKս��STM32������ʵ��1
 �����ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

 //const int h = 95;
 //const int l = 75;
 extern  int data[10];
 extern int xdir,ydir;
 extern long straight_x,straight_y;//ֱ�߲岹�յ�
 extern int circlecent_x,circlecent_y;//Բ��Բ��
 extern int circle_way;//Բ���˶�����˳��ʱ��
	extern int mark;
	extern int xdir,ydir;//������ǰ
  extern int anmark ;
	
	extern int mycircle_x;
	extern int mycircle_y;
	extern int mycircle_endx;
	extern int mycircle_endy;
	extern int mycircle_getr;
	extern int mycircle_way;
	
	extern int sin_A;
	extern int sin_w;
	extern int sin_b;
	extern int cos_A;
	extern int cos_w;
	extern int cos_b;
	
	extern int straight_k;
	extern int straight_b;
	
	long current_x = 0;
	long current_y  = 0;
	int speed_time=50;
  int allspeed=62;
	int get_r = 0;
	
 int main(void)
 {	
   double x1,y1,x2,y2;
	 double left;
	 double right;
	 int di;
	 
	 int k_x=0;
	 int k_y=0;
	 
	delay_init();	    //��ʱ������ʼ��	  
	STEPMOTOR_Init();	
  //STEPMOTOR_Init1();
 	uart_init(9600);
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
 	usart2_init(9600);	 
  openmv_init(115200);
  
	 
	 
	 
	 
	while(1)
	{	
		
		switch(mark){
		
			case 0://ɶҲ���ǣ�������
				printf("page0.t1.txt=\"%ld\"\xff\xff\xff",current_x);
			  printf("page0.t3.txt=\"%ld\"\xff\xff\xff",current_y);
				break;
			case 1://�����˶�
				
				while( anmark == 1){
				  
					if(xdir == 0){
					xzz(2);
					printf("page3.t3.txt=\"%ld\"\xff\xff\xff",current_y);
					}
					else if(xdir == 1){
					xfz(2);
				  printf("page3.t3.txt=\"%ld\"\xff\xff\xff",current_y);
					}
					if(ydir == 0){
					yzz(2);
					printf("page3.t2.txt=\"%ld\"\xff\xff\xff",current_x);
					}
					else if(ydir == 1){
					printf("page3.t2.txt=\"%ld\"\xff\xff\xff",current_x);
					yfz(2);
					
					}
					
				}
			
				mark = 0;
			  break;
			
			case 2://ֱ���˶�
				
			
				printf("page1.t5.txt=\"%ld\"\xff\xff\xff",current_x);
	      printf("page1.t7.txt=\"%ld\"\xff\xff\xff",current_y);
			
			  zhixianchabu(straight_x,straight_y);
			
			
			  mark = 0;
				break;
			case 3://Բ���˶�
				
			  
			  yuan(circlecent_x,circlecent_y,get_r,circle_way);
				   // printf("page2.t5.txt=\"%ld\"\xff\xff\xff",current_x);
	         // printf("page2.t7.txt=\"%ld\"\xff\xff\xff",current_y);
			

			  mark = 0;
				break;
		  case 4://����
				
			  //get_r = sqrt(abs(circlecent_x*circlecent_x  + circlecent_y*circlecent_y -current_x*current_x - current_y*current_y ));
			 // yuan(circlecent_x,circlecent_y,get_r,circle_way);
				   // printf("page2.t5.txt=\"%ld\"\xff\xff\xff",current_x);
	         // printf("page2.t7.txt=\"%ld\"\xff\xff\xff",current_y);
			
				if(current_x >0){
				while(current_x != 0){	
				xfz(2);
				}
				}
				if(current_x <0){
				while(current_x != 0){	
				xzz(2);
				}
				
				}
				
				if(current_y >0){
				while(current_y != 0){	
				yfz(2);
				}
				}
				if(current_y <0){
				while(current_y != 0){	
				yzz(2);
				}
				}
				
				mark = 0;
				break;
			
			case 5://Բ���岹
				yuanhuchabu(mycircle_x,mycircle_y,mycircle_endx,mycircle_endy,mycircle_getr,mycircle_way);
			  mark = 0;
			  break;
			case 6://���Ǻ���
	      sanjiao(sin_A,sin_w,sin_b);
        mark = 0;
        break;			
			case 7://y=kx+b
				 k_x = current_x + 100;
			   k_y = straight_k*k_x +straight_b;
			
			   zhixianchabu1(k_x,k_y); 
			   k_x =0;
			   k_y= 0;
			   mark = 0;
			   break;
				
			case 8://cos
				sanjiaocos(cos_A,cos_b,cos_w);
			  mark = 0;
			  break;
			case 9://car
			  draw_car();		
			  mark = 0;
			  break;
			case 10://star
			  liumangxing();
			  mark = 0;
			  break;
			default:
				break;
		}
		
		
	}
 }
	
		
		
		
		
	//	printf("t11.txt=\"%d\"\xff\xff\xff",data[1]);	

	//	printf("t12.txt=\"%d\"\xff\xff\xff",data[2]);		
		
		//printf("yi%d\r\n",1);
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	  //HMI_Send_End();	
//		
	//	go_circle(0,0,40,40);
	//	
	//	delay_ms(1000);
		
		
		
//////		
//////		if(mark == 1){//Բ��
//////		
//////			go_circle(getx1,gety1,gx2,gy2);
//////			
//////			
//////		}
//////		else if(mark == 2){
//////		
//////		x1= 75*(getx1 - 91)/179;
//////		y1 = 95 - 95*(gety1-14)/233;
//////		x2= 75*(getx2 - 91)/179;
//////		y2 = 95 - 95*(gety2-14)/233;
//////		
////////		
//////    printf("yi%f\r\n",x1);
//////	  printf("yi%f\r\n",y1); 
//////		printf("zuo%f\r\n",x2); 
//////		printf("zuo%f\r\n",y2);
//////   	di = getdirection(x1,y1,x2,y2);	
//////		left = maichong(leftmove(x1,y1,x2,y2));
//////		right = maichong(rightmove(x1,y1,x2,y2));
//////		GO1(left,right,di);
//////		delay_ms(100);
//////		
//////		
//////		}//ѭ��
//////		else if(mark == 3){
//////		
//////		go_straight(getx1,gety1,gx2,gy2);
//////		}//����ָ��λ��
//////		else if(mark == 4){
//////		
//////		}//����
		
	
//		
//     	 go_straight(25.,35.,10.,60.);
//			 delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(1000);
			
			
//		 delay_ms(1000);delay_ms(1000);delay_ms(1000);
	//	 go_circle(0.,0.,30.,30.);
////// 
	//STEPMOTORV1(left);

//	
	   
   
		

 /**
 *****************����ע�ӵĴ�����ͨ�����ÿ⺯����ʵ��IO���Ƶķ���*****************************************
int main(void)
{ 
 
	delay_init();		  //��ʼ����ʱ����
	LED_Init();		        //��ʼ��LED�˿�
	while(1)
	{
			GPIO_ResetBits(GPIOB,GPIO_Pin_5);  //LED0��Ӧ����GPIOB.5���ͣ���  ��ͬLED0=0;
			GPIO_SetBits(GPIOE,GPIO_Pin_5);   //LED1��Ӧ����GPIOE.5���ߣ��� ��ͬLED1=1;
			delay_ms(300);  		   //��ʱ300ms
			GPIO_SetBits(GPIOB,GPIO_Pin_5);	   //LED0��Ӧ����GPIOB.5���ߣ���  ��ͬLED0=1;
			GPIO_ResetBits(GPIOE,GPIO_Pin_5); //LED1��Ӧ����GPIOE.5���ͣ��� ��ͬLED1=0;
			delay_ms(300);                     //��ʱ300ms
	}
} 
 
 ****************************************************************************************************
 ***/
 

	
/**
*******************����ע�͵��Ĵ�����ͨ�� ֱ�Ӳ����Ĵ��� ��ʽʵ��IO�ڿ���**************************************
int main(void)
{ 
 
	delay_init();		  //��ʼ����ʱ����
	LED_Init();		        //��ʼ��LED�˿�
	while(1)
	{
     GPIOB->BRR=GPIO_Pin_5;//LED0��
	   GPIOE->BSRR=GPIO_Pin_5;//LED1��
		 delay_ms(300);
     GPIOB->BSRR=GPIO_Pin_5;//LED0��
	   GPIOE->BRR=GPIO_Pin_5;//LED1��
		 delay_ms(300);

	 }
 }
**************************************************************************************************
**/

