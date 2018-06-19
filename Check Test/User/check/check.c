#include "sys_config.h"

void Check_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                               RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
                               RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF |
                               RCC_APB2Periph_GPIOG,
                           ENABLE);

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    /*--------------OUT_OD-----------------*/

    // IN
    
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    //漫反射开关
    GPIO_InitStructure.GPIO_Pin = MFS1_PIN;
    GPIO_Init(MFS1_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = MFS2_PIN;
    GPIO_Init(MFS2_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = MFS3_PIN;
    GPIO_Init(MFS3_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = MFS4_PIN;
    GPIO_Init(MFS4_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = MFS5_PIN;
    GPIO_Init(MFS5_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = MFS6_PIN;
    GPIO_Init(MFS6_PORT, &GPIO_InitStructure);

    
    //制冰机信号读取
    GPIO_InitStructure.GPIO_Pin = ICE_P2_PIN;
    GPIO_Init(ICE_P2_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = ICE_P3_PIN;
    GPIO_Init(ICE_P3_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = ICE_P4_PIN;
    GPIO_Init(ICE_P4_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = ICE_P5_PIN;
    GPIO_Init(ICE_P5_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = ICE_P6_PIN;
    GPIO_Init(ICE_P6_PORT, &GPIO_InitStructure);
		
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    //牛奶压力传感器
    GPIO_InitStructure.GPIO_Pin = MILK1_DOUT_PIN;
    GPIO_Init(MILK1_DOUT_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = MILK2_DOUT_PIN;
    GPIO_Init(MILK2_DOUT_PORT, &GPIO_InitStructure);

    //液位管
    GPIO_InitStructure.GPIO_Pin = YWG1_PIN;
    GPIO_Init(YWG1_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = YWG2_PIN;
    GPIO_Init(YWG2_PORT, &GPIO_InitStructure);

    //缓冲水罐液位计
    GPIO_InitStructure.GPIO_Pin = YWJ1_HIGH_PIN;
    GPIO_Init(YWJ1_HIGH_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = YWJ1_LOW_PIN;
    GPIO_Init(YWJ1_LOW_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = YWJ2_HIGH_PIN;
    GPIO_Init(YWJ2_HIGH_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = YWJ2_LOW_PIN;
    GPIO_Init(YWJ2_LOW_PORT, &GPIO_InitStructure);


    //OUT
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    

		
    //压力传感器时序
    GPIO_InitStructure.GPIO_Pin = MILK1_SCK_PIN;
    GPIO_Init(MILK1_SCK_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = MILK2_SCK_PIN;
    GPIO_Init(MILK2_SCK_PORT, &GPIO_InitStructure);

    //制冰机控制
    GPIO_InitStructure.GPIO_Pin = POWER_SET_PIN;
    GPIO_Init(POWER_SET_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = ICE_SET_PIN;
    GPIO_Init(ICE_SET_PORT, &GPIO_InitStructure);
		
		//LED
		GPIO_InitStructure.GPIO_Pin = LED1_PIN;
    GPIO_Init(LED1_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = LED2_PIN;
    GPIO_Init(LED2_PORT, &GPIO_InitStructure);
		
		GPIO_SetBits(LED1_PORT, LED1_PIN);	
		GPIO_SetBits(LED2_PORT, LED2_PIN);	
    /*-------------INIT-------------------*/

}
