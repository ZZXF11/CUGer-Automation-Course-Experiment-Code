#include <reg52.h>


#define PD1  61        //  122/2 分成左右两半屏(122x32)


extern unsigned char Column;
extern unsigned char Page_ ;  // 页地址寄存器 D1,DO:页地址
extern unsigned char Code_ ;  // 字符代码寄存器

extern unsigned char Command; // 指令寄存器
extern unsigned char LCDData; // 数据寄存器

extern xdata unsigned char CWADD1;   // 写指令代码地址(E1)     *****地址译码接CS3*****
extern xdata unsigned char DWADD1;   // 写显示数据地址(E1)
extern xdata unsigned char CRADD1;   // 读状态字地址(E1)
extern xdata unsigned char DRADD1;   // 读显示数据地址(E1)

extern xdata unsigned char CWADD2;   // 写指令代码地址(E2)
extern xdata unsigned char DWADD2;   // 写显示数进地址(E2)
extern xdata unsigned char CRADD2;   // 读状态字地址(E2)
extern xdata unsigned char DRADD2;   // 读显示数据地址(E2)

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
 