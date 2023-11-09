/****************************************************************
 NAME: u2440mon.c
 DESC: u2440mon entry point,menu,download
 ****************************************************************/
#define	GLOBAL_CLK		1

#include <stdlib.h>
#include <string.h>
#include "def.h"
#include "option.h"
#include "2440addr.h"
#include "2440lib.h"
#include "2440slib.h"
#include "mmu.h"
#include "profile.h"
#include "memtest.h"

//-----add bgn------------
#include "lcd_tft.h"
#ifdef CSTM_LCD
#include "cstm_lcd.h"

U8 g_type;
#endif
//-----add end------------
unsigned char SONG_qcc[] ={      //穷哈哈
0x39,0x10,0x39,0x18,0x30,0x10,0x2b,0x10,0x2b,0x10,0x26,0x10,0x20,0x10,0x26,0x10,
0x26,0x18,0x20,0x10,0x1c,0x10,0x18,0x10,0x15,0x10,0x13,0x15,0x18,0x10,0x18,0x10,
0x18,0x10,0x18,0x10,0x2b,0x10,0x26,0x10,0x20,0x10,0x2b,0x10,0x26,0x18,0x20,0x10,
0x26,0x10,0x20,0x10,0x26,0x10,0x26,0x10,
0x20,0x10,0x1c,0x10,0x30,0x10,0x2b,0x10,0x30,0x10,0x30,0x10,0x2b,0x10,0x26,0x10,
0x20,0x10,0x20,0x10,0x26,0x10,0x1c,0x10,0x26,0x10,0x2b,0x10,0x30,0x20,0x30,0x10,
0x33,0x10,0x39,0x10,0x40,0x10,0x39,0x10,
};

//低音区
unsigned char one_l[] ={      //do
0x60,0x10,
};
unsigned char two_l[] ={      //re
0x55,0x10,
};
unsigned char three_l[] ={      //mi
0x4c,0x10,
};
unsigned char four_l[] ={      //fa
0x48,0x10,
};
unsigned char five_l[] ={      //so
0x40,0x10,
};
unsigned char six_l[] ={      //la
0x39,0x10,
};
unsigned char seven_l[] ={      //xi
0x33,0x10,
};
//低音区##
unsigned char one_s_l[] ={      //do
0x57,0x10,
};
unsigned char two_s_l[] ={      //re
0x51,0x10,
};
unsigned char four_s_l[] ={      //fa
0x44,0x10,
};
unsigned char five_s_l[] ={      //so
0x3c,0x10,
};
unsigned char six_s_l[] ={      //la
0x36,0x10,
};


//中音区
unsigned char one[] ={      //do
0x30,0x10,
};
unsigned char two[] ={      //re
0x2b,0x10,
};
unsigned char three[] ={      //mi
0x26,0x10,
};
unsigned char four[] ={      //fa
0x24,0x10,
};
unsigned char five[] ={      //so
0x20,0x10,
};
unsigned char six[] ={      //la
0x1c,0x10,
};
unsigned char seven[] ={      //xi
0x19,0x10,
};
//中音区##
unsigned char one_s[] ={      //do
0x2e,0x10,
};
unsigned char two_s[] ={      //re
0x28,0x10,
};
unsigned char four_s[] ={      //fa
0x22,0x10,
};
unsigned char five_s[] ={      //so
0x1e,0x10,
};
unsigned char six_s[] ={      //la
0x1b,0x10,
};


//高音区
unsigned char one_h[] ={      //do
0x18,0x10,
};
unsigned char two_h[] ={      //re
0x15,0x10,
};
unsigned char three_h[] ={      //mi
0x13,0x10,
};
unsigned char four_h[] ={      //fa
0x12,0x10,
};
unsigned char five_h[] ={      //so
0x10,0x10,
};
unsigned char six_h[] ={      //la
0x0e,0x10,
};
unsigned char seven_h[] ={      //xi
0x0d,0x10,
};
//高音区##
unsigned char one_s_h[] ={      //do
0x16,0x10,
};
unsigned char two_s_h[] ={      //re
0x14,0x10,
};
unsigned char four_s_h[] ={      //fa
0x11,0x10,
};
unsigned char five_s_h[] ={      //so
0x0f,0x10,
};
unsigned char six_s_h[] ={      //la
0x0d,0x10,
};

extern char Image$$RO$$Limit[];
extern char Image$$RO$$Base[];
extern char Image$$RW$$Limit[];
extern char Image$$RW$$Base[];
extern char Image$$ZI$$Limit[];
extern char Image$$ZI$$Base[];

	extern unsigned char tu1_320240[];
	extern unsigned char tu2_320240[];
	//extern unsigned char tu3_320240[];
	extern unsigned char tu4_320240[];
	extern unsigned char tu5_320240[];
	extern unsigned char tu6_320240[];
	extern unsigned char tu7_319156[];
	extern unsigned char keyboard_teach[];
	

void Isr_Init(void);
void HaltUndef(void);
void HaltSwi(void);
void HaltPabort(void);
void HaltDabort(void);
void ClearMemory(void);


void Clk0_Enable(int clock_sel);	
void Clk1_Enable(int clock_sel);
void Clk0_Disable(void);
void Clk1_Disable(void);

