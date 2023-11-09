/*************************************
*
* 文件名： cstmLcd.c
* 版权：广州天嵌计算机科技有限公司
* 作者： tq-zql
* 功能： 为在串口中输入屏幕相关参数提供相关支持。

* 修改历史：
* 时间： 2011-11-05 ，作者： tq-zql		版本：v0.1
* 原因： 创建
* 时间： 2011-11-10 ，作者： tq-zql		版本：v0.2
* 原因： 添加对不同屏初始化，与相关操作函数的操作
*
*************************************/
#include <stdlib.h>
#include <string.h>

#include "def.h"
#include "2440addr.h"
#include "2440lib.h"
#include "2440slib.h"
#include "LCD_TFT.h"

#include "cstm_lcd.h"





#define BUF(x,y) *(LCD_BUFFER+gp_lcd->Scr_xsize*(x)+(y))		//使它看下来像buf[][]


#ifdef CSTM_LCD
volatile unsigned short *LCD_BUFFER;
#else
extern volatile unsigned short LCD_BUFFER[SCR_YSIZE_TFT][SCR_XSIZE_TFT];
#endif

struct lcd_init_info_t *gp_lcd;

extern void Glib_FilledRectangle(int x1,int y1,int x2,int y2,int color);
extern void Glib_Line(int x1,int y1,int x2,int y2,int color);

//ads1.2 好像不支持c99，所以不可以用乱序赋值。只能这样赋值
struct lcd_init_info_t lcd_set[]=
{
//LCD_W35
	{
		13,
		0,
		1,
		0,
		1,
		3, 
		12,
		
		320,
		240,
		320,
		240,
		
		12,
		4,
		5,
		
		22,
		33,
		44,
		6,
		319,
		239,
	},
//LCD_S35	
	{
		13,
		0,
		1,
		0,
		1,
		3, 
		12,
		
		320,
		240,
		320,
		240,
		
		12,
		4,
		5,
		
		8,
		26,
		4,
		6,
		319,
		239,
	},
//LCD_T35		
	{
		13,
		0,
		1,
		0,
		1,
		3, 
		12,
		
		320,
		240,
		320,
		240,
		
		1,
		6,
		2,
		5,
		10,
		15,

		6,

		319,
		239,
	},
//LCD_W43
	{
		13,
		0,
		1,
		0,
		1,
		3, 
		12,
		
		480,
		272,
		480,
		272,

		2,
		4,
		8,
		10,
		19,
		30,

		4,

		479,
		271,
	},
//LCD_57	
	{
		13,
		0,
		1,
		0,
		1,
		3, 
		12,
		
		320,
		240,
		320,
		240,
		
		3,
		5,
		15,
		5,
		15,
		8,

		7,

		319,
		239,
	},
//VGA

	{
		13,
		0,
		1,
		0,
		1,
		3, 
		12,
		
		640,
		480,
		640,
		480,
		
		29,
		5,
		4,
		71,
		40,
		31,

		1,

		639,
		479,
	},
//LCD_A70
	{
		13,
		0,
		1,
		0,
		1,
		3, 
		12,
		
		800,
		480,
		800,
		480,
		
		3,
		5,
		15,
		5,
		15,
		8,

		7,

		799,
		479,
	},
//LCD_A104	
	{
		13,
		0,
		1,
		0,
		1,
		3, 
		12,
		
		800,
		600,
		800,
		600,
		
		5,
		6,
		1,
		28,
		14,
		180,

		3,

		799,
		599,
	},
};


