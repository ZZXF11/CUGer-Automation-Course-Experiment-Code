#include "def.h"
#include "2440addr.h"
#include "2440lib.h"

#include "Test_OV9650.h"

/************************************************/
//some macros and inline function to support porting
//from linux driver,
#define	CLKCON					rCLKCON
#define	CLKCON_CAMIF			(1<<19)
#define	UPLLCON					rUPLLCON
#define	CLKDIVN					rCLKDIVN
#define	DIVN_UPLL_EN			(1<<3)
#define	CAMDIVN					rCAMDIVN
#define	CAMCLK_SET_DIV			(1<<4)
#define	CAM_CTRL				rCIGCTRL	//??

#define	GPIO_E14				14
#define	GPIO_E15				15
#define	GPIO_PULLUP_EN			(0<<30)
#define	GPIO_PULLUP_DIS			(1<<30)
#define	GPIO_MODE_IN			(0<<31)
#define	GPIO_MODE_OUT			(1UL<<31)

#define	read_gpio_bit(x)		((rGPEDAT & (1<<(x))) ? 1 : 0)
#define	write_gpio_bit_set(x)	(rGPEDAT |= 1<<(x))
#define	write_gpio_bit_clear(x)	(rGPEDAT &= ~(1<<(x)))
//only support GPE, in and out
static __inline void set_gpio_ctrl(unsigned int gpio)
{
	rGPECON &= ~(3<<((gpio&0xf)*2));
	if(gpio&GPIO_MODE_OUT)
		rGPECON |= 1<<((gpio&0xf)*2);
	if(gpio&GPIO_PULLUP_DIS)
		rGPEUP |= 1<<(gpio&0xf);
	else
		rGPEUP &= ~(1<<(gpio&0xf));
}

#define	ENODEV			2
#define	udelay(x)		Delay(x/50)
#define	mdelay(x)		Delay((x)*8)
#define	printk			Uart_Printf

static U8 sccb_id = 0x60;	//OV9650



//---
static void CamModuleReset(void)
{
	//bit 30 is external reset
	rCIGCTRL |= (1<<30);	//external camera reset high
	Delay(30);
	rCIGCTRL &= ~(1<<30);	//external camera reset low
	Delay(30);
//	rCIGCTRL |= (1<<19);	//external camera reset high
//	Delay(30);
//	rCIGCTRL &= ~(1<<19);	//external camera reset low
//	Delay(30);
}
//---

typedef unsigned long dma_addr_t;

#define	panic	prink


/*********** start of OV9650 ********************/
/* refer to 25p of OV9650 datasheet */
#  define OV9650_SCCB_ID sccb_id//0x42  /* CS[2:0] = 000 */	//use variable

#  define OV9650_MAX_CLK 24000000 // 24MHz
#  define OV9650_PRODUCT_ID 0x7FA2


#  define OV9650_SCCB_DELAY    100 
#  define OV9650_SCCB_DELAY2   100

#  define SIO_C          (GPIO_E14)
#  define SIO_D          (GPIO_E15)
#  define MAKE_HIGH(_x)  write_gpio_bit_set(_x)
#  define MAKE_LOW(_x)   write_gpio_bit_clear(_x)
#  define BIT_READ(_x)   read_gpio_bit(_x)
#  define CFG_READ(_x)   set_gpio_ctrl(_x | GPIO_PULLUP_DIS | GPIO_MODE_IN)
#  define CFG_WRITE(_x)  set_gpio_ctrl(_x | GPIO_PULLUP_DIS | GPIO_MODE_OUT)


#if OV9650_SCCB_DELAY > 0
#  define WAIT_CYL udelay(OV9650_SCCB_DELAY)
#else
#  define WAIT_CYL (void)(0)
#endif

#if OV9650_SCCB_DELAY2 > 0
#  define WAIT_STAB udelay(OV9650_SCCB_DELAY2)
#else
#  define WAIT_STAB (void)(0)
#endif

static unsigned int get_camera_clk(void)
{
	return 24000000;//OV9650_MAX_CLK;
}

/* 2-wire SCCB */
void __inline OV9650_sccb_start(void)
{
	MAKE_HIGH(SIO_C);
	MAKE_HIGH(SIO_D);
	WAIT_STAB;
	MAKE_LOW(SIO_D);
	WAIT_STAB;
	MAKE_LOW(SIO_C);
	WAIT_STAB;
}

/* 2-wire SCCB */
void __inline OV9650_sccb_end(void)
{
	MAKE_LOW(SIO_D);
	WAIT_STAB;
	MAKE_HIGH(SIO_C);
	WAIT_STAB;
	MAKE_HIGH(SIO_D);
	WAIT_STAB;
}

void __inline OV9650_sccb_write_bit(unsigned char bit)
{
	if (bit)
		MAKE_HIGH(SIO_D);
	else
		MAKE_LOW(SIO_D);
	WAIT_STAB;
	MAKE_HIGH(SIO_C);
	WAIT_CYL;
	MAKE_LOW(SIO_C);
	WAIT_STAB;
}

