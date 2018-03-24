/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "sys_config.h"

uint8_t PAY_Finish=0;
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

//用于安卓和单片机通信
void USART1_IRQHandler(void)
{	
	uint8_t temp;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	{	
		temp = USART_ReceiveData(USART1);
		USART_SendData(USART1,temp);  
	}	 
}

//用于读取二维码
void UART4_IRQHandler(void)
{	
	uint8_t temp;
	if(USART_GetITStatus(UART4,USART_IT_RXNE)!=RESET)
	{	
		temp = USART_ReceiveData(UART4);
		USART_SendData(UART4,temp);  
	}	 
}

//用于监测监控系统的状态
void UART5_IRQHandler(void)
{	
	uint8_t temp;
	if(USART_GetITStatus(UART5,USART_IT_RXNE)!=RESET)
	{	
		temp = USART_ReceiveData(UART5);
		USART_SendData(UART5,temp);  
	}	 
}



void EXTI9_5_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line9) != RESET)
    {
			delay_ms(20);
			if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9) == Bit_SET)
			{

				Motor_Flag++;
				if(GPIO_ReadOutputDataBit(GPIOE,GPIO_Pin_7) == Bit_SET)
				{
					GPIO_ResetBits (GPIOE,GPIO_Pin_7);	
					TIM4->CCR1=7000;
					while(GPIO_ReadOutputDataBit(GPIOE,GPIO_Pin_7) == Bit_SET);
				}
				else
				{
					GPIO_SetBits (GPIOE,GPIO_Pin_7);	
					TIM4->CCR1=7000;
					while(GPIO_ReadOutputDataBit(GPIOE,GPIO_Pin_7) != Bit_SET);
				}
				if(Motor_Flag==3)
				{
					delay_ms(100);
					Motor_Flag=0;
					NVIC_DisableIRQ(EXTI15_10_IRQn);
					NVIC_DisableIRQ(EXTI9_5_IRQn);
					TIM4->CCR1=0;
				}
			}
    }
		EXTI_ClearITPendingBit(EXTI_Line9);
}

void EXTI15_10_IRQHandler(void)
{
		if(EXTI_GetITStatus(EXTI_Line10) != RESET)
    {
			delay_ms(20);
			if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10) == Bit_SET)
			{
				Motor_Flag++;
				if(GPIO_ReadOutputDataBit(GPIOE,GPIO_Pin_7) == Bit_SET)
				{
					GPIO_ResetBits (GPIOE,GPIO_Pin_7);	
					TIM4->CCR1=7000;
					while(GPIO_ReadOutputDataBit(GPIOE,GPIO_Pin_7) == Bit_SET);
				}
				else
				{

					GPIO_SetBits (GPIOE,GPIO_Pin_7);	
					TIM4->CCR1=7000;
					while(GPIO_ReadOutputDataBit(GPIOE,GPIO_Pin_7) != Bit_SET);
				}
				if(Motor_Flag==3)
				{
					delay_ms(100);
					Motor_Flag=0;
					NVIC_DisableIRQ(EXTI15_10_IRQn);
					NVIC_DisableIRQ(EXTI9_5_IRQn);
					TIM4->CCR1=0;
				}
			}
    }
	
		EXTI_ClearITPendingBit(EXTI_Line10);
}


void TIM6_IRQHandler(void)
{
    //定时1S 到达60后返回超时指令 并返回等待状态
    static int Time_count=0;
    if(TIM_GetITStatus( TIM6, TIM_IT_Update) != RESET) 
    { 
        Time_count++;
        if(Time_count>=60)
        {
            Time_Count=0;
            PAY_Finish=0;
            SWITCH_TO_WAITING();
        }
        //两种情况 1. 超时 判断条件是计数大于60，清空所有有关标志位，进入SWITCH_TO_WAITING
        //2. 接收到，转换后发送到上位机，清空所有标志位 ，进入SWITCH_TO_WORK,在WORK阶段判断。
        TIM_ClearITPendingBit(TIM6 , TIM_FLAG_Update);
    }
}

void TIM7_IRQHandler(void)
{
    if(TIM_GetITStatus( TIM7, TIM_IT_Update) != RESET) 
    { 
         
        TIM_ClearITPendingBit(TIM7 , TIM_FLAG_Update);
    }
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