/*
函数名	：get_pix
功能	：从串口中取得屏的像素值
参数	：pix_x:返回的x轴像素
		  pix_y:返回的y轴像素
返回	：type:屏的类型，0表自定义,1表3.5',2表4.3',3表7'
备注	：
*/
U8 get_pix(U32 *Pix_x,U32 *Pix_y)
{
	U32 pix_x,pix_y;
	U8 type;
	
//	Uart_Printf("\nPlease input the Pix-x(0 : using the default setting) : \n");	
//	pix_x = Uart_GetIntNum_GJ();
	pix_x=0;
	if(pix_x==0)
	{
		pix_x=gp_lcd->Phy_xsize;
		pix_y=gp_lcd->Phy_ysize;
	}
	else
	{
		Uart_Printf("\nPlease input the Pix-y : \n");	
		pix_y = Uart_GetIntNum_GJ();
	}
	if((pix_x==320)&&(pix_y==240))
		type = LCD_35;
	else if((pix_x==480)&&(pix_y==272))
		type = LCD_43;
	else if((pix_x==800)&&(pix_y==480))
		type = LCD_70;
	else 
		type = LCD_C;
	Uart_Printf("\nPix-x=%d Pix-y=%d: \n",pix_x,pix_y);	
	*Pix_x=pix_x;
	*Pix_y=pix_y;
	return type;
}
#ifdef CSTM_LCD
/*
函数名	：Lcd_MoveViewPort
功能	：屏幕内容的整体移动
参数	：vx:移动的x轴像素
		  vy:移植的y轴像素
返回	：
备注	：
*/
void Lcd_MoveViewPort(int vx,int vy)
{
	U32 addr;

	SET_IF(); 
	if(gp_lcd->Phy_xsize<32)
		while((rLCDCON1>>18)<=1); // if x<32
	else		
		while((rLCDCON1>>18)==0); // if x>32
	addr=(U32)LCD_BUFFER+(vx*2)+vy*(gp_lcd->Scr_xsize*2);
	rLCDSADDR1= ( (addr>>22)<<21 ) | M5D(addr>>1);
	rLCDSADDR2= M5D(((addr+(gp_lcd->Scr_xsize*gp_lcd->Phy_ysize*2))>>1));
    
	CLR_IF();
}    

/*
函数名	：MoveViewPort
功能	：屏幕移动的测试函数
参数	：
返回	：
备注	：
*/
void MoveViewPort(void)
{
    int vx=20,vy=20,vd=1;

    Uart_Printf("\n*Move the LCD view windos:\n");
    Uart_Printf(" press 8 is up\n");
    Uart_Printf(" press 2 is down\n");
    Uart_Printf(" press 4 is left\n");
    Uart_Printf(" press 6 is right\n");
    Uart_Printf(" press Enter to exit!\n");

    while(1)
    {
    	while(Uart_Getch()==0x00);
    	switch( Uart_Getch() )
    	{
    	case '8':
		    if(vy>=vd)vy-=vd; 
		    Uart_Printf("8\n");
        break;

    	case '4':
    	    if(vx>=vd)vx-=vd;
			Uart_Printf("4\n");
    	break;

    	case '6':
			if(vx<=(gp_lcd->Scr_xsize-gp_lcd->Phy_xsize-vd))vx+=vd;   	    
			Uart_Printf("6\n");
   	    break;

    	case '2':
			if(vy<=(gp_lcd->Scr_ysize-gp_lcd->Phy_ysize-vd))vy+=vd;   	    
			Uart_Printf("2\n");
   	    break;

    	case '\r':
   	    return;

    	default:
	    break;
		}
 		Uart_Printf("vx=%3d,vy=%3d\n",vx,vy);
		Lcd_MoveViewPort(vx,vy);
    }
}

/*
函数名	：PutPixel
功能	：屏幕移动的测试函数
参数	：x:x轴坐标，
		  y:y轴坐标
		  c:指定的颜色
返回	：
备注	：
*/
void PutPixel(U32 x,U32 y, U32 c )
{
	if ( (x < gp_lcd->Scr_xsize) && (y < gp_lcd->Scr_ysize) )
		BUF(y,x)=c;
}

/*
函数名	：Lcd_ClearScr
功能	：屏幕整个变成指定的颜色
参数  	:c:指定的颜色
返回	：
备注	：
*/
void Lcd_ClearScr( U32 c)
{
	unsigned int x,y ;
		
    for( y = 0 ; y < gp_lcd->Scr_ysize; y++ )
    {
    	for( x = 0 ; x < gp_lcd->Scr_xsize; x++ )
    	{
			BUF(y,x)=c;
    	}
    }
}
/*
函数名	：Lcd_ClearScr
功能	：屏幕整个变成指定的颜色
参数  	:c:指定区域的颜色
     	:x0:指定位置的x坐标
		 y0:指定位置的y轴坐标
		 h:区域的高(对应x)
		 l:区域的宽(对应y)
返回	：
备注	：
*/
void Lcd_ClearScr1(int x0,int y0,int h,int l,U32 c)
{
	unsigned int x,y;
		
    for( y = y0 ; y <y0+l; y++ )
    {
    	for( x = x0 ; x <x0+h ; x++ )
    	{
			BUF(y,x) = c ;
    	}
    }
}
/*
函数名	：Paint_Bmp
功能	：屏幕指定的位置显示图片
参数  	:x0:指定位置的x坐标
		 y0:指定位置的y轴坐标
		 h:图片的高(对应x)
		 l:图片的宽(对应y)
		 bmp:图片
		 
返回	：
备注	：
*/
void Paint_Bmp(int x0,int y0,int h,int l,unsigned char bmp[])
{
	int x,y;
	U32 c;
	int p = 0;
	
    for( y = 0 ; y < l ; y++ )
    {
    	for( x = 0 ; x < h ; x++ )
    	{
    		c = bmp[p+1] | (bmp[p]<<8) ;
			if ( ( (x0+x) < gp_lcd->Scr_xsize) && ( (y0+y) < gp_lcd->Scr_ysize) )
				BUF(y+y0,x+x0)=c;
			
    		p = p + 2 ;
    	}
    }
}
#endif


