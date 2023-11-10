/**************************************************************
The initial and control for 16Bpp TFT LCD
**************************************************************/

#include "def.h"
#include "option.h"
#include "2440addr.h"
#include "2440lib.h"
#include "2440slib.h" 
#include "LCD_TFT.h"


#define M5D(n)				((n) & 0x1fffff)	// To get lower 21bits

extern void Uart_Printf(char *f, ...) ;

volatile unsigned short LCD_BUFFER[SCR_YSIZE_TFT][SCR_XSIZE_TFT];

void delay(unsigned int z){//***************************我加的语句***********************************
	unsigned int x,y;
  	for (x=10000;x>0;x--)
		for(y=z;y>0;y--);
}
/**************************************************************
TFT LCD功能模块初始化
**************************************************************/
void Lcd_PowerEnable(int invpwren,int pwren);
void Lcd_Init(void)
{
	rGPCUP  = 0x00000000;
	rGPCCON = 0xaaaa02a9; 
	 
	rGPDUP  = 0x00000000;
	rGPDCON=0xaaaaaaaa; //Initialize VD[15:8]

	rLCDCON1=(CLKVAL_TFT<<8)|(MVAL_USED<<7)|(3<<5)|(12<<1)|0;
    	// TFT LCD panel,12bpp TFT,ENVID=off
	rLCDCON2=(VBPD<<24)|(LINEVAL_TFT<<14)|(VFPD<<6)|(VSPW);
	rLCDCON3=(HBPD<<19)|(HOZVAL_TFT<<8)|(HFPD);
	rLCDCON4=(MVAL<<8)|(HSPW);
	rLCDCON5 = (1<<11) | (0<<10) | (1<<9) | (1<<8) | (0<<7) | (0<<6) | (1<<3)  |(BSWP<<1) | (HWSWP);

	rLCDSADDR1=(((U32)LCD_BUFFER>>22)<<21)|M5D((U32)LCD_BUFFER>>1);
	rLCDSADDR2=M5D( ((U32)LCD_BUFFER+(SCR_XSIZE_TFT*LCD_YSIZE_TFT*2))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_TFT-LCD_XSIZE_TFT)/1)<<11)|(LCD_XSIZE_TFT/1);
	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
	rTCONSEL &= (~7) ;     // Disable LPC3480
	rTPAL=0; // Disable Temp Palette
}

/**************************************************************
LCD视频和控制信号输出或者停止，1开启视频输出
**************************************************************/
void Lcd_EnvidOnOff(int onoff)
{
	if(onoff==1)
		rLCDCON1|=1; // ENVID=ON
	else
		rLCDCON1 =rLCDCON1 & 0x3fffe; // ENVID Off
}

/**************************************************************
TFT LCD 电源控制引脚使能
**************************************************************/
void Lcd_PowerEnable(int invpwren,int pwren)
{
	//GPG4 is setted as LCD_PWREN
	rGPGUP=rGPGUP&(~(1<<4))|(1<<4); // Pull-up disable
	rGPGCON=rGPGCON&(~(3<<8))|(3<<8); //GPG4=LCD_PWREN
	rGPGDAT = rGPGDAT | (1<<4) ;
	//invpwren=pwren;
	//Enable LCD POWER ENABLE Function
	rLCDCON5=rLCDCON5&(~(1<<3))|(pwren<<3);   // PWREN
	rLCDCON5=rLCDCON5&(~(1<<5))|(invpwren<<5);   // INVPWREN
}

/**************************************************************
TFT LCD移动观察窗口
**************************************************************/
void Lcd_MoveViewPort(int vx,int vy)
{
	U32 addr;

	SET_IF(); 
	#if (LCD_XSIZE_TFT<32)
		while((rLCDCON1>>18)<=1); // if x<32
	#else	
		while((rLCDCON1>>18)==0); // if x>32
	#endif
    
	addr=(U32)LCD_BUFFER+(vx*2)+vy*(SCR_XSIZE_TFT*2);
	rLCDSADDR1= ( (addr>>22)<<21 ) | M5D(addr>>1);
	rLCDSADDR2= M5D(((addr+(SCR_XSIZE_TFT*LCD_YSIZE_TFT*2))>>1));
	CLR_IF();
}    

