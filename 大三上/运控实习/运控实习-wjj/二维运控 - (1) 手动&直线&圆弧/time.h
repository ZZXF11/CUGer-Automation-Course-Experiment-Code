#ifndef __TIME_H
#define __TIME_H

#include <reg52.h>
#include "intrins.h"

void delayms(unsigned int);	// ������ʱ����
void delayus(unsigned int);	// ΢����ʱ����
void inter_init();
void EX0init(void);
void TIM1init(void);

#endif