#ifndef __GM65_H
#define __GM65_H

#include "stm32f10x.h"

void GM65_SERIAL_Init(void);
void GM65_SCAN(void);
void GM65_ReadCommand(uint16_t Address,uint8_t Data);
void GM65_WriteCommand(uint8_t NumofData,uint16_t Address,uint8_t *data);
void GM65_SaveCommand(void);
void GM65_SetDefault(void);

#endif
