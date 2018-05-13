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
    while (1)
    {
        switch (COMMAND)
        {
        case START_SCAN:
            printf("start scan!");
            GM65_WriteCommand(0x0002, 0x41);
            COMMAND = 0X00;
            break;
        case STOP_SCAN:
            printf("stop scan!");
            COMMAND = 0X00;
            break;
        }

        if (ERROR_TYPE)
        {
            switch (ERROR_TYPE)
            {
            case LEN_ERROR:
                printf("Len Error! More Than 100! System Reboot\r\n");
                ERROR_TYPE = 0;
                break;
            case HEADER_ERROR:
                ERROR_TYPE = 0;
                printf("Header Error %x %x,System Reboot\r\n", rx_buff[0],
                       rx_buff[1]);
                break;
            case SUM_ERROR:
                ERROR_TYPE = 0;
                printf("Sum Error!\r\n");
                break;
            case TAIL_ERROR:
                printf("Tail Error!\r\n");
                ERROR_TYPE = 0;
                break;      
            }
        }

        delay_ms(1000);
        output(rx_buff);
        //		printf("SUCCESS;%ld;ERROR:%d\r\n",SUCCESS_FLAG,ERROR_FLAG);
        //		delay_ms(2000);
        //    if(Sys_status==WAITING)
        //    {
        //      //这个状态里有两个中断,一个TIM中断计数时间,如果30分钟没人来就开一次清洗
        //      //另一个中断为串口中断,等待上位机给的命令,设定优先级为串口中断高于TIM中断
        //      if(WORKING_FLAG==WASHING)
        //      {
        //        Start_Washing();
        //      }
        //      //如果等到支付信号就将状态切换为PAYING状态,并且将空闲TIM中断关闭,计数清零,
        //      //上位机串口中断关闭
        //    }
        //    else if(sys_status==PAYING)
        //    {
        //        GM65_SCAN();//发扫描命令之前打开UART4中断和TIM中断
        //        //20s内没有支付就停止,停止的时候把PAY_FLAG置1
        //        //等待上位机验证
        //        //上位机返回OK的话将sys_status置为WORKING,进入WORKING状态
        //        if(PAY_FLAG==1)
        //        {
        //          sys_status=WAITING;//跳回
        //          break;
        //        }

        //    }
        //    else//WORKING
        //    {
        //        Start_Working();
        //        //关闭UART4中断和TIM中断
        //        //加载结构体
        //    }
    }
}

/*********************************************END OF FILE**********************/
