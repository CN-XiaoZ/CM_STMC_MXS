/**
  ******************************************************************************
  * @file    bsp_usart.c
  * @version V1.0
  * @date    2018-02-01
  * @brief   调试用的printf串口，重定向printf到串口
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
    //USART时钟配置
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4 | RCC_APB1Periph_UART5, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_USART1, ENABLE);
    //USART中断设置
    //GPIO设置
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //TX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    //RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
    USART_Init(UART4, &USART_InitStructure);
    USART_Cmd(UART4, ENABLE);
    USART_Init(UART5, &USART_InitStructure);
    USART_Cmd(UART5, ENABLE);

}

///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE* f)
{
    /* 发送一个字节数据到串口 */
    USART_SendData(DEBUG_USARTx, (uint8_t)ch);

    /* 等待发送完毕 */
    while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET)
        ;

    return (ch);
}

///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE* f)
{
    /* 等待串口输入数据 */
    while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET)
        ;

    return (int)USART_ReceiveData(DEBUG_USARTx);
}
