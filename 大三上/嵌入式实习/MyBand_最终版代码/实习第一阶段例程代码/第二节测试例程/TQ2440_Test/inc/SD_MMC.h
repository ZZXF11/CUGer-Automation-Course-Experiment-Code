#ifndef __SD_H__
#define __SD_H__

#define	INICLK		300000
#define	SDCLK		24000000	//PCLK=49.392MHz
#define	MMCCLK		15000000	//PCLK=49.392MHz



/********************************************************
	宏定义
********************************************************/
#define INVALID_CARD	0
#define MMC_CARD		1
#define SD_V1X_CARD		2
#define SDHC_V20_CARD	3

/* SD卡信息结构体定义 */  
/* the information structure variable of SD Card*/ 
typedef struct SD_STRUCT 
{	 
	U8 cCardType;				/* 卡类型 */ 
	U8 cBlockSize;				// 卡的块长度，以为2的2次方表示，如512字节为2的9次方，则该值为9
	U8 cCardCID[16];			// 卡的CID信息
	U16 iCardRCA;				/* 卡逻辑地址 */ 
	U32 lCardCSD[4];			// 卡的CSD信息
	U32 lBlockNum;				/* 卡中块的数量 */ 
	U32 lBlockLen;				/* 卡的块长度(单位:字节) */ 
	U32 lSectorSize;			/* 一次可擦除的块个数 */ 
	U32 lCardSize;				//卡容量(单位:字节)
	
	 
	U32 timeout_read;			/* 读块超时时间(单位: 8 SPI clock) */ 
	U32 timeout_write;			/* 写块超时时间(单位: 8 SPI clock) */ 
	U32 timeout_erase;			/* 擦块超时时间(单位: 8 SPI clock) */ 
}sSD_struct; 








int Chk_CMD_End(int cmd, int be_resp);
void CMD0(void);
U8 CMD1(void);
U8 CMD8(void);
U8 CMD55(U16 iRCA);
U8 ACMD41(U16 iRCA)	;
U8 CMD2(U8 *cCID_Info);
U8 CMD3(U16 iCardType,U16 *iRCA);
U8 CMD7(U8 cSorD,U16 iRCA);
U16 CMD13(U16 iRCA)	;
U8 ACMD6(U8 BusWidth,U16 iRCA);
U8 CMD9(U16 iRCA,U32 *lCSD)	;
U8 CMD17(U32 Addr);
U8 CMD18(U32 Addr);
U8 CMD12(void);
U8 CMD24(U32 Addr);
U8 CMD25(U32 Addr);
U8 CMD32(U32 Addr);
U8 CMD33(U32 Addr);
U8 CMD38(void);

U8 Card_sel_desel(U8 cSelDesel,U16 iCardRCA);
U8 Set_bus_Width(U8 cCardType,U8 cBusWidth,U16 iRCA);
U8 SDinit(void);
U8 Read_One_Block(U32 Addr,U32* RxBuffer);
U8 Write_One_Block(U32 Addr,U32* TxBuffer);
U8 Read_Mult_Block(U32 Addr,U32 DatSize,U32* RxBuffer);
U8 Write_Mult_Block(U32 Addr,U32 DatSize,U32* TxBuffer);
U8 Erase_Block(U32 StartAddr,U32 EndAddr);
#endif

