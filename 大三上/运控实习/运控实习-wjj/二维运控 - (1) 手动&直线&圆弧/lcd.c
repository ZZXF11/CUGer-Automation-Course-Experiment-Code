#include <reg52.h>
#include "8x16zimo_lib.c"
#include "16x16zimo_lib.c"
//#include "directionArrows.c"
//#include "lcd_CUG_logo.c"

#define PD1  61        //  122/2 �ֳ�����������(122x32)

unsigned char Column;	 //	�е�ַ
unsigned char Page_ ;  // ҳ��ַ�Ĵ��� D1,DO:ҳ��ַ
unsigned char Code_ ;  // �ַ�����Ĵ���

unsigned char Command; // ָ��Ĵ���
unsigned char LCDData; // ���ݼĴ���

xdata unsigned char CWADD1 _at_ 0x1cff;   // дָ������ַ(E1)��Y8��
xdata unsigned char DWADD1 _at_ 0x1eff;   // д��ʾ���ݵ�ַ(E1)
xdata unsigned char CRADD1 _at_ 0x1dff;   // ��״̬�ֵ�ַ(E1)
xdata unsigned char DRADD1 _at_ 0x1fff;   // ����ʾ���ݵ�ַ(E1)

xdata unsigned char CWADD2 _at_ 0x3cff;   // дָ������ַ(E2) (Y9)
xdata unsigned char DWADD2 _at_ 0x3eff;   // д��ʾ������ַ(E2)
xdata unsigned char CRADD2 _at_ 0x3dff;   // ��״̬�ֵ�ַ(E2)
xdata unsigned char DRADD2 _at_ 0x3fff;   // ����ʾ���ݵ�ַ(E2)


// 1.дָ������ӳ���(E1)
void WriteCommandE1()
{
  while(CRADD1 & 0x80);
  CWADD1 = Command;
}

// 2.д��ʾ�����ӳ���(E1)
void WriteDataE1()
{
  while(CRADD1 & 0x80);
  DWADD1 = LCDData;
}

// 3.����ʾ�����ӳ���(E1)
void ReadDataE1()
{
  while(CRADD1 & 0x80);
  LCDData = DRADD1;
}

// 4.дָ������ӳ���(E2)
void WriteCommandE2()
{
  while(CRADD2 & 0x80);
  CWADD2 = Command;
}

// 5.д��ʾ�����ӳ���(E2)
void WriteDataE2()
{
  while(CRADD2 & 0x80);
  DWADD2 = LCDData;
}

// 6.����ʾ�����ӳ���(E2)
void ReadDataE2()
{
  while(CRADD2 & 0x80);
  LCDData = DRADD2;
}


void Init()  // ******��ʼ������******
{
  Command = 0xe2;  //��λָ��   
  WriteCommandE1();
  WriteCommandE2();

  Command = 0xa4;	//�رվ�̬��ʾ
  WriteCommandE1();
  WriteCommandE2();

  Command = 0xa9;//1/32DUTY
  WriteCommandE1();
  WriteCommandE2();

  Command = 0xa0;//��ʾ���򣺷���
  WriteCommandE1();
  WriteCommandE2();

  Command = 0xc0;//������ʾ��ʼ��(0~32),�е�ַ������ѭ������
  WriteCommandE1();
  WriteCommandE2();

  Command = 0xaf;//����Ļ��ʾ
  WriteCommandE1();
  WriteCommandE2();
}


void Clear()  // *********����*********
{
  unsigned char i,j;

  i = 0;
  do {

    Command = (i + 0xb8); // ҳ��ַ����
    WriteCommandE1();
    WriteCommandE2();

    Command = 0x00;      // �е�ַ����Ϊ"0"
    WriteCommandE1();
    WriteCommandE2();

    j = 0x50;            // һҳ�� 80���ֽ�
    do {
      LCDData = 0x00;    // ��ʾ����Ϊ"0"
      WriteDataE1();
      WriteDataE2();
    }while(--j !=0);     // ҳ���ֽ�����ѭ��

  }while(++i !=4);       // ҳ��ַ�ݴ�����һ
                         // ��ʾ������ѭ��
}

