/**
  ******************************************************************************
  * @file    usart.c
  * @version V1.0
  * @date    2018-1-4
  * @brief   USART配置
  ******************************************************************************
  */
#include "./usart/usart.h"

/**
  * @brief  USART GPIO 配置,工作参数配置
  * @param  无
  * @retval 无
  */
void USART_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    //	NVIC_InitTypeDef NVIC_InitStructure;

    //USART时钟配置
    //	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4|RCC_APB1Periph_UART5, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE); //使能USART1，GPIOA时钟

    USART_DeInit(USART1); //复位串口1
                          //USART中断设置
                          //	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
                          //	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
                          //	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
                          //  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
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
                          //GPIO设置
                          //	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
                          //	//TX
                          //	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
                          //	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
                          //	GPIO_Init(GPIOA, &GPIO_InitStructure);
                          //	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
                          //	GPIO_Init(GPIOC, &GPIO_InitStructure);
                          //	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
                          //	GPIO_Init(GPIOC, &GPIO_InitStructure);
                          //	//RX
                          //	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
                          //	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
                          //	GPIO_Init(GPIOA, &GPIO_InitStructure);
                          //	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
                          //	GPIO_Init(GPIOC, &GPIO_InitStructure);
                          //	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
                          //	GPIO_Init(GPIOD, &GPIO_InitStructure);

    //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);          //初始化PA9

    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);                //初始化PA10

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //开启中断
    USART_Cmd(USART1, ENABLE);                     //使能串口

    //	USART_Init(USART2, &USART_InitStructure);
    //	USART_Cmd(USART2, ENABLE);
}

///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
    /* 发送一个字节数据到串口 */
    USART_SendData(DEBUG_USARTx, (uint8_t)ch);

    /* 等待发送完毕 */
    while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET)
        ;

    return (ch);
}

///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
    /* 等待串口输入数据 */
    while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET)
        ;

    return (int)USART_ReceiveData(DEBUG_USARTx);
}

void output(uint8_t *buff)
{
    int i = 0;
    printf("buff:");
    for (i = 0; buff[i] != 0; i++)
    {
        printf("%x ", buff[i]);
    }
    printf("\r\n");
}
