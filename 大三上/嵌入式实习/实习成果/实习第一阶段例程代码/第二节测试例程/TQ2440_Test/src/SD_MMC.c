#include <stdio.h>
#include <string.h>
#include "def.h"
#include "option.h"
#include "2440addr.h"
#include "2440lib.h"
#include "SD_MMC.h"

/********************************************************
	�궨��
********************************************************/
#define __SD_MMC_DEBUG__
#define SDCard_BlockSize	9
#define SDCARD_BUFF_SIZE	512
/********************************************************
	��������
********************************************************/
volatile int iSD_MMC_RCA;
sSD_struct SDCard;
U8 cTxBuffer[SDCARD_BUFF_SIZE];
U8 cRxBuffer[SDCARD_BUFF_SIZE];

/********************************************************
	TEST API
********************************************************/
#ifdef __SD_MMC_DEBUG__
void Test_SDI(void)
{
	U16 i;
	
	if(SDinit())
	{
		#ifdef __SD_MMC_DEBUG__
		Uart_Printf("����ʼ����ϣ�\n");
		#endif
	}
	else
	{
		#ifdef __SD_MMC_DEBUG__
		Uart_Printf("����ʼ��ʧ�ܣ�\n");
		#endif
		return;
	}
	
//	if(Read_One_Block(8192*2,(U32 *)cRxBuffer))
//	{
//		for(i=0;i<512;)
//		{
//			Uart_Printf("%02x ",cRxBuffer[i+3]);
//			Uart_Printf("%02x ",cRxBuffer[i+2]);
//			Uart_Printf("%02x ",cRxBuffer[i+1]);
//			Uart_Printf("%02x ",cRxBuffer[i+0]);
//			i += 4;
//			if(i%16==0)
//				Uart_Printf("\n");
//		}
//		Uart_Printf("\nRead 8192 Block is OK!\n");
//	}
//	else
//	{
//		Uart_Printf("\nRead 8192 Block is Fail!\n");
//	}
	
	
//	for(i=0;i<SDCARD_BUFF_SIZE;i++)
//	{
//		cRxBuffer[i] = 0xff;
//	}
	
//	if(Write_One_Block(4096,(U32 *)cRxBuffer))
//	{
//		Uart_Printf("\nWrite 4096 Block is OK!\n");
//	}
//	else
//	{
//		Uart_Printf("\nWrite 4096 Block is Fail!\n");
//	}
	
	for(i=0;i<SDCARD_BUFF_SIZE;i++)
	{
		cRxBuffer[i] = 0x00;
	}
	
	if(Read_One_Block(4096,(U32 *)cRxBuffer))
	{
		for(i=0;i<512;)
		{
			Uart_Printf("%02x ",cRxBuffer[i+3]);
			Uart_Printf("%02x ",cRxBuffer[i+2]);
			Uart_Printf("%02x ",cRxBuffer[i+1]);
			Uart_Printf("%02x ",cRxBuffer[i+0]);
			i += 4;
			if(i%16==0)
				Uart_Printf("\n");
		}
		Uart_Printf("\nRead 4096 Block is OK!\n");
	}
	else
	{
		Uart_Printf("\nRead 4096 Block is Fail!\n");
	}
	
	
}
#endif

/********************************************************
	API����
********************************************************/

/**********************************************
���ܣ����SDIO����ͣ������Ƿ����
��ڣ�cmd:���� be_resp��=1��Ӧ�� =0��Ӧ��
���ڣ�=0Ӧ��ʱ =1ִ�гɹ�
˵������
**********************************************/
int Chk_CMD_End(int cmd, int be_resp)
{
	int finish0;

	if(!be_resp)    // No response
	{
		finish0 = rSDICSTA;
		while((finish0&0x800)!=0x800)	// Check cmd end
		finish0=rSDICSTA;

		rSDICSTA=finish0;// Clear cmd end state

		return 1;
	}
	else			// With response
	{
		finish0=rSDICSTA;
		while( !( ((finish0&0x200)==0x200) | ((finish0&0x400)==0x400) ))    // Check cmd/rsp end
			finish0=rSDICSTA;

		if(cmd==1 | cmd==41)	// CRC no check, CMD9 is a long Resp. command.
		{
			if( (finish0&0xf00) != 0xa00 )  // Check error
			{
				rSDICSTA=finish0;   // Clear error state

				if(((finish0&0x400)==0x400))
				return 0;	// Timeout error
			}
			rSDICSTA=finish0;		// Clear cmd & rsp end state
		}
		else				// CRC check
		{
			if( (finish0&0x1f00) != 0xa00 )	// Check error
			{
				#ifdef __SD_MMC_DEBUG__
				Uart_Printf("CMD%d:rSDICSTA=0x%x, rSDIRSP0=0x%x\n",cmd, rSDICSTA, rSDIRSP0);
				#endif
				rSDICSTA = finish0;			// Clear error state

				if(((finish0&0x400)==0x400))
					return 0;				// Timeout error
			}
			rSDICSTA=finish0;
		}
		return 1;
	}
}

