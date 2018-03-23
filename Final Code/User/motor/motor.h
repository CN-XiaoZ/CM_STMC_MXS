#ifndef __MOTOR_H_
#define __MOTOR_H_

#include "sys_config.h"

#define ENRICH_MOTOR_PWM_PIN GPIO_Pin_6
#define ENRICH_MOTOR_PWM_PORT GPIOB
#define ENRICH_MOTOR_PWM_CLK RCC_APB2Periph_GPIOB

#define ENRICH_MOTOR_PIN GPIO_Pin_7
#define ENRICH_MOTOR_PORT GPIOE
#define ENRICH_MOTOR_CLK RCC_APB2Periph_GPIOE

#define MOTOR_SPEED 15000
void ENRICHMOTOR_config(void);
void Motor_Start(void);
void Motor_Back(void);
void Motor_Config(void);
void Motor_Config2(void);
#endif