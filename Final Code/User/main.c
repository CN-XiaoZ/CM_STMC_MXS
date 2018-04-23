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

//1.蓝线接M2 红线接M1     E7置高是倒转  先碰右开关 
//  也就是应当先置低 等待右开关触发，停止，执行其他动作 再置高，等待碰到开关后停止。 PE9是右开关
uint8_t Sys_status;
//初定3.15是一次行程 n
/** 
 * @Author: ZJU_Xizo 
 * @Date: 2018-02-27 14:07:26 
 * @Desc: Main Func  
 */
int main(void)
{
	int i=0;
	float time=2.78;
  sys_init();
//		delay_s(5);
//		GPIO_ResetBits(GPIOD,GPIO_Pin_9);
//		delay_s(5);
//		GPIO_SetBits(GPIOD,GPIO_Pin_9);
//		//DAC_SetChannel2Data(DAC_Align_12b_R,3000);
/*----------冷水--------------*/
	//Motor_Step1();
	DAC_SetChannel2Data(DAC_Align_12b_R,3000);
	GPIO_ResetBits(JRS1);
	GPIO_ResetBits(JRS2);
	GPIO_SetBits(DCF2);

	
//	DAC_SetChannel2Data(DAC_Align_12b_R,3000);
//	delay_s(40);
//	DAC_SetChannel2Data(DAC_Align_12b_R,0);
//	GPIO_SetBits(DCF2);
//	GPIO_SetBits(DCF1);
//	delay_s(3);
//	GPIO_ResetBits(DCF2);
//	GPIO_ResetBits(DCF1);
//	Motor_Step2(); 
	

	while(1)
	{}
//	GPIO_ResetBits(MDJ1);
//	delay_s(time);
//	GPIO_SetBits(MDJ1);
//	Motor_Step1();
//	DAC_SetChannel2Data(DAC_Align_12b_R,3000);
//	GPIO_SetBits(DCF2);
//	delay_s(10);
//	DAC_SetChannel2Data(DAC_Align_12b_R,0);
//	GPIO_SetBits(DCF1);
//	delay_s(2);
//	GPIO_ResetBits(DCF2);
	
/*------------------------------*/
	 
    //蓝线接M2 红线接M1    
//		GPIO_ResetBits(JRS1);
//	GPIO_ResetBits(JRS2);
//	delay_s(1);
//	DAC_SetChannel2Data(DAC_Align_12b_R,1600);
//	GPIO_SetBits(DCF1);
//	delay_s(70);
//	GPIO_ResetBits(DCF1);
//	DAC_SetChannel2Data(DAC_Align_12b_R,0);
//	GPIO_SetBits(JRS1);
//	GPIO_SetBits(JRS2);
//	TIM4->CCR3=9000;
//	delay_s(40);
	
}



/*********************************************END OF FILE**********************/
