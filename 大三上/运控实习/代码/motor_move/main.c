#include <reg52.h>
#include <key.h>
#include <lcd.h>
#include <move.h>
#include <init.h>

unsigned char keynum;
unsigned char code table[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00};
void move_select_head(){
	while(1){
	if(TestKey()){
		keynum=KeyScan_1() & 0x0f;	//keynum就是按键对应的值
		switch (keynum)  //keynum就等于按键的数值
          {
							case 0x0a:  {xzz();break;}   //s7
              case 0x02:  {xfz();break;}   //s15
              case 0x07:  {yzz();break;}   //s12 手动控制 上下左右            
              case 0x05:  {yfz();break;}  //s10
							case 0x0c:  {break;}
           }      
		}
	if(keynum==0x0c){
		Show_select();
		break;}
	}
}

void input_num(){
	while(1){
	if(TestKey()){
		keynum=KeyScan() & 0x0f;	//keynum就是按键对应的值
		switch (keynum)  //keynum就等于按键的数值
          {
							case 0x0f:  {xzz();break;}   //s14 0
							case 0x0a:  {xzz();break;}   //s7 1
							case 0x09:  {xzz();break;}   //s8 2
							case 0x08:  {xzz();break;}   //s9 3
							case 0x06:  {xzz();break;}   //s11 4
							case 0x05:  {xzz();break;}   //s12 5
							case 0x04:  {xzz();break;}   //s13 6
              case 0x02:  {xfz();break;}   //s15 7
              case 0x01:  {yzz();break;}   //s16 8   
							case 0x00:  {yzz();break;}   //s17 9   
							case 0x0b:  {xzz();break;}   //s6 确认
              case 0x07:  {yfz();break;}  //s10 清除
							case 0x0c:  {break;}
           }      
		}
	if(keynum==0x0c){
		Show_select();
		break;}
	}
}

void Caozuokey()//设置模式：道路、标载、开启温度
{       
	if(TestKey()){

		keynum=KeyScan() & 0x0f;	//keynum就是按键对应的值
          switch (keynum)  //keynum就等于按键的数值
          {
               case 0x0f:  {Show_head();move_select_head();break;}//s2
               case 0x0b:  {Show_str();break;}//s6 
               case 0x07:  {Show_yh();break;}//s10
               case 0x03:   break; //s14
           
           }            
     }                     
}



void main(void)
{	
	int i=0;
	delay_ms(500);
	CAddr=0x81;//设置8255工作方式,A口输出
  LED=0x00;
	ShowXiangmu();
	delay_ms(5000);
	Show_select();

	while(1){

		Caozuokey();

	}

}