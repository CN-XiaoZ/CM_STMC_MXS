#include "./worksystem/worksystem.h"

uint16_t Order[60][3];//数据保存




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
    //从Flash读取一次配方数据
}

uint16_t Change8to16(uint8_t HighPart,uint8_t LowPart)
{
    uint16_t sum=0;
    sum=(HighPart<<8)|LowPart;
    return sum;
}


void Action(uint16_t Number,uint16_t action)
{
    switch (Number){
        case 0://冲泡器电机
            if(action==0)
                Motor_Step1();
            else 
                Motor_Step2();
        break;
        case 1://JRS
            if(action==0)
            {
                GPIO_ResetBits(JRS1);
                GPIO_ResetBits(JRS2);
            }
            else//关闭
            {
                GPIO_SetBits(JRS1);
                GPIO_SetBits(JRS2);
            }
        break;
        case 2://MDJ1
            if(action==0)
                GPIO_ResetBits(MDJ1);
            else
                GPIO_SetBits(MDJ1);
        break;
        case 3://MDJ2
            if(action==0)
                GPIO_ResetBits(MDJ2);
            else
                GPIO_SetBits(MDJ2);
        break;
        case 4://CSB
            if(action==0)
                GPIO_SetBits(CSB);
            else
                GPIO_ResetBits(CSB);
        break;
        case 5://DCF1
            if(action==0)
                GPIO_SetBits(DCF1);
            else
                GPIO_ResetBits(DCF1);
        break;
        case 6://DCF2
            if(action==0)
                GPIO_SetBits(DCF2);
            else
                GPIO_ResetBits(DCF2);
        break;
        case 7://DCF3
            if(action==0)
                GPIO_SetBits(DCF3);
            else
                GPIO_ResetBits(DCF3);
        break;
        case 8://DCF4
            if(action==0)
                GPIO_SetBits(DCF4);
            else
                GPIO_ResetBits(DCF4);
        break;     
        case 9://DCF5
            if(action==0)
                GPIO_SetBits(DCF5);
            else
                GPIO_ResetBits(DCF5);
        break;
        case 10://DCF6
           if(action==0)
                GPIO_SetBits(DCF6);
            else
                GPIO_ResetBits(DCF6);
        break;     
        case 11://DCF7
            if(action==0)
                GPIO_SetBits(DCF7);
            else
                GPIO_ResetBits(DCF7);
        break;
        case 12://DCF8
            if(action==0)
                GPIO_SetBits(DCF8);
            else
                GPIO_ResetBits(DCF8);
        break;     
        case 13://NDB1
            if(action==0)
                TIM4->CCR3=9000;
            else
                TIM4->CCR3=0;
        break;
        case 14://NDB2
            if(action==0)
                TIM4->CCR4=9000;
            else
                TIM4->CCR4=0;
        break;
        case 15://ZYB-ZQ
            if(action==0)
                DAC_SetChannel2Data(DAC_Align_12b_R,1600);
            else
                DAC_SetChannel2Data(DAC_Align_12b_R,0);
        break;     
        case 16://ZYB-RS
            if(action==0)
                DAC_SetChannel2Data(DAC_Align_12b_R,1600);
            else
                DAC_SetChannel2Data(DAC_Align_12b_R,0);     
        break;
        case 17:
            if(action==0)
                GPIO_SetBits()
            else

        break;     
        case 18:
            if(action==0)

            else

        break;
        case 19:
            if(action==0)

            else

        break;     
        case 20:
            if(action==0)

            else

        break;
        case 8:
            if(action==0)

            else

        break;     
        case 9:
            if(action==0)

            else

        break;
        case 8:
            if(action==0)

            else

        break;     
        case 9:
            if(action==0)

            else

        break;
        case 8:
            if(action==0)

            else

        break;     
        case 9:
            if(action==0)

            else

        break;

        case 8:
            if(action==0)

            else

        break;     
        case 9:
            if(action==0)

            else

        break;case 8:
            if(action==0)

            else

        break;     
        case 9:
            if(action==0)

            else

        break;

    }
}
//电机编号
/*
JRS   
MDJ1
MDJ2
CSB
DCF1
DCF2
DCF3
DCF4
DCF5
DCF6
DCF7
DCF8
ZYB
RDB
FLJ1
FLJ2
FLJ3
FLJ4
JBJ1
JBJ2
JBJ3
JBJ4

*/