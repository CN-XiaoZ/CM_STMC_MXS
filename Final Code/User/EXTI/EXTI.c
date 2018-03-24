#include "./EXTI/EXTI.h"

void EXTI_Config(void) {
    GPIO_InitTypeDef GPIO_InitStructure; 
    EXTI_InitTypeDef EXTI_InitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
    RCC_APB2PeriphClockCmd(SWITCH1_CLK | SWITCH2_CLK, ENABLE); 

    GPIO_InitStructure.GPIO_Pin = SWITCH1_PIN; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
    GPIO_Init(SWITCH1_PORT,  & GPIO_InitStructure); 

    GPIO_InitStructure.GPIO_Pin = SWITCH2_PIN; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
    GPIO_Init(SWITCH2_PORT,  & GPIO_InitStructure); 
		
	EXTI_ClearITPendingBit(EXTI_Line9); 
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource9); 
    EXTI_InitStructure.EXTI_Line = EXTI_Line9; 
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; 
    EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
    EXTI_Init( & EXTI_InitStructure); 

	EXTI_ClearITPendingBit(EXTI_Line10); 
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource10); 
    EXTI_InitStructure.EXTI_Line = EXTI_Line10; 
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; 
    EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
    EXTI_Init( & EXTI_InitStructure); 
    
}