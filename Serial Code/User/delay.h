#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"

void delay_ms(int nms);
void delay_us(int nus);
void delay_s(float time_s);

#endif
