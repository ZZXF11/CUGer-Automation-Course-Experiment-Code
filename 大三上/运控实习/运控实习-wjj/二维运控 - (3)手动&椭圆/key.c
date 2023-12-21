#include <reg52.h>
#include "key.h"

xdata unsigned char PortC _at_ 0x7c02;   // PC硬件地址,键盘
xdata unsigned char INC _at_ 0x6002 ; 
xdata unsigned char IN _at_ 0x6002 ;

//xdata unsigned char LED _at_ 0x5cff;	// 八段管dizhi
//xdata unsigned char LED_Y0 _at_ 0xe000;

/*code unsigned char LEDMAP[] = {  // 八段管显示码
  0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
  0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71
};*/


unsigned int count;



code unsigned char KeyTable[] = //键值表
{	
	0x0c,0x08,0x04,0x00,
	0x0d,0x09,0x05,0x01,
	0x0e,0x0a,0x06,0x02,
	0x0f,0x0b,0x07,0x03
};



void Delaykey(unsigned char CNT)	//键盘延时函数
{
  unsigned char i;

  while (CNT-- !=0)
    for (i=100; i !=0; i--);
}

unsigned char TestKey()	//有无键按下检测，有就返回非零
{
   PortC = 0x0f;            // 输出PC4~PC6置为0，四列一起扫描
   return (~INC & 0x0f);   //读回四行状态（PC0~PC3），被按下的被拉成0，取反为1
}

unsigned char keyscan()
{
  unsigned char Pos;
  unsigned char i;
  unsigned char k;

  i = 4;
  Pos = 0x80;     // 1000 0000，扫描用
  do {
    PortC = ~ Pos;
    Pos >>= 1;
    k = ~IN & 0x0f;
  } while ((--i != 0) && (k == 0));

  if (k != 0) {//如果有键按下
    i *= 4;
    if (k & 2)
      i += 1;
    else if (k & 4)
      i += 2;
    else if (k & 8)
      i += 3;

    //OUTBIT = 0;
   // do Delaykey(10); 
		//while (TestKey());  // deng键松开

    return(KeyTable[i]);  //有键按下返回键值
  } 
	else return(0xff);//无键按下，则返回0xff  ￥￥￥￥￥￥￥￥￥￥￥￥
}

void shoudong()
{
		unsigned char x,y;	
		unsigned char keynum;
		while(TestKey())
		{
		keynum=keyscan() & 0x0f;	
          switch (keynum)  //keynum就等于按键的数值
          {
               case 5:  {								 
									move_onestep('x','+',30);
							 break;} 
               case 7:  {							
								 move_onestep('x','-',30);
							 break;} 
               case 0x0a:  {							 
								 move_onestep('y','+',30);
							 break;} 
							 case 2: {
								 move_onestep('y','-',30);
							 break;}
							 case 1: {
								 move_onestep('x','+',30);
								 move_onestep('y','-',30);
							 break;}
							 case 3: {
								 move_onestep('x','-',30);
								 move_onestep('y','-',30);
							 break;}
							 case 9: {
								 move_onestep('x','+',30);
								 move_onestep('y','+',30);
							 break;}
							 case 11: {
								 move_onestep('x','-',30);
								 move_onestep('y','+',30);
							 break;}
							
					}
	 }
}