extern void Lcd_TFT_Init(void);
extern void Lcd_TFT_Test( void ) ;
/*extern void KeyScan_Test(void) ;
extern void Test_Touchpanel(void) ;
extern void Test_Adc(void) ;
extern void RTC_Display(void) ;
extern void Test_IrDA_Tx(void) ;
extern void PlayMusicTest(void) ;
extern void RecordTest( void ) ;
extern void Test_Iic(void) ;
extern void Test_SDI(void) ;
extern void Camera_Test( void ) ;*/
#define REQCNT 30
#define ADCPRS 9
#define LOOP 1
void __irq AdcTsAuto(void);
int count=0;
volatile int xdata, ydata;
extern void Lcd_ClearScr1(int x0,int y0,int h,int l,U32 c);


volatile U32 downloadAddress;

void (*restart)(void)=(void (*)(void))0x0;

volatile unsigned char *downPt;
volatile U32 downloadFileSize;
volatile U16 checkSum;
volatile unsigned int err=0;
volatile U32 totalDmaCount;

volatile int isUsbdSetConfiguration;

int download_run=0;
U32 tempDownloadAddress;
U8 key2;
int menuUsed=0;
int flag_irq=0;
int flag_piano_select=0;
int zkb=10;
int flag_jiaoxue=0;


extern char Image$$RW$$Limit[];
U32 *pMagicNum=(U32 *)Image$$RW$$Limit;
int consoleNum;
extern unsigned char feiYYmini[];
extern unsigned char meiYYmini[];
extern unsigned char manYY_2mini[];
extern unsigned char nuanYYmini[];
extern unsigned char xiYYmini[];
extern unsigned char lanYYmini[];
extern unsigned char feiYY[];
extern unsigned char meiYY[];
extern unsigned char manYY_2[];
extern unsigned char nuanYY[];
extern unsigned char xiYY[];
extern unsigned char lanYY[];
extern unsigned char bass[];
extern unsigned char bassmini[];

static U32 cpu_freq;
static U32 UPLL;
static void cal_cpu_bus_clk(void)
{
	U32 val;
	U8 m, p, s;
	
	val = rMPLLCON;
	m = (val>>12)&0xff;
	p = (val>>4)&0x3f;
	s = val&3;

	//(m+8)*FIN*2 不要超出32位数!
	FCLK = ((m+8)*(FIN/100)*2)/((p+2)*(1<<s))*100;
	
	val = rCLKDIVN;
	m = (val>>1)&3;
	p = val&1;	
	val = rCAMDIVN;
	s = val>>8;
	
	switch (m) {
	case 0:
		HCLK = FCLK;
		break;
	case 1:
		HCLK = FCLK>>1;
		break;
	case 2:
		if(s&2)
			HCLK = FCLK>>3;
		else
			HCLK = FCLK>>2;
		break;
	case 3:
		if(s&1)
			HCLK = FCLK/6;
		else
			HCLK = FCLK/3;
		break;
	}
	
	if(p)
		PCLK = HCLK>>1;
	else
		PCLK = HCLK;
	
	if(s&0x10)
		cpu_freq = HCLK;
	else
		cpu_freq = FCLK;
		
	val = rUPLLCON;
	m = (val>>12)&0xff;
	p = (val>>4)&0x3f;
	s = val&3;
	UPLL = ((m+8)*FIN)/((p+2)*(1<<s));
	UCLK = (rCLKDIVN&8)?(UPLL>>1):UPLL;
}






void Temp_function() { Uart_Printf("\nPlease input 1-11 to select test!!!\n"); }

/*struct {
	void (*fun)(void);
	char *tip;
}CmdTip[] = {
				{ Temp_function, "Please input 1-11 to select test" } ,
				{ BUZZER_PWM_Test, "Test PWM" } ,
				{ RTC_Display, "RTC time display" } ,
				{ Test_Adc, "Test ADC" } ,
				{ KeyScan_Test, "Test interrupt and key scan" } ,
				{ Test_Touchpanel, "Test Touchpanel" } ,
				{ Lcd_TFT_Test, "Test TFT LCD" } ,
				{ Test_Iic, "Test IIC EEPROM" } ,
				{ PlayMusicTest, "UDA1341 play music" } ,
				{ RecordTest, "UDA1341 record voice" } ,
				{ Test_SDI, "Test SD Card" } ,
				{ Camera_Test, "Test CMOS Camera"},
				{ 0, 0}						
			};*/

//----add bgn------------
//----add end------------	


void PWM_change(int zkb){

	rGPBCON &= ~3;			//set GPB0 as tout0, pwm output
	rGPBCON |= 2;
		
	rTCFG0 &= ~0xff;
	rTCFG0 |= 15;			//prescaler = 15+1
	rTCFG1 &= ~0xf;
	rTCFG1 |= 2;
	rTCMPB0 = rTCNTB0*zkb/10;	// 50%
	rTCON &= ~0x1f;
	rTCON |= 0xb;			//disable deadzone, auto-reload, inv-off, update TCNTB0&TCMPB0, start timer 0
	rTCON &= ~2;			//clear manual update bit
}