/**********************************************
���ܣ�ʹ������IDEL״̬
��ڣ���
���ڣ���
˵������
**********************************************/
void CMD0(void)
{
	rSDICARG = 0x0;	
	rSDICCON = (1<<8)|0x40;		// No_resp, start

	Chk_CMD_End(0, 0);
	rSDICSTA = 0x800;			// Clear cmd_end(no rsp)
}

/**********************************************
���ܣ�MMC�����
��ڣ���
���ڣ�=1:MMC�� =0:��MMC��
˵������
**********************************************/
U8 CMD1(void)
{
	rSDICARG = 0xff8000;					//(SD OCR:2.7V~3.6V)
	rSDICCON = (0x1<<9)|(0x1<<8)|0x41; 		//sht_resp, wait_resp, start, 

	if(Chk_CMD_End(1, 1)) 		//[31]:Card Power up status bit (busy)
	{
		if((rSDIRSP0>>16)==0x80ff)
		{
			rSDICSTA = 0xa00;	// Clear cmd_end(with rsp)
			return 1;			// Success
		}
		else
			return 0;
	}
	return 0;
}

/**********************************************
���ܣ���⿨���͡��̼��汾��������ѹ״��
��ڣ���
���ڣ�	=1��SD V1.X��MMC
		=2����׼SD����SDHC V2.0  
		=0����Ч��
˵������
**********************************************/
U8 CMD8(void)	
{
	rSDICARG = 0x000001AA;
	rSDICCON = (0x1<<9)|(0x1<<8)|0x48;	//sht_resp, wait_resp, start

	if(!Chk_CMD_End(8, 1)) 
		return 1;
		
	rSDICSTA = 0xa00;					// Clear cmd_end(with rsp)
	
	if((rSDIRSP0&0x1aa)==0x1aa)
		return 2;		
	else
		return 0;
}

