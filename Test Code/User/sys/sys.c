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
    //SPI_FLASH_Init();
    Motor_Config();
    USART_Config();
    //EXTI_Config();
    //NVIC_Config();
		GPIO_SetBits(GPIOD,GPIO_Pin_8);
		GPIO_SetBits(GPIOD,GPIO_Pin_9);
		GPIO_SetBits(GPIOD,GPIO_Pin_10);
		GPIO_SetBits(GPIOD,GPIO_Pin_11);
		GPIO_SetBits(GPIOA,GPIO_Pin_11);
}

void delay_ms(int nms)
{
    uint32_t i;
    SysTick_Config(SystemCoreClock / 1000);
    for (i = 0; i < nms; i++) {
        while (!((SysTick->CTRL) & (1 << 16)))
            ;
    }
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void delay_us(int nus)
{
    uint32_t i;
    SysTick_Config(SystemCoreClock / 1000000);
    for (i = 0; i < nus; i++) {
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
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void Work_Demo(void)
{
    //磨豆机运行 x秒
    delay_ms(1000);

    NVIC_EnableIRQ(EXTI9_5_IRQn);
    //中断触发后自动停止电机 关闭中断

    //开启锅炉的一档
    //打开废水阀
    //打开增压泵
    //等待5秒 等待出热水
    //关闭废水阀 打开前往冲泡器的阀
    //等待出水 等待几秒
    NVIC_EnableIRQ(EXTI15_10_IRQn);
    //到位之后关闭中断
    //此时已得到咖啡液
    //蠕动泵启动 加入牛奶若干
}
