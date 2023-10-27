#include <reg52.h>
#include "DIANZHEN.c"
#include "lcd.c"
#include "Keyled.c"
 
#define uchar unsigned char
//****矩阵键盘：列扫描，行读回****
unsigned int  count=0;			//计时
unsigned char flag_dot=0;		//点阵刷新标志，速度慢于蜂鸣器10倍
unsigned int  delay_time=0;	//延时的时间
unsigned char disp[4]=0;		//锁存数码管数据
unsigned char flag_miao=0;	//秒标志，为10时表示1秒
unsigned char flag_tube=0;	//晶码管刷新标志，每2ms扫描一次
unsigned char Time=0;				//定时器2，每1ms加一
unsigned char flag_key=0;		//按键刷新标志，每10ms扫描一次
unsigned char i=0;					//数码管，指在当前位
unsigned char flag_key2=0;	//按键按下标志，跳出歌曲播放
unsigned char flag_pause=0;	//暂停标志
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
void Caozuokey()//设置模式：道路、标载、开启温度
{       
	if(TestKey()){
		keynum=KeyScan() & 0x0f;	//keynum就是按键对应的值
          switch (keynum)  //keynum就等于按键的数值
          {
               case 0:  {initMotor=0x00;DisplayLcd();break;} //可容许右起1档,按1
               case 1:  {initMotor=0x01;DisplayLcd();break;} //可容许右起2档,按2
               case 2:  {initMotor=0x02;DisplayLcd();break;} //可容许所有档,按3 
               case 0x04:  {initYALI=0x0a;DisplayLcd();break;}//载重5人,按a 
               case 0x08:  {initYALI=0x0b;DisplayLcd();break;}//载重7人,按b 
               case 0x0c:  {initYALI=0x0c;DisplayLcd();break;}//载重9人,按c  
               case 0x0b:  {--initTEMP;DisplayLcd();break;}   //下调空调开启温度,按3(左上第2)
               case 0x0f:  {++initTEMP;DisplayLcd();break;}   //上调空调开启温度,按F（左上第1）                
               case 0x07:   DisplayDZtemp();break;  //按键左上第3代表实际温度超过阈值，进入温度报警
               case 0x03:   DisplayDZdistance();break; //按键左下角代表距离过近
           
           }            
     }                     
}
unsigned int dou=0;
uchar j=0;
uchar flag_i=0;
//以下为根据帅仁浩代码修改的时间显示程序
//使用定时器2实现计时
void timer2() interrupt 5 
{  
  TF2=0; //定时器2必须由软件对溢出标志位清零    
  Time++;//用于计时
	if(Time==100) {Time=0;flag_miao++;}
	if(!(Time%10)&&!flag_key2)	if(++flag_key>3) flag_key=0;//
	if(!(Time%2))	flag_tube=1;
	if(flag_miao==10)//整秒标志
	{
//显示播放时间
		flag_miao=0;
		disp[3]=count%10;
		disp[2]=count/10%10;
		disp[1]=count/100;
		if(!flag_pause)//暂停不加
			count++;
//八段管刷新
		P2=0x4f;//每秒都进行一次流水
		if(flag_i<8)
			P0=~(1<<flag_i),flag_i++;
		else if(flag_i<14)
			P0=~(0x80>>(flag_i-7)),flag_i++;
		else flag_i=0,P0=~(1<<flag_i),flag_i++;
		P2=0x6f;
	}
	if(delay_time)delay_time--;

//数码管扫描
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
		RCAP2L=(0xFFFF-917)%256;  //12MHz晶振下定时1ms，自动重装 
		TH2=RCAP2H; 
		TL2=RCAP2L;         //定时器2赋初值
		EA=1; 
		ET2=1; 
		TR2=1;              //启动定时器2 
	CAddr=mode;//设置8255工作方式,mode=0x81
  LED=0x00;
	ShowXiangmu();
	delay_ms(4000);
	ShowZuozhe();
	delay_ms(5400);
  DisplayLcd();

	while(1){
                         //***点阵放主程序里会拖慢循环时间，使按键扫描不及时**
          Caozuokey();


	}

}
