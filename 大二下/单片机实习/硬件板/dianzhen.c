#include <reg52.h>

#define uchar unsigned char
#define uint  unsigned int
xdata unsigned char LED _at_ 0x5cff;
sbit BEEP   = P3^5 ;
//��ˮ��4000��8255��ַ6000
//************P1�����У��е�ַP1*************************
//************PA�����У��е�ַPortA**********************
//��ѡ��������

xdata unsigned char PortA _at_ 0x7c00;   // PA��ַ

//��ģ   ÿ��8x8,   8�ֽ�
code uchar Font[][8] = {

/*   4    */
0x10,0x18,0x1C,0x14,0x12,0x3E,0x10,0x38,

/*-- ! --*/
0x1C,0x1C,0x1C,0x08,0x08,0x08,0x00,0x08,

/*--  ͬ���  --*/
/*--  ���x�߶�=8x8  --*/
0x18,0x24,0x42,0x99,0x99,0x42,0x24,0x18,

/*--  ���ο���  --*/
/*--  ���x�߶�=8x8  --*/
0xFF,0x81,0xA5,0x81,0xBD,0xA5,0x81,0xFF,
 

  };

unsigned char LEDMAP_1[8] =    //һ���������వ
{
	0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f
};

void delay_1( unsigned int CNT )
{
	 unsigned char i;

	 while ( CNT-- != 0)
	 	for( i=100; i != 0; --i)
			;
}

void Delay1()//������ר����ʱ
{
  unsigned char i;
  for (i=0; i<200; i++);
}
	
void delayDZ (uint t)//��ʱ�ӳ���
{
    uint i;
    for(i=0;i<t;++i) ;
}
void BEE(){
	
	int i;
	P2=0x5f;
	P0=~P0;
	for(i=0;i<8;++i){//LED��˸��������bee
		P0 =  LEDMAP_1[i];
		BEEP=0;
		Delay1();
		BEEP=1;
		Delay1();
 }
}

//********************�¶ȱ�����ʾ������**************************
void DisplayDZtemp()
{
	uchar j,i;
     uchar count;
     uchar bitmask;

     //******����*********
     PortA=0xff;//�͵�ƽ��Ч
     P1=0xff;//�͵�ƽ��Ч

//--------------------------------------------------------------------------

    for(j=3; j<4; j++){              //�����ʾ��ѡ��ͼ��j:��ģ���е�j���֡�

      for(count =0; count <150; count ++){//ÿ������ʾ150��
				BEE();
        bitmask = 0x01;
        for(i=0;i<8;i++){               //�ѵ�j��������ɨ��
             
//          PortA=0xff;//�͵�ƽ��Ч//******����*********
//          P1=0xff;//�͵�ƽ��Ч
                  
          P1= ~ Font[j][i];//����i����ֵ��P1�����棩          
          PortA=bitmask;//�����һ�У�������һ�У�

          delayDZ (150);
          bitmask <<= 1;               //������һ��
        }
      }
      P1  = 0xff;
    }
}


//*********************���뱨����ʾ������*****************************
void DisplayDZdistance()
{
	uchar j,i;
     uchar count;
     uchar bitmask;

     //******����*********
     PortA=0xff;//�͵�ƽ��Ч
     P1=0xff;//�͵�ƽ��Ч

//--------------------------------------------------------------------------

    for(j=1; j<2; j++){              //�����ʾ��ѡ��ͼ��j:��ģ���е�j���֡�
      for(count =0; count <150; count ++){//ÿ������ʾ150��
				BEE();
        bitmask = 0x01;
        for(i=0;i<8;i++){               //�ѵ�j��������ɨ��
             
//          PortA=0xff;//�͵�ƽ��Ч//******����*********
//          P1=0xff;//�͵�ƽ��Ч
                  
          P1= ~ Font[j][i];//����i����ֵ��P1�����棩          
          PortA=bitmask;//�����һ�У�������һ�У�

          delayDZ (150);
          bitmask <<= 1;               //������һ��
        }
      }
      P1  = 0xff;
    }
}