/*static void __irq Key_ISR(void)
{
	U8 key;
	U32 r;

	EnterCritical(&r);
	if(rINTPND==BIT_EINT1)
	{
		//Uart_Printf("eint1\n");
		ClearPending(BIT_EINT1);
	}
	if(rINTPND==BIT_EINT4_7)
	{
		ClearPending(BIT_EINT4_7);
		if(rEINTPEND&(1<<4))
		{
			//Uart_Printf("eint4\n");
			rEINTPEND |= 1<< 4;
		}
	}
	if(rINTPND==BIT_EINT0)
	{
		//Uart_Printf("eint0\n");
		ClearPending(BIT_EINT0);
	}
	if(rINTPND==BIT_EINT2)
	{
		//Uart_Printf("eint2\n");
		ClearPending(BIT_EINT2);
	}

	key=Key_Scan();
	if( key == 0xff )
		Uart_Printf( "Interrupt occur... Key is released!\n") ;
	else
		Uart_Printf( "Interrupt occur... K%d is pressed!\n", key) ;

	ExitCritical(&r);
}*/
void Buzzer_Freq_Set0(U32 freq ){
	rGPBCON &= ~3;			//set GPB0 as tout0, pwm output
	rGPBCON |= 2;
		
	rTCFG0 &= ~0xff;
	rTCFG0 |= 15;			//prescaler = 15+1
	rTCFG1 &= ~0xf;
	rTCFG1 |= 2;			//mux = 1/8

	rTCNTB0 = (PCLK>>7)/freq;
	rTCMPB0 = rTCNTB0*0.03;	//修改这一句，来调整占空比，同学们可以自己做实验尝试
	
	rTCON &= ~0x1f;
	rTCON |= 0xb;			//disable deadzone, auto-reload, inv-off, update TCNTB0&TCMPB0, start timer 0
	rTCON &= ~2;			//clear manual update bit
}

void Buzzer_Freq_Set1(U32 freq ,float zkb){
	rGPBCON &= ~3;			//set GPB0 as tout0, pwm output
	rGPBCON |= 2;
		
	rTCFG0 &= ~0xff;
	rTCFG0 |= 15;			//prescaler = 15+1
	rTCFG1 &= ~0xf;
	rTCFG1 |= 2;			//mux = 1/8

	rTCNTB0 = (PCLK>>7)/freq;
	rTCMPB0 = rTCNTB0*zkb/10;	//修改这一句，来调整占空比，同学们可以自己做实验尝试
	
	rTCON &= ~0x1f;
	rTCON |= 0xb;			//disable deadzone, auto-reload, inv-off, update TCNTB0&TCMPB0, start timer 0
	rTCON &= ~2;			//clear manual update bit
}

unsigned char Temp1,Temp2;
unsigned int Addr=0;
U16 freq =800;

void display_menu(void){
	//先把菜单显示一遍
	Paint_Bmp(0, 0, 480, 272, menu);//菜单背景
	Paint_Bmp(8,170,105,60,drummini);//项目1
	Paint_Bmp(128,170,105,60,keyboardmini);//项目2
	Paint_Bmp(248,170,105,60,bassmini);//项目3
	Glib_Rectangle(232,4,318,52,0x000000);//'高八度'用黄色框框住
	Glib_Rectangle(107,4,193,52,0x000000);//把'低八度'用黄色框框住
	Glib_Rectangle(358,4,444,52,0x000000);//把'教学'用黄色框框住
	//Paint_Bmp(248,170,105,60,microphonemini);//项目4
}

void select_irq(void){
		if(ydata>170&&ydata<230)//判断位置显示图放在了校准里
		{
			if(xdata>8 && xdata<113)//如果点击项目1
			{
				Paint_Bmp(0, 0, 480, 272, drum);
				flag_irq=2;
			}
			else if(xdata>128 && xdata<233)//如果点击项目2
			{
				
				Paint_Bmp(0, 0, 480, 272, keyboard);
				flag_irq=1;
			}
			else if(xdata>248 && xdata<353)//如果点击项目3
			{
				
				Paint_Bmp(0, 0, 480, 272, bass);
				flag_irq=3;			
			}

		}//判断位置显示图结束

}

