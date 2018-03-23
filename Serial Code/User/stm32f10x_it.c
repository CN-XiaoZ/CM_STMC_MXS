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
 

void USART1_IRQHandler(void)
{	
  static uint8_t rx_buff[100] = {0};
	static uint8_t pointer = 0;
  static uint8_t LEN;
  uint8_t count=0;
	uint8_t temp;
  uint8_t ERROR_FLAG=0;
  uint16_t sum=0; 
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	{	
    temp = USART1->DR;//收入一个信号
    if (pointer < 2)
		{
			rx_buff[pointer++] = temp;
			return;
		}
    if (pointer == 2) //防止缺位
		{
			if ((rx_buff[0] == 0x12) && (rx_buff[1] == 0x34))
			{
        rx_buff[pointer++] = temp;
        LEN=temp;
      }
			else
			{
				rx_buff[0] = rx_buff[1];
				rx_buff[1] = temp;
			}
			return;
		}
    if (pointer > 2)
		{
      if(pointer<LEN)
      {
        rx_buff[pointer++] = temp;
			  if (pointer == LEN)
			  {
          //指令接收结束
          if(rx_buff[LEN]==0x2F&&rx_buff[LEN-1]==0x1F)
          {s
            for(count=2;count<LEN-3;count++)
            {
              sum=rx_buff[count]+sum;
            }
            if(sum==rx_buff[LEN-2])//验证校验
            {

            }
          }

          //指令判断流程
          //验证文件尾
          //验证指令校验位
          //读取指令


          //标志清空
          if(ERROR_FLAG==1)
          {
            //发送接收错误指令 等待下一次接收
          }
          pointer=0;
          memset(rx_buff,0,100*sizeof(uint8_t));
        }
      }
    }
	}	
  USART_ClearITPendingBit(USART6, USART_IT_RXNE);
	USART_ClearFlag(USART6, USART_FLAG_RXNE); 
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
