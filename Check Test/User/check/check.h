#ifndef __CHECK_H_
#define __CHECK_H_

#include "sys_config.h"

#define MILK1_SCK_PIN GPIO_Pin_0
#define MILK1_SCK_PORT GPIOD
#define MILK1_SCK_CLK RCC_APB2Periph_GPIOD

#define MILK1_DOUT_PIN GPIO_Pin_1
#define MILK1_DOUT_PORT GPIOD
#define MILK1_DOUT_CLK RCC_APB2Periph_GPIOD

#define MILK2_SCK_PIN GPIO_Pin_3
#define MILK2_SCK_PORT GPIOD
#define MILK2_SCK_CLK RCC_APB2Periph_GPIOD

#define MILK2_DOUT_PIN GPIO_Pin_4
#define MILK2_DOUT_PORT GPIOD
#define MILK2_DOUT_CLK RCC_APB2Periph_GPIOD

#define YWG1_PIN GPIO_Pin_8
#define YWG1_PORT GPIOD
#define YWG1_CLK RCC_APB2Periph_GPIOD

#define YWG2_PIN GPIO_Pin_9
#define YWG2_PORT GPIOD
#define YWG2_CLK RCC_APB2Periph_GPIOD

#define MFS6_PIN GPIO_Pin_10
#define MFS6_PORT GPIOD
#define MFS6_CLK RCC_APB2Periph_GPIOD

#define MFS5_PIN GPIO_Pin_11
#define MFS5_PORT GPIOD
#define MFS5_CLK RCC_APB2Periph_GPIOD

#define MFS4_PIN GPIO_Pin_12
#define MFS4_PORT GPIOD
#define MFS4_CLK RCC_APB2Periph_GPIOD

#define MFS3_PIN GPIO_Pin_13
#define MFS3_PORT GPIOD
#define MFS3_CLK RCC_APB2Periph_GPIOD

#define MFS2_PIN GPIO_Pin_14
#define MFS2_PORT GPIOD
#define MFS2_CLK RCC_APB2Periph_GPIOD

#define MFS1_PIN GPIO_Pin_15
#define MFS1_PORT GPIOD
#define MFS1_CLK RCC_APB2Periph_GPIOD

#define ICE_SET_PIN GPIO_Pin_7
#define ICE_SET_PORT GPIOE
#define ICE_SET_CLK RCC_APB2Periph_GPIOE

#define POWER_SET_PIN GPIO_Pin_1
#define POWER_SET_PORT GPIOG
#define POWER_SET_CLK RCC_APB2Periph_GPIOG

#define YWJ1_HIGH_PIN GPIO_Pin_9
#define YWJ1_HIGH_PORT GPIOG
#define YWJ1_HIGH_CLK RCC_APB2Periph_GPIOG

#define YWJ1_LOW_PIN GPIO_Pin_10
#define YWJ1_LOW_PORT GPIOG
#define YWJ1_LOW_CLK RCC_APB2Periph_GPIOG

#define YWJ2_HIGH_PIN GPIO_Pin_11
#define YWJ2_HIGH_PORT GPIOG
#define YWJ2_HIGH_CLK RCC_APB2Periph_GPIOG

#define YWJ2_LOW_PIN GPIO_Pin_12
#define YWJ2_LOW_PORT GPIOG
#define YWJ2_LOW_CLK RCC_APB2Periph_GPIOG

#define LED1_PIN GPIO_Pin_4
#define LED1_PORT GPIOC
#define LED1_CLK RCC_APB2Periph_GPIOC

#define LED2_PIN GPIO_Pin_5
#define LED2_PORT GPIOC
#define LED2_CLK RCC_APB2Periph_GPIOC

#define KEY1_PIN GPIO_Pin_2
#define KEY1_PORT GPIOC
#define KEY1_CLK RCC_APB2Periph_GPIOC

#define KEY2_PIN GPIO_Pin_3
#define KEY2_PORT GPIOC
#define KEY2_CLK RCC_APB2Periph_GPIOC

#define ICE_P2_PIN GPIO_Pin_12
#define ICE_P2_PORT GPIOF
#define ICE_P2_CLK RCC_APB2Periph_GPIOF

#define ICE_P3_PIN GPIO_Pin_13
#define ICE_P3_PORT GPIOF
#define ICE_P3_CLK RCC_APB2Periph_GPIOF

#define ICE_P4_PIN GPIO_Pin_14
#define ICE_P4_PORT GPIOF
#define ICE_P4_CLK RCC_APB2Periph_GPIOF

#define ICE_P5_PIN GPIO_Pin_15
#define ICE_P5_PORT GPIOF
#define ICE_P5_CLK RCC_APB2Periph_GPIOF

#define ICE_P6_PIN GPIO_Pin_0
#define ICE_P6_PORT GPIOG
#define ICE_P6_CLK RCC_APB2Periph_GPIOG

#define led1_on GPIO_ResetBits(GPIOC, GPIO_Pin_4)
#define led1_off GPIO_SetBits(GPIOC, GPIO_Pin_4)

#define led2_on GPIO_ResetBits(GPIOC, GPIO_Pin_5)
#define led2_off GPIO_SetBits(GPIOC, GPIO_Pin_5)

#define key1_press GPIO_ReadInputDataBit(KEY1_PORT, KEY1_PIN)
#define key2_press GPIO_ReadInputDataBit(KEY2_PORT, KEY2_PIN)

#define mfs1 GPIO_ReadInputDataBit(MFS1_PORT, MFS1_PIN)

#define ywj1 GPIO_ReadInputDataBit(YWJ1_LOW_PORT, YWJ1_LOW_PIN)

#define ice_p2 GPIO_ReadInputDataBit(ICE_P2_PORT, ICE_P2_PIN)
#define ice_p3 GPIO_ReadInputDataBit(ICE_P3_PORT, ICE_P3_PIN)
#define ice_p4 GPIO_ReadInputDataBit(ICE_P4_PORT, ICE_P4_PIN)
#define ice_p5 GPIO_ReadInputDataBit(ICE_P5_PORT, ICE_P5_PIN)
#define ice_p6 GPIO_ReadInputDataBit(ICE_P6_PORT, ICE_P6_PIN)

#define key1_press GPIO_ReadInputDataBit(KEY1_PORT, KEY1_PIN)
#define ice_power_press GPIO_SetBits(GPIOG, GPIO_Pin_1)
#define ice_power_release GPIO_ResetBits(POWER_SET_PORT, POWER_SET_PIN)


void Check_Config(void);

#endif
