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

/*-------------FLAG---------------—*/

/*-------------FLAG----------------*/
//WAITING

//PAYING

//WORKING



/*-------------FLAG----------------*/

const uint8_t SUM_FAIL_FEEDBACK={0x12,0x34,0xFE,0x1F,0x2F};
const uint8_t WASHING_ENTER_FEEDBACK={0x12,0x34,0xFE,0x1F,0x2F};
const uint8_t WASHING_FINISH_FEEDBACK={0x12,0x34,0xFE,0x1F,0x2F};
const uint8_t PAY_TIMEOUT_FEEDBACK={0x12,0x34,0xFE,0x1F,0x2F};
const uint8_t SUM_FAIL_FEEDBACK={0x12,0x34,0xFE,0x1F,0x2F};
const uint8_t SUM_FAIL_FEEDBACK={0x12,0x34,0xFE,0x1F,0x2F};
const uint8_t SUM_FAIL_FEEDBACK={0x12,0x34,0xFE,0x1F,0x2F};
const uint8_t SUM_FAIL_FEEDBACK={0x12,0x34,0xFE,0x1F,0x2F};
const uint8_t SUM_FAIL_FEEDBACK={0x12,0x34,0xFE,0x1F,0x2F};
const uint8_t SUM_FAIL_FEEDBACK={0x12,0x34,0xFE,0x1F,0x2F};
const uint8_t SUM_FAIL_FEEDBACK={0x12,0x34,0xFE,0x1F,0x2F};
const uint8_t SUM_FAIL_FEEDBACK={0x12,0x34,0xFE,0x1F,0x2F};


/**
 * @Author: ZJU_Xizo
 * @Date: 2018-02-27 14:07:26
 * @Desc: Main Func
 */
int main(void)
{
    uint8_t NEXT_ACTION=0;
    sys_init();
    printf("WORKING!");
    while (1)
    {
        if (SYS_STATUS == WAITING)
        {                            
            NVIC_EnableIRQ(USRAT1_IRQn); //功能为等待在WAITING时期的命令
            while(NEXT_ACTION==0);
            NEXT_ACTION=0;
        }
        else if (SYS_STATUS == WASHING)
        {
            delay_s(5);//TODO:这里之后加入清洗流程
            printf("WASHING COMPELTE\r\n");
            SYS_STATUS=WAITING;
            NEXT_ACTION=0;
        }
        else if (SYS_STATUS == PAYING)
        {
            NVIC_EnableIRQ(USART1_IRQn);
            NVIC_EnableIRQ(UART4_IRQn);
            while(NEXT_ACTION==0);
            NEXT_ACTION==0;
        }
        else//working
        {
            delay_s(2);
            
        }
    }
}

/*********************************************END OF FILE**********************/