/**************************************************************
TFT LCD移动观察窗口
**************************************************************/
void MoveViewPort(void)
{
    int vx=0,vy=0,vd=1;

    Uart_Printf("\n*Move the LCD view windos:\n");
    Uart_Printf(" press 8 is up\n");
    Uart_Printf(" press 2 is down\n");
    Uart_Printf(" press 4 is left\n");
    Uart_Printf(" press 6 is right\n");
    Uart_Printf(" press Enter to exit!\n");

    while(1)
    {
    	switch( Uart_GetKey() )
    	{
    	case '8':
	    if(vy>=vd)vy-=vd;    	   	
        break;

    	case '4':
    	    if(vx>=vd)vx-=vd;
    	break;

    	case '6':
                if(vx<=(SCR_XSIZE_TFT-LCD_XSIZE_TFT-vd))vx+=vd;   	    
   	    break;

    	case '2':
                if(vy<=(SCR_YSIZE_TFT-LCD_YSIZE_TFT-vd))vy+=vd;   	    
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

/**************************************************************
TFT LCD单个象素的显示数据输出
**************************************************************/
void PutPixel(U32 x,U32 y, U32 c )
{
	if ( (x < SCR_XSIZE_TFT) && (y < SCR_YSIZE_TFT) )
		LCD_BUFFER[(y)][(x)] = c;
}

/**************************************************************
TFT LCD全屏填充特定颜色单元或清屏
**************************************************************/
void Lcd_ClearScr( U32 c)
{
	unsigned int x,y ;
		
    for( y = 0 ; y < SCR_YSIZE_TFT ; y++ )
    {
    	for( x = 0 ; x < SCR_XSIZE_TFT ; x++ )
    	{
			LCD_BUFFER[y][x] = c ;
    	}
    }
}

/**************************************************************
LCD屏幕显示垂直翻转
// LCD display is flipped vertically
// But, think the algorithm by mathematics point.
//   3I2
//   4 I 1
//  --+--   <-8 octants  mathematical cordinate
//   5 I 8
//   6I7
**************************************************************/
void Glib_Line(int x1,int y1,int x2,int y2,int color)
{
	int dx,dy,e;
	dx=x2-x1; 
	dy=y2-y1;
    
	if(dx>=0)
	{
		if(dy >= 0) // dy>=0
		{
			if(dx>=dy) // 1/8 octant
			{
				e=dy-dx/2;
				while(x1<=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else		// 2/8 octant
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   // dy<0
		{
			dy=-dy;   // dy=abs(dy)

			if(dx>=dy) // 8/8 octant
			{
				e=dy-dx/2;
				while(x1<=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else		// 7/8 octant
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
	else //dx<0
	{
		dx=-dx;		//dx=abs(dx)
		if(dy >= 0) // dy>=0
		{
			if(dx>=dy) // 4/8 octant
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		// 3/8 octant
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   // dy<0
		{
			dy=-dy;   // dy=abs(dy)

			if(dx>=dy) // 5/8 octant
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		// 6/8 octant
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
}

/**************************************************************
在LCD屏幕上画一个矩形
**************************************************************/
void Glib_Rectangle(int x1,int y1,int x2,int y2,int color)
{
    Glib_Line(x1,y1,x2,y1,color);
    Glib_Line(x2,y1,x2,y2,color);
    Glib_Line(x1,y2,x2,y2,color);
    Glib_Line(x1,y1,x1,y2,color);
}

/**************************************************************
在LCD屏幕上用颜色填充一个矩形
**************************************************************/
void Glib_FilledRectangle(int x1,int y1,int x2,int y2,int color)
{
    int i;

    for(i=y1;i<=y2;i++)
	Glib_Line(x1,i,x2,i,color);
}

/**************************************************************
在LCD屏幕上指定坐标点画一个指定大小的图片
**************************************************************/
void Paint_Bmp(int x0,int y0,int h,int l,unsigned char bmp[])
{
	int x,y;
	U32 c;
	int p = 0;
	
    for( y = y0 ; y < l+y0 ; y++ )
    {
    	for( x = x0 ; x < h+x0 ; x++ )
    	{
    		c = bmp[p+1] | (bmp[p]<<8) ;

			if ( ( (x0+x) < SCR_XSIZE_TFT) && ( (y0+y) < SCR_YSIZE_TFT) )
				LCD_BUFFER[y0+y][x0+x] = c ;
			
    		p = p + 2 ;
    	}
    }
}

/**************************************************************
**************************************************************/
void Lcd_TFT_Init(void)
{
	Lcd_Init();
	Lcd_PowerEnable(0, 1);
	Lcd_EnvidOnOff(1);		//turn on vedio

	Lcd_ClearScr( (0x00<<11) | (0x00<<5) | (0x00) );  
	#define LCD_BLANK		12
	#define C_UP		( LCD_XSIZE_TFT - LCD_BLANK*2 )
	#define C_RIGHT		( LCD_XSIZE_TFT - LCD_BLANK*2 )
	#define V_BLACK		( ( LCD_YSIZE_TFT - LCD_BLANK*4 ) / 6 )
	Glib_FilledRectangle( LCD_BLANK, LCD_BLANK, ( LCD_XSIZE_TFT - LCD_BLANK ), ( LCD_YSIZE_TFT - LCD_BLANK ),0x0000);		//fill a Rectangle with some color

	Glib_FilledRectangle( (LCD_BLANK*2), (LCD_BLANK*2 + V_BLACK*0), (C_RIGHT), (LCD_BLANK*2 + V_BLACK*1),0x001f);		//fill a Rectangle with some color
	Glib_FilledRectangle( (LCD_BLANK*2), (LCD_BLANK*2 + V_BLACK*1), (C_RIGHT), (LCD_BLANK*2 + V_BLACK*2),0x07e0);		//fill a Rectangle with some color
	Glib_FilledRectangle( (LCD_BLANK*2), (LCD_BLANK*2 + V_BLACK*2), (C_RIGHT), (LCD_BLANK*2 + V_BLACK*3),0xf800);		//fill a Rectangle with some color
	Glib_FilledRectangle( (LCD_BLANK*2), (LCD_BLANK*2 + V_BLACK*3), (C_RIGHT), (LCD_BLANK*2 + V_BLACK*4),0xffe0);		//fill a Rectangle with some color
	Glib_FilledRectangle( (LCD_BLANK*2), (LCD_BLANK*2 + V_BLACK*4), (C_RIGHT), (LCD_BLANK*2 + V_BLACK*5),0xf81f);		//fill a Rectangle with some color
	Glib_FilledRectangle( (LCD_BLANK*2), (LCD_BLANK*2 + V_BLACK*5), (C_RIGHT), (LCD_BLANK*2 + V_BLACK*6),0x07ff);		//fill a Rectangle with some color

	Glib_Line( LCD_BLANK,LCD_BLANK, (LCD_XSIZE_TFT-LCD_BLANK), (LCD_YSIZE_TFT-LCD_BLANK), 0x0000 ) ;
	Glib_Line( LCD_BLANK,(LCD_YSIZE_TFT-LCD_BLANK), (LCD_XSIZE_TFT-LCD_BLANK), LCD_BLANK, 0x0000 ) ;
	Glib_Line( (LCD_XSIZE_TFT/2),(LCD_BLANK*2 + V_BLACK*0), (LCD_XSIZE_TFT/2), (LCD_BLANK*2 + V_BLACK*6), 0x0000 ) ;
	
}

/*void Lcd_TFT_Test( void ) 
{
int ii;
   	Uart_Printf("\nTest TFT LCD!\n");
	Lcd_ClearScr( (0x00<<11) | (0x00<<5) | (0x00)  )  ;		//clear screen
	//Paint_Bmp(0, 0, 480, 272, caocao);
	
	Uart_Printf( "\nDisplay Black! Press any key to continue!\n" );
	Uart_Getch() ;		//wait uart input


	Lcd_ClearScr( (0x1f<<11) | (0x3f<<5) | (0x1f)  )  ;		//clear screen
	Paint_Bmp(0, 0, 480, 272, TQ_LOGO_480272);
	Uart_Printf( "Display White! Press any key to continue!\n" );
	Uart_Getch() ;		//wait uart input

	Lcd_ClearScr( (0x00<<11) | (0x00<<5) | (0x1f)  )  ;		//clear screen
	Paint_Bmp(0, 0, 480, 272, caocao);
	Uart_Printf( "Display Blue! Press any key to continue!\n" );
	Uart_Getch() ;		//wait uart input

	Lcd_ClearScr( (0x00<<11) | (0x3f<<5) | (0x00)  )  ;		//clear screen
	Paint_Bmp(80, 10, 90, 124, TQ_LOGO_90124);
	Uart_Printf( "Display Green! Press any key to continue!\n" );
	Uart_Getch() ;		//wait uart input

	Lcd_ClearScr( (0x1f<<11) | (0x00<<5) | (0x00)  )  ;		//clear screen
	Uart_Printf( "Display Red! Press any key to continue!\n" );
	Uart_Getch() ;		//wait uart input

	Lcd_ClearScr( (0x00<<11) | (0x3f<<5) | (0x1f)  )  ;		//clear screen
	Uart_Printf( "LCD clear screen is finished! press any key to continue!\n" );
	Uart_Getch() ;		//wait uart input

	Lcd_ClearScr( (0x1f<<11) | (0x00<<5) | (0x1f)  )  ;		//clear screen
	Uart_Printf( "LCD clear screen is finished! press any key to continue!\n" );
	Uart_Getch() ;		//wait uart input

	Lcd_ClearScr( (0x1f<<11) | (0x3f<<5) | (0x00)  )  ;		//clear screen
	Uart_Printf( "LCD clear screen is finished! press any key to continue!\n" );
	Uart_Getch() ;		//wait uart input

	Lcd_ClearScr(0xffff);		//fill all screen with some color
	#define LCD_BLANK		12
	#define C_UP		( LCD_XSIZE_TFT - LCD_BLANK*2 )
	#define C_RIGHT		( LCD_XSIZE_TFT - LCD_BLANK*2 )
	#define V_BLACK		( ( LCD_YSIZE_TFT - LCD_BLANK*4 ) / 6 )
	Glib_FilledRectangle( LCD_BLANK, LCD_BLANK, ( LCD_XSIZE_TFT - LCD_BLANK ), ( LCD_YSIZE_TFT - LCD_BLANK ),0x0000);		//fill a Rectangle with some color

	Glib_FilledRectangle( (LCD_BLANK*2), (LCD_BLANK*2 + V_BLACK*0), (C_RIGHT), (LCD_BLANK*2 + V_BLACK*1),0x001f);		//fill a Rectangle with some color
	Glib_FilledRectangle( (LCD_BLANK*2), (LCD_BLANK*2 + V_BLACK*1), (C_RIGHT), (LCD_BLANK*2 + V_BLACK*2),0x07e0);		//fill a Rectangle with some color
	Glib_FilledRectangle( (LCD_BLANK*2), (LCD_BLANK*2 + V_BLACK*2), (C_RIGHT), (LCD_BLANK*2 + V_BLACK*3),0xf800);		//fill a Rectangle with some color
	Glib_FilledRectangle( (LCD_BLANK*2), (LCD_BLANK*2 + V_BLACK*3), (C_RIGHT), (LCD_BLANK*2 + V_BLACK*4),0xffe0);		//fill a Rectangle with some color
	Glib_FilledRectangle( (LCD_BLANK*2), (LCD_BLANK*2 + V_BLACK*4), (C_RIGHT), (LCD_BLANK*2 + V_BLACK*5),0xf81f);		//fill a Rectangle with some color
	Glib_FilledRectangle( (LCD_BLANK*2), (LCD_BLANK*2 + V_BLACK*5), (C_RIGHT), (LCD_BLANK*2 + V_BLACK*6),0x07ff);		//fill a Rectangle with some color

	Glib_Line( LCD_BLANK,LCD_BLANK, (LCD_XSIZE_TFT-LCD_BLANK), (LCD_YSIZE_TFT-LCD_BLANK), 0x0000 ) ;
	Glib_Line( LCD_BLANK,(LCD_YSIZE_TFT-LCD_BLANK), (LCD_XSIZE_TFT-LCD_BLANK), LCD_BLANK, 0x0000 ) ;
	Glib_Line( (LCD_XSIZE_TFT/2),(LCD_BLANK*2 + V_BLACK*0), (LCD_XSIZE_TFT/2), (LCD_BLANK*2 + V_BLACK*6), 0x0000 ) ;

 	#if(LCD_Type == LCDT35)
		Uart_Printf( "Press any key to continue!\n" );
		Uart_Getch() ;		//Any Key To Next
		Paint_Bmp(0, 0, 240, 320, TQ_LOGO_240320);
	#elif((LCD_Type == LCDW35) || (LCD_Type == LCDS35))
		Uart_Printf( "Press any key to continue!\n" );
		Uart_Getch() ;		//Any Key To Next
		Paint_Bmp(0, 0, 320, 240, TQ_LOGO_320240);
	#elif(LCD_Type == LCDW43)                      //*******************给4.3寸屏幕   显示一张图片
		Uart_Printf( "Press any key to continue!\n" );
		Uart_Getch() ;		//Any Key To Next
		for(ii=1;ii<100;ii++){
		//Lcd_ClearScr( (0x00<<11) | (0x00<<5) | (0x00)  )  ;		//clear screen
		Paint_Bmp(0, 0, 480, 272, caocao);
		//delay(10);
		}
		Paint_Bmp(0, 0, 480, 272, TQ_LOGO_480272);
		Paint_Bmp(80, 10, 90, 124, TQ_LOGO_90124);
	#elif(LCD_Type == VGA)
		Uart_Printf( "Press any key to continue!\n" );
		Uart_Getch() ;		//Any Key To Next
		Paint_Bmp(0, 0, 640, 480, TQ_LOGO_640480);
	#elif(LCD_Type == LCDA70)
		Uart_Printf( "Press any key to continue!\n" );
		Uart_Getch() ;		//Any Key To Next
		Paint_Bmp(0, 0, 800, 480, TQ_LOGO_800480);
	#endif
	Uart_Printf("LCD Test Complete!\n");
	Uart_Printf("Press any key to quit!\n");
	Uart_Getch();	
        
}*/
//*************************************************************
