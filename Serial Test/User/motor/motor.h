#ifndef __MOTOR_H_
#define __MOTOR_H_

#include "sys_config.h"

#define DJ_POS1 750 // 90
#define DJ_POS2 750 // 90

#define CPQ 0
#define MDJ1 1
#define MDJ2 2
#define JRS1 3
#define JRS2 4
#define CBDJ 5
#define CSB1 6
#define CSB2 7
#define CSB3 8
#define DCF1 9
#define DCF2 10
#define DCF3 11
#define DCF4 12
#define DCF5 13
#define DCF6 14
#define DCF7 15
#define DCF8 16
#define DCF9 17
#define DCF10 18
#define JBJ1 19
#define JBJ2 20
#define FLJ1 21
#define FLJ2 22
#define RDB1 23
#define RDB2 24
#define RDB3 25
#define RDB4 26
#define RDB5 27
#define RDB6 28
#define RDB7 29
#define DJ 30
#define ZYB 31

void Motor_Config(void);
void Motor_Step1(void);
void Motor_Step2(void);
void Action(uint16_t Number, uint16_t action);

#endif
