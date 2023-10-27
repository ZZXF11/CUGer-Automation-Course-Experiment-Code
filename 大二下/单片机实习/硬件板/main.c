#include <reg52.h>
#include "DIANZHEN.c"
#include "lcd.c"
#include "Keyled.c"
 
#define uchar unsigned char
//****������̣���ɨ�裬�ж���****
unsigned int  count=0;			//��ʱ
unsigned char flag_dot=0;		//����ˢ�±�־���ٶ����ڷ�����10��
unsigned int  delay_time=0;	//��ʱ��ʱ��
unsigned char disp[4]=0;		//�������������
unsigned char flag_miao=0;	//���־��Ϊ10ʱ��ʾ1��
unsigned char flag_tube=0;	//�����ˢ�±�־��ÿ2msɨ��һ��
unsigned char Time=0;				//��ʱ��2��ÿ1ms��һ
unsigned char flag_key=0;		//����ˢ�±�־��ÿ10msɨ��һ��
unsigned char i=0;					//����ܣ�ָ�ڵ�ǰλ
unsigned char flag_key2=0;	//�������±�־��������������
unsigned char flag_pause=0;	//��ͣ��־
uchar code table[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00};

void delay_ms(int i)
{
	uchar j;
	while(i--)
	{
		for(j=0;j<200;j++);
		j=0;
	}
}
void Caozuokey()//����ģʽ����·�����ء������¶�
{       
	if(TestKey()){
		keynum=KeyScan() & 0x0f;	//keynum���ǰ�����Ӧ��ֵ
          switch (keynum)  //keynum�͵��ڰ�������ֵ
          {
               case 0:  {initMotor=0x00;DisplayLcd();break;} //����������1��,��1
               case 1:  {initMotor=0x01;DisplayLcd();break;} //����������2��,��2
               case 2:  {initMotor=0x02;DisplayLcd();break;} //���������е�,��3 
               case 0x04:  {initYALI=0x0a;DisplayLcd();break;}//����5��,��a 
               case 0x08:  {initYALI=0x0b;DisplayLcd();break;}//����7��,��b 
               case 0x0c:  {initYALI=0x0c;DisplayLcd();break;}//����9��,��c  
               case 0x0b:  {--initTEMP;DisplayLcd();break;}   //�µ��յ������¶�,��3(���ϵ�2)
               case 0x0f:  {++initTEMP;DisplayLcd();break;}   //�ϵ��յ������¶�,��F�����ϵ�1��                
               case 0x07:   DisplayDZtemp();break;  //�������ϵ�3����ʵ���¶ȳ�����ֵ�������¶ȱ���
               case 0x03:   DisplayDZdistance();break; //�������½Ǵ���������
           
           }            
     }                     
}
unsigned int dou=0;
uchar j=0;
uchar flag_i=0;
//����Ϊ����˧�ʺƴ����޸ĵ�ʱ����ʾ����
//ʹ�ö�ʱ��2ʵ�ּ�ʱ
void timer2() interrupt 5 
{  
  TF2=0; //��ʱ��2����������������־λ����    
  Time++;//���ڼ�ʱ
	if(Time==100) {Time=0;flag_miao++;}
	if(!(Time%10)&&!flag_key2)	if(++flag_key>3) flag_key=0;//
	if(!(Time%2))	flag_tube=1;
	if(flag_miao==10)//�����־
	{
//��ʾ����ʱ��
		flag_miao=0;
		disp[3]=count%10;
		disp[2]=count/10%10;
		disp[1]=count/100;
		if(!flag_pause)//��ͣ����
			count++;
//�˶ι�ˢ��
		P2=0x4f;//ÿ�붼����һ����ˮ
		if(flag_i<8)
			P0=~(1<<flag_i),flag_i++;
		else if(flag_i<14)
			P0=~(0x80>>(flag_i-7)),flag_i++;
		else flag_i=0,P0=~(1<<flag_i),flag_i++;
		P2=0x6f;
	}
	if(delay_time)delay_time--;

//�����ɨ��
	if(flag_tube)
	{
		flag_tube=0;
		P2&=0xe3;
		P2|=i<<2;
		PortB=table[disp[i]];
		i++;
		if(i>3) i=0;
	}
} 

void main(void)
{	
   	RCAP2H=(0xFFFF-917)/256; 
		RCAP2L=(0xFFFF-917)%256;  //12MHz�����¶�ʱ1ms���Զ���װ 
		TH2=RCAP2H; 
		TL2=RCAP2L;         //��ʱ��2����ֵ
		EA=1; 
		ET2=1; 
		TR2=1;              //������ʱ��2 
	CAddr=mode;//����8255������ʽ,mode=0x81
  LED=0x00;
	ShowXiangmu();
	delay_ms(4000);
	ShowZuozhe();
	delay_ms(5400);
  DisplayLcd();

	while(1){
                         //***������������������ѭ��ʱ�䣬ʹ����ɨ�費��ʱ**
          Caozuokey();


	}

}
