/*************************************
*
* 文件名： cstm_Lcd.h
* 版权：广州天嵌计算机科技有限公司
* 作者： tq-zql
* 功能： 为在串口中输入屏幕相关参数提供相关支持。cstmlcd.c的头文件

* 修改历史：
* 时间： 2011-11-5 ，作者： tq-zql
* 原因： 创建
*
*************************************/

#ifndef _CSTM_LCD_
#define _CSTM_LCD_

#define LCD_C		0
#define LCD_35		1
#define LCD_43		2
#define LCD_70		3



struct lcd_init_info_t
{
	U8 Mval;
	U8 Mval_Used;
	U8 Invvden;
	U8 Bswp;
	U8 HWswp;
	U8 PNRmode; 
	U8 BPPmode;
	
	U32 Phy_xsize;
	U32 Phy_ysize;
	U32 Scr_xsize;
	U32 Scr_ysize;

	U8 vbpd;
	U8 vfpd;
	U8 vspw;
	U8 hbpd;
	U8 hfpd;
	U8 hspw;
	
	U8 clk_tft;
	U32 hozval_tft;
	U32 Lineval_tft;
};

#if 0
struct lcd_init_info_t lcd_set[]=
{
//LCD_W35
	{
		.Mval		=	13,
		.Mval_Used	=	0,
		.Invvden	=	1,
		.Bswp		=	0,
		.HWswp		=	1,
		.PNRmode	=	3; 
		.BPPmode	=	12;
		
		.Phy_xsize	=	320;
		.Phy_ysize	=	240;
		.Scr_xsize	=	320;
		.Scr_ysize	=	240;
		
		.vbpd		=	12;
		.vfpd		=	4;
		.vspw		=	5;
		
		.hbpd		=	22;
		.hfpd		=	33;
		.hspw		=	44;
		.clk_tft	=	6;
		.hozval_tft	=	319;
		.Lineval_tft=	239;
	},
//LCD_S35	
	{
		.Mval		=	13;
		.Mval_Used	=	0;
		.Invvden	=	1;
		.Bswp		=	0;
		.HWswp		=	1;
		.PNRmode	=	3; 
		.BPPmode	=	12;
		
		.Phy_xsize	=	320;
		.Phy_ysize	=	240;
		.Scr_xsize	=	320;
		.Scr_ysize	=	240;
		
		.vbpd		=	12;
		.vfpd		=	4;
		.vspw		=	5;
		
		.hbpd		=	8;
		.hfpd		=	26;
		.hspw		=	4;
		.clk_tft	=	6;
		.hozval_tft	=	319;
		.Lineval_tft=	239;
	},
//LCD_T35		
	{
		.Mval		=	13;
		.Mval_Used	=	0;
		.Invvden	=	1;
		.Bswp		=	0;
		.HWswp		=	1;
		.PNRmode	=	3; 
		.BPPmode	=	12;
		
		.Phy_xsize	=	320;
		.Phy_ysize	=	240;
		.Scr_xsize	=	320;
		.Scr_ysize	=	240;
		
		.vbpd		=	1;
		.vfpd		=	2;
		.vspw		=	6;
		
		.hbpd		=	5;
		.hfpd		=	10;
		.hspw		=	15;
		.clk_tft	=	6;
		.hozval_tft	=	319;
		.Lineval_tft=	239;
	},
//LCD_W43
	{
		.Mval		=	13;
		.Mval_Used	=	0;
		.Invvden	=	1;
		.Bswp		=	0;
		.HWswp		=	1;
		.PNRmode	=	3; 
		.BPPmode	=	12;
		
		.Phy_xsize	=	480;
		.Phy_ysize	=	272;
		.Scr_xsize	=	480;
		.Scr_ysize	=	272;
		
		.vbpd		=	2;
		.vfpd		=	4;
		.vspw		=	8;		
		.hbpd		=	10;
		.hfpd		=	19;
		.hspw		=	30;
		
		.clk_tft	=	4;
		
		.hozval_tft	=	479;
		.Lineval_tft=	271;
	},
//LCD_57	
	{
		.Mval		=	13;
		.Mval_Used	=	0;
		.Invvden	=	1;
		.Bswp		=	0;
		.HWswp		=	1;
		.PNRmode	=	3; 
		.BPPmode	=	12;
		
		.Phy_xsize	=	320;
		.Phy_ysize	=	240;
		.Scr_xsize	=	320;
		.Scr_ysize	=	240;
		
		.vbpd		=	3;
		.vfpd		=	5;
		.vspw		=	15;
		.hbpd		=	5;
		.hfpd		=	15;
		.hspw		=	8;
		
		.clk_tft	=	7;
		.hozval_tft	=	319;
		.Lineval_tft=	239;
	},
//VGA

	{
		.Mval		=	13;
		.Mval_Used	=	0;
		.Invvden	=	1;
		.Bswp		=	0;
		.HWswp		=	1;
		.PNRmode	=	3; 
		.BPPmode	=	12;
		
		.Phy_xsize	=	640;
		.Phy_ysize	=	480;
		.Scr_xsize	=	640;
		.Scr_ysize	=	480;
		
		.vbpd		=	29;
		.vfpd		=	5;
		.vspw		=	4;
		
		.hbpd		=	71;
		.hfpd		=	40;
		.hspw		=	31;
		.clk_tft	=	1;
		.hozval_tft	=	639;
		.Lineval_tft=	479;
	},
//LCD_A70
	{
		.Mval		=	13;
		.Mval_Used	=	0;
		.Invvden	=	1;
		.Bswp		=	0;
		.HWswp		=	1;
		.PNRmode	=	3; 
		.BPPmode	=	12;
		
		.Phy_xsize	=	800;
		.Phy_ysize	=	480;
		.Scr_xsize	=	800;
		.Scr_ysize	=	480;
		
		.vbpd		=	3;
		.vfpd		=	5;
		.vspw		=	15;
		
		.hbpd		=	5;
		.hfpd		=	15;
		.hspw		=	8;
		.clk_tft	=	7;
		.hozval_tft	=	799;
		.Lineval_tft=	479;
	},
	{
		.Mval		=	13;
		.Mval_Used	=	0;
		.Invvden	=	1;
		.Bswp		=	0;
		.HWswp		=	1;
		.PNRmode	=	3; 
		.BPPmode	=	12;
		
		.Phy_xsize	=	800;
		.Phy_ysize	=	600;
		.Scr_xsize	=	800;
		.Scr_ysize	=	600;
		
		.vbpd		=	5;
		.vfpd		=	6;
		.vspw		=	1;
		.hbpd		=	2;
		.hfpd		=	14;
		.hspw		=	180;

		.clk_tft	=	3;
		.hozval_tft =	799;
		.Lineval_tft=	479;
	},
}

#endif



U8 get_pix(U32 *Pix_x,U32 *Pix_y);
void cstmLcd_init(void);
void tst_lcd(void);
void Lcd_ClearScr1(int x0,int y0,int h,int l,U32 c);

#endif
