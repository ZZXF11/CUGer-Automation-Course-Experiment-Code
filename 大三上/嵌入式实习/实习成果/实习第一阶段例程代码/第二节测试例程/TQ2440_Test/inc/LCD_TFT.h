/**************************************************************
The initial and control for TFT LCD
**************************************************************/

#define LCDW35			1		// 天嵌3.5寸屏(320X240)或东华3.5寸屏或奇美3.5寸屏
#define LCDS35			2		// 三星3.5寸屏(320X240)
#define LCDT35			3		// 东芝3.5寸屏(240X320)
#define LCDW43			4		// 天嵌4.3寸屏(480X272)
#define LCD57			5		// 5.7寸屏
#define LCDA70			6		// 7.0寸屏(800X480)
#define VGA			7		// VGA(640X480)
#define LCDA104			8		// 10.4寸屏(800X600)

#define LCD_Type		LCDW43		//设定屏的类型

#if(LCD_Type == LCDW35)				// 东华屏

#define MVAL		(13)
#define MVAL_USED 	(0)			//0=each frame   1=rate by MVAL
#define INVVDEN		(1)			//0=normal       1=inverted
#define BSWP		(0)			//Byte swap control
#define HWSWP		(1)			//Half word swap control
#define PNRMODE		(3)			// 设置为TFT屏
#define BPPMODE		(12)			// 设置为16bpp模式

//TFT_SIZE
#define LCD_XSIZE_TFT 	(320)	
#define LCD_YSIZE_TFT 	(240)

#define SCR_XSIZE_TFT 	(320)
#define SCR_YSIZE_TFT 	(240)

//Timing parameter for 3.5' LCD
#define VBPD 		(12)			//垂直同步信号的后肩
#define VFPD 		(4)			//垂直同步信号的前肩
#define VSPW 		(5)			//垂直同步信号的脉宽

#define HBPD 		(22)			//水平同步信号的后肩
#define HFPD 		(33)			//水平同步信号的前肩
#define HSPW 		(44)			//水平同步信号的脉宽

#define CLKVAL_TFT 	(6) 	

#elif(LCD_Type == LCDS35)			// 三星屏

#define MVAL		(13)
#define MVAL_USED 	(0)			//0=each frame   1=rate by MVAL
#define INVVDEN		(1)			//0=normal       1=inverted
#define BSWP		(0)			//Byte swap control
#define HWSWP		(1)			//Half word swap control
#define PNRMODE		(3)			// 设置为TFT屏
#define BPPMODE		(12)			// 设置为16bpp模式

//TFT_SIZE
#define LCD_XSIZE_TFT 	(320)	
#define LCD_YSIZE_TFT 	(240)

#define SCR_XSIZE_TFT 	(320)
#define SCR_YSIZE_TFT 	(240)

//Timing parameter for 3.5' LCD
#define VBPD 		(12)			//垂直同步信号的后肩
#define VFPD 		(4)			//垂直同步信号的前肩
#define VSPW 		(5)			//垂直同步信号的脉宽

#define HBPD 		(8)			//水平同步信号的后肩
#define HFPD 		(16)			//水平同步信号的前肩
#define HSPW 		(4)			//水平同步信号的脉宽

#define CLKVAL_TFT 	(6) 	

#elif(LCD_Type == LCDT35)			// 东芝屏

#define MVAL		(13)
#define MVAL_USED 	(0)			//0=each frame   1=rate by MVAL
#define INVVDEN		(1)			//0=normal       1=inverted
#define BSWP		(0)			//Byte swap control
#define HWSWP		(1)			//Half word swap control
#define PNRMODE		(3)			// 设置为TFT屏
#define BPPMODE		(12)			// 设置为16bpp模式

//TFT_SIZE
#define LCD_XSIZE_TFT 	(240)	
#define LCD_YSIZE_TFT 	(320)

#define SCR_XSIZE_TFT 	(240)
#define SCR_YSIZE_TFT 	(320)

//Timing parameter for 3.5' LCD
#define VBPD 		(1)			//垂直同步信号的后肩
#define VFPD 		(2)			//垂直同步信号的前肩
#define VSPW 		(6)			//垂直同步信号的脉宽

#define HBPD 		(5)			//水平同步信号的后肩
#define HFPD 		(10)			//水平同步信号的前肩
#define HSPW 		(15)			//水平同步信号的脉宽

#define CLKVAL_TFT 	(4) 	

#elif(LCD_Type == LCDW43)			// 4.3寸屏

#define MVAL		(13)
#define MVAL_USED 	(0)			//0=each frame   1=rate by MVAL
#define INVVDEN		(1)			//0=normal       1=inverted
#define BSWP		(0)			//Byte swap control
#define HWSWP		(1)			//Half word swap control
#define PNRMODE		(3)			// 设置为TFT屏
#define BPPMODE		(12)			// 设置为16bpp模式

//TFT_SIZE
#define LCD_XSIZE_TFT 	(480)	
#define LCD_YSIZE_TFT 	(272)

#define SCR_XSIZE_TFT 	(480)
#define SCR_YSIZE_TFT 	(272)

//Timing parameter for 4.3' LCD
#define VBPD 		(2)			//垂直同步信号的后肩
#define VFPD 		(4)			//垂直同步信号的前肩
#define VSPW 		(8)			//垂直同步信号的脉宽

#define HBPD 		(10)			//水平同步信号的后肩
#define HFPD 		(19)			//水平同步信号的前肩
#define HSPW 		(30)			//水平同步信号的脉宽

#define CLKVAL_TFT 	(4) 	

#elif(LCD_Type == LCD57)			// 5.7寸屏