void play_the_bass(void){
	if(ydata>0 && ydata<54){
			if(xdata<54) {Uart_Printf("退出函数");flag_irq=0;display_menu();}	
		}
	else if(ydata>78 && ydata<118){
		if(xdata>0 && xdata<115){Temp1=five_s[Addr++];Temp2=five_s[Addr++];freq=25000/Temp1;Buzzer_Freq_Set0( freq );Delay(12*Temp2);}
		if(xdata>120 && xdata<170){Temp1=six[Addr++];Temp2=six[Addr++];freq=25000/Temp1;Buzzer_Freq_Set0( freq );Delay(12*Temp2);}
		if(xdata>176 && xdata<222){Temp1=six_s[Addr++];Temp2=six_s[Addr++];freq=25000/Temp1;Buzzer_Freq_Set0( freq );Delay(12*Temp2);}
	}
	else if(ydata>125 && ydata<165){
		if(xdata>0 && xdata<115){Temp1=two_s[Addr++];Temp2=two_s[Addr++];freq=25000/Temp1;Buzzer_Freq_Set0( freq );Delay(12*Temp2);}
		if(xdata>120 && xdata<170){Temp1=three[Addr++];Temp2=three[Addr++];freq=25000/Temp1;Buzzer_Freq_Set0( freq );Delay(12*Temp2);}
		if(xdata>176 && xdata<222){Temp1=four[Addr++];Temp2=four[Addr++];freq=25000/Temp1;Buzzer_Freq_Set0( freq );Delay(12*Temp2);}
	}
	else if(ydata>173 && ydata<213){
		if(xdata>0 && xdata<115){Temp1=six_s_l[Addr++];Temp2=six_s_l[Addr++];freq=25000/Temp1;Buzzer_Freq_Set0( freq );Delay(12*Temp2);}
		if(xdata>120 && xdata<170){Temp1=seven_l[Addr++];Temp2=seven_l[Addr++];freq=25000/Temp1;Buzzer_Freq_Set0( freq );Delay(12*Temp2);}
		if(xdata>176 && xdata<222){Temp1=one[Addr++];Temp2=one[Addr++];freq=25000/Temp1;Buzzer_Freq_Set0( freq );Delay(12*Temp2);}
	}
	else if(ydata>222 && ydata<262){
		if(xdata>0 && xdata<115){Temp1=four_l[Addr++];Temp2=four_l[Addr++];freq=25000/Temp1;Buzzer_Freq_Set0( freq );Delay(12*Temp2);}
		if(xdata>120 && xdata<170){Temp1=four_s_l[Addr++];Temp2=four_s_l[Addr++];freq=25000/Temp1;Buzzer_Freq_Set0( freq );Delay(12*Temp2);}
		if(xdata>176 && xdata<222){Temp1=five_l[Addr++];Temp2=five_l[Addr++];freq=25000/Temp1;Buzzer_Freq_Set0( freq );Delay(12*Temp2);}
	}
}

void play_the_drum(void){
	if(ydata>0 && ydata<54){
			if(xdata<54) {Uart_Printf("退出函数");flag_irq=0;display_menu();}	
		}
	else if(ydata>80 && ydata<115 && xdata>24 && xdata<130){Temp1=one[Addr++];Temp2=one[Addr++];freq=25000/Temp1;Buzzer_Freq_Set0( freq );Delay(12*Temp2);}
	else if(ydata>154 && ydata<182 && xdata>38 && xdata<130){Temp1=two[Addr++];Temp2=two[Addr++];freq=25000/Temp1;Buzzer_Freq_Set0( freq );Delay(12*Temp2);}
	else if(ydata>194 && ydata<248 && xdata>184 && xdata<296){Temp1=five_l[Addr++];Temp2=five_l[Addr++];freq=25000/Temp1;Buzzer_Freq_Set0( freq );Delay(12*Temp2);}
	else if(ydata>194 && ydata<248 && xdata>75 && xdata<160){Temp1=four_l[Addr++];Temp2=four_l[Addr++];freq=25000/Temp1;Buzzer_Freq_Set0( freq );Delay(12*Temp2);}
	else if(ydata>194 && ydata<248 && xdata>310 && xdata<422){Temp1=four_s_l[Addr++];Temp2=four_s_l[Addr++];freq=25000/Temp1;Buzzer_Freq_Set0( freq );Delay(12*Temp2);}
	else if(ydata>115 && ydata<154 && xdata>166 && xdata<220){Temp1=seven_l[Addr++];Temp2=seven_l[Addr++];freq=25000/Temp1;Buzzer_Freq_Set0( freq );Delay(12*Temp2);}
	else if(ydata>115 && ydata<154 && xdata>276 && xdata<328){Temp1=six[Addr++];Temp2=six[Addr++];freq=25000/Temp1;Buzzer_Freq_Set0( freq );Delay(12*Temp2);}
	else if(ydata>115 && ydata<154 && xdata>400 && xdata<440){Temp1=four[Addr++];Temp2=four[Addr++];freq=25000/Temp1;Buzzer_Freq_Set0( freq );Delay(12*Temp2);}
}

