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
#include "LCD_TFT.h"

extern char Image$$RO$$Limit[];
extern char Image$$RO$$Base[];
extern char Image$$RW$$Limit[];
extern char Image$$RW$$Base[];
extern char Image$$ZI$$Limit[];
extern char Image$$ZI$$Base[];

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
void Buzzer_Freq_Set0(U32 freq );//wang++
void Buzzer_Freq_Set1(U32 freq );

extern void Lcd_TFT_Init(void);
extern void Lcd_TFT_Test( void ) ;
//extern void Test_Touchpanel(void) ;
//extern void Test_Adc(void) ;
//extern void KeyScan_Test(void) ;
//extern void RTC_Display(void) ;
//extern void Test_IrDA_Tx(void) ;
//extern void PlayMusicTest(void) ;
//extern void RecordTest( void ) ;
//extern void Test_Iic(void) ;
//extern void Test_SDI(void) ;
//extern void Camera_Test( void ) ;

volatile U32 downloadAddress;

void (*restart)(void)=(void (*)(void))0x0;

volatile unsigned char *downPt;
volatile U32 downloadFileSize;
volatile U16 checkSum;
volatile unsigned int err=0;
volatile U32 totalDmaCount;

volatile int isUsbdSetConfiguration;

unsigned char SONG[] ={      //祝你平安
0x26,0x20,0x20,0x20,0x20,0x20,0x26,0x10,0x20,0x10,0x20,0x80,0x26,0x20,0x30,0x20,
0x30,0x20,0x39,0x10,0x30,0x10,0x30,0x80,0x26,0x20,0x20,0x20,0x20,0x20,0x1c,0x20,
0x20,0x80,0x2b,0x20,0x26,0x20,0x20,0x20,0x2b,0x10,0x26,0x10,0x2b,0x80,0x26,0x20,
0x30,0x20,0x30,0x20,0x39,0x10,0x26,0x10,0x26,0x60,0x40,0x10,0x39,0x10,0x26,0x20,
0x30,0x20,0x30,0x20,0x39,0x10,0x26,0x10,0x26,0x80,0x26,0x20,0x2b,0x10,0x2b,0x10,
0x2b,0x20,0x30,0x10,0x39,0x10,0x26,0x10,0x2b,0x10,0x2b,0x20,0x2b,0x40,0x40,0x20,
0x20,0x10,0x20,0x10,0x2b,0x10,0x26,0x30,0x30,0x80,0x18,0x20,0x18,0x20,0x26,0x20,
0x20,0x20,0x20,0x40,0x26,0x20,0x2b,0x20,0x30,0x20,0x30,0x20,0x1c,0x20,0x20,0x20,
0x20,0x80,0x1c,0x20,0x1c,0x20,0x1c,0x20,0x30,0x20,0x30,0x60,0x39,0x10,0x30,0x10,
0x20,0x20,0x2b,0x10,0x26,0x10,0x2b,0x10,0x26,0x10,0x26,0x10,0x2b,0x10,0x2b,0x80,
0x18,0x20,0x18,0x20,0x26,0x20,0x20,0x20,0x20,0x60,0x26,0x10,0x2b,0x20,0x30,0x20,
0x30,0x20,0x1c,0x20,0x20,0x20,0x20,0x80,0x26,0x20,0x30,0x10,0x30,0x10,0x30,0x20,
0x39,0x20,0x26,0x10,0x2b,0x10,0x2b,0x20,0x2b,0x40,0x40,0x10,0x40,0x10,0x20,0x10,
0x20,0x10,0x2b,0x10,0x26,0x30,0x30,0x80,
};


unsigned char SONG_qcc[] ={      //穷哈哈
0x39,0x10,0x39,0x18,0x30,0x10,0x2b,0x10,0x2b,0x10,0x26,0x10,0x20,0x10,0x26,0x10,
0x26,0x18,0x20,0x10,0x1c,0x10,0x18,0x10,0x15,0x10,0x13,0x15,0x18,0x10,0x18,0x10,
0x18,0x10,0x18,0x10,0x2b,0x10,0x26,0x10,0x20,0x10,0x2b,0x10,0x26,0x18,0x20,0x10,
0x26,0x10,0x20,0x10,0x26,0x10,0x26,0x10,
0x20,0x10,0x1c,0x10,0x30,0x10,0x2b,0x10,0x30,0x10,0x30,0x10,0x2b,0x10,0x26,0x10,
0x20,0x10,0x20,0x10,0x26,0x10,0x1c,0x10,0x26,0x10,0x2b,0x10,0x30,0x20,0x30,0x10,
0x33,0x10,0x39,0x10,0x40,0x10,0x39,0x10,
};