/*
函数名	：tst_lcd
功能	：lcd的测试程序
参数  	:
返回	：
备注	：
*/
void tst_lcd(void)
{
	Lcd_ClearScr( (0x00<<11) | (0x00<<5) | (0x00) );  
   	Uart_Printf("\nTest TFT LCD!\n");

	Lcd_ClearScr( (0x00<<11) | (0x00<<5) | (0x00)  )  ;		//clear screen
	Uart_Printf( "\nDisplay Black! Press any key to continue!\n" );
	Uart_Getch() ;		//wait uart input

	Lcd_ClearScr( (0x1f<<11) | (0x3f<<5) | (0x1f)  )  ;		//clear screen
	Uart_Printf( "Display White! Press any key to continue!\n" );
	Uart_Getch() ;		//wait uart input

	Lcd_ClearScr( (0x00<<11) | (0x00<<5) | (0x1f)  )  ;		//clear screen
	Uart_Printf( "Display Blue! Press any key to continue!\n" );
	Uart_Getch() ;		//wait uart input

	Lcd_ClearScr( (0x00<<11) | (0x3f<<5) | (0x00)  )  ;		//clear screen
	Uart_Printf( "Display Green! Press any key to continue!\n" );
	Uart_Getch() ;		//wait uart input

	Lcd_ClearScr( (0x1f<<11) | (0x00<<5) | (0x00)  )  ;		//clear screen
	Uart_Printf( "Display Red! Press any key to continue!\n" );
	Uart_Getch() ;		//wait uart input


	Lcd_ClearScr(0xffff);		//fill all screen with some color
	#define LCD_BLANK		12
	#define C_UP		( gp_lcd->Phy_xsize- LCD_BLANK*2 )
	#define C_RIGHT		( gp_lcd->Phy_xsize- LCD_BLANK*2 )
	#define V_BLACK		( ( gp_lcd->Phy_ysize- LCD_BLANK*4 ) / 6 )
	Glib_FilledRectangle( LCD_BLANK, LCD_BLANK, ( gp_lcd->Phy_xsize- LCD_BLANK ), ( gp_lcd->Phy_ysize- LCD_BLANK ),0x0000);		//fill a Rectangle with some color

	Glib_FilledRectangle( (LCD_BLANK*2), (LCD_BLANK*2 + V_BLACK*0), (C_RIGHT), (LCD_BLANK*2 + V_BLACK*1),0x001f);		//fill a Rectangle with some color
	Glib_FilledRectangle( (LCD_BLANK*2), (LCD_BLANK*2 + V_BLACK*1), (C_RIGHT), (LCD_BLANK*2 + V_BLACK*2),0x07e0);		//fill a Rectangle with some color
	Glib_FilledRectangle( (LCD_BLANK*2), (LCD_BLANK*2 + V_BLACK*2), (C_RIGHT), (LCD_BLANK*2 + V_BLACK*3),0xf800);		//fill a Rectangle with some color
	Glib_FilledRectangle( (LCD_BLANK*2), (LCD_BLANK*2 + V_BLACK*3), (C_RIGHT), (LCD_BLANK*2 + V_BLACK*4),0xffe0);		//fill a Rectangle with some color
	Glib_FilledRectangle( (LCD_BLANK*2), (LCD_BLANK*2 + V_BLACK*4), (C_RIGHT), (LCD_BLANK*2 + V_BLACK*5),0xf81f);		//fill a Rectangle with some color
	Glib_FilledRectangle( (LCD_BLANK*2), (LCD_BLANK*2 + V_BLACK*5), (C_RIGHT), (LCD_BLANK*2 + V_BLACK*6),0x07ff);		//fill a Rectangle with some color

	Glib_Line( LCD_BLANK,LCD_BLANK, (gp_lcd->Phy_xsize-LCD_BLANK), (gp_lcd->Phy_ysize-LCD_BLANK), 0x0000 ) ;
	Glib_Line( LCD_BLANK,(gp_lcd->Phy_ysize-LCD_BLANK), (gp_lcd->Phy_xsize-LCD_BLANK), LCD_BLANK, 0x0000 ) ;
	Glib_Line( (gp_lcd->Phy_xsize/2),(LCD_BLANK*2 + V_BLACK*0), (gp_lcd->Phy_xsize/2), (LCD_BLANK*2 + V_BLACK*6), 0x0000 ) ;

}

