#ifndef __TIME_H
#define __TIME_H

#include <reg52.h>
#include "intrins.h"

void delayms(unsigned int);	// 毫秒延时函数
void delayus(unsigned int);	// 微秒延时函数
void inter_init();
void EX0init(void);
void TIM1init(void);

#endif