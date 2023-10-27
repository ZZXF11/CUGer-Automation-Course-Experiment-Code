#include <reg52.h>
#include "KEY-LED.h"

xdata unsigned char PortC _at_ 0x7c02;   // PCӲ����ַ
xdata unsigned char PortB _at_ 0x7c01;   // PBӲ����ַ
xdata unsigned char CAddr _at_ 0x7c03;   // 8255�����ֵ�ַ
//----------------------------------------------------------
code unsigned char KeyTable[] = {   // ΰ��6x4���붨���
  0x16, 0x15, 0x14, 0xff,
  0x13, 0x12, 0x11, 0x10,
  0x0d, 0x0c, 0x0b, 0x0a,
  0x0e, 0x03, 0x06, 0x09,
  0x0f, 0x02, 0x05, 0x08,
  0x00, 0x01, 0x04, 0x07
};
//-----------------------------------------------------------

code unsigned char LEDMAP[] = {  // �˶ιܶ���⣬16����������
  0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,  //0��1��2....7
  0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71   //8��9��a....F
};

void delay(uint z)  //����ȥ��
{
	uint x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--);
}


uchar GetKey()	//��ⰴ�µļ�ֵ������������ֵ���Ӻ���
{
     uchar j,i;  //i�У�j�У�keynum��ֵ
     keynum=9;
//	uchar cord_l,cord_h;//�������ߺ����ߵ�ֵ�Ĵ������
//	unsigned char i;    //i����ģ�
//     unsigned char b;
//	unsigned char Pos;
//	i=4;
//	Pos = 0x80;  //Pos = 1000 0000
	PortC = 0x0f;//PC����λ���0
	if( (PortC & 0x0f) != 0x0f)//�ж��Ƿ��а������£�
	{                          //**�м�����ʱ��((PortC & 0x0f) != 0x0f)**
		delay(5);//�������
		if( (PortC & 0x0f) != 0x0f)//�ж��Ƿ��а�������
		{
//-------------------------��ȡ��ֵ��ʼ---------------------------------------
//			do{
//				PortC= ~ Pos; // PortC = 0111 1111
//				Pos >>= 1;    // ����
//			     b=~PortC & 0x0f; //1000 0000 & 0000 1111
//			}while ((--i != 0) && (b == 0));
//			
//			if (b != 0)
//               {
//                    i *= 4;
//                    if (b & 2)     i += 1;    //0000 0010
//                    else if (b & 4)     i += 2;//0000 0100
//                    else if (b & 8)     i += 3;//0000 1000
//
//			     PortC = 0;
//                    do Delay(10); while (TestKey());  // �ȼ��ͷ�
//			     return(KeyTable[i]); //ȡ�����루����ĸ�4λ���ã�
//		     }
//               else return(0xff);
                           
               uchar bitmask;
               bitmask = 0x80; //1000 0000
               for(i=0;i<4;i++)   //��4������ɨ�裬��i�У�PortC��4λ��
               {                                
                    PortC = ~ bitmask ;//����i����0��ɨ���i��          
                    if((PortC & 0x0f)!=0x0f) //��ĳһ���м�������
                    {   //i���м������£����������i������������j
                         j = (~(PortC & 0x0f)) & 0x0f;
                         switch (j)
                         {  
                              case 0x01:  j=0;break;//0000 0001,0�а���  
                              case 0x02:  j=1;break;//0000 0010,1�а���  
                              case 0x04:  j=2;break;//0000 0100,2�а���
                              case 0x08:  j=3;break;//0000 1000,3�а���  
                         }   //���������j
                         keynum=j*4+i;//��ü�ֵkeynum ***************
                         //break;//����ɨ��
                         do delay(10); 
                         while ((PortC & 0x0f) != 0x0f);  // �ȼ��ͷ�
			          return keynum; //ȡ������              
                    }
                    bitmask >>=1;
               }
//---------------------------��ȡ��ֵ����--------------------------------------
	      }
     }
     return 0xff;

}
////////
//uchar K;

//void KeyPro()
//{
//	K=PortC&0x0f;
//	switch( K )
//	{
//
//	 	//��һ�м�ֵ��
//		case 7: PortB = LEDMAP[0];		break;
//		case 11: PortB = LEDMAP[1];		break;
//		case 13: PortB = LEDMAP[2];		break;
//		case 14: PortB = LEDMAP[3];		break;
//		
//		//�ڶ��м�ֵ��
//		case 0xed: PortB = LEDMAP[4];		break;
//		case 0xdd: PortB = LEDMAP[5];		break;
//		case 0xbd: PortB = LEDMAP[6];		break;
//		case 0x7d: PortB = LEDMAP[7];		break;
//
//		//�����м�ֵ��
//		case 0xeb: PortB = LEDMAP[8];		break;
//		case 0xdb: PortB = LEDMAP[9];		break;
//		case 0xbb: PortB = LEDMAP[10];	break;
//		case 0x7b: PortB = LEDMAP[11];	break;
//
//		//�����м�ֵ��
//		case 0xe7: PortB = LEDMAP[12];	break;
//		case 0xd7: PortB = LEDMAP[13];	break;
//		case 0xb7: PortB = LEDMAP[14];	break;
//		case 0x77: PortB = LEDMAP[15];	break;
//				//��������
//		case 0xfe: PortB = LEDMAP[16];	break;
//		case 0xfd: PortB = LEDMAP[17];	break;
//		case 0xfb: PortB = LEDMAP[18];	break;
//		case 0xf7: PortB = LEDMAP[19];	break;
//	}	
//}
//////
//void (){
////	CAddr=mode;
////	PortB = 0x06;
////	P0 = 0x06;
//}