/**********************************************
���ܣ���⿨�Ƿ����
��ڣ�iRCA:RCA
���ڣ�=0���ɹ� =1��ʧ��
˵������
**********************************************/
U8 CMD55(U16 iRCA)	
{
	rSDICARG = iRCA<<16;
	rSDICCON = (0x1<<9)|(0x1<<8)|0x77;	//sht_resp, wait_resp, start

	if(!Chk_CMD_End(55, 1)) 
		return 0;
		
	rSDICSTA = 0xa00;					// Clear cmd_end(with rsp)
	return 1;
}
/**********************************************
���ܣ����SD���ϵ�״̬
��ڣ�iRCA:RCA
���ڣ�=0Ӧ�������߿���æ
	  =1��׼SD��
	  =2SDHC V2.0
˵������
**********************************************/
U8 ACMD41(U16 iRCA)	
{
	U8 cReturn;
	
	if(!CMD55(iRCA))			
		return 0;
	
	rSDICARG=0x40ff8000;	//ACMD41(SD OCR:2.7V~3.6V)
	//rSDICARG=0xffc000;	//ACMD41(MMC OCR:2.6V~3.6V)
	rSDICCON=(0x1<<9)|(0x1<<8)|0x69;//sht_resp, wait_resp, start, ACMD41

	if(Chk_CMD_End(41, 1)) 
	{
		if(rSDIRSP0==0xc0ff8000)
			cReturn = 2;	//SDHC
		else if(rSDIRSP0==0x80ff8000)
			cReturn = 1;	//��׼SD
		else
			cReturn = 0;	//Ӧ�����
		
		rSDICSTA = 0xa00;	// Clear cmd_end(with rsp)
		return cReturn;	// Success	    
	}
	
	rSDICSTA = 0xa00;	// Clear cmd_end(with rsp)
	return 0;
}
/**********************************************
���ܣ���ȡ����CID�Ĵ���������
��ڣ���
���ڣ�=0ʧ�� =1�ɹ�
˵������
**********************************************/
U8 CMD2(U8 *cCID_Info)	
{
	rSDICARG = 0x0;
	rSDICCON = (0x1<<10)|(0x1<<9)|(0x1<<8)|0x42; //lng_resp, wait_resp, start

	if(!Chk_CMD_End(2, 1)) 
		return 0;
	
	*(cCID_Info+0) = rSDIRSP0>>24;
	*(cCID_Info+1) = rSDIRSP0>>16;
	*(cCID_Info+2) = rSDIRSP0>>8;
	*(cCID_Info+3) = rSDIRSP0;
	*(cCID_Info+4) = rSDIRSP1>>24;
	*(cCID_Info+5) = rSDIRSP1>>16;
	*(cCID_Info+6) = rSDIRSP1>>8;
	*(cCID_Info+7) = rSDIRSP1;
	*(cCID_Info+8) = rSDIRSP2>>24;
	*(cCID_Info+9) = rSDIRSP2>>16;
	*(cCID_Info+10) = rSDIRSP2>>8;
	*(cCID_Info+11) = rSDIRSP2;
	*(cCID_Info+12) = rSDIRSP3>>24;
	*(cCID_Info+13) = rSDIRSP3>>16;
	*(cCID_Info+14) = rSDIRSP3>>8;
	*(cCID_Info+15) = rSDIRSP3;
	
	rSDICSTA = 0xa00;			// Clear cmd_end(with rsp)
	return 1;
}
/**********************************************
���ܣ���SD���趨һ����ַ(RCA)
��ڣ�iCardType = 0:SD����=1:MMC��
���ڣ�=0 ʧ�� =1 �ɹ�
˵������
**********************************************/
U8 CMD3(U16 iCardType,U16 *iRCA)	
{
	rSDICARG = iCardType<<16;	    	// (MMC:Set RCA, SD:Ask RCA-->SBZ)
	rSDICCON = (0x1<<9)|(0x1<<8)|0x43;	// sht_resp, wait_resp, start

	if(!Chk_CMD_End(3, 1)) 
		return 0;
		
	rSDICSTA=0xa00;						// Clear cmd_end(with rsp)

	if(iCardType)
	{
		*iRCA = 1;
	}
	else 
    {
		*iRCA =( rSDIRSP0 & 0xffff0000 )>>16;
	}
	
	if( rSDIRSP0 & 0x1e00!=0x600 )  	// CURRENT_STATE check
		return 0;
	else
		return 1;
}
/**********************************************
���ܣ��ÿ�����ѡ��״̬
��ڣ�cSorD = 0:����ҪӦ�� = 1��ҪӦ��
���ڣ���
˵������
**********************************************/
U8 CMD7(U8 cSorD,U16 iRCA)	
{
	if(cSorD)
	{
		rSDICARG = iRCA<<16;				// (RCA,stuff bit)
		rSDICCON = (0x1<<9)|(0x1<<8)|0x47;   // sht_resp, wait_resp, start
	
		if(!Chk_CMD_End(7, 1))
			return 0;
			
		rSDICSTA = 0xa00;	// Clear cmd_end(with rsp)
	
		//--State(transfer) check
		if( rSDIRSP0 & 0x1e00!=0x800 )
			return 0;
		else
			return 1;
	}
	else
	{
		rSDICARG = 0<<16;		//(RCA,stuff bit)
		rSDICCON = (0x1<<8)|0x47;	//no_resp, start

		if(!Chk_CMD_End(7, 0))
			return 0;
		rSDICSTA = 0x800;		//Clear cmd_end(no rsp)
		return 1;
	}
}
/**********************************************
���ܣ���ȡ����״̬
��ڣ���
���ڣ���״̬��0ֵ
˵������
**********************************************/
U16 CMD13(U16 iRCA)	
{
	rSDICARG = iRCA<<16;				// (RCA,stuff bit)
	rSDICCON = (0x1<<9)|(0x1<<8)|0x4d;	// sht_resp, wait_resp, start

	if(!Chk_CMD_End(13, 1)) 
		return 0;

	rSDICSTA=0xa00;	// Clear cmd_end(with rsp)
	return rSDIRSP0;
}