/*
函数名	：_lcd_init
功能	：lcd初始化程序
参数  	: info:初始化屏幕的基本信息
返回	：
备注	：这个函数为内部使用，只被cstmLcd_init调用
*/
static void _lcd_init(struct lcd_init_info_t *info)
{
/*	*/	
	rGPCUP  = 0x00000000;
	rGPCCON = 0xaaaa02a9; 
	 
	rGPDUP  = 0x00000000;
	rGPDCON=0xaaaaaaaa; //Initialize VD[15:8]

	rLCDCON1=(info->clk_tft<<8)|(info->Mval_Used<<7)|(3<<5)|(12<<1)|0;
    	// TFT LCD panel,12bpp TFT,ENVID=off
	rLCDCON2=(info->vbpd<<24)|(info->Lineval_tft<<14)|(info->vfpd<<6)|(info->vspw);
	rLCDCON3=(info->hbpd<<19)|(info->hozval_tft<<8)|info->hfpd;
	rLCDCON4=(info->Mval<<8)|(info->hspw);
	rLCDCON5 = (1<<11) | (0<<10) | (1<<9) | (1<<8) | (0<<7) | (0<<6) | (1<<3)  |(info->Bswp<<1)|(info->HWswp);
	rLCDSADDR1=(((U32)LCD_BUFFER>>22)<<21)|M5D((U32)LCD_BUFFER>>1);
#if 1
	rLCDSADDR2=M5D( ((U32)LCD_BUFFER+info->Scr_xsize*info->Phy_ysize*2)>>1 );
	rLCDSADDR3=(((info->Scr_xsize-info->Phy_xsize)/1)<<11)|(info->Phy_xsize/1);
	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
	rTCONSEL &= (~7) ;     // Disable LPC3480
	rTPAL=0; // Disable Temp Palette
#else
	rLCDSADDR2=M5D( ((U32)LCD_BUFFER+(SCR_XSIZE_TFT*LCD_YSIZE_TFT*2))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_TFT-LCD_XSIZE_TFT)/1)<<11)|(LCD_XSIZE_TFT/1);
	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
	rTCONSEL &= (~7) ;     // Disable LPC3480
	rTPAL=0; // Disable Temp Palette

#endif
	Uart_Printf("\ncon1=0x%x,con2=0x%x,con3=0x%x,con4=0x%x,con5=0x%x\n",rLCDCON1,rLCDCON2,rLCDCON3,rLCDCON4,rLCDCON5);
	Lcd_PowerEnable(0, 1);
	Lcd_EnvidOnOff(1);		//turn on vedio
}

/*
函数名	：cstmLcd_init
功能	：lcd初始化主程序
参数  	: 
返回	：
备注	：
*/
void cstmLcd_init()
{
	U8 i;
	
	/*do{
		Uart_Printf("\nPlease select your LCD type  :\n");
		Uart_Printf("0:		W35	\n");
		Uart_Printf("1:		S35\n");
		Uart_Printf("2:		T35\n");
		Uart_Printf("3:		W43\n");
		Uart_Printf("4:		LCD57\n");
		Uart_Printf("5:		VGA\n");
		Uart_Printf("6:		A70\n");
		Uart_Printf("7:		LCD104\n");
		
		i = Uart_GetIntNum_GJ();
		if(i>7)
		{
			Uart_Printf("\nerr input,input again?,	0:no 1:yes 2 use default setting LCDW43\n");
			i = Uart_GetIntNum_GJ();
			if(i==0)
			{
				Uart_Printf("\nexit!\n");				
				return ;
			}
			else if(i==2)
				i=3;
		}
	}while(i>7);*/
	i=3;
	gp_lcd=&lcd_set[i];
#ifdef CSTM_LCD
	LCD_BUFFER=(volatile unsigned short *)malloc(sizeof(short)*gp_lcd->Scr_ysize*gp_lcd->Scr_xsize);
	_lcd_init(gp_lcd);
#endif
//	tst_lcd();
}

//******************END　OF FILE***********************************************************