// *******122x32��ʾ�ӳ���*******
/*void WritePicture122x32()       //*********����һ����ʾһ����*****
{
  unsigned char i,j,k;

  i = 0;
  j = 0;
  //while(j<2) {
	while(j<4){	//�õ�4ҳ�͸�Ϊ4*********************************************
    Command = ((Page_ + j) & 0x03) | 0xb8;   // ����ҳ��ַ
    WriteCommandE1();
    WriteCommandE2();
    k = Column;                   // �е�ֵַ
    while(k < Column + 122){//*****122��******************************************
      if (k < PD1) {              // Ϊ�������ʾ����(E1)
        Command = k;
        WriteCommandE1();         // �����е�ֵַ
        LCDData = CUGlogoTAB[Code_][i]; // ȡ������ģ����/**������****************
        WriteDataE1();            // д��ģ����
      } else{                     // Ϊ�Ұ�����ʾ����(E2)
        Command = k-PD1;
        WriteCommandE2();         // �����е�ֵַ
        LCDData = CUGlogoTAB[Code_][i]; // ȡ������ģ����/**������****************
        WriteDataE2();            // д��ģ����
      };
      i++;
      if( ++k >= PD1 * 2) break;  // �е�ַ�Ƿ񳬳���ʾ��Χ
    } ;
    j++;
  };
}*/



// *******32x32��ʾ�ӳ���*******
//void WritePicture32x32()       //*********����һ����ʾһ����*****
//{
//  unsigned char i,j,k;
//  i = 0;
//  j = 0;
//  //while(j<2) {
//	while(j<4){	//�õ�4ҳ�͸�Ϊ4*********************************************
//    Command = ((Page_ + j) & 0x03) | 0xb8;   // ����ҳ��ַ
//    WriteCommandE1();
//    WriteCommandE2();
//    k = Column;                   // �е�ֵַ
//    while(k < Column + 32){//*****32��******************************************
//      if (k < PD1) {              // Ϊ�������ʾ����(E1)
//        Command = k;
//        WriteCommandE1();         // �����е�ֵַ
//        LCDData = ArrowsTAB[Code_][i]; // ȡ������ģ����
//        WriteDataE1();            // д��ģ����
//      } else{                     // Ϊ�Ұ�����ʾ����(E2)
//        Command = k-PD1;
//        WriteCommandE2();         // �����е�ֵַ
//        LCDData = ArrowsTAB[Code_][i]; // ȡ������ģ����
//        WriteDataE2();            // д��ģ����
//      };

//      i++;
//      if( ++k >= PD1 * 2) break;  // �е�ַ�Ƿ񳬳���ʾ��Χ
//    } ;
//    j++;
//  };
//}



// *******16��16��ʾ�ӳ���*******
void WriteCHN16x16()       //*********����һ����ʾһ����*****
{
  unsigned char i,j,k;

  i = 0;
  j = 0;
  while(j<2) {
    Command = ((Page_ + j) & 0x03) | 0xb8;   // ����ҳ��ַ
    WriteCommandE1();
    WriteCommandE2();
    k = Column;                   // �е�ֵַ
    while(k < Column + 16){
      if (k < PD1) {              // Ϊ�������ʾ����(E1)
        Command = k;
        WriteCommandE1();         // �����е�ֵַ
        LCDData = CCTAB[Code_][i]; // ȡ������ģ����
        WriteDataE1();            // д��ģ����
      } else{                     // Ϊ�Ұ�����ʾ����(E2)
        Command = k-PD1;
        WriteCommandE2();         // �����е�ֵַ
        LCDData = CCTAB[Code_][i]; // ȡ������ģ����
        WriteDataE2();            // д��ģ����
      };

      i++;
      if( ++k >= PD1 * 2) break;  // �е�ַ�Ƿ񳬳���ʾ��Χ
    } ;
    j++;
  };
}

