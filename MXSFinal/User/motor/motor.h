#ifndef __MOTOR_H_
#define __MOTOR_H_

#include "sys_config.h"

#define DJ_POS1 750 //90
#define DJ_POS2 750 //90

void Motor_Config(void);
void Motor_Step1(void);
void Motor_Step2(void);
void Action(uint16_t Number, uint16_t action);

#endif