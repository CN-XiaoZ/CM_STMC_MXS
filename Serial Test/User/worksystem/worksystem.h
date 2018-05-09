#ifndef __WORK_SYSTEM_H_
#define __WORK_SYSTEM_H_

#include "sys_config.h"
/**
 * Flash空间分配
 * uint8_t Order_buffer[256];
 * uint8_t Sys_info[256];
 * 需要存储的数据：机器编号 固件版本 30配方信息 每条指令需要6字节 每个配方信息最多40条指令 每个配方256字节 （带配方编号）
 * 256字节*40+1+2 //20KB空间 不能使用内嵌的 直接用Flash读取
 * 每个地址存储一个uint8_t位数据 2M->2*1024K->2*1024*1024个Byte,即uint8_t 地址空间：0x00000000-0x001FFFFF 
 * 扇区等于16页 即16*256=4096数据 扇区地址为0x00000000+n*4096 页地址为0x00000000+n*256
 * 第一页写信息 第17页开始写配方
 * 第一页信息示例
 * 信息存储区地址为0x00000000
 * 配方存储区地址为0x00001000
 * 配方n的存储地址为0x00001000+n*0x100
 * 
 * 
 * 
 */



#define SYS_INFO_ADDR 0x00000000

#define FORMULA_ADDR(n) 0x00001000+n*0x100
//Flash部分
void Update_Sysinfo(uint8_t * Sys_info); //更新系统信息

void Formula_Insert(uin8_t * Order_Buffer,uint8_t index);//加入配方

void Read_Formula(uint8_t * Order_Buffer);

//事件处理部分
void Work_Start(uint8_t * Order_Buffer);//方便调试


//配方最后6位为FFFFFF





#endif