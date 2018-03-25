#include "./worksystem/worksystem.h"

void Update_Sysinfo(uint8_t * Sys_info)//本函数放在等待阶段的中断函数中
{
    SPI_FLASH_SectorErase(SYS_INFO_ADDR);//擦除原数据
    SPI_FLASH_PageWrite(Sys_info,SYS_INFO_ADDR,256);//加入新的信息
}

void Formula_Insert(uin8_t * Order_Buffer,uint8_t index)//加配方
{
    SPI_FLASH_PageWrite(Order_Buffer,FORMULA_ADDR(index),256);
}

void Read_Formula(uint8_t * Order_Buffer)
{
    SPI_FLASH_BufferRead(Order_Buffer,FORMULA_ADDR(index),256);
}

/**
 * OrderBuffer的格式
 * 每6个Byte是一条指令
 * Byte[0] 部件序号
 * Byte[1]Byte[2] 起始时间 
 * Byte[3]Byte[4] 关闭时间 
 * Byte[5]        校验位 上面的加起来取后两位
 * 
 */
void Work_Start(uint8_t * Order_Buffer)
{
    uint16_t INFO[3][100]={0};
    uint8_t i;
    bool ReadFinish_Flag=0;
    //从Order_Buffer里读取
    for(i=0;ReadFinish==0;i++)
    {

    }
}