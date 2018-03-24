/**
  ******************************************************************************
  * @file    sys.c
  * @version V1.0
  * @date    2018-1-4
  * @brief   delay函数,中断向量配置,系统初始化配置
  ******************************************************************************
  */
#include "./sys/sys.h"

void sys_init(void)
{
    SPI_FLASH_Init();
	Motor_Config();
    USART_Config();
    EXTI_Config();
    NVIC_Config();
}

void delay_ms(int nms)
{
    uint32_t i;
    SysTick_Config(SystemCoreClock / 1000);
    for (i = 0; i < nms; i++)
    {
        while (!((SysTick->CTRL) & (1 << 16)))
            ;
    }
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void delay_us(int nus)
{
    uint32_t i;
    SysTick_Config(SystemCoreClock / 1000000);
    for (i = 0; i < nus; i++)
    {
        while (!((SysTick->CTRL) & (1 << 16)))
            ;
    }
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void delay_s(float time_s)
{
    int time, time_spart, time_mspart, count;
    time = time_s * 1000;
    time_spart = time / 1000;
    time_mspart = time % 1000;
    for (count = 0; count < time_spart; count++)
        delay_ms(1000);
    delay_ms(time_mspart);
}

void NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE; 
	NVIC_Init(&NVIC_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE; 
	NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = USART1;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE; 
	NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = UART5;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE; 
	NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE; 
	NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE; 
	NVIC_Init(&NVIC_InitStructure);
}

// enum Sys_status
// {
//     Sys_WAITING = 0,  //等待
//     Sys_WASHING,      //清洗
//     Sys_WAITING_LOAD, //等待装填
//     Sys_PAYING,       //支付阶段
//     Sys_WORKING,      //制作阶段
// };

void SWITCH_TO_WAITING()//打开USART1，UART5 中断
{
    NVIC_DisableIRQ(EXTI9_5_IRQn);
    NVIC_DisableIRQ(EXTI15_10_IRQn);
    NVIC_DisableIRQ(TIM6_IRQn);
    NVIC_DisableIRQ(TIM7_IRQn);
    NVIC_EnableIRQ(USART1_IRQn);
    NVIC_DisableIRQ(UART4_IRQn);
    NVIC_EnableIRQ(UART5_IRQn);
    
}

void SWITCH_TO_WASHING()//关闭所有中断
{
    NVIC_DisableIRQ(EXTI9_5_IRQn);
    NVIC_DisableIRQ(EXTI15_10_IRQn);
    NVIC_DisableIRQ(TIM6_IRQn);
    NVIC_DisableIRQ(TIM7_IRQn);
    NVIC_DisableIRQ(USART1_IRQn);
    NVIC_DisableIRQ(UART4_IRQn);
    NVIC_DisableIRQ(UART5_IRQn);
}

void SWITCH_TO_WAITING_LOAD()//打开USART1，UART5 中断
{
    NVIC_DisableIRQ(EXTI9_5_IRQn);
    NVIC_DisableIRQ(EXTI15_10_IRQn);
    NVIC_DisableIRQ(TIM6_IRQn);
    NVIC_DisableIRQ(TIM7_IRQn);
    NVIC_EnableIRQ(USART1_IRQn);
    NVIC_DisableIRQ(UART4_IRQn);
    NVIC_EnableIRQ(UART5_IRQn);
}

void SWITCH_TO_PAYING()//TIM6，UART4
{
    NVIC_DisableIRQ(EXTI9_5_IRQn);
    NVIC_DisableIRQ(EXTI15_10_IRQn);
    NVIC_EnableIRQ(TIM6_IRQn);
    NVIC_DisableIRQ(TIM7_IRQn);
    NVIC_DisableIRQ(USART1_IRQn);
    NVIC_EnableIRQ(UART4_IRQn);
    NVIC_DisableIRQ(UART5_IRQn);
}

void SWITCH_TO_WORKING()//TIM7
{
    NVIC_DisableIRQ(EXTI9_5_IRQn);
    NVIC_DisableIRQ(EXTI15_10_IRQn);
    NVIC_DisableIRQ(TIM6_IRQn);
    NVIC_EnableIRQ(TIM7_IRQn);
    NVIC_DisableIRQ(USART1_IRQn);
    NVIC_DisableIRQ(UART4_IRQn);
    NVIC_DisableIRQ(UART5_IRQn);
}


void System_Reset(void)
{
    __set_FAULTMASK(1);
    NVIC_SystemReset();
}