void play_the_piano(void){

		if(ydata>0 && ydata<54){
			if(xdata<54) {Uart_Printf("退出函数");flag_irq=0;display_menu();}
			if(xdata<190 && xdata>110) {if(flag_piano_select>-1){flag_piano_select--;}}//低八度
			if(xdata<315 && xdata>235) {if(flag_piano_select<1){flag_piano_select++;}}//高八度
			}
		else if(ydata>54 && ydata<185&&ydata!=74&&ydata!=76&&ydata!=77&&ydata!=73&&ydata!=95&&ydata!=96&&ydata!=97&&ydata!=113&&ydata!=116&&ydata!=115&&ydata!=60
		&&ydata!=62&&ydata!=63&&ydata!=64)
		{
			if(xdata>30 && xdata<60)
			{
				//SC
				if(flag_piano_select==0){Temp1=one_s[Addr++];Temp2=one_s[Addr++];}
				if(flag_piano_select==1){Temp1=one_s_h[Addr++];Temp2=one_s_h[Addr++];}
				if(flag_piano_select==-1){Temp1=one_s_l[Addr++];Temp2=one_s_l[Addr++];}
				freq=25000/Temp1;	
				Buzzer_Freq_Set0( freq );
		    	Delay(12*Temp2);
			}
			if(xdata>83 && xdata<113)
			{
				//SD
				if(flag_piano_select==0){Temp1=two_s[Addr++];Temp2=two_s[Addr++];}
				if(flag_piano_select==1){Temp1=two_s_h[Addr++];Temp2=two_s_h[Addr++];}
				if(flag_piano_select==-1){Temp1=two_s_l[Addr++];Temp2=two_s_l[Addr++];}
				freq=25000/Temp1;	
				Buzzer_Freq_Set0( freq );
		    	Delay(12*Temp2);
			}
				if(xdata>174 && xdata<204)
			{
				//SF
				if(flag_piano_select==0){Temp1=four_s[Addr++];Temp2=four_s[Addr++];}
				if(flag_piano_select==1){Temp1=four_s_h[Addr++];Temp2=four_s_h[Addr++];}
				if(flag_piano_select==-1){Temp1=four_s_l[Addr++];Temp2=four_s_l[Addr++];}
				freq=25000/Temp1;	
				Buzzer_Freq_Set0( freq );
		    	Delay(12*Temp2);
			}
				if(xdata>225 && xdata<255)
			{
				//SG
				if(flag_piano_select==0){Temp1=five_s[Addr++];Temp2=five_s[Addr++];}
				if(flag_piano_select==1){Temp1=five_s_h[Addr++];Temp2=five_s_h[Addr++];}
				if(flag_piano_select==-1){Temp1=five_s_l[Addr++];Temp2=five_s_l[Addr++];}
				freq=25000/Temp1;	
				Buzzer_Freq_Set0( freq );
		    	Delay(12*Temp2);
			}
				if(xdata>275 && xdata<305 )
			{
				//SA
				if(flag_piano_select==0){Temp1=six_s[Addr++];Temp2=six_s[Addr++];}
				if(flag_piano_select==1){Temp1=six_s_h[Addr++];Temp2=six_s_h[Addr++];}
				if(flag_piano_select==-1){Temp1=six_s_l[Addr++];Temp2=six_s_l[Addr++];}
				freq=25000/Temp1;	
				Buzzer_Freq_Set0( freq );
		    	Delay(12*Temp2);
			}
				if(xdata>366 && xdata<396&&xdata!=453 &&xdata!=452)
			{
				//SCh
				//Uart_Printf("jinru1\n");
				//Uart_Printf("count=%03d  XP=%04d, YP=%04d\n", count++, xdata, ydata);
				//if(flag_piano_select==-1){Temp1=one_s[Addr++];Temp2=one_s[Addr++];}
				//if(flag_piano_select==0){Temp1=one_s_h[Addr++];Temp2=one_s_h[Addr++];}
				//if(flag_piano_select!=1){
				//freq=25000/Temp1;	
				//Buzzer_Freq_Set0( freq );
		    	//Delay(12*Temp2);}
				
			}
				if(xdata>419 && xdata<433&&xdata!=437 &&xdata!=436)
			{
				//SDh
				//Uart_Printf("jinru2\n");
				Uart_Printf("count=%03d  XP=%04d, YP=%04d\n", count++, xdata, ydata);
				
			}
				
		}
		else if(ydata<272 && ydata>195)
		{

			if(xdata>0 && xdata<48)
			{
				//C
				if(flag_piano_select==0){Temp1=one[Addr++];Temp2=one[Addr++];}
				if(flag_piano_select==1){Temp1=one_h[Addr++];Temp2=one_h[Addr++];}
				if(flag_piano_select==-1){Temp1=one_l[Addr++];Temp2=one_l[Addr++];}
				freq=25000/Temp1;	
				Buzzer_Freq_Set0( freq );
		    	Delay(12*Temp2);
			}
			else if(xdata>48 && xdata<96)
			{
				//D
				if(flag_piano_select==0){Temp1=two[Addr++];Temp2=two[Addr++];}
				if(flag_piano_select==1){Temp1=two_h[Addr++];Temp2=two_h[Addr++];}
				if(flag_piano_select==-1){Temp1=two_l[Addr++];Temp2=two_l[Addr++];}
				freq=25000/Temp1;	
				Buzzer_Freq_Set0( freq );
		    	Delay(12*Temp2);
			}
			else if(xdata>96 && xdata<144)
			{
				//E
				if(flag_piano_select==0){Temp1=three[Addr++];Temp2=three[Addr++];}
				if(flag_piano_select==1){Temp1=three_h[Addr++];Temp2=three_h[Addr++];}
				if(flag_piano_select==-1){Temp1=three_l[Addr++];Temp2=three_l[Addr++];}
				freq=25000/Temp1;	
				Buzzer_Freq_Set0( freq );
		    	Delay(12*Temp2);
			}
			
			else if(xdata>144 && xdata<192)
			{
				//F
				if(flag_piano_select==0){Temp1=four[Addr++];Temp2=four[Addr++];}
				if(flag_piano_select==1){Temp1=four_h[Addr++];Temp2=four_h[Addr++];}
				if(flag_piano_select==-1){Temp1=four_l[Addr++];Temp2=four_l[Addr++];}
				freq=25000/Temp1;	
				Buzzer_Freq_Set0( freq );
		    	Delay(12*Temp2);
			}
			
			else if(xdata>192 && xdata<240)
			{
				//G
				if(flag_piano_select==0){Temp1=five[Addr++];Temp2=five[Addr++];}
				if(flag_piano_select==1){Temp1=five_h[Addr++];Temp2=five_h[Addr++];}
				if(flag_piano_select==-1){Temp1=five_l[Addr++];Temp2=five_l[Addr++];}
				freq=25000/Temp1;	
				Buzzer_Freq_Set0( freq );
		    	Delay(12*Temp2);
			}
			
			else if(xdata>240 && xdata<288)
			{
				//A
				if(flag_piano_select==0){Temp1=six[Addr++];Temp2=six[Addr++];}
				if(flag_piano_select==1){Temp1=six_h[Addr++];Temp2=six_h[Addr++];}
				if(flag_piano_select==-1){Temp1=six_l[Addr++];Temp2=six_l[Addr++];}
				freq=25000/Temp1;	
				Buzzer_Freq_Set0( freq );
		    	Delay(12*Temp2);
			}
			
			else if(xdata>288 && xdata<336)
			{
				//B
				if(flag_piano_select==0){Temp1=seven[Addr++];Temp2=seven[Addr++];}
				if(flag_piano_select==1){Temp1=seven_h[Addr++];Temp2=seven_h[Addr++];}
				if(flag_piano_select==-1){Temp1=seven_l[Addr++];Temp2=seven_l[Addr++];}
				freq=25000/Temp1;	
				Buzzer_Freq_Set0( freq );
		    	Delay(12*Temp2);
			}
			
			else if(xdata>336 && xdata<384)
			{
				//Ch
				if(flag_piano_select==-1){Temp1=one[Addr++];Temp2=one[Addr++];}
				if(flag_piano_select==0){Temp1=one_h[Addr++];Temp2=one_h[Addr++];}
				if(flag_piano_select!=1){
				freq=25000/Temp1;	
				Buzzer_Freq_Set0( freq );
		    	Delay(12*Temp2);}
			}
			
			else if(xdata>384 && xdata<432)
			{
				//Dh
				if(flag_piano_select==-1){Temp1=two[Addr++];Temp2=two[Addr++];}
				if(flag_piano_select==0){Temp1=two_h[Addr++];Temp2=two_h[Addr++];}
				if(flag_piano_select!=1){
				freq=25000/Temp1;	
				Buzzer_Freq_Set0( freq );
		    	Delay(12*Temp2);}
			}
			
			else
			{
				//Eh
				if(flag_piano_select==-1){Temp1=three[Addr++];Temp2=three[Addr++];}
				if(flag_piano_select==0){Temp1=three_h[Addr++];Temp2=three_h[Addr++];}
				if(flag_piano_select!=1){
				freq=25000/Temp1;	
				Buzzer_Freq_Set0( freq );
		    	Delay(12*Temp2);}
			}
			
			
		}
		//if(xdata<430 && xdata>315 && ydata>0 && ydata<54) {Paint_Bmp(0, 0, 480, 272, keyboard);}
}