// *******8��16��ģ��ʾ�ӳ���*******
void WriteNUM8x16()       //*********����һ����ʾһ����*****
{
  unsigned char i,j,k;
  i = 0;
  j = 0;
  while(j<2) { //***********page��������16�ж�Ӧ2��page*********
    Command = ((Page_ + j) & 0x03) | 0xb8;   // ����ҳ��ַ
    WriteCommandE1();
    WriteCommandE2();
    k = Column;                   // �е�ֵַ
    while(k < Column + 8){        //*******ȡģ8x16���б��8��*******
      if (k < PD1) {              // Ϊ�������ʾ����(E1)
        Command = k;
        WriteCommandE1();         // �����е�ֵַ
        LCDData = DIGTAB[Code_][i]; // ȡ������ģ����
        WriteDataE1();            // д��ģ����
      } else{                     // Ϊ�Ұ�����ʾ����(E2)
        Command = k-PD1;
        WriteCommandE2();         // �����е�ֵַ
        LCDData = DIGTAB[Code_][i]; // ȡ������ģ����
        WriteDataE2();            // д��ģ����
      };
      i++;
      if( ++k >= PD1 * 2) break;  // �е�ַ�Ƿ񳬳���ʾ��Χ
    } ;
    j++;
  };
}

//void show_CUGlogo()
//{
//  Init();        //��ʼ��  
//  Clear();       //����
//	
//  Page_ = 0x02;     
//  Column = 0x00;
//  Code_ = 0x00;
//  WritePicture122x32();   //���й����ʴ�ѧ��
//	
//}


void show_menu()
{
  Init();        //��ʼ��  
  Clear();       //����
	
  Page_ = 0x02;     
  Column = 0x00;
  Code_ = 0x00;
  WriteCHN16x16();   //��ѡ��

  Page_ = 0x02; 
  Column = 0x10;
  Code_ = 0x01;
  WriteCHN16x16();   //����
	
  Page_ = 0x02; 
  Column = 0x20;
  Code_ = 0x02;
  WriteCHN16x16();   //���١�
	
  Page_ = 0x02; 
  Column = 0x30;
  Code_ = 0x03;
  WriteCHN16x16();   //������

  Page_ = 0x02; 
  Column = 0x40;
  Code_ = 0x11;
  WriteCHN16x16();   //������

	Page_ = 0x00;     
  Column = 0x07;
  Code_ = 0x04;
  WriteCHN16x16();   //���١�
	
	Page_ = 0x00;     
  Column = 0x25;
  Code_ = 0x05;
  WriteCHN16x16();   //���ڡ�
	
	Page_ = 0x00;     
  Column = 0x43;
  Code_ = 0x06;
  WriteCHN16x16();   //���ۡ�
	
	Page_ = 0x00;     
  Column = 0x61;
  Code_ = 0x07;
  WriteCHN16x16();   //���ܡ�
	
}

//void DisplayTest(void)	
//{  
//  Init();        //��ʼ��  (�Ƶ�������)
//  Clear();       //����
//	
//	Page_ = 0x02;     
//  Column = 0x00;
//  Code_ = 0x0d;
//  WriteCHN16x16();   //���١�
//}

//void DisplayTest2(void)	
//{  
//  Init();        //��ʼ��  (�Ƶ�������)
//  Clear();       //����
//	
//	Page_ = 0x02;     
//  Column = 0x00;
//  Code_ = 0x0e;
//  WriteCHN16x16();   //����
//}
//void DisplayTest3(void)	//
//{  
//  Init();        //��ʼ��  (�Ƶ�������)
//  Clear();       //����
//	
//	Page_ = 0x02;     
//  Column = 0x00;
//  Code_ = 0x0f;
//  WriteCHN16x16();   //����
//}

void Display_1(int SDpeed)	//��ʾ�ֶ�
{  
  Init();        //��ʼ��  (�Ƶ�������)
  Clear();       //����
	
	Page_ = 0x02;     
  Column = 0x00;
  Code_ = 0x04;
  WriteCHN16x16();   //���١�
	
	Page_ = 0x02;     
  Column = 0x10;
  Code_ = 0x0e;
  WriteCHN16x16();   //���֡�
	
	Page_ = 0x02;     
  Column = 0x20;
  Code_ = 0x0f;
  WriteCHN16x16();   //������	
	
	Page_ = 0x00;     
  Column = 0x30;
  Code_ = ((106-SDpeed)/10);
  WriteNUM8x16();   //����
	
	Page_ = 0x00;     
  Column = 0x38;
  Code_ = ((106-SDpeed)%10);
  WriteNUM8x16();   //����
	
	
}

