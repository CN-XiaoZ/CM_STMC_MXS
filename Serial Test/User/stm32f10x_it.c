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
#include "sys_config.h"
extern Sys_status SYS_STATUS;
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

//不使用TIM7中断
extern uint16_t Order[60][3];
extern uint8_t Config[16];
extern uint8_t FEEDBACK[5];
int TIM6TICK;
int Pos = 0;
void TIM6_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
    {
        while (Order[Pos][1] == TIM6TICK )
        {
            Action(Order[Pos][0], Order[Pos][2]);
						printf("MechineID:%d Time:%d ONorOFF:%d\r\n",Order[Pos][0],Order[Pos][1],Order[Pos][2]);
						Pos++;
        }
				
        TIM6TICK++;
        if(Order[Pos][0]+Order[Pos][1]+Order[Pos][2]==0)
        {
					printf("System Stop!\r\n");
					TIM6TICK=0;
          Pos=0;
          NVIC_DisableIRQ(TIM6_IRQn);
					//printf("System Stop!\r\n");
            
					
        }
        
        TIM_ClearITPendingBit(TIM6, TIM_FLAG_Update);
        TIM_ClearFlag(TIM6, USART_FLAG_RXNE);
    }
}

uint8_t pointer = 0;
uint8_t rx_buff[256];
uint8_t LEN;
uint8_t count;
uint8_t sum;
void USART1_IRQHandler(void)
{
    uint8_t temp;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        temp = USART_ReceiveData(USART1);
        if (pointer < 2)
        {
            rx_buff[pointer++] = temp;
            return;
        }
        if (pointer == 2)
        {
            if ((rx_buff[0] == 0x12) && (rx_buff[1] == 0x34))
            {
                rx_buff[pointer++] = temp;
                LEN                = temp;
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
                        if ( rx_buff[LEN - 3]==sum)
                        {
                            if (SYS_STATUS ==
                                Sys_INIT) // INIT里，先检查第一位是不是0x00，代表这个是INIT指令
                            { //之后检查是不是第一位和第二位为起始标志，是的话将接收到的20和数组写入FLASH中
                                if (rx_buff[3] == 0x00 && rx_buff[4] == 0x01 &&
                                    rx_buff[5] == 0xFE)
                                {
                                    SPI_FLASH_BulkErase();
                                    for (count = 4; count < 24; count++)
                                    {
                                        app_config[count - 4] = rx_buff
                                            [count]; //数组信息复制到app_config内
                                    }
                                    SPI_FLASH_BufferWrite(app_config,
                                                          SYS_INFO_ADDR,
                                                          20); //写入Flash
                                    SYS_STATUS =
                                        Sys_WAITING; //写入完成改写系统状态为WAITING状态
                                    NEXT_ACTION = 1; //进入下一个
                                }
                                if (rx_buff[3] == 0x00 && rx_buff[4] == 0xFE)
                                {
                                    FEEDBACK[2] = 0x01;
                                    FeedBack(FEEDBACK, USART1, 5); // DEBUG
                                    SYS_STATUS  = Sys_DEBUG;
                                    NEXT_ACTION = 1;
                                }
																if (rx_buff[3] == 0x00 && rx_buff[4] == 0xFD)
                                {
                                    FEEDBACK[2] = 0x02;
                                    FeedBack(FEEDBACK, USART1, 5); // WAITING
                                    SYS_STATUS  = Sys_WAITING;
                                    NEXT_ACTION = 1;
                                }
                            }
                            else if (SYS_STATUS == Sys_WAITING) // WAITING中功能
                            {
                                //功能：
                                //跳转到WASHING，WAITING——LOAD，PAYING，DEBUGING，返回检测数据
                                if (rx_buff[3] == 0x01)
                                {
                                    FEEDBACK[2] = 0x02;
                                    FeedBack(FEEDBACK, USART1, 5); // WASHING
                                    SYS_STATUS  = Sys_WASHING;
                                    NEXT_ACTION = 1;
                                }
                                if (rx_buff[3] == 0x02)
                                {
                                    FEEDBACK[2] = 0x03;
                                    FeedBack(FEEDBACK, USART1,
                                             5); // WAITING_LOAD
                                    SYS_STATUS  = Sys_WAITING_LOAD;
                                    NEXT_ACTION = 1;
                                }
                                if (rx_buff[3] == 0x03)
                                {
                                    FEEDBACK[2] = 0x04;
                                    FeedBack(FEEDBACK, USART1, 5); // PAYING
                                    SYS_STATUS  = Sys_PAYING;
                                    NEXT_ACTION = 1;
                                }
                                if (rx_buff[3] == 0x04)
                                {
                                    FEEDBACK[2] = 0x01;
                                    FeedBack(FEEDBACK, USART1, 5); // DEBUG
                                    SYS_STATUS  = Sys_DEBUG;
                                    NEXT_ACTION = 1;
                                }
                                if (rx_buff[3] == 0x05)
                                {
                                    // TODO:返回监测数据
                                }
                                // TODO:机体信息接口
                            }
                            else if (SYS_STATUS ==
                                     Sys_PAYING) //序号从0x20开始
                                                 //指令跳回WAITING，
                            {
                                if (rx_buff[3] == 0x20) //不再支付，跳回WAITING
                                {
                                    FEEDBACK[2] = 0x06;
                                    FeedBack(FEEDBACK, USART1, 5); // STOP SCAN
                                    NEXT_ACTION = 1;
                                }
                            }
                            else if (
                                SYS_STATUS ==
                                Sys_DEBUG) //接收指令并执行指令内容，跳回WAITING
                            {
                                if (rx_buff[3] == 0x21)
                                {
                                    FEEDBACK[2] = 0x02;
                                    FeedBack(FEEDBACK, USART1, 5); // WAITING
                                    SYS_STATUS  = Sys_WAITING;
                                    NEXT_ACTION = 1;
                                }
                                if (rx_buff[2] == 0xFF)
                                {

                                    FEEDBACK[2] = 0x08;
                                    FeedBack(FEEDBACK, USART1, 5);//接收到指令

                                    for (count = 0; count < 9; count++)
                                    {
                                        Config[count] = rx_buff[count + 3];
                                    }
                                    for (count = 0; count < 60; count++)
                                    {
                                        Order[count][0] = rx_buff[4 * count + 12];
                                        Order[count][1] =
                                            Change8to16(rx_buff[4 * count + 13],
                                                        rx_buff[4 * count + 14]);
                                        Order[count][2] = rx_buff[4 * count + 15];
                                    }
                                    TIM6TICK=0;
                                    Pos=0;
                                    FEEDBACK[2] = 0x09;
                                    FeedBack(FEEDBACK, USART1, 5);
																		for(count=0;count<17;count++)
																		{
																			printf("Action(%d,%d,%d)\r\n",Order[count][0],Order[count][1],Order[count][2]);
																		}
																		
																		NVIC_EnableIRQ(TIM6_IRQn);
                                }
                                //
                            }
                            else if (SYS_STATUS ==
                                     Sys_WAITING_LOAD) // Sys_WAITING_LOAD
                            {
                                //等检测系统搞好再来
                            }
                            else if (SYS_STATUS == Sys_WORKING)
                            {
                                FEEDBACK[2] = 0x07;
                                FeedBack(FEEDBACK, USART1, 5); // WORKING
                            }
                        }
                        else
                        {
                            printf("Error Sum! Sum=%x",sum);
                        }
                    }
                    else
                    {
                        printf("Error Tailrx_buff[LEN - 1] == %x && rx_buff[LEN - 2] == %x",rx_buff[LEN - 1],rx_buff[LEN - 2]);
                    }
                    sum     = 0;
                    pointer = 0;
                    memset(rx_buff, 0, 256 * sizeof(uint8_t));
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
/*
USART1_IRQn,
UART4_IRQn,
TIM6_IRQn,
TIM7_IRQn,
中断情况记录：
WAITING：UART5 USART1 中断优先级USART1>UART5
逻辑改为需要上位机发送指令来读取才会给UART5发送指令让其读入，所以没有优先级，必然USART1和UART5会相继触发
PAYING:
开启UASRT1，打开UART4和TIM7中断，TIM7设置为1S一次，打开Update中断，等待25S如果没有返回就等待1S再发送一遍读取指令，再次没有返回就停止。USART1可能会有停止命令
再已经返回后可能有校验成功或不成功的命令
WORKING：只打开TIM6中断 Work全部在TIm6中完成。
*/

static int ERCode_Pos      = 0;
static int ERCode_Temp[25] = {0};
void UART4_IRQHandler(void)
{
    if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
    {
        if (ERCode_Pos < 25)
        {
            ERCode_Temp[ERCode_Pos] = USART_ReceiveData(UART4);
            ERCode_Pos++;
        }
        if (ERCode_Pos == 25)
        {
            //组织好指令
            //向UASRT1传输
            ERCode_Pos = 0;
            memset(ERCode_Temp, 0, 25);
        }
    }
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    USART_ClearFlag(USART1, USART_FLAG_RXNE);
}

void UART5_IRQHandler(void)
{
    uint8_t temp;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        temp = USART_ReceiveData(USART1);
        USART_SendData(USART1, temp);
    }
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
