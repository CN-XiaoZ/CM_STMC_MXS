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
    USART_Config();
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
	   
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//抢占优先级3
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级3
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	  NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

//	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
//	NVIC_Init(&NVIC_InitStructure); 

//	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//	NVIC_Init(&NVIC_InitStructure);

//	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;                                                                 
//    NVIC_Init(&NVIC_InitStructure);
}
