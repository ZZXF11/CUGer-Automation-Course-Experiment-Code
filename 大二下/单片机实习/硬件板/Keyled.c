#include <reg52.h>

#define mode 0x81   
#define uchar unsigned char
#define uint  unsigned int
	
//xdata unsigned char PortA _at_ 0x6000 ; // Port A
xdata unsigned char PortB _at_ 0x6001 ; // Port B
xdata unsigned char PortC _at_ 0x6002 ; // Port C
xdata unsigned char INC _at_ 0x6002 ; 
xdata unsigned char IN _at_ 0x6002 ;
xdata unsigned char CAddr _at_ 0x6003 ; // 控制字地址
xdata unsigned char LED _at_ 0x5cff;
xdata unsigned char LED_Y0 _at_ 0xe000;

code unsigned char KeyTable[] = {
	0x0c,0x08,0x04,0x00,
	0x0d,0x09,0x05,0x01,
	0x0e,0x0a,0x06,0x02,
	0x0f,0x0b,0x07,0x03
};

code unsigned char LEDMAP[] = {  // 八段管显示码
  0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
  0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71
};

void Delay(unsigned char CNT)
{
  unsigned char i;

  while (CNT-- !=0)
    for (i=100; i !=0; i--);
}

unsigned char TestKey()
{
   PortC = 0x0f;            // 输出线置为0
   return (~INC & 0x0f);   // 读入键状态(高四位不用)
//     PortC = 0x0f;
//     if((PortC & 0x0f)!=0x0f) return 1;
//     else return 0x00;
}

//根据伟福实验箱修改的GetKey()函数
unsigned char KeyScan()
{
  unsigned char Pos;
  unsigned char i;
  unsigned char k;

  i = 4;
  Pos = 0x80;   
  do {
    PortC = ~ Pos;
    Pos >>= 1;
    k = ~IN & 0x0f;
  } while ((--i != 0) && (k == 0));

  if (k != 0) {
    i *= 4;
    if (k & 2)
      i += 1;
    else if (k & 4)
      i += 2;
    else if (k & 8)
      i += 3;

    do Delay(10); 
		while (TestKey());  

    return(KeyTable[i]);  
  } else return(0xff);
}
////////以下为测试代码，没有实际意义
uchar K;

void KeyPro()
{
	K=PortC&0x0f;
	switch( K )
	{

	 	//第一行键值码
		case 7: PortB = LEDMAP[0];		break;
		case 11: PortB = LEDMAP[1];		break;
		case 13: PortB = LEDMAP[2];		break;
		case 14: PortB = LEDMAP[3];		break;
		
		//第二行键值码
		case 0xed: PortB = LEDMAP[4];		break;
		case 0xdd: PortB = LEDMAP[5];		break;
		case 0xbd: PortB = LEDMAP[6];		break;
		case 0x7d: PortB = LEDMAP[7];		break;

		//第三行键值码
		case 0xeb: PortB = LEDMAP[8];		break;
		case 0xdb: PortB = LEDMAP[9];		break;
		case 0xbb: PortB = LEDMAP[10];	break;
		case 0x7b: PortB = LEDMAP[11];	break;

		//第四行键值码
		case 0xe7: PortB = LEDMAP[12];	break;
		case 0xd7: PortB = LEDMAP[13];	break;
		case 0xb7: PortB = LEDMAP[14];	break;
		case 0x77: PortB = LEDMAP[15];	break;
				//独立键盘
		case 0xfe: PortB = LEDMAP[16];	break;
		case 0xfd: PortB = LEDMAP[17];	break;
		case 0xfb: PortB = LEDMAP[18];	break;
		case 0xf7: PortB = LEDMAP[19];	break;
	}	
}
//////
uchar keynum;
//void main(){
//	CAddr=mode;
//	P0=0x06;
//	LED_Y0=0x06;
//	while(1){
//		if(TestKey()){
//			keynum=KeyScan() & 0x0f;	//keynum就是按键对应的值
//			//PortB = LEDMAP[1];
//			PortB = LEDMAP[keynum];
//		}
//	}
//}