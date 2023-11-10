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

#include "lcd_tft.h"
#ifdef CSTM_LCD
#include "cstm_lcd.h"
#endif
extern char Image$$RO$$Limit[];
extern char Image$$RO$$Base[];
extern char Image$$RW$$Limit[];
extern char Image$$RW$$Base[];
extern char Image$$ZI$$Limit[];
extern char Image$$ZI$$Base[];

	extern unsigned char kobeshot_320240[];
	extern unsigned char ball_014014[];


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
int menuUsed=0;

extern char Image$$RW$$Limit[];
U32 *pMagicNum=(U32 *)Image$$RW$$Limit;
int consoleNum;

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

//-----add bgn---------------
#ifdef CSTM_LCD
extern void Glib_FilledRectangle(int x1,int y1,int x2,int y2,int color);
#endif
//------add end--------------
void Main(void)
{
	char *mode;
	int i,ii,iii;
	U8 key;
	U32 mpll_val = 0 ;
	//U32 divn_upll = 0 ;
//-----add bgn------------------------------
#ifdef CSTM_LCD
	U32 pix_x,pix_y;
	U32 offset_x,offset_y;		//对不同的屏，x与y的补偿值

#endif
//-----add end------------------------------	 
	#if ADS10   
//	__rt_lib_init(); //for ADS 1.0
	#endif

	Port_Init();
	
	Isr_Init();
	
	i = 2 ;	//don't use 100M!
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
	}
	
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
//-----add bgn-------------------
#ifdef CSTM_LCD
	while(1)
	{
		get_pix(&pix_x,&pix_y);
		offset_x=(pix_x-320)/2;
		offset_y=(pix_y-240)/2;
		
		Lcd_ClearScr( (0x00<<11) | (0x00<<5) | (0x00) );  
		
		Paint_Bmp(0,0, 480, 272, fb1);
		Paint_Bmp(240,40, 35, 35, fball);
		Delay(100);			
		
		Paint_Bmp(0,0, 480, 272, fb2);
		Paint_Bmp(280,40, 35, 35, fball);
		Delay(100);			
		
		Paint_Bmp(0,0, 480, 272, fb3);
		Paint_Bmp(320,40, 35, 35, fball);
		Delay(100);			
		
		Paint_Bmp(0,0, 480, 272, fb4);
		Paint_Bmp(360,40, 35, 35, fball);
		Delay(100);			
		
		Paint_Bmp(0,0, 480, 272, fb5);
		Paint_Bmp(400,40, 35, 35, fball);
		Delay(100);			
		
		Paint_Bmp(0,0, 480, 272, fb6);
		Paint_Bmp(440,40, 35, 35, fball);
		Delay(100);			
		
		
		/*for(ii=0;ii<16;ii++)
		{
			if(ii<8) 
				iii=60-8*ii;
			else 
				iii=(ii-7)*10;	
			Paint_Bmp(0+offset_x, 0+offset_y, 320, 240, kobeshot_320240);
			Glib_FilledRectangle(200+offset_x,40+offset_y,240+offset_x,80+offset_y,0x0000);
			Paint_Bmp(205-10*ii+offset_x,iii+offset_y, 14, 14, ball_014014);
			Delay(500);			
		}*/
		

	}
//-----add end--------------------
#else
	while(1)
	{		
		for(ii=0;ii<16;ii++)
		{
			if(ii<8) 
				iii=60-8*ii;
			else 
				iii=(ii-7)*10;	
			Paint_Bmp(0, 0, 320, 240, kobeshot_320240);
			Glib_FilledRectangle(200,40,240,80,0x0000);
			Paint_Bmp(205-10*ii,iii, 14, 14, ball_014014);
			Delay(500);			
		}
	}	  	
#endif
}

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

