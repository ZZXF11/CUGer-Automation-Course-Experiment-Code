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

//----add bgn-----------------
#include "lcd_tft.h"
#ifdef CSTM_LCD
#include "cstm_lcd.h"

#endif
//----add end-----------------

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


#include "config.h"      //Ϊ�ֿ���ӵ�������"config.h" ��ucosii���ң������"config.h" ������ɾ��������Ҫʹ�õ�include��������еı������
#include  "stdarg.h"    //Ϊ�ֿ���ӵ�������"stdarg.h" ��ADS1.2��װ�ļ�������ȥ�ң����Lcd_printf�����е�һЩ�������

extern unsigned char __VGA[];//Ϊ�ֿ���ӵ�������Ӣ��ASCII����
extern unsigned char __CHS[];//Ϊ�ֿ���ӵ������������ֿ�����

void Lcd_PutHZ(unsigned int x,unsigned int y,unsigned short int QW,unsigned int c,unsigned int bk_c,unsigned int st);//Ϊ�ֿ���ӵ�����
void Lcd_PutASCII(unsigned int x,unsigned int y,unsigned char ch,unsigned int c,unsigned int bk_c,unsigned int st);//Ϊ�ֿ���ӵ�����
void Lcd_printf(unsigned int x,unsigned int y,unsigned int c,unsigned int bk_c,unsigned int st,char *fmt,...);//Ϊ�ֿ���ӵ�����

extern void Lcd_TFT_Init(void);

volatile U32 downloadAddress;

void (*restart)(void)=(void (*)(void))0x0;

volatile unsigned char *downPt;
volatile U32 downloadFileSize;
volatile U16 checkSum;
volatile unsigned int err=0;
volatile U32 totalDmaCount;

volatile int isUsbdSetConfiguration;
int ii_x,ii_y;
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

	//(m+8)*FIN*2 ��Ҫ����32λ��!
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



void Main(void)
{
	char *mode;
	int i;	
	U8 key;
	U32 mpll_val = 0 ;	
//-----add bgn----------------
	U32 pix_x,pix_y;
//-----add end----------------
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
#ifdef CSTM_LCD
	cstmLcd_init();
#else
	Lcd_TFT_Init() ;		// LCD initial
#endif
	download_run=1; //The default menu is the Download & Run mode.
	Lcd_ClearScr((0x3f<<5) | (0x1f)	);//ˢ��ˢΪ��ɫ
//--------add bgn-------�����ߵ�ֱ�ӷŵ�while�з������Ĳ���---------
#ifdef CSTM_LCD

	get_pix(&pix_x,&pix_y);
	
	for(i=1;(i*50)<pix_x||(i*50)<pix_y;i++)
	{//������Ϊ50Ϊһ��ĸ��ӣ�����鿴�ֵ�λ��
		Glib_Line(0,50*i,pix_x,50*i,0x0000);
		Glib_Line(50*i,0,50*i,pix_y,0x0000);    
	}
	
#else
//--------add end-----------------
	for(i=1;i<10;i++){//������Ϊ50Ϊһ��ĸ��ӣ�����鿴�ֵ�λ��
		Glib_Line(0,50*i,320,50*i,0x0000);
		Glib_Line(50*i,0,50*i,240,0x0000);    
	}
#endif
 

	while(1)
	{	
	
	
	for(ii_x=100;ii_x<200;ii_x++){
		for(ii_y=80;ii_y<230;ii_y++){
		ii_y=2*ii_x-150;
		Lcd_printf(ii_x,ii_y, 0x0000,(0x1f<<11) | (0x3f<<5) | (0),1,"�¸�ţţ���������ѣ�");
		Lcd_printf(ii_x,ii_y+18, 0x0000,(0x1f<<11) | (0x3f<<5) | (0),1,"Brave cow! Not afraid of difficulties!");
		Delay(100);
		Lcd_ClearScr((0x00<<5) | (0x1f)	);
		if(ii_y==240) {
			ii_x=100;
			ii_y=2*ii_x-150;
		}
//ǰ��ɫΪ��ɫ	0x0000������ɫΪ��ɫ
//rgb��ɫԭ��(0x1f<<11) | (0x3f<<5) | (0)
//Red�� (0x1f<<11) | (0x00<<5) | (0x00)��ʵ���Ƕ���������11111 000000 00000
//Green��(0x00<<11) | (0x3f<<5) | (0x00)��ʵ���Ƕ���������00000 111111 00000
//Bule��(0x00<<11) | (0x00<<5) | (0x1f) ��ʵ���Ƕ���������00000 000000 11111
//White��(0x1f<<11) | (0x3f<<5) | (0x1f)��ʵ���Ƕ���������11111 111111 11111
//Black��(0x00<<11) | (0x00<<5) | (0x00) ��ʵ���Ƕ���������00000 000000 00000
}
	}
	}	  	

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

