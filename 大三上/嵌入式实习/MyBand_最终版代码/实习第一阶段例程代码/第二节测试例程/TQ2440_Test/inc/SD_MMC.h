#ifndef __SD_H__
#define __SD_H__

#define	INICLK		300000
#define	SDCLK		24000000	//PCLK=49.392MHz
#define	MMCCLK		15000000	//PCLK=49.392MHz



/********************************************************
	�궨��
********************************************************/
#define INVALID_CARD	0
#define MMC_CARD		1
#define SD_V1X_CARD		2
#define SDHC_V20_CARD	3

/* SD����Ϣ�ṹ�嶨�� */  
/* the information structure variable of SD Card*/ 
typedef struct SD_STRUCT 
{	 
	U8 cCardType;				/* ������ */ 
	U8 cBlockSize;				// ���Ŀ鳤�ȣ���Ϊ2��2�η���ʾ����512�ֽ�Ϊ2��9�η������ֵΪ9
	U8 cCardCID[16];			// ����CID��Ϣ
	U16 iCardRCA;				/* ���߼���ַ */ 
	U32 lCardCSD[4];			// ����CSD��Ϣ
	U32 lBlockNum;				/* ���п������ */ 
	U32 lBlockLen;				/* ���Ŀ鳤��(��λ:�ֽ�) */ 
	U32 lSectorSize;			/* һ�οɲ����Ŀ���� */ 
	U32 lCardSize;				//������(��λ:�ֽ�)
	
	 
	U32 timeout_read;			/* ���鳬ʱʱ��(��λ: 8 SPI clock) */ 
	U32 timeout_write;			/* д�鳬ʱʱ��(��λ: 8 SPI clock) */ 
	U32 timeout_erase;			/* ���鳬ʱʱ��(��λ: 8 SPI clock) */ 
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

