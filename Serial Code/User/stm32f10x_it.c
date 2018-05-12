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
#include "string.h"
#include "usart.h"
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
void NMI_Handler(void) {}

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
void SVC_Handler(void) {}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void) {}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void) {}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void) {}

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
uint8_t rx_buff[100]  = {0};
uint8_t ERROR_FLAG    = 0;
int ERROR_TYPE = 0;
long int SUCCESS_FLAG = 0;
int COMMAND = 0x00;
void USART1_IRQHandler(void)
{
    static uint8_t pointer = 0;
    static uint8_t LEN;
    uint8_t count = 0;
    uint8_t temp;

    uint16_t sum = 0;
    int i = 0;
    if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
    {
        temp = USART_ReceiveData(USART1); //收入一个信号
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
                LEN = temp+6;
                if (LEN > 0x64)
                {
                    
										ERROR_TYPE = 1;
									__set_FAULTMASK(1);
                    NVIC_SystemReset();
                }
            }
            else
            {
                //printf("Header Error %x %x,System Reboot\r\n", rx_buff[0], rx_buff[1]);
								ERROR_TYPE = 2;
                //__set_FAULTMASK(1);
                //NVIC_SystemReset();
                rx_buff[0] = rx_buff[1];
                rx_buff[1] = temp;
            }
            return;
        }
        if (pointer > 2)
        {
            if (pointer < LEN)
            {
                rx_buff[pointer++] = temp;
                if (pointer == LEN)
                {

                    if (rx_buff[LEN - 1] == 0x2F && rx_buff[LEN - 2] == 0x1F)
                    {
                        for (count = 2; count < LEN - 3; count++)
                        {
                            sum = rx_buff[count] + sum;
                        }
                        if (sum == rx_buff[LEN - 3]) //验证校验
                        {
                            SUCCESS_FLAG++;
                            //做数据处理
														//将命令放入变量中
														COMMAND = rx_buff[3];
                            printf("Success! Content:");
//                            for (i = 0; i < LEN - 6; i++)
//                            {
//                                printf("%x ", rx_buff[3 + i]);
//                            }
//                            printf("\r\n");
                        }
                        else
                        {
                            ERROR_FLAG++;
                            //printf("Sum Error! Sum=%x\r\n", sum);
														ERROR_TYPE = 3;
                        }
                    }
                    else
                    {
                        ERROR_FLAG++;
												ERROR_TYPE = 4;
                        //printf("Tail Error! Tail:%x %x\r\n", rx_buff[LEN - 2], rx_buff[LEN - 1]);
                    }
                    sum     = 0;
                    pointer = 0;
                    memset(rx_buff, 0, 100 * sizeof(uint8_t));
                }
                else
                {
                    return;
                }
            }
        }
    }
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    USART_ClearFlag(USART1, USART_FLAG_RXNE);
}
//中断向量有：
/*USART1_IRQn
UART4_IRQn,
TIM6_IRQn,
TIM7_IRQn,
中断情况记录：
WAITING：UART5 USART1 中断优先级USART1>UART5 逻辑改为需要上位机发送指令来读取才会给UART5发送指令让其读入，所以没有优先级，必然USART1和UART5会相继触发
PAYING: 开启UASRT1，打开UART4和TIM7中断，TIM7设置为1S一次，打开Update中断，等待25S如果没有返回就等待1S再发送一遍读取指令，再次没有返回就停止。USART1可能会有停止命令 再已经返回后可能有校验成功或不成功的命令
WORKING：只打开TIM6中断 Work全部在TIm6中完成。
*/

void UART4_IRQHandler(void)
{
    if (USART_GetFlagStatus(UART4, USART_FLAG_RXNE) == SET)
    {
        USART_SendData(USART1, USART_ReceiveData(UART4));
    }
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
