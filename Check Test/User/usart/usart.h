#ifndef __USART_H
#define	__USART_H


#include "stm32f10x.h"
#include "stdio.h"
#include "sys_config.h"

void USART_Config(void); 
void FeedBack(uint8_t *data, USART_TypeDef *USARTx, int LEN);

#endif /* __USART_H */
