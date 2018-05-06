#ifndef __SYS_CONFIG_H_
#define __SYS_CONFIG_H_

#include "stm32f10x.h"
#include "./flash/W25Q16.h"
//#include "./scan/GM65.h"
#include "./sys/sys.h"
#include "./usart/usart.h"
#include "./Motor/motor.h"

#define DAC1VOL 1.5
#define DAC2VOL 1.5

enum Sys_status
{
    Sys_WAITING = 0,  //等待
    Sys_WASHING,      //清洗
    Sys_WAITING_LOAD, //等待装填
    Sys_PAYING,       //支付阶段
    Sys_WORKING,      //制作阶段
};

extern int Flow_Index;//流量计序号
extern int Flow_Count;//流量计达到流量需要值标志

#endif