/**********************************************
���ܣ��趨��������λ��
��ڣ�BusWidth =0��1bit =1��4bit
		iRCA:RCA
���ڣ�=0��ʧ�� =1���ɹ�
˵������
**********************************************/
U8 ACMD6(U8 BusWidth,U16 iRCA)	
{
	if(!CMD55(iRCA))
		return 0;

	rSDICARG = BusWidth<<1;	    		//Wide 0: 1bit, 1: 4bit
	rSDICCON = (0x1<<9)|(0x1<<8)|0x46;	//sht_resp, wait_resp, start

	if(!Chk_CMD_End(6, 1)) 
		return 0;
	rSDICSTA=0xa00;	    				// Clear cmd_end(with rsp)
	return 1;
}
/**********************************************
���ܣ���ȡ����CSD�Ĵ�����ֵ
��ڣ�iRCA:����RCA lCSD����ȡ��CSD����
���ڣ�=0ʧ�� =1�ɹ�
˵������
**********************************************/
U8 CMD9(U16 iRCA,U32 *lCSD)	
{
	rSDICARG = iRCA<<16;					// (RCA,stuff bit)
	rSDICCON = (0x1<<10)|(0x1<<9)|(0x1<<8)|0x49;	// long_resp, wait_resp, start

	if(!Chk_CMD_End(9, 1)) 
		return 0;

	*(lCSD+0) = rSDIRSP0;
	*(lCSD+1) = rSDIRSP1;
	*(lCSD+2) = rSDIRSP2;
	*(lCSD+3) = rSDIRSP3;
	return 1;
}

/**********************************************
���ܣ���ȡһ�����ݿ�
��ڣ���ʼ��ַ
���ڣ�=1���ɹ� =0��ʧ��
˵������
**********************************************/
U8 CMD17(U32 Addr)	
{
    //STEP1:����ָ�� 
    rSDICARG = Addr;				//�趨ָ����� 
    rSDICCON = (1<<9)|(1<<8)|0X51;	//����CMD17ָ��
    
    if(Chk_CMD_End(17,1))
    	return 1;
    else
    	return 0;
}
/**********************************************
���ܣ���ȡ������ݿ�
��ڣ���ʼ��ַ
���ڣ�=1���ɹ� =0��ʧ��
˵������
**********************************************/
U8 CMD18(U32 Addr)	
{
    //STEP1:����ָ�� 
    rSDICARG = Addr;				//�趨ָ����� 
    rSDICCON = (1<<9)|(1<<8)|0X52;	//����CMD17ָ��
    
    if(Chk_CMD_End(18,1))
    	return 1;
    else
    	return 0;
}
/**********************************************
���ܣ�ֹͣ���ݴ���
��ڣ���
���ڣ�=1���ɹ� =0��ʧ��
˵������
**********************************************/
U8 CMD12(void)	
{
	rSDICARG = 0x0;	    
	rSDICCON = (0x1<<9)|(0x1<<8)|0x4c;	//sht_resp, wait_resp, start,

	if(!Chk_CMD_End(12, 1)) 
		return 0;
	else
		rSDICSTA = 0xa00;				//Clear cmd_end(with rsp)
	return 1;
}
/**********************************************
���ܣ�д��һ�����ݿ�
��ڣ���
���ڣ�=1���ɹ� =0��ʧ��
˵������
**********************************************/
U8 CMD24(U32 Addr)	
{
    //STEP1:����ָ�� 
    rSDICARG = Addr;				//�趨ָ����� 
    rSDICCON = (1<<9)|(1<<8)|0x58;	//����CMD24ָ��
    
    if(Chk_CMD_End(24,1))
    	return 1;
    else
    	return 0;
}
/**********************************************
���ܣ�д�������ݿ�
��ڣ���
���ڣ�=1���ɹ� =0��ʧ��
˵������
**********************************************/
U8 CMD25(U32 Addr)	
{
    //STEP1:����ָ�� 
    rSDICARG = Addr;				//�趨ָ����� 
    rSDICCON = (1<<9)|(1<<8)|0x59;	//����CMD25ָ��
    
    if(Chk_CMD_End(25,1))
    	return 1;
    else
    	return 0;
}
/**********************************************
���ܣ����ò�����ʼ��ַ
��ڣ���
���ڣ�=1���ɹ� =0��ʧ��
˵������
**********************************************/
U8 CMD32(U32 Addr)	
{
    //STEP1:����ָ�� 
    rSDICARG = Addr;				//�趨ָ����� 
    rSDICCON = (1<<9)|(1<<8)|0x60;	//����CMD32ָ��
    
    if(Chk_CMD_End(32,1))
    	return 1;
    else
    	return 0;
}
/**********************************************
���ܣ����ò�����ֹ��ַ
��ڣ���
���ڣ�=1���ɹ� =0��ʧ��
˵������
**********************************************/
U8 CMD33(U32 Addr)	
{ 
    //STEP1:����ָ�� 
    rSDICARG = Addr;				//�趨ָ����� 
    rSDICCON = (1<<9)|(1<<8)|0x61;	//����CMD33ָ��
    
    if(Chk_CMD_End(33,1))
    	return 1;
    else
    	return 0;
}
/**********************************************
���ܣ���������ָ�����������
��ڣ���
���ڣ�=1���ɹ� =0��ʧ��
˵������
**********************************************/
U8 CMD38(void)		
{ 
    //STEP1:����ָ�� 
    rSDICARG = 0;					//�趨ָ����� 
    rSDICCON = (1<<9)|(1<<8)|0x66;	//����CMD38ָ��
    
    if(Chk_CMD_End(38,1))
    	return 1;
    else
    	return 0;
}


