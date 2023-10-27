/*C语言函数
*/
/*寄存器地址*/
#define GPBCON		(*(volatile unsigned *)0x56000010)
#define GPBDAT		(*(volatile unsigned *)0x56000014)
#define GPBUP		(*(volatile unsigned *)0x56000018)
#define GPFCON		(*(volatile unsigned *)0x56000050)
#define GPFDAT		(*(volatile unsigned *)0x56000054)
#define GPFUP		(*(volatile unsigned *)0x56000058)
#define SRCPND		(*(volatile unsigned *)0x4A000000)
#define INTMSK		(*(volatile unsigned *)0x4A000008)
#define INTPND		(*(volatile unsigned *)0x4A000010)
#define INTOFFSET	(*(volatile unsigned *)0x4A000014)
#define TCFG0		(*(volatile unsigned *)0x51000000)
#define TCFG1		(*(volatile unsigned *)0x51000004)
#define TCON		(*(volatile unsigned *)0x51000008)
#define TCNTB0		(*(volatile unsigned *)0x5100000C)
#define EXTINT0		(*(volatile unsigned *)0x56000088)
#define EINTPEND   (*(volatile unsigned long *)0x560000A8)

#define EINTMASK   (*(volatile unsigned long *)0x560000A4)

/**GPB5--->LED1**
***GPB6--->LED2**
***GPB7--->LED3**/
#define GPB5_out (1<<(5*2))		
#define GPB6_out (1<<(6*2))
#define GPB7_out (1<<(7*2))
#define GPB8_out (1<<(8*2))


/**GPF0--->KEY4**
***GPF1--->KEY1**
***GPF2--->KEY3**
***GPF4--->KEY2**/
#define GPF0_EINT (2<<(0*2))
#define GPF1_EINT (2<<(1*2))
#define GPF2_EINT (2<<(2*2))
#define GPF4_EINT (2<<(4*2))*

#define GPF0_int     (0x2<<(0*2))
#define GPF1_int     (0x2<<(1*2))
#define GPF2_int     (0x2<<(2*2))
#define GPF4_int     (0x2<<(4*2))

#define GPF0_msk    (3<<(0*2))
#define GPF1_msk    (3<<(1*2))
#define GPF2_msk    (3<<(2*2))
#define GPF4_msk    (3<<(4*2))



extern void delay(int);
extern void EnterCritical(unsigned int*);
extern void ExitCritical(unsigned int*);

void init_irq()
{
	//GPFCON = GPF0_EINT | GPF1_EINT | GPF2_EINT | GPF4_EINT;
	
	GPFCON &= ~(GPF0_msk | GPF1_msk | GPF2_msk | GPF4_msk); 
	GPFCON |= GPF0_int | GPF1_int | GPF2_int | GPF4_int;

	// 对于EINT4，需要在EINTMASK寄存器中使能它,EINT4下面还有次中断，实际的中断源来自次中断.
    EINTMASK &= ~(1<<4);


	//INTMSK = 0xFFE8;	//使能EINT0,EINT1,EINT2,EINT4
	// EINT0、EINT1、EINT2、EINT4_使能
    INTMSK &= (~(1<<0)) & (~(1<<1)) & (~(1<<2)) & (~(1<<4));

	
	
	//INTMSK &= (~(1<<10));	//定时器0使能
	SRCPND = 0xFFFFFFFF;
	INTPND = 0xFFFFFFFF;
	
	EXTINT0 |= 0x20222;	//下降沿触发
}

void init_led()
{
	 // LED0,LED1,LED2、LED4对应的4根引脚设为输出
	GPBCON = GPB5_out | GPB6_out | GPB7_out|GPB8_out;		//设置I/O口GPB5,GPB6,GPB7,GPB8为输出属性
	
	GPBUP = 0xffff;			
	GPBDAT=0x1ff;
}

void irq_hander()
{
	unsigned int r;
	unsigned int intoffset = INTOFFSET;
	
	EnterCritical(&r);	//进入临界区，禁止中断
	
	
	switch(intoffset)
	{
		case 1:
			delay(5000);
			if((GPFDAT & (1 << 1)) == 0)        
				GPBDAT = GPBDAT^(1<<5);	//LED1-K1
			break;
		
		case 4:
			delay(5000);
			if((GPFDAT & (1 << 4)) == 0)         
				GPBDAT = GPBDAT^(1<<6);	//LED2- K2
			break;
		
		case 2:
			delay(5000);
			if((GPFDAT & (1 << 2)) == 0)
				GPBDAT = GPBDAT^(1<<7);	//LED3-K3
			break;
			
		case 0:
			delay(5000);
			if((GPFDAT & (1 << 0)) == 0)
				GPBDAT = GPBDAT^(1<<8);	//LED3-K3
			break;
			
			
	}
	ExitCritical(&r);	//退出临界区，打开中断
	if(intoffset == 4)
		EINTPEND = 1 << 4;
	SRCPND = 1<<intoffset;
	INTPND = 1<<intoffset;
	
}
