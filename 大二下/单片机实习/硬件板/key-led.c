#include <reg52.h>
#include "KEY-LED.h"

xdata unsigned char PortC _at_ 0x7c02;   // PC硬件地址
xdata unsigned char PortB _at_ 0x7c01;   // PB硬件地址
xdata unsigned char CAddr _at_ 0x7c03;   // 8255控制字地址
//----------------------------------------------------------
code unsigned char KeyTable[] = {   // 伟福6x4键码定义库
  0x16, 0x15, 0x14, 0xff,
  0x13, 0x12, 0x11, 0x10,
  0x0d, 0x0c, 0x0b, 0x0a,
  0x0e, 0x03, 0x06, 0x09,
  0x0f, 0x02, 0x05, 0x08,
  0x00, 0x01, 0x04, 0x07
};
//-----------------------------------------------------------

code unsigned char LEDMAP[] = {  // 八段管段码库，16个，共阴极
  0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,  //0，1，2....7
  0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71   //8，9，a....F
};

void delay(uint z)  //用在去抖
{
	uint x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--);
}


uchar GetKey()	//监测按下的键值函数，带返回值的子函数
{
     uchar j,i;  //i列，j行，keynum键值
     keynum=9;
//	uchar cord_l,cord_h;//声明列线和行线的值的储存变量
//	unsigned char i;    //i干嘛的？
//     unsigned char b;
//	unsigned char Pos;
//	i=4;
//	Pos = 0x80;  //Pos = 1000 0000
	PortC = 0x0f;//PC高四位输出0
	if( (PortC & 0x0f) != 0x0f)//判断是否有按键按下，
	{                          //**有键按下时，((PortC & 0x0f) != 0x0f)**
		delay(5);//软件消抖
		if( (PortC & 0x0f) != 0x0f)//判断是否有按键按下
		{
//-------------------------提取键值开始---------------------------------------
//			do{
//				PortC= ~ Pos; // PortC = 0111 1111
//				Pos >>= 1;    // 移行
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
//                    do Delay(10); while (TestKey());  // 等键释放
//			     return(KeyTable[i]); //取出键码（结果的高4位无用）
//		     }
//               else return(0xff);
                           
               uchar bitmask;
               bitmask = 0x80; //1000 0000
               for(i=0;i<4;i++)   //把4列逐列扫描，第i列（PortC高4位）
               {                                
                    PortC = ~ bitmask ;//给第i列送0，扫描第i列          
                    if((PortC & 0x0f)!=0x0f) //有某一行有键被按下
                    {   //i列有键被按下，获得所在列i，再求所在行j
                         j = (~(PortC & 0x0f)) & 0x0f;
                         switch (j)
                         {  
                              case 0x01:  j=0;break;//0000 0001,0行按下  
                              case 0x02:  j=1;break;//0000 0010,1行按下  
                              case 0x04:  j=2;break;//0000 0100,2行按下
                              case 0x08:  j=3;break;//0000 1000,3行按下  
                         }   //获得所在行j
                         keynum=j*4+i;//获得键值keynum ***************
                         //break;//结束扫描
                         do delay(10); 
                         while ((PortC & 0x0f) != 0x0f);  // 等键释放
			          return keynum; //取出键码              
                    }
                    bitmask >>=1;
               }
//---------------------------提取键值结束--------------------------------------
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
//	 	//第一行键值码
//		case 7: PortB = LEDMAP[0];		break;
//		case 11: PortB = LEDMAP[1];		break;
//		case 13: PortB = LEDMAP[2];		break;
//		case 14: PortB = LEDMAP[3];		break;
//		
//		//第二行键值码
//		case 0xed: PortB = LEDMAP[4];		break;
//		case 0xdd: PortB = LEDMAP[5];		break;
//		case 0xbd: PortB = LEDMAP[6];		break;
//		case 0x7d: PortB = LEDMAP[7];		break;
//
//		//第三行键值码
//		case 0xeb: PortB = LEDMAP[8];		break;
//		case 0xdb: PortB = LEDMAP[9];		break;
//		case 0xbb: PortB = LEDMAP[10];	break;
//		case 0x7b: PortB = LEDMAP[11];	break;
//
//		//第四行键值码
//		case 0xe7: PortB = LEDMAP[12];	break;
//		case 0xd7: PortB = LEDMAP[13];	break;
//		case 0xb7: PortB = LEDMAP[14];	break;
//		case 0x77: PortB = LEDMAP[15];	break;
//				//独立键盘
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