/**********************************************
���ܣ��������߽���SD��
��ڣ�cSelDesel = 1:���� =0����
       iCardRCA: CARD RCA
���ڣ�=1���ɹ� =0��ʧ��
˵������
**********************************************/
U8 Card_sel_desel(U8 cSelDesel,U16 iCardRCA)
{
	if(CMD7(cSelDesel,iCardRCA))
		return 1;
	else
		return 0;
}


/**********************************************
���ܣ����ÿ�ͨ�ſ��
��ڣ�cCardType ������
      cBusWidth =0��1bit =1��4bit
���ڣ�=1���ɹ� =0��ʧ��
˵������
**********************************************/
U8 Set_bus_Width(U8 cCardType,U8 cBusWidth,U16 iRCA)
{
	if(cCardType==MMC_CARD)
		return 0;
	
	return ACMD6(cBusWidth,iRCA);
}




/**********************************************************************************
��  �ܣ��ú������ڴ�SD���ж���ָ������ʼ��ַ�ĵ������ݿ�
��  ����
 U32  Addr  ���������ʼ��ַ
 U32* RxBuffer ���ڽ��ն������ݵĻ�����
����ֵ��
 0 ����������ɹ�
 1 ��������ɹ�
��  ����
 �����������ж���һ��������Ϊ���ջ���������U32 Rx_buffer[BlockSize];
 Ȼ��ʼ����Read_One_Block(addr,Rx_buffer);
**********************************************************************************/
U8 Read_One_Block(U32 Addr,U32* RxBuffer)
{
	U16 i=0;
	U32 status=0;
	U16 BlockSize;			//������С
	BlockSize=(1<<(SDCard_BlockSize-2)); 	//��WordΪ��λ


	rSDIDTIMER=0x7fffff;		// Set timeout count
	rSDIBSIZE=0x200;			// 512byte(128word)
	rSDIFSTA=rSDIFSTA|(1<<16);	// FIFO reset
	rSDIDCON=(1<<SDCard_BlockSize)|(2<<12)|(1<<14)|(1<<16)|(1<<17)|(1<<19)|(2<<22);
	
	if(CMD17(Addr)!=1)		//���Ͷ�������ָ��
 		return 0;
 
	while(i<BlockSize)
	{ //��ʼ�������ݵ�������
		if(rSDIDSTA&0x60)
		{ //����Ƿ�ʱ��CRCУ���Ƿ����
			rSDIDSTA=(0x3<<0x5); //�����ʱ��־��CRC�����־
			return 0;
		}
		status=rSDIFSTA;
		if((status&0x1000)==0x1000)
		{ //�������FIFO��������
			*RxBuffer=rSDIDAT;
			RxBuffer++;
			i++;
		}
	}
 
	rSDIDCON=rSDIDCON&~(7<<12);
	return 1;
}


