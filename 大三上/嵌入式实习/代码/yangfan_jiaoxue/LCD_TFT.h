/**************************************************************
The initial and control for TFT LCD
**************************************************************/

#define LCDW35			1		// ��Ƕ3.5����(320X240)�򶫻�3.5����������3.5����
#define LCDS35			2		// ����3.5����(320X240)
#define LCDT35			3		// ��֥3.5����(240X320)
#define LCDW43			4		// ��Ƕ4.3����(480X272)
#define LCD57			5		// 5.7����
#define LCDA70			6		// 7.0����(800X480)
#define VGA			7		// VGA(640X480)
#define LCDA104			8		// 10.4����(800X600)

#define LCD_Type		LCDW43		//�趨��������

#if(LCD_Type == LCDW35)				// ������

#define MVAL		(13)
#define MVAL_USED 	(0)			//0=each frame   1=rate by MVAL
#define INVVDEN		(1)			//0=normal       1=inverted
#define BSWP		(0)			//Byte swap control
#define HWSWP		(1)			//Half word swap control
#define PNRMODE		(3)			// ����ΪTFT��
#define BPPMODE		(12)			// ����Ϊ16bppģʽ

//TFT_SIZE
#define LCD_XSIZE_TFT 	(320)	
#define LCD_YSIZE_TFT 	(240)

#define SCR_XSIZE_TFT 	(320)
#define SCR_YSIZE_TFT 	(240)

//Timing parameter for 3.5' LCD
#define VBPD 		(12)			//��ֱͬ���źŵĺ��
#define VFPD 		(4)			//��ֱͬ���źŵ�ǰ��
#define VSPW 		(5)			//��ֱͬ���źŵ�����

#define HBPD 		(22)			//ˮƽͬ���źŵĺ��
#define HFPD 		(33)			//ˮƽͬ���źŵ�ǰ��
#define HSPW 		(44)			//ˮƽͬ���źŵ�����

#define CLKVAL_TFT 	(6) 	

#elif(LCD_Type == LCDS35)			// ������

#define MVAL		(13)
#define MVAL_USED 	(0)			//0=each frame   1=rate by MVAL
#define INVVDEN		(1)			//0=normal       1=inverted
#define BSWP		(0)			//Byte swap control
#define HWSWP		(1)			//Half word swap control
#define PNRMODE		(3)			// ����ΪTFT��
#define BPPMODE		(12)			// ����Ϊ16bppģʽ

//TFT_SIZE
#define LCD_XSIZE_TFT 	(320)	
#define LCD_YSIZE_TFT 	(240)

#define SCR_XSIZE_TFT 	(320)
#define SCR_YSIZE_TFT 	(240)

//Timing parameter for 3.5' LCD
#define VBPD 		(12)			//��ֱͬ���źŵĺ��
#define VFPD 		(4)			//��ֱͬ���źŵ�ǰ��
#define VSPW 		(5)			//��ֱͬ���źŵ�����

#define HBPD 		(8)			//ˮƽͬ���źŵĺ��
#define HFPD 		(16)			//ˮƽͬ���źŵ�ǰ��
#define HSPW 		(4)			//ˮƽͬ���źŵ�����

#define CLKVAL_TFT 	(6) 	

#elif(LCD_Type == LCDT35)			// ��֥��

#define MVAL		(13)
#define MVAL_USED 	(0)			//0=each frame   1=rate by MVAL
#define INVVDEN		(1)			//0=normal       1=inverted
#define BSWP		(0)			//Byte swap control
#define HWSWP		(1)			//Half word swap control
#define PNRMODE		(3)			// ����ΪTFT��
#define BPPMODE		(12)			// ����Ϊ16bppģʽ

//TFT_SIZE
#define LCD_XSIZE_TFT 	(240)	
#define LCD_YSIZE_TFT 	(320)

#define SCR_XSIZE_TFT 	(240)
#define SCR_YSIZE_TFT 	(320)

//Timing parameter for 3.5' LCD
#define VBPD 		(1)			//��ֱͬ���źŵĺ��
#define VFPD 		(2)			//��ֱͬ���źŵ�ǰ��
#define VSPW 		(6)			//��ֱͬ���źŵ�����

#define HBPD 		(5)			//ˮƽͬ���źŵĺ��
#define HFPD 		(10)			//ˮƽͬ���źŵ�ǰ��
#define HSPW 		(15)			//ˮƽͬ���źŵ�����

#define CLKVAL_TFT 	(4) 	

#elif(LCD_Type == LCDW43)			// 4.3����

#define MVAL		(13)
#define MVAL_USED 	(0)			//0=each frame   1=rate by MVAL
#define INVVDEN		(1)			//0=normal       1=inverted
#define BSWP		(0)			//Byte swap control
#define HWSWP		(1)			//Half word swap control
#define PNRMODE		(3)			// ����ΪTFT��
#define BPPMODE		(12)			// ����Ϊ16bppģʽ

//TFT_SIZE
#define LCD_XSIZE_TFT 	(480)	
#define LCD_YSIZE_TFT 	(272)

#define SCR_XSIZE_TFT 	(480)
#define SCR_YSIZE_TFT 	(272)

//Timing parameter for 4.3' LCD
#define VBPD 		(2)			//��ֱͬ���źŵĺ��
#define VFPD 		(4)			//��ֱͬ���źŵ�ǰ��
#define VSPW 		(8)			//��ֱͬ���źŵ�����

#define HBPD 		(10)			//ˮƽͬ���źŵĺ��
#define HFPD 		(19)			//ˮƽͬ���źŵ�ǰ��
#define HSPW 		(30)			//ˮƽͬ���źŵ�����

#define CLKVAL_TFT 	(4) 	