#define MVAL		(13)
#define MVAL_USED 	(0)			//0=each frame   1=rate by MVAL
#define INVVDEN		(1)			//0=normal       1=inverted
#define BSWP		(0)			//Byte swap control
#define HWSWP		(1)			//Half word swap control
#define PNRMODE		(3)			// 设置为TFT屏
#define BPPMODE		(12)			// 设置为16bpp模式

//TFT_SIZE
#define LCD_XSIZE_TFT 	(320)	
#define LCD_YSIZE_TFT 	(240)

#define SCR_XSIZE_TFT 	(320)
#define SCR_YSIZE_TFT 	(240)

//Timing parameter for 5.7' LCD
#define VBPD 		(3)			//垂直同步信号的后肩
#define VFPD 		(5)			//垂直同步信号的前肩
#define VSPW 		(15)			//垂直同步信号的脉宽

#define HBPD 		(5)			//水平同步信号的后肩
#define HFPD 		(15)			//水平同步信号的前肩
#define HSPW 		(8)			//水平同步信号的脉宽

#define CLKVAL_TFT 	(7) 	

#elif(LCD_Type == VGA)				// VGA

#define MVAL		(13)
#define MVAL_USED 	(0)			//0=each frame   1=rate by MVAL
#define INVVDEN		(1)			//0=normal       1=inverted
#define BSWP		(0)			//Byte swap control
#define HWSWP		(1)			//Half word swap control
#define PNRMODE		(3)			// 设置为TFT屏
#define BPPMODE		(12)			// 设置为16bpp模式

//TFT_SIZE
#define LCD_XSIZE_TFT 	(640)	
#define LCD_YSIZE_TFT 	(480)

#define SCR_XSIZE_TFT 	(640)
#define SCR_YSIZE_TFT 	(480)

//Timing parameter for VGA
#define VBPD 		(29)			//垂直同步信号的后肩
#define VFPD 		(5)			//垂直同步信号的前肩
#define VSPW 		(4)			//垂直同步信号的脉宽

#define HBPD 		(71)			//水平同步信号的后肩
#define HFPD 		(40)			//水平同步信号的前肩
#define HSPW 		(31)			//水平同步信号的脉宽

#define CLKVAL_TFT 	(1) 	

#elif(LCD_Type == LCDA70)			// 7.0寸屏

#define MVAL		(13)
#define MVAL_USED 	(0)			//0=each frame   1=rate by MVAL
#define INVVDEN		(1)			//0=normal       1=inverted
#define BSWP		(0)			//Byte swap control
#define HWSWP		(1)			//Half word swap control
#define PNRMODE		(3)			// 设置为TFT屏
#define BPPMODE		(12)			// 设置为16bpp模式

//TFT_SIZE
#define LCD_XSIZE_TFT 	(800)	
#define LCD_YSIZE_TFT 	(480)

#define SCR_XSIZE_TFT 	(800)
#define SCR_YSIZE_TFT 	(480)

//Timing parameter for 7.0' LCD
#define VBPD 		(3)			//垂直同步信号的后肩
#define VFPD 		(5)			//垂直同步信号的前肩
#define VSPW 		(15)			//垂直同步信号的脉宽

#define HBPD 		(5)			//水平同步信号的后肩
#define HFPD 		(15)			//水平同步信号的前肩
#define HSPW 		(8)			//水平同步信号的脉宽

#define CLKVAL_TFT 	(7) 	

#elif(LCD_Type == LCDA104)			// 10.4寸屏

#define MVAL		(13)
#define MVAL_USED 	(0)			//0=each frame   1=rate by MVAL
#define INVVDEN		(1)			//0=normal       1=inverted
#define BSWP		(0)			//Byte swap control
#define HWSWP		(1)			//Half word swap control
#define PNRMODE		(3)			// 设置为TFT屏
#define BPPMODE		(12)			// 设置为16bpp模式

//TFT_SIZE
#define LCD_XSIZE_TFT 	(800)	
#define LCD_YSIZE_TFT 	(600)

#define SCR_XSIZE_TFT 	(800)
#define SCR_YSIZE_TFT 	(600)

//Timing parameter for 4.3' LCD
#define VBPD 		(5)			//垂直同步信号的后肩
#define VFPD 		(6)			//垂直同步信号的前肩
#define VSPW 		(1)			//垂直同步信号的脉宽

#define HBPD 		(28)			//水平同步信号的后肩
#define HFPD 		(14)			//水平同步信号的前肩
#define HSPW 		(180)			//水平同步信号的脉宽

#define CLKVAL_TFT 	(3) 	

#endif

#define HOZVAL_TFT	(LCD_XSIZE_TFT-1)
#define LINEVAL_TFT	(LCD_YSIZE_TFT-1)

void Lcd_TFT_Init(void);

void Lcd_TFT_Test( void ) ;

void  Lcd_EnvidOnOff(int );

void Lcd_PowerEnable(int ,int );

void Lcd_Init(void);
extern unsigned char xiYY[];
extern unsigned char lanYY[];
extern unsigned char meiYY[];
extern unsigned char feiYY[];
extern unsigned char nuanYY[];
extern unsigned char manYY_2[];

#if((LCD_Type == LCDW35) || (LCD_Type == LCDS35))	// 3.5寸屏
	extern unsigned char TQ_LOGO_320240[];//自定义的图片
#elif(LCD_Type == LCDT35)				// 3.5寸屏
	extern unsigned char TQ_LOGO_240320[];//自定义的图片
#elif(LCD_Type == LCDW43)				// 3.5寸屏
	extern unsigned char TQ_LOGO_480272[];//自定义的图片
#elif(LCD_Type == VGA)					//VGA
	extern unsigned char TQ_LOGO_640480[];//自定义的图片
#elif(LCD_Type == LCDA70)				// 7寸屏
	extern unsigned char TQ_LOGO_800480[];//自定义的图片
#endif


