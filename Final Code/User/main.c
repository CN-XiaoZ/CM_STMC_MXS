/**
  ******************************************************************************
  * @file    main.c
  * @author  ZJU-Xizo
  * @version V1.0
  * @date    2018-02-03
  * @brief   米修斯科技有限公司 原型机 Version 1.0
  ******************************************************************************
  */
#include "stm32f10x.h"
#include "sys_config.h"

uint8_t Sys_status;

/** 
 * @Author: ZJU_Xizo 
 * @Date: 2018-02-27 14:07:26 
 * @Desc: Main Func  
 */
int main(void)
{
		/*可在main中进行改动作为测试*/
    sys_init();//初始化

		NVIC_DisableIRQ(EXTI15_10_IRQn);
		NVIC_DisableIRQ(EXTI9_5_IRQn);
		
		
		while(1)
		{
				delay_s(10);
				GPIO_SetBits(GPIOF,GPIO_Pin_1);
				delay_s(10);
				GPIO_ResetBits(GPIOF,GPIO_Pin_1);
		}
}

/*********************************************END OF FILE**********************/