#elif(LCD_Type == LCD57)			// 5.7����

#define MVAL		(13)
#define MVAL_USED 	(0)			//0=each frame   1=rate by MVAL
#define INVVDEN		(1)			//0=normal       1=inverted
#define BSWP		(0)			//Byte swap control
#define HWSWP		(1)			//Half word swap control
#define PNRMODE		(3)			// ����ΪTFT��
#define BPPMODE		(12)			// ����Ϊ16bppģʽ

//TFT_SIZE
#define LCD_XSIZE_TFT 	(320)	
#define LCD_YSIZE_TFT 	(240)

#define SCR_XSIZE_TFT 	(320)
#define SCR_YSIZE_TFT 	(240)

//Timing parameter for 5.7' LCD
#define VBPD 		(3)			//��ֱͬ���źŵĺ��
#define VFPD 		(5)			//��ֱͬ���źŵ�ǰ��
#define VSPW 		(15)			//��ֱͬ���źŵ�����

#define HBPD 		(5)			//ˮƽͬ���źŵĺ��
#define HFPD 		(15)			//ˮƽͬ���źŵ�ǰ��
#define HSPW 		(8)			//ˮƽͬ���źŵ�����

#define CLKVAL_TFT 	(7) 	

#elif(LCD_Type == VGA)				// VGA

#define MVAL		(13)
#define MVAL_USED 	(0)			//0=each frame   1=rate by MVAL
#define INVVDEN		(1)			//0=normal       1=inverted
#define BSWP		(0)			//Byte swap control
#define HWSWP		(1)			//Half word swap control
#define PNRMODE		(3)			// ����ΪTFT��
#define BPPMODE		(12)			// ����Ϊ16bppģʽ

//TFT_SIZE
#define LCD_XSIZE_TFT 	(640)	
#define LCD_YSIZE_TFT 	(480)

#define SCR_XSIZE_TFT 	(640)
#define SCR_YSIZE_TFT 	(480)

//Timing parameter for VGA
#define VBPD 		(29)			//��ֱͬ���źŵĺ��
#define VFPD 		(5)			//��ֱͬ���źŵ�ǰ��
#define VSPW 		(4)			//��ֱͬ���źŵ�����

#define HBPD 		(71)			//ˮƽͬ���źŵĺ��
#define HFPD 		(40)			//ˮƽͬ���źŵ�ǰ��
#define HSPW 		(31)			//ˮƽͬ���źŵ�����

#define CLKVAL_TFT 	(1) 	

#elif(LCD_Type == LCDA70)			// 7.0����

#define MVAL		(13)
#define MVAL_USED 	(0)			//0=each frame   1=rate by MVAL
#define INVVDEN		(1)			//0=normal       1=inverted
#define BSWP		(0)			//Byte swap control
#define HWSWP		(1)			//Half word swap control
#define PNRMODE		(3)			// ����ΪTFT��
#define BPPMODE		(12)			// ����Ϊ16bppģʽ

//TFT_SIZE
#define LCD_XSIZE_TFT 	(800)	
#define LCD_YSIZE_TFT 	(480)

#define SCR_XSIZE_TFT 	(800)
#define SCR_YSIZE_TFT 	(480)

//Timing parameter for 7.0' LCD
#define VBPD 		(3)			//��ֱͬ���źŵĺ��
#define VFPD 		(5)			//��ֱͬ���źŵ�ǰ��
#define VSPW 		(15)			//��ֱͬ���źŵ�����

#define HBPD 		(5)			//ˮƽͬ���źŵĺ��
#define HFPD 		(15)			//ˮƽͬ���źŵ�ǰ��
#define HSPW 		(8)			//ˮƽͬ���źŵ�����

#define CLKVAL_TFT 	(7) 	

#elif(LCD_Type == LCDA104)			// 10.4����

#define MVAL		(13)
#define MVAL_USED 	(0)			//0=each frame   1=rate by MVAL
#define INVVDEN		(1)			//0=normal       1=inverted
#define BSWP		(0)			//Byte swap control
#define HWSWP		(1)			//Half word swap control
#define PNRMODE		(3)			// ����ΪTFT��
#define BPPMODE		(12)			// ����Ϊ16bppģʽ

//TFT_SIZE
#define LCD_XSIZE_TFT 	(800)	
#define LCD_YSIZE_TFT 	(600)

#define SCR_XSIZE_TFT 	(800)
#define SCR_YSIZE_TFT 	(600)

//Timing parameter for 4.3' LCD
#define VBPD 		(5)			//��ֱͬ���źŵĺ��
#define VFPD 		(6)			//��ֱͬ���źŵ�ǰ��
#define VSPW 		(1)			//��ֱͬ���źŵ�����

#define HBPD 		(28)			//ˮƽͬ���źŵĺ��
#define HFPD 		(14)			//ˮƽͬ���źŵ�ǰ��
#define HSPW 		(180)			//ˮƽͬ���źŵ�����

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

#if((LCD_Type == LCDW35) || (LCD_Type == LCDS35))	// 3.5����
	extern unsigned char TQ_LOGO_320240[];//�Զ����ͼƬ
#elif(LCD_Type == LCDT35)				// 3.5����
	extern unsigned char TQ_LOGO_240320[];//�Զ����ͼƬ
#elif(LCD_Type == LCDW43)				// 3.5����
	extern unsigned char TQ_LOGO_480272[];//�Զ����ͼƬ
#elif(LCD_Type == VGA)					//VGA
	extern unsigned char TQ_LOGO_640480[];//�Զ����ͼƬ
#elif(LCD_Type == LCDA70)				// 7����
	extern unsigned char TQ_LOGO_800480[];//�Զ����ͼƬ
#endif


