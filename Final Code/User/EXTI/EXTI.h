#ifndef __EXTI_H_
#define __EXTI_H_   

#include "sys_config.h"

#define SWITCH1_PIN GPIO_Pin_9
#define SWITCH1_CLK RCC_APB2Periph_GPIOE
#define SWITCH1_PORT GPIOE

#define SWITCH2_PIN GPIO_Pin_10
#define SWITCH2_CLK RCC_APB2Periph_GPIOE
#define SWITCH2_PORT GPIOE

void EXTI_Config(void);

#endif