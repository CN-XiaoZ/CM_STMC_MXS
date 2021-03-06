#include "./worksystem/worksystem.h"

uint16_t Order[60][3];//数据保存
uint8_t Config[16];




// void Update_Sysinfo(uint8_t * Sys_info)//本函数放在等待阶段的中断函数中
// {
//     SPI_FLASH_SectorErase(SYS_INFO_ADDR);//擦除原数据
//     SPI_FLASH_PageWrite(Sys_info,SYS_INFO_ADDR,256);//加入新的信息
// }

// void Formula_Insert(uin8_t * Order_Buffer,uint8_t index)//加配方
// {
//     SPI_FLASH_PageWrite(Order_Buffer,FORMULA_ADDR(index),256);
// }

// void Read_Formula(uint8_t * Order_Buffer)
// {
//     SPI_FLASH_BufferRead(Order_Buffer,FORMULA_ADDR(index),256);
// }

// /**
//  * OrderBuffer的格式
//  * 每6个Byte是一条指令
//  * Byte[0] 部件序号
//  * Byte[1]Byte[2] 起始时间 
//  * Byte[3]Byte[4] 关闭时间 
//  * Byte[5]        校验位 上面的加起来取后两位
//  * 
//  */
// void Work_Start(uint8_t * Order_Buffer)
// {
//     uint16_t INFO[3][100]={0};
//     uint8_t i;
//     bool ReadFinish_Flag=0;
//     //从Order_Buffer里读取
//     for(i=0;ReadFinish==0;i++)
//     {

//     }
// }

//目标 完成一个可以随时调动的代码

/*-----工作流程-------
分两种
1. 冰饮
冰饮的顺序
    1.先加冰块，控制量为冰块数量
    2.再加糖浆，控制量为糖浆的量
    3.咖啡豆和萃取
    4.

2. 热饮

*/

void WorkSystem_Config(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE)
    TIM_TimeBaseStructure.TIM_Period = 10000-1;
    TIM_TimeBaseStructure.TIM_Prescaler = 143;
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

    TIM_ClearFlag(TIM6, TIM_FLAG_Update);
    TIM_ITConfig(BASIC_TIM,TIM_IT_Update,ENABLE);
    TIM_Cmd(BASIC_TIM, ENABLE);
}

void WorkSystem_Start(void)//输入配方的号码
{
    //相关标志位清零
    NVIC_EnableIRQ(TIM6_IRQn);
}

void GetOrder(uint8_t Number)//在WorkSystem_Start函数前进行
{
    uint16_t i;
    uint8_t temp[256];
    SPI_FLASH_BufferRead(temp,FORMULA_ADDR(Number),256);
    for(i=0;i<16;i++)
    {
        Config[i]=temp[i];
    }
    for(i=0;i<60;i++)
    {
        Order[i][0]=temp[4*i+16];
        Order[i][1]=Change8to16(temp[4*i+17],temp[4*i+18]);
        Order[i][2]=temp[4*i+19];
    }
    


}



uint16_t Change8to16(uint8_t HighPart,uint8_t LowPart)
{
    uint16_t sum=0;
    sum=(HighPart<<8)|LowPart;
    return sum;
}