void Main(void)
{
	char *mode;
	int i;

	U8 key;
	U32 mpll_val = 0 ;
	U16 freq;// lci  1000
	//U32 divn_upll = 0 ;
//----add bgn------------
	U32 pix_x,pix_y;
//----add end------------	
	    
	#if ADS10   
//	__rt_lib_init(); //for ADS 1.0
	#endif

	Port_Init();

	Isr_Init();
	key = 14;
		mpll_val = (92<<12)|(1<<4)|(1);	//init FCLK=400M, so change MPLL first
	
	/*i = 2 ;	//don't use 100M!
	switch ( i ) {
	case 0:	//200
		key = 12;
		mpll_val = (92<<12)|(4<<4)|(1);
		break;
	case 1:	//300
		key = 13;
		mpll_val = (67<<12)|(1<<4)|(1);
		break;
	case 2:	//400
		key = 14;
		mpll_val = (92<<12)|(1<<4)|(1);
		break;
	case 3:	//440!!!
		key = 14;
		mpll_val = (102<<12)|(1<<4)|(1);
		break;
	default:
		key = 14;
		mpll_val = (92<<12)|(1<<4)|(1);
		break;
	}*/
	
	//init FCLK=400M, so change MPLL first
	ChangeMPllValue((mpll_val>>12)&0xff, (mpll_val>>4)&0x3f, mpll_val&3);
	ChangeClockDivider(key, 12);
	cal_cpu_bus_clk();
	
	consoleNum = 0;	// Uart 1 select for debug.
	Uart_Init( 0,115200 );
	Uart_Select( consoleNum );
	
	Beep(2000, 100);
	
	Uart_SendByte('\n');
	Uart_Printf("<***************************************>\n");
	Uart_Printf("               TQ2440 Test Program\n");
	Uart_Printf("                www.embedsky.net\n");
//	Uart_Printf("      Build time is: %s  %s\n", __DATE__ , __TIME__  );
	Uart_Printf("<***************************************>\n");

	rMISCCR=rMISCCR&~(1<<3); // USBD is selected instead of USBH1 
	rMISCCR=rMISCCR&~(1<<13); // USB port 1 is enabled.


	rDSC0 = 0x2aa;
	rDSC1 = 0x2aaaaaaa;
	//Enable NAND, USBD, PWM TImer, UART0,1 and GPIO clock,
	//the others must be enabled in OS!!!
	rCLKCON = 0xfffff0;

	MMU_Init();	//

	pISR_SWI=(_ISR_STARTADDRESS+0xf0);	//for pSOS

	Led_Display(0x66);

	mode="DMA";

	Clk0_Disable();
	Clk1_Disable();
	
	mpll_val = rMPLLCON;
	
	
#ifdef CSTM_LCD
	cstmLcd_init();

#else
	Lcd_TFT_Init() ;		// LCD initial

#endif
		
	download_run=1; //The default menu is the Download & Run mode.

//************************************************************************	
	rADCDLY=50000;                  //Normal conversion mode delay about (1/3.6864M)*50000=13.56ms
	rADCCON=(1<<14)+(ADCPRS<<6);   //ADCPRS En, ADCPRS Value

	Uart_Printf("\nTouch Screen test\n");

	rADCTSC=0xd3;  //Wfait,XP_PU,XP_Dis,XM_Dis,YP_Dis,YM_En

	pISR_ADC = (int)AdcTsAuto;
	rINTMSK=~BIT_ADC;       //ADC Touch Screen Mask bit clear
	rINTSUBMSK=~(BIT_SUB_TC);
	rGPBUP = rGPBUP & ~0x03f0|0x03f0;			//  LED [8:5] => PU En
	rGPBCON = rGPBCON & ~0x3d57fc|0x3d57fc;		//LED[8:5] => OUTPUT;
	rGPFCON = rGPFCON & (~((3<<4)|(3<<0)|(3<<8)|(3<<2))) | ((2<<4)|(2<<0)|(2<<8)|(2<<2)) ;		//GPF4,2,1,0 set EINT
	
	rEXTINT0 &= ~(7|(7<<4)|(7<<8)|(7<<16));	
	rEXTINT0 |= (0|(0<<4)|(0<<8)|(0<<16));		//set eint0,1,2,4 falling edge int


	rEINTPEND |= (1<<4);							//clear eint 4
	rEINTMASK &= ~(1<<4);						//enable eint 4

#ifdef CSTM_LCD

	g_type=get_pix(&pix_x,&pix_y);
	Lcd_ClearScr(0);
	PlayMusicTest();
	display_menu();
	KeyScan_Test();
	/*****************************while**********************************/
	/*****************************while**********************************/
	/*****************************while**********************************/
	/*****************************while**********************************/
	/*****************************while**********************************/
	/*****************************while**********************************/
	/*****************************while**********************************/
	/*****************************while**********************************/
	while(1)
	{
	/*ClearPending(BIT_EINT0|BIT_EINT1|BIT_EINT2|BIT_EINT4_7);
	pISR_EINT0 = pISR_EINT1 = pISR_EINT2 = pISR_EINT4_7 = (U32)Key_ISR;
	EnableIrq(BIT_EINT0|BIT_EINT1|BIT_EINT2|BIT_EINT4_7);*/
	if(flag_piano_select==-1){
	Glib_Rectangle(107,4,193,52,0xffff00);//把'低八度'用黄色框框住
	Glib_Rectangle(232,4,318,52,0x000000);
	}//'高八度'用黄色框框住
	
	if(flag_piano_select==0){
	Glib_Rectangle(107,4,193,52,0x000000);//把'低八度'用黄色框框住
	Glib_Rectangle(232,4,318,52,0x000000);
	}//'高八度'用黄色框框住
	
	if(flag_piano_select==1){
	Glib_Rectangle(107,4,193,52,0x000000);//把'低八度'用黄色框框住
	Glib_Rectangle(232,4,318,52,0xffff00);}
	
	//if(flag_jiaoxue!=1){Glib_Rectangle(358,4,444,52,0x000000);}
	//if(flag_jiaoxue==1){Glib_Rectangle(358,4,444,52,0xffff00);}
	
	//zkb=(Test_Adc())/1000000;
	//Uart_Printf( "AIN2: %04d\n", zkb);
	//Delay(1000);
	key2 = Key_Scan();
	       //Uart_Printf("key=%d,",key2);
	       if(key2 == 1){
	       Uart_Printf("key=%d,",key2);
	       if(flag_irq==1){
	       if(flag_jiaoxue!=0){
			flag_jiaoxue=0;
			Paint_Bmp(0, 0, 480, 272, keyboard_teach);
			Delay(50);
			Glib_Rectangle(358,4,444,52,0xffff00);//把'教学'用黄色框框住
			}
			else {
				flag_jiaoxue=1;
				Paint_Bmp(0, 0, 480, 272, keyboard);
				Delay(50);
				Glib_Rectangle(358,4,444,52,0x000000);//把'教学'用黄色框框住
			}
			}
	       }
	       
	       if(key2 == 2){
	       flag_piano_select=0;
	       }
           if(key2 == 3){
              if(flag_piano_select>-1){flag_piano_select--;}
           }
           if(key2 ==4){
           if(flag_piano_select<1){flag_piano_select++;}
           }
	
	}

#endif
}


