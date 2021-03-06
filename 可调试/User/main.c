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

#define ON 0
#define OFF 1
uint8_t NEXT_ACTION=0;
/**
 * @Author: ZJU_Xizo
 * @Date: 2018-02-27 14:07:26
 * @Desc: Main Func7
 */
int main(void)
{
    sys_init();
    //printf("WORKING!");
		//打开蠕动泵，打开锅炉，看是不是蒸汽
//着那个是RDB7
Motor_Step1();
	Motor_Step2(); 

Motor_Step2();
	while(1)
	{
	}
}

/*********************************************END OF FILE**********************/