/********************************************************************************** 
�� �ܣ��ú������ڴ� SD ���ж���ָ������ʼ��ַ�����ݿ���Ŀ�Ķ���������ݿ飬��Ҫ��ȡ�� 
����������ʱ��ֹͣ��ȡ�� 
�� ���� 
U32 Addr ���������ʼ��ַ 
U32 DatSize �ڴ���������������Ŀ���� Word Ϊ��λ 
U32* RxBuffer ���ڽ��ն������ݵĻ����� 
����ֵ�� 
0 ����������ɹ� 
1 ��������ɹ� 
�� ���� 
�����������ж���һ��������Ϊ���ջ��������� U32 Rx_buffer[BufferSize]; 
Ȼ��ʼ���� Read_Mult_Block(addr,BufferSize,Rx_buffer); 
**********************************************************************************/ 
U8 Read_Mult_Block(U32 Addr,U32 DatSize,U32* RxBuffer)
{ 
	U32 i = 0; 
	U32 status = 0; 

	rSDIDTIMER=0x7fffff;		// Set timeout count
	rSDIBSIZE=0x200;			// 512byte(128word)
	rSDIFSTA = rSDIFSTA|(1<<16); // FIFO reset 
	rSDIDCON = (1<<SDCard_BlockSize)|(2<<12)|(1<<14)|(1<<16)|(1<<17)|(1<<19)|(2<<22); 
	
	if(CMD18(Addr)!=1)//���Ͷ�������ָ�� 
		return 0;
	
	while(i<DatSize)
	{//�������ݵ������� 
		if(rSDIDSTA&0x60)
		{//����Ƿ�ʱ�� CRC �Ƿ���� 
			rSDIDSTA = (0x3<<0x5);//�����ʱ��־�� CRC �����־ 
			return 0; 
		} 
		status = rSDIFSTA; 
		if((status&0x1000)==0x1000)
		{//������� FIFO �������� 
			*RxBuffer = rSDIDAT; 
			RxBuffer++; 
			i++; 
		} 
	} 
	rSDIDCON = rSDIDCON&~(7<<12); 
	rSDIFSTA = rSDIFSTA&0x200;//Clear Rx FIFO Last data Ready 
	rSDIDSTA = 0x10;//Clear data Tx/Rx end detect 
	
	while(CMD12()!=1);//���ͽ���ָ�� 
	return 1;
}


/**********************************************************************************
��  �ܣ��ú���������SD����һ�����ݿ�д������
��  ����
 U32  Addr  ��д�����ʼ��ַ
 U32* TxBuffer ���ڷ������ݵĻ�����
����ֵ��
 0 ����д�����ʧ��
 1 ����д������ɹ�
��  ����
 �����������ж���һ��������Ϊ���ͻ���������U32 Tx_buffer[BlockSize];
 Ȼ��ʼ����Write_One_Block(addr,Tx_buffer);
**********************************************************************************/
U8 Write_One_Block(U32 Addr,U32* TxBuffer)
{
	U16 i=0;
	U32 status = 0;
	U16 BlockSize; //������С
	
	BlockSize = (1<<(SDCard_BlockSize-2)); //��WordΪ��λ

	rSDIDTIMER=0x7fffff;		// Set timeout count
	rSDIBSIZE=0x200;			// 512byte(128word)
	rSDIFSTA = rSDIFSTA|(1<<16); // FIFO reset
	rSDIDCON = (1<<SDCard_BlockSize)|(3<<12)|(1<<14)|(1<<16)|(1<<17)|(1<<20)|(2<<22);
	rSDIDCON = (1<<SDCard_BlockSize)|(3<<12)|(1<<14)|(1<<16)|(1<<17)|(1<<20)|(2<<22);
	
	if(CMD24(Addr)!=1) //����д�������ָ��
		return 0;
	
	while(i<BlockSize)
	{ //��ʼ�������ݵ�������
		status=rSDIFSTA;
		if((status&0x2000)==0x2000)
		{ //�������FIFO���ã���FIFOδ��
			rSDIDAT=*TxBuffer;
			TxBuffer++;
			i++;
		}
	}
	rSDIDCON = rSDIDCON&~(7<<12);
 
	do
	{ //�ȴ����ݷ��ͽ���
		status=rSDIDSTA;
	}while((status&0x2)==0x2);
	rSDIDSTA = status;
 
	if((status&0xFC)!=0x00)
	{
  		return 0;
 	}
 	else
 	{
  		return 1;
	}
}