//中断函数开始
void __irq AdcTsAuto(void)
{
	U32 saveAdcdly;
	U32 temp;

	xdata=0;
	ydata=0;
	if(rADCDAT0&0x8000)
	{
		//Uart_Printf("\nStylus Up!!\n");
		rADCTSC&=0xff;	// Set stylus down interrupt bit
	}
	//else 
		//Uart_Printf("\nStylus Down!!\n");

	rADCTSC=(1<<3)|(1<<2);         //Pull-up disable, Seq. X,Y postion measure.
	saveAdcdly=rADCDLY;
	rADCDLY=40000;                 //Normal conversion mode delay about (1/50M)*40000=0.8ms

	rADCCON|=0x1;                   //start ADC

	while(rADCCON & 0x1);		//check if Enable_start is low
	while(!(rADCCON & 0x8000));        //check if EC(End of Conversion) flag is high, This line is necessary~!!
		
	while(!(rSRCPND & (BIT_ADC)));  //check if ADC is finished with interrupt bit

	xdata=(rADCDAT0&0x3ff);
 	ydata=(rADCDAT1&0x3ff);

	//check Stylus Up Interrupt.
	rSUBSRCPND|=BIT_SUB_TC;
	ClearPending(BIT_ADC);
	rINTSUBMSK=~(BIT_SUB_TC);
	rINTMSK=~(BIT_ADC);
			 
	rADCTSC =0xd3;    //Waiting for interrupt
	rADCTSC=rADCTSC|(1<<8); // Detect stylus up interrupt signal.

	while(1)		//to check Pen-up state
	{
	xdata *= 0.272;
    ydata *= 0.480;
    ydata = 480-ydata;
    temp = ydata;
    ydata = xdata;
    xdata = temp;

    xdata = (xdata - 20.0303) / 0.8972;
    ydata = (ydata - 37.86667) / 0.7486;
	
	if (g_type == LCD_35)
	{
		xdata=480-xdata;
		xdata=(double)((double)320/480)*xdata;
		ydata=272-ydata;
		ydata=(double)((double)240/271)*ydata;
	}
	else if(g_type == LCD_70)
	{
		xdata=480-xdata;
		xdata=(double)((double)800/480)*xdata;
	//	ydata=272-ydata;
		ydata=ydata<0?0:ydata;
		ydata=(double)((double)480/272)*ydata;
	}
	if(flag_irq==1)play_the_piano();
	if(flag_irq==0)select_irq();
	if(flag_irq==3)	play_the_bass();
	if(flag_irq==2)	play_the_drum();

		if(rSUBSRCPND & (BIT_SUB_TC))	//check if ADC is finished with interrupt bit
		{
			//Uart_Printf("Stylus Up Interrupt~!\n");
			Addr=0;	
		    Buzzer_Stop();
			break;	//if Stylus is up(1) state
		}
	}	

//-----add bgn---------------------------------------

	Delay(20);
//-----add end---------------------------------------------
    Uart_Printf("count=%03d  XP=%04d, YP=%04d\n", count++, xdata, ydata);
 
	rADCDLY=saveAdcdly; 
	rADCTSC=rADCTSC&~(1<<8); // Detect stylus Down interrupt signal.
	rSUBSRCPND|=BIT_SUB_TC;
	rINTSUBMSK=~(BIT_SUB_TC);	// Unmask sub interrupt (TC)     
	ClearPending(BIT_ADC);
}
//中断函数结束

