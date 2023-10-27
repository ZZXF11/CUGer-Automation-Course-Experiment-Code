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

/**GPB5--->LED1**
***GPB6--->LED2**
***GPB7--->LED3**/
#define GPB5_out (1<<(5*2))		
#define GPB6_out (1<<(6*2))
#define GPB7_out (1<<(7*2))

/**GPF0--->KEY1**
***GPF1--->KEY2**
***GPF2--->KEY3**/
#define GPF0_EINT (2<<(0*2))
#define GPF1_EINT (2<<(1*2))
#define GPF2_EINT (2<<(2*2))

extern void delay(int);
extern void EnterCritical(unsigned int*);
extern void ExitCritical(unsigned int*);

void init_irq()
{
	//GPFCON = GPF0_EINT | GPF1_EINT | GPF2_EINT;
	GPFCON = GPFCON & (~((3<<4)|(3<<0)|(3<<8)|(3<<2))) | ((2<<4)|(2<<0)|(2<<8)|(2<<2));
	INTMSK = 0xFFF8;	//使能EINT0,EINT1,EINT2
	//INTMSK &= (~(1<<10));	//定时器0使能
	SRCPND = 0xFFFFFFFF;
	INTPND = 0xFFFFFFFF;
	EXTINT0 &= 0xFFFFF000;
	EXTINT0 |= 0x222;	//下降沿触发
}

void init_led()
{
	GPBCON = GPB5_out | GPB6_out | GPB7_out;		//设置I/O口GPB5,GPB6,GPB7为输出属性
	GPBUP = 0xffff;			//禁止GPF端口的上拉
	GPBDAT=0xff;
}

void irq_hander()
{
	unsigned int r;
	unsigned int intoffset = INTOFFSET;
	
	EnterCritical(&r);	//进入临界区，禁止中断
	SRCPND = 1<<intoffset;
	INTPND = 1<<intoffset;
	switch(intoffset)
	{
		case 0:
			delay(5000);
			if((GPFDAT & (1 << 0)) == 0)
				GPBDAT = GPBDAT^(1<<5);	//LED1
			break;
		case 1:
			delay(5000);
			if((GPFDAT & (1 << 1)) == 0)
				GPBDAT = GPBDAT^(1<<6);	//LED2
			break;
		case 2:
			delay(5000);
			if((GPFDAT & (1 << 2)) == 0)
				GPBDAT = GPBDAT^(1<<7);	//LED3
			break;
	}
	ExitCritical(&r);	//退出临界区，打开中断
}