/********************************************************************************** 
�� �ܣ��ú��������� SD ���Ķ�����ݿ�д������ 
�� ���� 
	U32 Addr ��д�����ʼ��ַ 
	U32 DatSize �ڴ���д�����ݵ���Ŀ���� Word Ϊ��λ 
	U32* TxBuffer ���������ݵĻ����� 
����ֵ�� 
	0 ����д�����ʧ�� 
	1 ����д������ɹ� 
�� ���� 
�����������ж���һ��������Ϊ���ͻ��������� U32 Tx_buffer[BlockSize]; 
Ȼ��ʼ���� Write_Mult_Block(addr,DatSize,Tx_buffer); 
**********************************************************************************/ 
U8 Write_Mult_Block(U32 Addr,U32 DatSize,U32* TxBuffer)
{ 
	U16 i = 0; 
	U32 status = 0; 

	rSDIDTIMER=0x7fffff;		// Set timeout count
	rSDIBSIZE=0x200;			// 512byte(128word)
	rSDIFSTA = rSDIFSTA|(1<<16); // FIFO reset 
	rSDIDCON = (1<<SDCard_BlockSize)|(3<<12)|(1<<14)|(1<<16)|(1<<17)|(1<<20)|(2<<22); 
	while((rSDIDCON&0x4000)!=0x4000)
	{ 
		rSDIDCON = rSDIDCON| 0x4000; 
	} 
	
	if(CMD25(Addr)!=1)//����д������ָ��
		return 0;

	while(i<DatSize)
	{//��ʼ�������ݵ�������
		status = rSDIFSTA; 
		if((status&0x2000)==0x2000)
		{//������� FIFO ���ã��� FIFO δ�� 
			rSDIDAT = *TxBuffer; 
			TxBuffer++; 
			i++; 
		} 
	} 
	rSDIDCON = rSDIDCON&~(7<<12); 
	
	while(CMD12()!=1);//���ͽ���ָ�� 
	
	do
	{//�ȴ����ݷ��ͽ��� 
		status = rSDIDSTA; 
	}while((status&0x2)==0x2); 
	
	rSDIDSTA = status;
	
	if((status&0x89)!=0x00)
	{ 

		return 0; 
	}
	else
	{ 
		return 1; 
	} 
} 



/********************************************************************************** 
�� �ܣ��ú������ڲ���ָ����ַ��������� 
�� ���� 
	U32 StartAddr ��������ʼ��ַ 
	U32 EndAddr �����Ľ�����ַ 
����ֵ�� 
	0 ���������ɹ� 
	1 ��������ʧ�� 
ע �⣺ 
	��ʼ�ͽ�����ַ������������룬��������С��λ�������������ʼ�ڽ�����ַ��һ�������Ĵ�
	С��������û�����������룬�Ӷ�ʹ��ʼ��ַ�ͽ�����ַ���Ϊ������������ô�������������� 
	�������� 
**********************************************************************************/ 
U8 Erase_Block(U32 StartAddr,U32 EndAddr)
{ 
	if(CMD32(StartAddr)!=1)
		return 0;
	if(CMD33(EndAddr)!=1) 
		return 0;
	if(CMD38()!=1)
		return 0;
	return 1; 
} 

