#ifndef __SYS_CONFIG_H_
#define __SYS_CONFIG_H_

#include "stm32f10x.h"
#include "./flash/W25Q16.h"
//#include "./scan/GM65.h"
#include "./sys/sys.h"
#include "./usart/usart.h"
#include "./Motor/motor.h"
#include "./worksystem/worksystem.h"

typedef enum Sys_status
{
    Sys_WAITING = 0,  //等待
    Sys_WASHING,      //清洗
    Sys_WAITING_LOAD, //等待装填
    Sys_PAYING,       //支付阶段
    Sys_WORKING,      //制作阶段
    Sys_DEBUG,        //调试BUG
}Sys_status;

/*--------------------FLASH----------------------*/
extern uint8_t app_config[20];//设备信息
/*--------------------GM65----------------------*/

/*--------------------Motor----------------------*/

/*------------------WorkSystem--------------------*/
extern uint8_t NEXT_ACTION;//跳转控制条件
/*---------------------WAITING---------------------*/

/*---------------------WASHING---------------------*/

/*---------------------WAITING_LOAD---------------------*/

/*---------------------PAYING---------------------*/

/*---------------------WORKING---------------------*/


#endif
