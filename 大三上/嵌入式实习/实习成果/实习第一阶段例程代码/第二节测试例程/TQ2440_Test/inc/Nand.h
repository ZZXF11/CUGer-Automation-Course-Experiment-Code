#ifndef __NAND_H
#define __NAND_H

#define NUM_BLOCKS			0x1000	//  64 MB Smartmedia card.
#define SECTOR_SIZE			512
#define SPARE_SIZE			16
#define PAGES_PER_BLOCK			32

//  For flash chip that is bigger than 32 MB, we need to have 4 step address
//  
#define NFCONF_INIT			0xF830  // 512-byte 4 Step Address
#define NEED_EXT_ADDR			1
//#define NFCONF_INIT			0xA830  // 256-byte 4 Step Address
//#define NEED_EXT_ADDR			0

//#define NFCONF_INIT			0xF840

//  NAND Flash Command. This appears to be generic across all NAND flash chips
#define CMD_READ			0x00	//  Read
#define CMD_READ1			0x01	//  Read1
#define CMD_READ2			0x50	//  Read2
#define CMD_READ3			0x30	//  Read3
#define CMD_READID			0x90	//  ReadID
#define CMD_WRITE1			0x80	//  Write phase 1
#define CMD_WRITE2			0x10	//  Write phase 2
#define CMD_ERASE1			0x60	//  Erase phase 1
#define CMD_ERASE2			0xd0	//  Erase phase 2
#define CMD_STATUS			0x70	//  Status read
#define CMD_RESET			0xff	//  Reset

//  Status bit pattern
#define STATUS_READY			0x40	//  Ready
#define STATUS_ERROR			0x01	//  Error

//  Status bit pattern
#define STATUS_READY			0x40
#define STATUS_ERROR			0x01

#define NF_CMD(cmd)			{rNFCMD  = (cmd); }
#define NF_ADDR(addr)			{rNFADDR = (addr); }	
#define NF_nFCE_L()			{rNFCONT &= ~(1<<1); }
#define NF_nFCE_H()			{rNFCONT |= (1<<1); }
#define NF_RSTECC()			{rNFCONT |= (1<<4); }
#define NF_RDMECC()			(rNFMECC0 )
#define NF_RDSECC()			(rNFSECC )
#define NF_RDDATA()			(rNFDATA)
#define NF_RDDATA8()			(rNFDATA8)
#define NF_WRDATA(data)			{rNFDATA = (data); }
#define NF_WAITRB()			{while(!(rNFSTAT&(1<<0)));} 
#define NF_CLEAR_RB()			{rNFSTAT |= (1<<2); }
#define NF_DETECT_RB()			{while(!(rNFSTAT&(1<<2)));}
#define NF_MECC_UnLock()		{rNFCONT &= ~(1<<5); }
#define NF_MECC_Lock()			{rNFCONT |= (1<<5); }
#define NF_SECC_UnLock()		{rNFCONT &= ~(1<<6); }
#define NF_SECC_Lock()			{rNFCONT |= (1<<6); }

#define	RdNFDat8()			(rNFDATA8)	//byte access
#define	RdNFDat()			RdNFDat8()	//for 8 bit nand flash, use byte access
#define	WrNFDat8(dat)			(rNFDATA8 = (dat))	//byte access
#define	WrNFDat(dat)			WrNFDat8()	//for 8 bit nand flash, use byte access

#define pNFCONF				rNFCONF 
#define pNFCMD				rNFCMD  
#define pNFADDR				rNFADDR 
#define pNFDATA				rNFDATA 
#define pNFSTAT				rNFSTAT 
#define pNFECC				rNFECC0  

#define NF_CE_L()			NF_nFCE_L()
#define NF_CE_H()			NF_nFCE_H()
#define NF_DATA_R()			rNFDATA
#define NF_ECC()			rNFECC0

// HCLK=100Mhz
#define TACLS				1	// 1-clk(0ns) 
#define TWRPH0				4	// 3-clk(25ns)
#define TWRPH1				0	// 1-clk(10ns)  //TACLS+TWRPH0+TWRPH1>=50ns


#endif /*__NAND_H*/

