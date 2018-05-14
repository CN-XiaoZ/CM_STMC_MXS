#ifndef __MOTOR_H_
#define __MOTOR_H_

#include "sys_config.h"

#define DJ_POS1 750 // 90
#define DJ_POS2 750 // 90

#define CPQ 0   //00
#define MDJ1 1  //01
#define MDJ2 2  //02
#define JRS1 3  //03
#define JRS2 4  //04
#define CBDJ 5  //05
#define CSB1 6  //06
#define CSB2 7  //07
#define CSB3 8  //08
#define DCF1 9  //09
#define DCF2 10  //0A
#define DCF3 11  //0B
#define DCF4 12  //0C
#define DCF5 13  //0D
#define DCF6 14  //0E
#define DCF7 15  //0F
#define DCF8 16  //10
#define DCF9 17  //11
#define DCF10 18  //12
#define JBJ1 19  //13
#define JBJ2 20  //14
#define FLJ1 21  //15
#define FLJ2 22  //16
#define RDB1 23  //17
#define RDB2 24  //18
#define RDB3 25  //19
#define RDB4 26  //1A
#define RDB5 27  //1B
#define RDB6 28  //1C
#define RDB7 29  //1D
#define DJ 30  //1E
#define ZYB 31  //1F

void Motor_Config(void);
void Motor_Step1(void);
void Motor_Step2(void);
void Action(uint16_t Number, uint16_t action);

#endif