void Display_2(int indexX1,int indexX2,int indexX3,int indexY1,int indexY2,int indexY3)	//��ֱ��
{  
  Init();        //��ʼ��  (�Ƶ�������)
  Clear();       //����
	
	Page_ = 0x02;     
  Column = 0x00;
  Code_ = 0x05;
  WriteCHN16x16();   //���ڡ�
		
	Page_ = 0x02;     
  Column = 0x10;
  Code_ = 0x08;
  WriteCHN16x16();   //������
	
	Page_ = 0x02;     
  Column = 0x20;
  Code_ = 0x09;
  WriteCHN16x16();   //��ֱ��
	
	Page_ = 0x02;     
  Column = 0x30;
  Code_ = 0x10a;
  WriteCHN16x16();   //���ߡ�
	
	Page_ = 0x00;     
  Column = 0x00;
  Code_ = 0x0a;
  WriteNUM8x16();   //��X��
	
	Page_ = 0x00;     
  Column = 0x08;
  Code_ = 0x11;
  WriteNUM8x16();   //��=��
	
	Page_ = 0x00;     
  Column = 0x10;
	Code_ = indexX1;  //��λ����
  WriteNUM8x16();   //
	
	Page_ = 0x00;     
  Column = 0x18;
  Code_ = indexX2;	//ʮλ����
  WriteNUM8x16();   //
	
	Page_ = 0x00;     
  Column = 0x20;
  Code_ = indexX3;	//��λ����
 	WriteNUM8x16();   //
	
	Page_ = 0x00;     
  Column = 0x3c;
  Code_ = 0x0b;
  WriteNUM8x16();   //��Y��
	
	Page_ = 0x00;     
  Column = 0x44;
  Code_ = 0x11;
  WriteNUM8x16();   //��=��

	Page_ = 0x00;     
  Column = 0x4c;
	Code_ = indexY1;//��λ����
	WriteNUM8x16();   //
	//Code_ = 0xb5;//Code_>b4��ȫ��,b5=181��
	
	Page_ = 0x00;     
  Column = 0x54;
  Code_ = indexY2;	//ʮλ����
  WriteNUM8x16();   //
	
	Page_ = 0x00;     
  Column = 0x5c;
  Code_ = 0x03;
  Code_ = indexY3;	//��λ����
  WriteNUM8x16();   //
}



void Display_4(int indexR1,int indexR2,int indexR3,int indexAng1,int indexAng2,int indexAng3)//��Բ
{  
  Init();        //��ʼ��  (�Ƶ�������)
  Clear();       //����
	
	Page_ = 0x02;     
  Column = 0x00;
  Code_ = 0x07;
  WriteCHN16x16();   //���ܡ�
		
	Page_ = 0x02;     
  Column = 0x10;
  Code_ = 0x08;
  WriteCHN16x16();   //������
	
	Page_ = 0x02;     
  Column = 0x20;
  Code_ = 0x0d;
  WriteCHN16x16();   //��Բ��
	
	Page_ = 0x00;     
  Column = 0x00;
  Code_ = 0x10;
  WriteNUM8x16();   //��R��
	
	Page_ = 0x00;     
  Column = 0x10;
  Code_ = 0x11;
  WriteNUM8x16();   //��=��
	
	Page_ = 0x00;     
  Column = 0x18;
	Code_ = indexR1;//
	WriteNUM8x16();   //
	
	Page_ = 0x00;     
  Column = 0x20;
  Code_ = indexR2;	//
  WriteNUM8x16();   //
	
	Page_ = 0x00;     
  Column = 0x28;
  Code_ = indexR3;	//
  WriteNUM8x16();   //	

	Page_ = 0x00;     
  Column = 0x3c;
  Code_ = 0x10;
  WriteCHN16x16();   //���ȡ�
	
	Page_ = 0x00;     
  Column = 0x4c;
  Code_ = 0x11;
  WriteNUM8x16();   //��=��
	
	Page_ = 0x00;     
  Column = 0x54;
	Code_ = indexAng1;//
	WriteNUM8x16();   //
	
	Page_ = 0x00;     
  Column = 0x5c;
  Code_ = indexAng2;	//
  WriteNUM8x16();   //
	
	Page_ = 0x00;     
  Column = 0x64;
  Code_ = indexAng3;	//
  WriteNUM8x16();   //	
}