void Isr_Init(void)
{
	pISR_UNDEF=(unsigned)HaltUndef;
	pISR_SWI  =(unsigned)HaltSwi;
	pISR_PABORT=(unsigned)HaltPabort;
	pISR_DABORT=(unsigned)HaltDabort;
	rINTMOD=0x0;	  // All=IRQ mode
	rINTMSK=BIT_ALLMSK;	  // All interrupt is masked.
}


void HaltUndef(void)
{
	Uart_Printf("Undefined instruction exception!!!\n");
	while(1);
}

void HaltSwi(void)
{
	Uart_Printf("SWI exception!!!\n");
	while(1);
}

void HaltPabort(void)
{
	Uart_Printf("Pabort exception!!!\n");
	while(1);

}

void HaltDabort(void)
{
	Uart_Printf("Dabort exception!!!\n");
	while(1);
}


void ClearMemory(void)
{
	int memError=0;
	U32 *pt;
	
	Uart_Printf("Clear Memory (%xh-%xh):WR",_RAM_STARTADDRESS,HEAPEND);

	pt=(U32 *)_RAM_STARTADDRESS;
	while((U32)pt < HEAPEND)
	{
		*pt=(U32)0x0;
		pt++;
	}
	
	if(memError==0)Uart_Printf("\b\bO.K.\n");
}

void Clk0_Enable(int clock_sel)	
{	// 0:MPLLin, 1:UPLL, 2:FCLK, 3:HCLK, 4:PCLK, 5:DCLK0
	rMISCCR = rMISCCR&~(7<<4) | (clock_sel<<4);
	rGPHCON = rGPHCON&~(3<<18) | (2<<18);
}
void Clk1_Enable(int clock_sel)
{	// 0:MPLLout, 1:UPLL, 2:RTC, 3:HCLK, 4:PCLK, 5:DCLK1	
	rMISCCR = rMISCCR&~(7<<8) | (clock_sel<<8);
	rGPHCON = rGPHCON&~(3<<20) | (2<<20);
}
void Clk0_Disable(void)
{
	rGPHCON = rGPHCON&~(3<<18);	// GPH9 Input
}
void Clk1_Disable(void)
{
	rGPHCON = rGPHCON&~(3<<20);	// GPH10 Input
}

