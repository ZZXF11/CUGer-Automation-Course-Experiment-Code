/**************************************************
**	文件名:config.h
**	版本号:V 1.0
**	文件说明:设置和系统相关的变量和配置参数，
**		同时完成对其他参数设置的头文件的调用，
**		实现只需要调用该头文件就可以完成各个参数或变量的调用。
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

typedef unsigned char  uint8;                   // 无符号8位整型变量
typedef signed   char  int8;                    // 有符号8位整型变量
typedef unsigned short uint16;                  // 无符号16位整型变量
typedef signed   short int16;                   // 有符号16位整型变量
typedef unsigned int   uint32;                  // 无符号32位整型变量
typedef signed   int   int32;                   // 有符号32位整型变量
typedef float          fp32;                    // 单精度浮点数(32位长度)
typedef double         fp64;                    // 双精度浮点数(64位长度)

#define U32 unsigned int
#define U16 unsigned short
#define S32 int
#define S16 short int
#define U8  unsigned char
#define	S8  char

/*********************【uC/OS-II的特殊代码】******************/
#define		USER_USING_MODE    0x10             // 用户模式,ARM代码
                                                // 只能是0x10,0x30,0x1f,0x3f之一
//#include	"ucos_ii.h" //wang废掉                                     
//#include	"app_cfg.h" //wang废掉
//#include	"Printf.h" //wang废掉

/**********************【ARM的特殊代码】******************/
//#include	"S3C2440slib.h"  //wang废掉
//#include	"S3C2440addr.h"  //wang废掉
#include	"option.h"
//#include	"S3C2440lib.h"   //wang废掉

void TargetInit(void);

// IRQ中断向量地址表
//extern  uint32 VICVectAddr[];


/**********************【应用程序配置】******************/
#include	<stdio.h>
#include	<ctype.h>
#include	<stdlib.h>
#include	<stdarg.h>
#include	<string.h>

/******************【其它及自定义头文件】*****************/
//#include	"lcd.h" //wang废掉
//#include	"TIMER.H"//wang废掉
#include	"mmu.h"

/*******************【用户自定义变量】*******************/
#define RGB(r,g,b)		(unsigned int)( (r << 16) + (g << 8) + b )
#define FROM_BCD(n)		((((n) >> 4) * 10) + ((n) & 0xf))
#define TO_BCD(n)		((((n) / 10) << 4) | ((n) % 10))


#endif
