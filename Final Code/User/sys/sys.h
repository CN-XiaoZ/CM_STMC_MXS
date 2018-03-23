#ifndef __SYS_H_
#define __SYS_H_

#include "sys_config.h"

#define ANDRIOD_SERIAL USART1
#define SCAN_SERIAL UART4
#define FEEDBACK_SERIAL UART5

void sys_init(void);
void delay_ms(int nms);
void delay_us(int nus);
void delay_s(float timw_s);
void NVIC_Config(void);
void Sys_DefalutConfig(void);


#endif