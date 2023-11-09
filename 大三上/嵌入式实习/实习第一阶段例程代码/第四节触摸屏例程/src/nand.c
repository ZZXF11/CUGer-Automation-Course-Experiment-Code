/*
 support 512 page and 2048 page NAND Flash
*/
#include <string.h>

#include "def.h"
#include "2440addr.h"
#include "2440lib.h"
#include "2440slib.h"
#include "Nand.h"


//
//  Reset the chip
//
static void rNF_Reset()
{
	NF_CE_L();
	NF_CLEAR_RB();
	NF_CMD(CMD_RESET);  
	NF_DETECT_RB();
	NF_CE_H();
}


static void rNF_Init(void)
{
	rNFCONF = (TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4)|(0<<0);
	rNFCONT = (0<<13)|(0<<12)|(0<<10)|(0<<9)|(0<<8)|(1<<6)|(1<<5)|(1<<4)|(1<<1)|(1<<0);
	rNFSTAT = 0;
	rNF_Reset();
}

static char rNF_ReadID()
{
	char	pMID;
	char	pDID;
	char	nBuff;
	char	n4thcycle;
	int	i;


	NF_nFCE_L();    
	NF_CLEAR_RB();
	NF_CMD(CMD_READID);	// read id command
	NF_ADDR(0x0);
	for ( i = 0; i < 100; i++ );

	pMID = NF_RDDATA8();
	pDID = NF_RDDATA8();

	nBuff     = NF_RDDATA8();
	n4thcycle = NF_RDDATA8();
	NF_nFCE_H();


	return (pDID);
}

static void rSB_ReadPage(U32 addr, unsigned char * to)
{
	U32 i;

	rNF_Reset();

	//  Enable the chip
	NF_nFCE_L();
	NF_CLEAR_RB();

	// Issue Read command
	NF_CMD(CMD_READ);

	//  Set up address
	NF_ADDR(0x00);
	NF_ADDR((addr) & 0xff);
	NF_ADDR((addr >> 8) & 0xff);
	NF_ADDR((addr >> 16) & 0xff);


	NF_DETECT_RB();		// wait tR(max 12us)

	for (i = 0; i < 512; i++)
	{
		to[i] =  NF_RDDATA8();
	}

	NF_nFCE_H();

}

static void rLB_ReadPage(U32 addr, unsigned char * to)
{
	U32 i;

	rNF_Reset();

	//  Enable the chip
	NF_nFCE_L();   
	NF_CLEAR_RB();

	// Issue Read command
	NF_CMD(CMD_READ);

	//  Set up address
	NF_ADDR(0x00);
	NF_ADDR(0x00);
	NF_ADDR((addr) & 0xff);
	NF_ADDR((addr >> 8) & 0xff);
	NF_ADDR((addr >> 16) & 0xff);

	NF_CMD(CMD_READ3);

	NF_DETECT_RB();		// wait tR(max 12us)

	for (i = 0; i < 2048; i++)
	{
		to[i] =  NF_RDDATA8();
	}

	NF_nFCE_H();

}


void RdNF2SDRAM( )
{
	U32 i;
	U32 start_addr = 0x0;
	unsigned char * to = (unsigned char *)0x30000000;
	U32 size = 0x100000;
	rNF_Init();
	switch(rNF_ReadID())
	{
		case 0x76:
			for(i = (start_addr >> 9); size > 0; )
			{
				rSB_ReadPage(i, to);
				size -= 512;
				to += 512;
				i ++;
			}
			break;
		case 0xf1:
		case 0xda:
		case 0xdc:
		case 0xd3:
			for(i = (start_addr >> 11); size > 0; )
			{
				rLB_ReadPage(i, to);
				size -= 2048;
				to += 2048;
				i ++;
			}
			break;
	}
}		


