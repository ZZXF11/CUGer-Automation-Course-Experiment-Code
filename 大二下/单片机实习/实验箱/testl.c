#include <reg52.h>

#define mode 0x81   
#define uchar unsigned char
#define uint  unsigned int
#define LEDLen 4
unsigned char LEDBuf[LEDLen]={
	0x0000,0x0400,0x0800,0x0c00
	//0x1000,0x1400,0x1800,0x1c00
};	

#define VELOCITY_30C	3495       //30���϶�ʱ�����٣�����V= 331.5 + 0.6*�¶ȣ� 
#define VELOCITY_23C	3453       //23���϶�ʱ�����٣�����V= 331.5 + 0.6*�¶ȣ� 

sbit INPUT  = P3^6;                //�������ն˿�
sbit OUTPUT = P3^0;                //���������˿�
sbit Beep   = P3^5 ;			   // ��������

long int distance=0;               //�������
uchar count;
xdata unsigned char PortA _at_ 0x6000 ; // Port A
xdata unsigned char PortB _at_ 0x6001 ; // Port B
xdata unsigned char PortC _at_ 0x6002 ; // Port C
xdata unsigned char INC _at_ 0x6002 ; 
xdata unsigned char IN _at_ 0x6002 ;
xdata unsigned char CAddr _at_ 0x6003 ; // �����ֵ�ַ
xdata unsigned char LED _at_ 0x5cff;
xdata unsigned char LED_Y0 _at_ 0xe000;

code unsigned char KeyTable[] = {
  0x0c,0x08,0x04,0x00,
	0x0d,0x09,0x05,0x01,
	0x0e,0x0a,0x06,0x02,
	0x0f,0x0b,0x07,0x03
};

code unsigned char LEDMAP[] = {  // �˶ι���ʾ��
  0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
  0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71
};

void Delay_xMs(unsigned int x)
{
    unsigned int i,j;
    for(i = 0;i < x;i++ )
    {
        for(j = 0;j < 3;j++ )
        {
            ;
        }
    }
}
//��������������                                                 */
void Alarm(uchar t)
{
	uchar i;
	for(i = 0;i < t;i++)
	{
		Beep = 0;
		Delay_xMs(10);
		Beep = 1;
		Delay_xMs(10);
	}
}		

void delayt(uint x)
{
    uchar j;
    while(x-- > 0)
    {
  	    for(j = 0;j < 125;j++)
        {
            ;
        }
    }
}

void Init_MCU(void)//��ʼ����Ƭ������
{
	TMOD = 0x01;	  //��ʱ��2��ʼ��,����Ϊ16λ�Զ���װģʽ
 	TL0 = 0x66;
	TH0 = 0xfc;	      //1ms
  ET0 = 1;	      //����ʱ��2
	EA = 1;		      //���ж�ʹ��
}

void Init_Parameter(void)//��ʼ��������IO�ں���
{
	 OUTPUT =1;
	 INPUT = 1;
	 count = 0;
	 distance = 0;
}

void Trig_SuperSonic(void)//��������
{
	 OUTPUT = 1;
	 delayt(1);
	 OUTPUT = 0;
}

void Delay(unsigned char CNT)
{
  unsigned char i;

  while (CNT-- !=0)
    for (i=100; i !=0; i--);
}

void DisplayLED()
{
  unsigned char i;
  unsigned char Pos;
  unsigned char LED;

  Pos = 0x00;  P2=0x00;     // ???????
  for (i = 0; i < 4; i++) {
    //OUTBIT = 0;     // ??????
    LED = LEDBuf[i];
    //OUTSEG = LED;
		P2=Pos;
    PortC = P2;   // ???????
    Delay(1);
    //Pos >>= 1;      // ?????
		Pos += 4;
		
  }
	Pos = 0x00; 
}


//void DisplayLED()
//{
//  unsigned char i;
//  unsigned char Pos;
//  unsigned char LED;