int __inline OV9650_sccb_read_bit(void)
{
	int tmp = 0;

	MAKE_HIGH(SIO_C);
	WAIT_CYL;
	tmp = BIT_READ(SIO_D);
	MAKE_LOW(SIO_C);
	WAIT_STAB;

	return tmp;
}	

void __inline OV9650_sccb_writechar(unsigned char data)
{
	int i = 0;

	/* data */
	for (i = 0; i < 8; i++ ) {
		OV9650_sccb_write_bit(data & 0x80);
		data <<= 1;
	}

	/* 9th bit - Don't care */
	OV9650_sccb_write_bit(1);
}

void __inline OV9650_sccb_readchar(unsigned char *val)
{
	int i;
	int tmp = 0;

	CFG_READ(SIO_D);

	for (i = 7; i >= 0; i--)
		tmp |= OV9650_sccb_read_bit() << i;

	CFG_WRITE(SIO_D);

	/* 9th bit - N.A. */
	OV9650_sccb_write_bit(1);

	*val = tmp & 0xff;
}

/* 3-phase write */
static void OV9650_sccb_sendbyte(unsigned char subaddr, unsigned char data)
{
//	down(&dev.bus_lock);

	OV9650_sccb_start();
	OV9650_sccb_writechar(OV9650_SCCB_ID);
	OV9650_sccb_writechar(subaddr);
	OV9650_sccb_writechar(data);
	OV9650_sccb_end();

	mdelay(7);

//	up(&dev.bus_lock);
}

/* 2-phase read */
static unsigned char OV9650_sccb_receivebyte(unsigned char subaddr)
{
	unsigned char value;

//	down(&dev.bus_lock);

	/* 2-phase write */
	OV9650_sccb_start();
	OV9650_sccb_writechar(OV9650_SCCB_ID);
	OV9650_sccb_writechar(subaddr);
	OV9650_sccb_end();

	/* 2-phase read */
	OV9650_sccb_start();
	OV9650_sccb_writechar(OV9650_SCCB_ID | 0x01);
	OV9650_sccb_readchar(&value);
	OV9650_sccb_end();

	mdelay(7);

	return value;
}

void __inline OV9650_init(void)
{
	CFG_WRITE(SIO_C);
	CFG_WRITE(SIO_D);
	mdelay(10);
}

void __inline OV9650_deinit(void)
{
	CFG_READ(SIO_C);
	CFG_READ(SIO_D);
}

void __inline OV9650_config(void)
{
	int i;

	for (i = 0; i < OV9650_REGS; i++) {
		if (ov9650_reg[i].subaddr == CHIP_DELAY)
			Delay(ov9650_reg[i].value);
			//mdelay(ov9650_reg[i].value);
		else
			OV9650_sccb_sendbyte(ov9650_reg[i].subaddr & 0xff
					, ov9650_reg[i].value & 0xff);
	}
}

int __inline check_OV9650(void)
{
	int ret = 0;
	int OV9650_mid = 0;
	int try_count =0;	//2 times

try_again:
	OV9650_mid = (OV9650_sccb_receivebyte(0x1c) << 8);
	OV9650_mid |= OV9650_sccb_receivebyte(0x1d);
	
	if (OV9650_mid != OV9650_PRODUCT_ID) {
		if (!try_count++) goto try_again;

		printk("Invalid manufacture ID (0x%04X). there is no OV9650(0x%04X)\n",
				OV9650_mid, OV9650_PRODUCT_ID);
		ret = -ENODEV;
	} else {
		//printk("OV9650(0x%04X) detected.\n", OV9650_mid);
	}
	
	//for ov9650
	OV9650_mid = (OV9650_sccb_receivebyte(0x0a) << 8);
	OV9650_mid |= OV9650_sccb_receivebyte(0x0b);
	//printk("Product ID is 0x%04x\n", OV9650_mid);

	return ret;
}

/********* end of OV9650 ********************/

/********** start of S/W YUV2RGB ************/

#define XLATTABSIZE		256
#define MulDiv(x, y, z)		((long)((int) x * (int) y) / (int) z)

//#define CLIP(x)	min_t(int, 255, max_t(int, 0, (x)))
#define CLIP(x) {if(x<0) x=0;if(x>255) x=255;}

#define RED_REGION		0xf800
#define GREEN_REGION		0x07e0
#define BLUE_REGION		0x001f

int XlatY[XLATTABSIZE] = { 0 };
int XlatV_B[XLATTABSIZE] = { 0 };
int XlatV_G[XLATTABSIZE] = { 0 };
int XlatU_G[XLATTABSIZE] = { 0 };
int XlatU_R[XLATTABSIZE] = { 0 };

