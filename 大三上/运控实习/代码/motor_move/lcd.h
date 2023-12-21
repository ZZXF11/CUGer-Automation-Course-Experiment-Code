#include <reg52.h>


#define PD1  61        //  122/2 �ֳ�����������(122x32)


extern unsigned char Column;
extern unsigned char Page_ ;  // ҳ��ַ�Ĵ��� D1,DO:ҳ��ַ
extern unsigned char Code_ ;  // �ַ�����Ĵ���

extern unsigned char Command; // ָ��Ĵ���
extern unsigned char LCDData; // ���ݼĴ���

extern xdata unsigned char CWADD1;   // дָ������ַ(E1)     *****��ַ�����CS3*****
extern xdata unsigned char DWADD1;   // д��ʾ���ݵ�ַ(E1)
extern xdata unsigned char CRADD1;   // ��״̬�ֵ�ַ(E1)
extern xdata unsigned char DRADD1;   // ����ʾ���ݵ�ַ(E1)

extern xdata unsigned char CWADD2;   // дָ������ַ(E2)
extern xdata unsigned char DWADD2;   // д��ʾ������ַ(E2)
extern xdata unsigned char CRADD2;   // ��״̬�ֵ�ַ(E2)
extern xdata unsigned char DRADD2;   // ����ʾ���ݵ�ַ(E2)

void WriteCommandE1();
void WriteDataE1();
void ReadDataE1();
void WriteCommandE2();
void WriteDataE2();
void ReadDataE2();
void Init();
void Clear();


void WriteCHN16x16();
void WriteNUM8x16();
void ShowXiangmu();
void Show_select();
void Show_head();
void Show_str();
void Show_yh();
 