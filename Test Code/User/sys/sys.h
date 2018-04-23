#ifndef __SYS_H_
#define __SYS_H_

#include "sys_config.h"

#define ANDRIOD_SERIAL USART1
#define SCAN_SERIAL UART4
#define FEEDBACK_SERIAL UART5

#define JRS1 GPIOD, GPIO_Pin_11
#define JRS2 GPIOA, GPIO_Pin_11

#define MDJ1 GPIOD, GPIO_Pin_9
#define MDJ2 GPIOD, GPIO_Pin_8

#define CSB GPIOD, GPIO_Pin_10

#define SWITCH1 GPIOE, GPIO_Pin_9
#define SWITCH2 GPIOE, GPIO_Pin_10

#define DCF1 GPIOF, GPIO_Pin_1
#define DCF2 GPIOF, GPIO_Pin_5
#define DCF3 GPIOF, GPIO_Pin_2
#define DCF4 GPIOF, GPIO_Pin_3
#define DCF5 GPIOE, GPIO_Pin_14
#define DCF6 GPIOE, GPIO_Pin_15
#define DCF7 GPIOF, GPIO_Pin_4
#define DCF8 GPIOF, GPIO_Pin_0

#define MOTOR_PWM GPIOB, GPIO_Pin_6
#define MOTOR_CTRL GPIOE, GPIO_Pin_7

#define DAC_PORT GPIOA,GPIO_Pin_4
//TIM4-CH3
#define RDB1 GPIOB, GPIO_Pin_8
//TIM4-CH4
#define RDB2 GPIOB, GPIO_Pin_9

#define FLJ1 GPIOB, GPIO_Pin_8
#define FLJ2 GPIOB, GPIO_Pin_9
#define FLJ3 GPIOB, GPIO_Pin_8
#define FLJ4 GPIOB, GPIO_Pin_9

#define JBJ1 GPIOE, GPIO_Pin_1
#define JBJ2 GPIOE, GPIO_Pin_2
#define JBJ3 GPIOE, GPIO_Pin_3
#define JBJ4 GPIOE, GPIO_Pin_4



void sys_init(void);
void delay_ms(int nms);
void delay_us(int nus);
void delay_s(float timw_s);
void NVIC_Config(void);
void Sys_DefalutConfig(void);

#endif