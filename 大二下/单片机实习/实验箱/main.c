#include <reg51.h>
#include "8255.c"
#include "KEYLED.c"
#include "YALI.c"
#include "BEEP.c"
#include "temp.c"
#include "motor.c"
#include "dianzhen.c"
#include "Bmotor.c"
#include "LCD.c"



sbit P1_0 = P1^0;
sbit P1_1 = P1^1;



unsigned char speed;//���ڶ�ȡ��ǰ�ٶ�
int TT=60;//ѭ����ʱ
int overspeed;
unsigned char ADResult0,ADResult1;//ѹ���������¶ȶ���

//void Setmoshi()//����ģʽ����·�����ء������¶�
//{       
//        if(TestKey())
//        {            
//           switch (GetKey()& 0x0f)  // (GetKey()& 0x0f)��ֵ�͵��ڰ�������ֵ
//           {
//               case 1:  initMotor=0x45;break; //����������2��
//               case 2:  initMotor=0x54;break; //����������3��
//               case 3:  initMotor=0x59;break; //���������е�                 
//           }               
//        }          
//}

void Setmoshi()//����ģʽ����·�����ء������¶�
{       
        if(TestKey())
        {            
           switch (GetKey()& 0x0f)  // (GetKey()& 0x0f)��ֵ�͵��ڰ�������ֵ
           {
               case 1:  {initMotor=0x45;DisplayLcd();break;} //����������1��,��1
               case 2:  {initMotor=0x54;DisplayLcd();break;} //����������2��,��2
               case 3:  {initMotor=0x59;DisplayLcd();break;} //���������е�,��3 
               case 0x0a:  {initYALI=0x07;DisplayLcd();break;}//����5��,��a 
               case 0x0b:  {initYALI=0x15;DisplayLcd();break;}//����7��,��b 
               case 0x0c:  {initYALI=0x25;DisplayLcd();break;}//����9��,��c  
               case 0x00:  {--initTEMP;DisplayLcd();break;}   //�µ��յ������¶�,��0
               case 0x0f:  {++initTEMP;DisplayLcd();break;}   //�ϵ��յ������¶�,��F                
           }    //****�ǵ����ӣ�1��40��2��55��3��75***           
        }          
}

void DisplayS()//�ٶ���ʾ����
{
	unsigned int i=0,sum=0;
	i=(speed>>4) & 0x0f;
	if(i>9) sum=16*(i-0x0a+10);
	else sum=16*i;
	i=speed & 0x0f;
	if(i>9) sum+=i-0x0a+10;
	else sum+=i;
	LEDBuf[4] = LEDMAP[sum/10];
	LEDBuf[5] = LEDMAP[sum%10];
//  LEDBuf[4] = LEDMAP[(speed>>4) & 0x0f];
//  LEDBuf[5] = LEDMAP[speed & 0x0f];
}

unsigned char SetSpeed(){
	unsigned char S,R;
	S=PortB;//���صĸ�4λ�����ٶ�
	if(S>=0x00&&S<=0x0f)R=0xc5;
	if(S>=0x10&&S<=0x1f)R=0xcf;
	if(S>=0x20&&S<=0x3f)R=0xdf;
	if(S>=0x40&&S<=0x7f)R=0xef;
	if(S>=0x80&&S<=0xff)R=0xff;
	return R;
}

int oil(){
	unsigned char S,Z;
	int R;
	Z=PortB;
	S = (Z & 0x0f);
	if(S==0x01){
		R=0;//������
	}
	else if(S==0x00){
		R=2;//û��
	}
	else R=1;
	return R;
}

void INTT0() interrupt 0 //�ⲿ�ж�0
{
	//��Ҫ�رն�ʱ�ͼ���������speed��0
	TR0  = 0;//�ر�T0
  TH0  = 0x3c;//���ó�ֵ��50000�����
  TL0  = 0xb0;
	TR1  = 0;//���ü�����T1
  TH1  = 0;
  TL1  = 0;
	speed=TL1;
	TT=60;
  //����Ϊ�رն�ʱ���ͼ�����
	MOTOR=0xc5;
	PortA=0xff;
	if(oil()==0){//��ʾ������
		DZO();
	}
	if(ADResult0>initYALI){//��ʾ�ѳ���
		DZZ();
	}
	PortA=0x00;//PA����0
	P1_0=1;//�ر��ж�
	//���´򿪶�ʱ���ͼ�����
  TR0  = 1;//�򿪶�ʱ��
	TR1  = 1;//�򿪼�����
}

void TT0() interrupt 1 //��ʱ��T0�ж�
{
	if(TT!=0){
	TH0  = 0x3c;//���ó�ֵ��50000�����
  TL0  = 0xb0;
		TR0=1;
		--TT;
	}
	if(TT==0){
	TT=60;
	TH0  = 0x3c;//���ó�ֵ��50000�����
  TL0  = 0xb0;
	speed=TL1;
  TH1  = 0;
  TL1  = 0;
	TR0=1;
	TR1=1;
	}
	
}

void INTT1() interrupt 2 //�ⲿ�ж�1
{
	//��Ҫ�رն�ʱ�ͼ���������speed��0
	TR0  = 0;//�ر�T0
  TH0  = 0x3c;//���ó�ֵ��50000�����
  TL0  = 0xb0;
	TR1  = 0;//���ü�����T1
  TH1  = 0;
  TL1  = 0;
	speed=TL1;
	TT=60;
  //����Ϊ�رն�ʱ���ͼ�����
	MOTOR=0x80;
	if(oil()==2){//��ʾ�����
			 DZOO();
		 }
	if(overspeed==1){//���ٶȳ����趨ֵ�������ж�0
			 DZS();
		   overspeed=0;
		 }
	PortA=0x00;//PA����0
	MOTOR=SetSpeed();
	P1_1=1;//�ر��ж�
  //���´򿪶�ʱ���ͼ�����
  TR0  = 1;//�򿪶�ʱ��
	TR1  = 1;//�򿪼�����
}

void main()  //������
{
   unsigned char i = 0;
	 register unsigned char dd;//��λ��������ʾ
   unsigned char j,OIL;
	 CAddr=mode; // ��ʽ0��PA��PC�����PB����
	 IE=0x87;//�жϳ�ʼ��
	 TCON=0x05;//�ⲿ�ж�0��1��Ϊ�͵�ƽ����
	 P1=0xff;
	 readSpeed();
   DisplayLcd();
   while(1) {
		 Setmoshi();//����ģʽ
		 MOTOR=SetSpeed();//���õ��ת��
     ADResult0 =  ReadYALI();//ѹ������
		 ADResult1 =  ReadTemp();//�¶ȶ���
		 PortC = 0x00;
		 dd = PortB;     //��λ��������ʾ
     PortA = dd;
		 if(ADResult0>initYALI){//��ѹ�������趨ֵ�������ж�0
			 P1_0=0;}
		 if(ADResult1>initTEMP&&ADResult1<0x80){//��ѹ�¶ȳ����趨ֵ���������ת��
			  PortC = 0x01;}
		 if(oil()==0){//������������ж�0
			 P1_0=0; }
		 if(oil()==2){//����û�ͣ������ж�1
			 P1_1=0;}
		 if(speed>initMotor&&speed<0x59){//���ٶȳ����趨ֵ�������ж�0
			 overspeed=1;
			 P1_1=0;}
		 DisplayT();//��ʾ�¶�
		 DisplayS();//��ʾ�ٶ�
     for(j=0; j<30; j++)DisplayLED();   // ��ʱ
   }
}

