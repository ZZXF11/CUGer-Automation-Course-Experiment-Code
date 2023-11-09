/**************************************************
**	�ļ���:config.h
**	�汾��:V 1.0
**	�ļ�˵��:���ú�ϵͳ��صı��������ò�����
**		ͬʱ��ɶ������������õ�ͷ�ļ��ĵ��ã�
**		ʵ��ֻ��Ҫ���ø�ͷ�ļ��Ϳ�����ɸ�������������ĵ��á�
***************************************************/

#ifndef  CONFIG_H
#define  CONFIG_H

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL  		0
#endif

#ifndef OK
#define OK		1
#endif

#ifndef FAIL
#define FAIL		0
#endif

typedef unsigned char  uint8;                   // �޷���8λ���ͱ���
typedef signed   char  int8;                    // �з���8λ���ͱ���
typedef unsigned short uint16;                  // �޷���16λ���ͱ���
typedef signed   short int16;                   // �з���16λ���ͱ���
typedef unsigned int   uint32;                  // �޷���32λ���ͱ���
typedef signed   int   int32;                   // �з���32λ���ͱ���
typedef float          fp32;                    // �����ȸ�����(32λ����)
typedef double         fp64;                    // ˫���ȸ�����(64λ����)

#define U32 unsigned int
#define U16 unsigned short
#define S32 int
#define S16 short int
#define U8  unsigned char
#define	S8  char

/*********************��uC/OS-II��������롿******************/
#define		USER_USING_MODE    0x10             // �û�ģʽ,ARM����
                                                // ֻ����0x10,0x30,0x1f,0x3f֮һ
//#include	"ucos_ii.h" //wang�ϵ�                                     
//#include	"app_cfg.h" //wang�ϵ�
//#include	"Printf.h" //wang�ϵ�

/**********************��ARM��������롿******************/
//#include	"S3C2440slib.h"  //wang�ϵ�
//#include	"S3C2440addr.h"  //wang�ϵ�
#include	"option.h"
//#include	"S3C2440lib.h"   //wang�ϵ�

void TargetInit(void);

// IRQ�ж�������ַ��
//extern  uint32 VICVectAddr[];


/**********************��Ӧ�ó������á�******************/
#include	<stdio.h>
#include	<ctype.h>
#include	<stdlib.h>
#include	<stdarg.h>
#include	<string.h>

/******************���������Զ���ͷ�ļ���*****************/
//#include	"lcd.h" //wang�ϵ�
//#include	"TIMER.H"//wang�ϵ�
#include	"mmu.h"

/*******************���û��Զ��������*******************/
#define RGB(r,g,b)		(unsigned int)( (r << 16) + (g << 8) + b )
#define FROM_BCD(n)		((((n) >> 4) * 10) + ((n) & 0xf))
#define TO_BCD(n)		((((n) / 10) << 4) | ((n) % 10))


#endif
