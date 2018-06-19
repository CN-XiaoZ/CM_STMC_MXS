/**
 ******************************************************************************
 * @file    main.c
 * @author  fire
 * @version V1.0
 * @date    2013-xx-xx
 * @brief   华邦
 *8M串行flash测试，并将测试信息通过串口1在电脑的超级终端中打印出来
 ******************************************************************************
 * @attention
 *
 * 实验平台:秉火 F103-霸道 STM32 开发板
 * 论坛    :http://www.firebbs.cn
 * 淘宝    :https://fire-stm32.taobao.com
 *
 ******************************************************************************
 */
#include "stm32f10x.h"
#include "string.h"
#include "sys_config.h"

#define START_SCAN 0x01
#define STOP_SCAN 0x02

#define LEN_ERROR 1
#define HEADER_ERROR 2
#define SUM_ERROR 3
#define TAIL_ERROR 4
//自行修改为对应命令码

enum Sys_status
{
    Sys_WAITING = 0,  //等待
    Sys_WASHING,      //清洗
    Sys_WAITING_LOAD, //等待装填
    Sys_PAYING,       //支付阶段
    Sys_WORKING,      //制作阶段
};
extern uint8_t rx_buff[100];
extern uint8_t ERROR_FLAG;
extern long int SUCCESS_FLAG;
extern int COMMAND;
extern int ERROR_TYPE;

int main(void)
{
    sys_init();

    //    printf("aa\r\n");
    // GM65_WriteCommand(0x0000,0x7F);//1
    printf("Working\r\n");
    ice_power_press;
    delay_ms(500);
    ice_power_release;

    /*
    压力传感器，改引脚号
    //    GPIO_ResetBits(GPIOF, GPIO_Pin_6);		//拉低sck
    //		count = 0;
    //		while(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_7));//等待dout下降沿
    //		for(i=0;i<24;i++)
    //		{
    //			GPIO_SetBits(GPIOF, GPIO_Pin_6);	
    //			count = count<<1;
    //			GPIO_ResetBits(GPIOF, GPIO_Pin_6);	
    //			if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_7))
    //				count++;
    //		}//读取24位
    //		GPIO_SetBits(GPIOF, GPIO_Pin_6);	
    //		count = count^0x800000;
    //		GPIO_ResetBits(GPIOF, GPIO_Pin_6);	
    */
    while (1)
    {
        if (ice_p6)
            led1_on;
        else
            led1_off;
        if (ice_p2 && !ice_p3 && ice_p4 && !ice_p5 && ice_p6)
            led2_on;
        else
            led2_off;
    }
}

/*********************************************END OF FILE**********************/
