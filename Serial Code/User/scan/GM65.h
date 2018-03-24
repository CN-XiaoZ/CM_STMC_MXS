#ifndef __GM65_H
#define __GM65_H

#include "stm32f10x.h"

void GM65_Init(void);
void GM65_SCAN(void);
void GM65_ReadCommand(uint16_t Address,uint8_t Data);
void GM65_WriteCommand(uint16_t Address, uint8_t Data);
void GM65_SaveCommand(void);


#endif
