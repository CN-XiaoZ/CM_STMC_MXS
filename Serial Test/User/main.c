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

const uint8_t SUM_FAIL_FEEDBACK[5]={0x12,0x34,0xFE,0x1F,0x2F};


uint8_t NEXT_ACTION=0;
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
        if (SYS_STATUS == Sys_WAITING)
        {                            
            NVIC_EnableIRQ(USART1_IRQn); //功能为等待在WAITING时期的命令
            while(NEXT_ACTION==0);
            NEXT_ACTION=0;
        }
        else if (SYS_STATUS == Sys_WASHING)
        {
            delay_s(5);//TODO:这里之后加入清洗流程
            printf("WASHING COMPELTE\r\n");
            SYS_STATUS=Sys_WAITING;
            NEXT_ACTION=0;
        }
        else if (SYS_STATUS == Sys_PAYING)
        {
            NVIC_EnableIRQ(USART1_IRQn);
            NVIC_EnableIRQ(UART4_IRQn);
            while(NEXT_ACTION==0);
            NEXT_ACTION=0;
        }
        else//working
        {
            delay_s(2);
            
        }
    }
}

/*********************************************END OF FILE**********************/