int download_run=0;
U32 tempDownloadAddress;
int menuUsed=0;

extern char Image$$RW$$Limit[];
U32 *pMagicNum=(U32 *)Image$$RW$$Limit;
int consoleNum;
int zkb=5;
U16 freq =800;// lci  1000 ;
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

struct {
	void (*fun)(void);
	char *tip;
}CmdTip[] = {
				{ Temp_function, "Please input 1-11 to select test" } ,
				//{ BUZZER_PWM_Test, "Test PWM" } ,
				//{ RTC_Display, "RTC time display" } ,
				//{ Test_Adc, "Test ADC" } ,
				//{ KeyScan_Test, "Test interrupt and key scan" } ,
				//{ Test_Touchpanel, "Test Touchpanel" } ,
				//{ Lcd_TFT_Test, "Test TFT LCD" } ,
				//{ Test_Iic, "Test IIC EEPROM" } ,
				//{ PlayMusicTest, "UDA1341 play music" } ,
				//{ RecordTest, "UDA1341 record voice" } ,
				//{ Test_SDI, "Test SD Card" } ,
				//{ Camera_Test, "Test CMOS Camera"},
				{ 0, 0}						
			};


void Main(void){
	char *mode;
	unsigned char Temp1,Temp2;
	unsigned int Addr=0;
	U8 key;
	U32 mpll_val = 0 ;	
	U16 freq;// lci  1000  
	Port_Init();	
	Isr_Init();	
		key = 14;
		mpll_val = (92<<12)|(1<<4)|(1);	//init FCLK=400M, so change MPLL first
	ChangeMPllValue((mpll_val>>12)&0xff, (mpll_val>>4)&0x3f, mpll_val&3);
	ChangeClockDivider(key, 12);
	cal_cpu_bus_clk();	
	consoleNum = 0;	// Uart 1 select for debug.
	Uart_Init( 0,115200 );
	rMISCCR=rMISCCR&~(1<<3); // USBD is selected instead of USBH1 
	rMISCCR=rMISCCR&~(1<<13); // USB port 1 is enabled.
	rDSC0 = 0x2aa;
	rDSC1 = 0x2aaaaaaa;
	rCLKCON = 0xfffff0;
	MMU_Init();	//
	pISR_SWI=(_ISR_STARTADDRESS+0xf0);	//for pSOS
	Led_Display(0x66);
	mode="DMA";
	Clk0_Disable();
	Clk1_Disable();	
	mpll_val = rMPLLCON;
	Lcd_TFT_Init() ;		// LCD initial	
	download_run=1; //The default menu is the Download & Run mode.
	Lcd_ClearScr( (0x00<<11) | (0x00<<5) | (0x1f)  );			 
	 while(1){	
		    Temp1=SONG_qcc[Addr++];	    
		    Temp2=SONG_qcc[Addr++];    	    
		    freq=25000/Temp1;	
			Buzzer_Freq_Set0( freq );
		    Delay(12*Temp2);		    
		    Uart_Printf("freq=%d,",freq);
		 if(Addr>215){
		    Addr=0;
		 }
     }  	
}


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

//这个函数中rTCMPB0 = rTCNTB0*freqk;有可能会溢出，使用时要小心
void Buzzer_Freq_Set1(U32 freqk ){    
	rGPBCON &= ~3;			//set GPB0 as tout0, pwm output
	rGPBCON |= 2;
		
	rTCFG0 &= ~0xff;
	rTCFG0 |= 15;			//prescaler = 15+1
	rTCFG1 &= ~0xf;
	rTCFG1 |= 2;			//mux = 1/8
	rTCNTB0 = (PCLK>>7)/800;
	rTCMPB0 = rTCNTB0*freqk;	// 50%
	rTCON &= ~0x1f;
	rTCON |= 0xb;			//disable deadzone, auto-reload, inv-off, update TCNTB0&TCMPB0, start timer 0
	rTCON &= ~2;			//clear manual update bit
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