#define ORIG_XLAT 1
void init_yuvtable (void)
{
	int i, j;

	for (i = 0; i < XLATTABSIZE; i++) {
#if ORIG_XLAT
		j = min(253, max(16, i));
#else
		j = (255 * i + 110) / 220;	// scale up
		j = min(255, max(j, 16));
#endif
		// orig: XlatY[i] = (int ) j;
		XlatY[i] = j-16;
	}

	for (i = 0; i < XLATTABSIZE; i++) {
#if ORIG_XLAT
		j = min(240, max(16, i));
		j -= 128;
#else
		j = i - 128;		// make signed
		if (j < 0)
			j++;			// noise reduction
		j = (127 * j + 56) / 112;	// scale up
		j = min(127, max(-128, j));
#endif

		XlatV_B[i] = MulDiv (j, 1000, 564);	/* j*219/126 */
		XlatV_G[i] = MulDiv (j, 1100, 3328);
		XlatU_G[i] = MulDiv (j, 3100, 4207);
		XlatU_R[i] = MulDiv (j, 1000, 713);
	}
}

#define MORE_QUALITY 1
void __inline yuv_convert_rgb16(unsigned char *rawY, unsigned char *rawU,
	  	unsigned char *rawV, unsigned char *rgb, int size)
{
	unsigned short  buf1, buf3;
	int   red;
	int   blue;
	int   green;
	unsigned long   cnt;
	int    Y, U, V;
	unsigned short  data;
	unsigned short  data2;

	for ( cnt = 0 ; cnt < size; cnt +=2){
		buf1 = *(rawY+cnt) & 0xff;  // Y data
		buf3 = *(rawY+cnt+1) & 0xff;  // Y data

		U = *(rawV+cnt/2) & 0xff;
		V = *(rawU+cnt/2) & 0xff;

#if MORE_QUALITY
		Y = buf1;
#else
		Y = ((buf1+buf3)/2);
#endif

		red = XlatY[Y] + XlatU_R[U];
		CLIP(red);
		green = XlatY[Y] - XlatV_G[V] - XlatU_G[U];
		CLIP(green);
		blue = XlatY[Y] + XlatV_B[V];
		CLIP(blue);

		data = ((red << 8) & RED_REGION)
				| ((green << 3) & GREEN_REGION)
				| (blue >> 3);

#if MORE_QUALITY
		Y = buf3;
		red = XlatY[Y] + XlatU_R[U];
		CLIP(red);
		green = XlatY[Y] - XlatV_G[V] - XlatU_G[U];
		CLIP(green);
		blue = XlatY[Y] + XlatV_B[V];
		CLIP(blue);

		data2 = ((red << 8) & RED_REGION)
				| ((green << 3) & GREEN_REGION)
				| (blue >> 3);
#else
		data2 = data;
#endif

		*(unsigned short *)(rgb + 2 * cnt) = data;
		*(unsigned short *)(rgb + 2 * (cnt + 1))= data2;
	}
}

/********** end of S/W YUV2RGB ******************/

static void s3c2440_cam_gpio_init(void)
{
	//--- changed
	rGPJCON = 0x2aaaaaa;
	rGPJDAT = 0;
	rGPJUP  = 0;	//pull-up enable
}

/* 
 * $\> SW.LEE
 * 
 * OV9650_CLK is 12Mhz or 24Mhz
 *
 * CAMCLK = OV9650_CLK;
 * CAMCLK_DIV =  UPLL / ( CAMCLK * 2)  - 1 ; 
 */ 


void __inline s3c2440_camif_init(void)
{
	unsigned int upll, uclk, camclk,camclk_div;

	camclk = get_camera_clk();
	CLKCON |= CLKCON_CAMIF;
	//--- change above to this
	ChangeUPllValue(56, 2, 1);	//0x38==56
	CLKDIVN |= DIVN_UPLL_EN;	//UCLK=UPLL/2
	upll = 96000000;
	//---
	uclk = (CLKDIVN & DIVN_UPLL_EN) ? upll/2 : upll;
	printk("CAMERA : UPLL %08d  UCLK %08d CAMCLK %08d \n",upll, uclk, camclk);

	camclk_div = upll /( camclk * 2) -1 ;
	CAMDIVN = CAMCLK_SET_DIV | (camclk_div & 0xf ) ;
}

void __inline s3c2440_camif_deinit(void)
{
	CLKCON &= ~CLKCON_CAMIF;
	CAM_CTRL = 0;
	mdelay(5);
}

/***************************************************/
int Test_OV9650(void)
{
	int ret;
	
	init_yuvtable();
	
	s3c2440_cam_gpio_init();
	s3c2440_camif_init();
	
	CamModuleReset();	
	
	OV9650_init();
	
	printk("Check camera ID\n");
	ret = check_OV9650() ;
	if (ret) {
		printk("Can't find camera!\n");
		return ret;
	}
	
	printk("Initial Camera now, Please wait several minutes...\n");
	OV9650_config();
	
	return 0;
}

