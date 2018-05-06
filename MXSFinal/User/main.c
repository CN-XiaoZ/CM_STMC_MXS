/**
  ******************************************************************************
  * @file    main.c
  * @author  ZJU-Xizo
  * @version V2.0
  * @date    2018-02-03
  * @brief   米修斯科技有限公司 原型机 Version 2.0
  ******************************************************************************
  */
#include "stm32f10x.h"
#include "sys_config.h"

// 1.蓝线接M2 红线接M1     E7置高是倒转  先碰右开关
//  也就是应当先置低 等待右开关触发，停止，执行其他动作
//  再置高，等待碰到开关后停止。 PE9是右开关
Sys_status SYS_STATUS;
uint8_t WORK_FLAG = 0;//记录是否为第一次进入阶段在转换阶段命令下改为0
uint8_t PAY_FLAG = 0;//记录是否完成
//初定3.15是一次行程 n
/**
 * @Author: ZJU_Xizo
 * @Date: 2018-02-27 14:07:26
 * @Desc: Main Func
 */
int main(void)
{
    sys_init();
    printf("WORKING!");
    while (1)
    {
        if (SYS_STATUS == WAITING)
        {
            if (WORK_FLAG == 1)
            {                                //只有第一次进入才打开
                NVIC_EnableIRQ(USRAT1_IRQn); //功能为等待在WAITING时期的命令
                WORK_FLAG = 0;
            }
        }
        else if (SYS_STATUS == PAYING)
        {
            if (WORK_FLAG == 1)
            {
                NVIC_EnableIRQ(UART4_IRQn); //等待接收一次，并且在接收之后进行一次校验（从GM65开始的校验），如果成功校验发到上位机，并打开USART1中断进行判断返回正确还是错误，正确的话跳到WORK，错误的话清空相关标志位并重新启动扫描。
                NVIC_EnableIRQ(TIM6_IRQn);  //
                WORK_FLAG=0;
            }
        }
        else//SYS_STATUS
        {
            WorkSystem_Start();
        }
    }
}

/*********************************************END OF FILE**********************/
