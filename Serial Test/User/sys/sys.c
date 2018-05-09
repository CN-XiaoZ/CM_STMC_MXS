/**
  ******************************************************************************
  * @file    sys.c
  * @version V1.0
  * @date    2018-1-4
  * @brief   delay函数,中断向量配置,系统初始化配置
  ******************************************************************************
  */
#include "./sys/sys.h"
#include "sys_config.h"

extern Sys_status SYS_STATUS;

void sys_init(void)
{
    uint8_t Default_config[20]={0};
    Default_config[0]=0x01;
    Default_config[1]=0xFE;
    Default_config[10]=0x01;
    SPI_FLASH_Init();
    Motor_Config();
    USART_Config();
    SPI_FLASH_BufferRead(app_config,SYS_INFO_ADDR,20);
    if(app_config[0]!=0X01||app_config[1]!=0xFE)
    {
        SPI_FLASH_BulkErase();
        delay_ms(1000);
        SPI_FLASH_BufferWrite(Default_config,SYS_INFO_ADDR,20);
        SPI_FLASH_BufferRead(app_config,SYS_INFO_ADDR,20);
    }
    //TODO:新机初始化向上位机请求信息
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
    time        = time_s * 1000;
    time_spart  = time / 1000;
    time_mspart = time % 1000;
    for (count = 0; count < time_spart; count++)
        delay_ms(1000);
    delay_ms(time_mspart);
}

void NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitStructure.NVIC_IRQChannel                   = TIM6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel                   = TIM7_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 4;
    NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel                   = UART4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel                   = UART5_IRQn ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0; 
    NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&NVIC_InitStructure);
}


void Sys_TIM_Config(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6|RCC_APB1Periph_TIM7,ENABLE);
    //100ms
    TIM_TimeBaseStructure.TIM_Period=1000-1;
    TIM_TimeBaseStructure.TIM_Prescaler= 7200-1;  
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
    //定时1S
    TIM_TimeBaseStructure.TIM_Period=10000-1;
    TIM_TimeBaseStructure.TIM_Prescaler= 7200-1;  
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);
    TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
    TIM_ClearFlag(TIM7, TIM_FLAG_Update);
    TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM6, ENABLE);
    TIM_Cmd(TIM7, ENABLE);
}

void Work_System_Config(void) 
{

}


void Sys_Status_Change(Sys_status SYS_STATUS)
{
    if(SYS_STATUS==Sys_WAITING)
    {
        NVIC_EnableIRQ(USART1_IRQn);
        NVIC_EnableIRQ(UART5_IRQn);
        NVIC_DisableIRQ(TIM6_IRQn);
        NVIC_DisableIRQ(TIM7_IRQn);
        NVIC_DisableIRQ(UART4_IRQn);
    }
    else if(SYS_STATUS==Sys_PAYING)
    {
        NVIC_EnableIRQ(TIM7_IRQn);
        NVIC_EnableIRQ(USART1_IRQn);//等待停止标志
        NVIC_EnableIRQ(UART4_IRQn);
        NVIC_DisableIRQ(UART5_IRQn);
        NVIC_DisableIRQ(TIM6_IRQn);
    }
    else if(SYS_STATUS==Sys_WORKING)
    {
        NVIC_DisableIRQ(USART1_IRQn);
        NVIC_EnableIRQ(TIM6_IRQn);
        NVIC_DisableIRQ(UART4_IRQn);
        NVIC_DisableIRQ(UART5_IRQn);
        NVIC_DisableIRQ(TIM7_IRQn);
    }
    else if(SYS_STATUS==Sys_WAITING_LOAD)
    {
        NVIC_DisableIRQ(UART4_IRQn);
        NVIC_DisableIRQ(UART5_IRQn);
        NVIC_DisableIRQ(TIM7_IRQn);
        NVIC_DisableIRQ(TIM6_IRQn);
        NVIC_EnableIRQ(USART1_IRQn);
    }
    else 
    {
        NVIC_DisableIRQ(UART4_IRQn);
        NVIC_DisableIRQ(UART5_IRQn);
        NVIC_EnableIRQ(TIM7_IRQn);
        NVIC_DisableIRQ(TIM6_IRQn);
        NVIC_DisableIRQ(USART1_IRQn);
    }
}