//  Pos = 0x80;       // ����߿�ʼ��ʾ
//  for (i = 0; i < 4; i++) {
//    PortC = 0x00;     // �����а˶ι�
//    LED = LEDBuf[i];
//    P0 = LED;
//    OUTBIT = Pos;   // ��ʾһλ�˶ι�
//    Delay(1);
//    Pos >>= 1;      // ��ʾ��һλ
//  }
//}

unsigned char TestKey()
{
   PortC = 0x0f;            // �������Ϊ0
   return (~INC & 0x0f);   // �����״̬(����λ����)
}

//unsigned char KeyScan()	//������ֵ���Ӻ���
//{
//	unsigned char Pos;
//	unsigned char i;
//  unsigned char b;

//	i=4;
//	Pos = 0x80;
//			do{
//				INC= ~ Pos;
//				Pos >>= 1;
//			  b= ~INC & 0x0f;
//			}while ((--i != 0) && (b == 0));
//			
//			if (b != 0) {
//           i *= 4;
//      if (b & 2)
//           i += 1;
//      else if (b & 4)
//           i += 2;
//      else if (b & 8)
//            i += 3;
//			//PortC = 0x00;
//			do Delay(10); 
//			while (TestKey());  // �ȼ��ͷ�
//			return(KeyTable[i]);
//			
//		}	else return(0xff);
//	
//}



unsigned char KeyScan()
{
  unsigned char Pos;
  unsigned char i;
  unsigned char k;

  i = 4;
  Pos = 0x80;     // ??????
  do {
    PortC = ~ Pos;
    Pos >>= 1;
    k = ~IN & 0x0f;
  } while ((--i != 0) && (k == 0));

  // ?? = ? x 4 + ?
  if (k != 0) {
    i *= 4;
    if (k & 2)
      i += 1;
    else if (k & 4)
      i += 2;
    else if (k & 8)
      i += 3;

    //OUTBIT = 0;
    do Delay(10); 
		while (TestKey());  // ????

    return(KeyTable[i]);  // ????
  } else return(0xff);
}

void Wacth(int k,uchar w){
	switch (k) 
           {
               case 0:  {P2=LEDBuf[0];PortB=w;DisplayLED();break;} //����������1��,��1
               case 1:  {P2=LEDBuf[1];PortB=w;DisplayLED();break;} //����������2��,��2
               case 2:  {P2=LEDBuf[2];PortB=w;DisplayLED();break;} //���������е�,��3 
               case 3:  {P2=LEDBuf[3];PortB=w;DisplayLED();break;}//����5��,��a 
           }
}

uchar DD;
void main(){
	CAddr=mode;
	TMOD = 0x01;	  //��ʱ��2��ʼ��,����Ϊ16λ�Զ���װģʽ
 	TL0 = 0x66;
	TH0 = 0xfc;	      //1ms
  ET0 = 1;	      //����ʱ��2
	EA = 1;		      //���ж�ʹ��
	Init_Parameter();
	Alarm(200);
	Delay_xMs(30000);
	
	while(1){
		Trig_SuperSonic();         //��������������
		 while(INPUT == 0)          //�ȴ�����
         {
             ;
         }
		 Measure_Distance();        //��������ת��Ϊ����

		 if(distance<=50){
			 Alarm(50);
		 }
		 //PortB = LEDMAP[distance/10];
		if(TestKey()){
			DD=KeyScan();
		PortB = LEDMAP[DD & 0x0f];
		}
		 Init_Parameter();          // �������³�ʼ��
		 delayt(100);  //��ʱ�����η���֮��Ҫ������10ms���
	 	 DisplayLED();
	}
}
void timer0 (void) interrupt 1
{
	TF0 = 0;
	TL0 = 0x66;
	TH0 = 0xfc;
	count++;
	if(count == 18)//�����������������18ms
	{
		TR0 =0;
		TL0 = 0x66;
		TH0 = 0xfc;
		count = 0;
	}
}