/**********************************************
���ܣ�SD����ʼ��
��ڣ���
���ڣ�=0ʧ�� =1�ɹ�
˵������
**********************************************/
U8 SDinit(void) 
{
	U16 i;
	U16 iTemp;
	
	#ifdef __SD_MMC_DEBUG__
	Uart_Printf("\n************\n");
	Uart_Printf("\nTest SD Func\n");
	Uart_Printf("\n************\n");
	#endif
	
	rSDIPRE = PCLK/(INICLK)-1;	// 400KHz  
	rSDICON = (1<<4)|1;			// Type B, clk enable
	rSDIFSTA=rSDIFSTA|(1<<16);	// FIFO reset
	
	for(i=0;i<0x1000;i++);  	// Wait 74SDCLK for card
	
	CMD0();
	
	if(CMD1())
	{
		SDCard.cCardType = MMC_CARD;
	}
	else
	{
		switch(CMD8())
		{ 
			case 0://���̼���Ч 
				SDCard.cCardType = INVALID_CARD;
				break; 
			case 1://�� SD2.0 �� 
				SDCard.cCardType = SD_V1X_CARD;
				break; 
			case 2://SD2.0 �� 
				SDCard.cCardType = SDHC_V20_CARD;
				break; 
		} 	
	}
	
	SDCard.iCardRCA = 0;
	for(i=0;i<50;i++)
	{
		if(ACMD41(SDCard.iCardRCA))
			break;
		Delay(200);
	}
	
	if(i==50)
	{
		#ifdef __SD_MMC_DEBUG__
		Uart_Printf("Initialize fail\nNo Card assertion\n");
		#endif
		return 0;
		
	}
	else
	{
		#ifdef __SD_MMC_DEBUG__
		Uart_Printf("SD is ready\n");
		#endif
	}
	
	if(CMD2(SDCard.cCardCID))
	{
		#ifdef __SD_MMC_DEBUG__
		Uart_Printf("CID\n");
		Uart_Printf("MID = %d\n",SDCard.cCardCID[0]);
		Uart_Printf("OLD = %d\n",(SDCard.cCardCID[1]*0X100)+SDCard.cCardCID[2]);
		Uart_Printf("��������:%s\n",(SDCard.cCardCID+3));
		Uart_Printf("��������:20%d,%d\n",((SDCard.cCardCID[13]&0x0f)<<4)+((SDCard.cCardCID[14]&0xf0)>>4),(SDCard.cCardCID[14]&0x0f));
		#endif
	}
	else
	{
		#ifdef __SD_MMC_DEBUG__
		Uart_Printf("Read Card CID is fail!\n");
		#endif
		return 0;
	}
	
	//RCA
	if(SDCard.cCardType==MMC_CARD)
	{
		if(CMD3(1,&SDCard.iCardRCA))
		{
			SDCard.iCardRCA = 1;
			rSDIPRE = (PCLK/MMCCLK)-1;	
			#ifdef __SD_MMC_DEBUG__
			Uart_Printf("MMC Frequency is %dHz\n",(PCLK/(rSDIPRE+1)));
			#endif
		}
		else
		{
			#ifdef __SD_MMC_DEBUG__
			Uart_Printf("Read MMC RCA is fail!\n");
			#endif
			return 0;
		}
	}
	else
	{
		if(CMD3(0,&SDCard.iCardRCA))
		{
			rSDIPRE = PCLK/(SDCLK)-1;	// Normal clock=25MHz
			#ifdef __SD_MMC_DEBUG__
			Uart_Printf("SD Card RCA = 0x%x\n",SDCard.iCardRCA);
			Uart_Printf("SD Frequency is %dHz\n",(PCLK/(rSDIPRE+1)));
			#endif
		}
		else
		{
			#ifdef __SD_MMC_DEBUG__
			Uart_Printf("Read SD RCA is fail!\n");
			#endif
			return 0;
		}
	}
	
	//CSD
	if(CMD9(SDCard.iCardRCA,SDCard.lCardCSD))
	{
		SDCard.lCardSize = (((SDCard.lCardCSD[1]&0x0000003f)<<16)+((SDCard.lCardCSD[2]&0xffff0000)>>16)+1)*512;
		SDCard.lSectorSize = ((SDCard.lCardCSD[2]>>6)&0x0000007f)+1;
		#ifdef __SD_MMC_DEBUG__
		Uart_Printf("Read Card CSD OK!\n");
		Uart_Printf("0x%08x\n",SDCard.lCardCSD[0]);
		Uart_Printf("0x%08x\n",SDCard.lCardCSD[1]);
		Uart_Printf("0x%08x\n",SDCard.lCardCSD[2]);
		Uart_Printf("0x%08x\n",SDCard.lCardCSD[3]);
		Uart_Printf("������Ϊ:%dKB,%dMB\n",SDCard.lCardSize,SDCard.lCardSize/1024);
		
		#endif
	}
	else
	{
		#ifdef __SD_MMC_DEBUG__
		Uart_Printf("Read Card CSD Fail!\n");
		#endif
		return 0;
	}
	
	
	if(Card_sel_desel(1,SDCard.iCardRCA))
	{
		#ifdef __SD_MMC_DEBUG__
		Uart_Printf("Card sel desel OK!\n");
		#endif
	}
	else
	{
		#ifdef __SD_MMC_DEBUG__
		Uart_Printf("Card sel desel fail!\n");
		#endif
		return 0;
	}
	
	//cmd13
	iTemp = CMD13(SDCard.iCardRCA);
	if(iTemp)
	{
		#ifdef __SD_MMC_DEBUG__
		Uart_Printf("Card Status is 0x%x\n",iTemp);
		#endif
	}
	
	if(Set_bus_Width(SDCard.cCardType,1,SDCard.iCardRCA))
	{
		#ifdef __SD_MMC_DEBUG__
		Uart_Printf("Bus Width is 4bit\n");
		#endif
	}
	else
	{
		#ifdef __SD_MMC_DEBUG__
		Uart_Printf("Bus Width is 1bit\n");
		#endif
		return 0;
	}
	
	return 1;
}









