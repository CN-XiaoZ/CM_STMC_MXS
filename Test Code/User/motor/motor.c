//要开一个PWM(TIM4_CH1),一个普通引脚

#include "sys_config.h"

int Flow_Index;//流量计序号
int Flow_Count;//流量计达到流量需要值标志


//流量计程序设计要点
//1. 为了有个固定的时间作为时间差 所以需要一个定时中断做时间差积分

void Motor_Config(void)
{
    float DAC1VAL,DAC2VAL;
    /** 
     * 需要初始化的东西:TIM4 TIM5 TIM3 DAC 
     * 磨豆机两个接口 OUT_OD D8 D9
     * 抽水泵一个接口 OUT_OD D10
     * 加热丝两个接口 OUT_OD D11 A11
     * 增压泵接口 OUT_OD A12
     * 冲泡器电机初始化TIM4_CH1 和 E7 Out_pp
     * 冲泡器限位开关 E9 E10 INFLAOTING
     * 搅拌电机四个接口 OUT_OD E1 E2 E3 E4
     * 粉料电机四个接口 OUT_OD D12 D13 D14 D15
     * 搅拌器 初始化TIM4_CH2
     * 蠕动泵两个 初始化TIM4_CH3 TIM4_CH4
     * 电磁阀八个 OUT_OD F0 F1 F2 F3 F4 F5 E14 E15
     * DAC两个 AIN A4 A5
     * 
     * 舵机连接 A6 PWM
     * 流量计 E0 B5 G15 INFLIOATING
     * 步进PA7 E5 E6 E8
     */
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    DAC_InitTypeDef DAC_InitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4|RCC_APB1Periph_TIM5|RCC_APB1Periph_DAC,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|\
                            RCC_APB2Periph_GPIOB|\
                            RCC_APB2Periph_GPIOC|\
                            RCC_APB2Periph_GPIOD|\
                            RCC_APB2Periph_GPIOE|\
                            RCC_APB2Periph_GPIOF|\
                            RCC_APB2Periph_GPIOG,ENABLE);
    //  GPIO部分
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //  Out_PP类型引脚
    //  磨豆机
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
		
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    //  抽水泵
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    //  加热丝
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    //  增压泵
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
		//  冲泡器控制脚
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
		

		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		
		//  电磁阀
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    //  搅拌电机
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    //  粉料电机
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    //  步进电机
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    //  冲泡器
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    //  限位开关
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    //  流量计
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOG, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    //  DAC引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    //  TIM3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    //  TIM4
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    //  TIM5
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //初始化TIM
    TIM_TimeBaseStructure.TIM_Period = 10000-1;
    TIM_TimeBaseStructure.TIM_Prescaler = 143;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
    //设定TIM6中断
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

    TIM_OC1Init(TIM3, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_OC1Init(TIM4, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

    TIM_OC1Init(TIM5, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
    TIM_OC2Init(TIM5, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
    TIM_OC3Init(TIM5, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);
    TIM_OC4Init(TIM5, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM3, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
    TIM_ARRPreloadConfig(TIM4, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
    TIM_ARRPreloadConfig(TIM5, ENABLE);
    TIM_Cmd(TIM5, ENABLE);
    // 初始化DAC
    DAC_InitStructure.DAC_Trigger=DAC_Trigger_None;
    DAC_InitStructure.DAC_WaveGeneration=DAC_WaveGeneration_None;
    DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;
    DAC_InitStructure.DAC_OutputBuffer=DAC_OutputBuffer_Disable;
		DAC_Init(DAC_Channel_2,&DAC_InitStructure);
    DAC_Cmd(DAC_Channel_2, ENABLE);

    DAC2VAL=0;
//		
//    DAC1VAL=1600;
//    DAC2VAL=1600;//比较好的出蒸汽的量
//		DAC1VAL=0;
//		DAC2VAL=0 ;
    DAC_SetChannel2Data(DAC_Align_12b_R, DAC2VAL);
}

void Motor_Step1(void)
{
		while(GPIO_ReadInputDataBit(SWITCH2)==0)  
		{
			TIM4->CCR1=5000; 
			GPIO_ResetBits(MOTOR_CTRL);
			while(GPIO_ReadInputDataBit(SWITCH2)==0);
			delay_ms(20);
		}
		TIM4->CCR1=0;
}

void Motor_Step2(void)
{
		while(GPIO_ReadInputDataBit(SWITCH1)==0)  
		{
			TIM4->CCR1=5000; 
			GPIO_SetBits(MOTOR_CTRL);
			while(GPIO_ReadInputDataBit(SWITCH1)==0);
			delay_ms(20);
		}
		TIM4->CCR1=0;
}


//void Motor_Step1(void)
//{
//	TIM4->CCR1=5000;
//	GPIO_SetBits(MOTOR_CTRL);
//	NVIC_EnableIRQ(EXTI15_10_IRQn);
//}
//void Motor_Step2(void)
//{
//	TIM4->CCR1=5000;
//	GPIO_ResetBits(MOTOR_CTRL);
//	NVIC_EnableIRQ(EXTI9_5_IRQn);
//}



/*-----Demo------



---------------*/