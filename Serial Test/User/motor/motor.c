/**
 ******************************************************************************
 * @file    motor.c
 * @author  MXS-Xizo
 * @version V2.0
 * @date    2018-04-24
 * @brief   Motor的初始化函数和各部件调用函数
 ******************************************************************************
 */
#include "sys_config.h"

void Motor_Config(void)
{
    float DAC1VAL, DAC2VAL;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    DAC_InitTypeDef DAC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4|RCC_APB1Periph_TIM5|RCC_APB1Periph_DAC,ENABLE);
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|\
                            RCC_APB2Periph_GPIOB|\
                            RCC_APB2Periph_GPIOC|\
                            RCC_APB2Periph_GPIOD|\
                            RCC_APB2Periph_GPIOE|\
                            RCC_APB2Periph_GPIOF|\
                            RCC_APB2Periph_GPIOG,ENABLE);

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    /*--------------OUT_OD-----------------*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    // MDJ1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    // MDJ2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    // JRS1_1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    // JRS1_2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    // JRS2_1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    // JRS2_2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    // CPQ_REV
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*--------------OUT_PP-----------------*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    // CBDJ
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOG, &GPIO_InitStructure);
    // CSB1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOG, &GPIO_InitStructure);
    // CSB2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    // CSB3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    // DCF1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    // DCF2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    // DCF3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOG, &GPIO_InitStructure);
    // DCF4
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOG, &GPIO_InitStructure);
    // DCF5
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    // DCF6
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    // DCF7
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    // DCF8
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    // DCF9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    // DCF10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    // JBJ1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    // JBJ2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    // FLJ1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    // FLJ2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    /*--------------IPD-----------------*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    // SIG1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    // SIG2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    // LLJ1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    // LLJ2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    // LLJ3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    // LLJ4
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    // LLJ5
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    // LLJ6
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    /*--------------AIN-----------------*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    // DAC1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    // DAC2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*--------------AF_PP-----------------*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    // RDB1 TIM3_CH1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    // RDB2 TIM3_CH2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    // RDB3 TIM3_CH3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    // RDB4 TIM3_CH4
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    // RDB5 TIM4_CH1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    // RDB6 TIM4_CH2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    // RDB7 TIM4_CH3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    // DJ   TIM4_CH4
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    // CPQ  TIM2_CH2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*--------------TIM_CONFIG-----------------*/
    TIM_TimeBaseStructure.TIM_Period        = (10000 - 1);
    TIM_TimeBaseStructure.TIM_Prescaler     = (144 - 1);
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse       = 0;
    TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_Low;

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

    TIM_OC2Init(TIM2, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
    TIM_ARRPreloadConfig(TIM3, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
    TIM_ARRPreloadConfig(TIM4, ENABLE);
    TIM_Cmd(TIM5, ENABLE);

    /*--------------TIM_CONFIG-----------------*/
    DAC_InitStructure.DAC_Trigger        = DAC_Trigger_None;
    DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
    DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
    DAC_Init(DAC_Channel_1, &DAC_InitStructure);
    DAC_Cmd(DAC_Channel_1, ENABLE);
    DAC_Init(DAC_Channel_2, &DAC_InitStructure);
    DAC_Cmd(DAC_Channel_2, ENABLE);

    /*-------------INIT-------------------*/
    DAC1VAL = 0;
    DAC2VAL = 0;
    DAC_SetChannel1Data(DAC_Align_12b_R, DAC1VAL);
    DAC_SetChannel2Data(DAC_Align_12b_R, DAC2VAL);
    GPIO_ResetBits(GPIOD, GPIO_Pin_8);
    GPIO_ResetBits(GPIOD, GPIO_Pin_9);
    GPIO_ResetBits(GPIOD, GPIO_Pin_10);
    GPIO_ResetBits(GPIOD, GPIO_Pin_11);
    GPIO_ResetBits(GPIOD, GPIO_Pin_12);
    GPIO_ResetBits(GPIOD, GPIO_Pin_13);
}

void Motor_Step1(void)
{
    while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8) == 0)
    {
        TIM2->CCR2 = 5000;
        GPIO_ResetBits(GPIOA, GPIO_Pin_0);
        while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8) == 0)
            ;
        delay_ms(20);
    }
    TIM2->CCR2 = 0;
}

void Motor_Step2(void)
{
    while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9) == 0)
    {
        TIM2->CCR2 = 5000;
        GPIO_SetBits(GPIOA, GPIO_Pin_0);
        while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9) == 0)
            ;
        delay_ms(20);
    }
    TIM2->CCR2 = 0;
}

void Action(uint16_t Number, uint16_t action)
{
    switch (Number)
    {
    case 0: // CPQ
        if (action == 0)
        {
            Motor_Step1();
        }
        else
        {
            Motor_Step2();
        }
        break;
    case 1: // MDJ1
        if (action == 0)
        {
            GPIO_ResetBits(GPIOD, GPIO_Pin_8);
        }
        else
        {
            GPIO_SetBits(GPIOD, GPIO_Pin_8);
        }
        break;
    case 2: // MDJ2
        if (action == 0)
        {
            GPIO_ResetBits(GPIOD, GPIO_Pin_9);
        }
        else
        {
            GPIO_SetBits(GPIOD, GPIO_Pin_9);
        }
        break;
    case 3: // JRS1
        if (action == 0)
        {
            GPIO_ResetBits(GPIOD, GPIO_Pin_10);
            GPIO_ResetBits(GPIOD, GPIO_Pin_11);
        }
        else
        {
            GPIO_SetBits(GPIOD, GPIO_Pin_10);
            GPIO_SetBits(GPIOD, GPIO_Pin_11);
        }
        break;
    case 4: // JRS2
        if (action == 0)
        {
            GPIO_ResetBits(GPIOD, GPIO_Pin_12);
            GPIO_ResetBits(GPIOD, GPIO_Pin_13);
        }
        else
        {
            GPIO_SetBits(GPIOD, GPIO_Pin_12);
            GPIO_SetBits(GPIOD, GPIO_Pin_13);
        }
        break;
    case 5: // CBDJ
        if (action == 0)
        {
            GPIO_SetBits(GPIOG, GPIO_Pin_2);
        }
        else
        {
            GPIO_ResetBits(GPIOG, GPIO_Pin_2);
        }
        break;
    case 6: // CSB1
        if (action == 0)
        {
            GPIO_SetBits(GPIOG, GPIO_Pin_5);
        }
        else
        {
            GPIO_ResetBits(GPIOG, GPIO_Pin_5);
        }
        break;
    case 7: // CSB2
        if (action == 0)
        {
            GPIO_SetBits(GPIOE, GPIO_Pin_0);
        }
        else
        {
            GPIO_ResetBits(GPIOE, GPIO_Pin_0);
        }
        break;
    case 8: // CSB3
        if (action == 0)
        {
            GPIO_SetBits(GPIOE, GPIO_Pin_1);
        }
        else
        {
            GPIO_ResetBits(GPIOE, GPIO_Pin_1);
        }
        break;
    case 9: // DCF1
        if (action == 0)
        {
            GPIO_SetBits(GPIOD, GPIO_Pin_14);
        }
        else
        {
            GPIO_ResetBits(GPIOD, GPIO_Pin_14);
        }
        break;
    case 10: // DCF2
        if (action == 0)
        {
            GPIO_SetBits(GPIOD, GPIO_Pin_15);
        }
        else
        {
            GPIO_ResetBits(GPIOD, GPIO_Pin_15);
        }
        break;
    case 11: // DCF3
        if (action == 0)
        {
            GPIO_SetBits(GPIOG, GPIO_Pin_3);
        }
        else
        {
            GPIO_ResetBits(GPIOG, GPIO_Pin_3);
        }
        break;
    case 12: // DCF4
        if (action == 0)
        {
            GPIO_SetBits(GPIOG, GPIO_Pin_4);
        }
        else
        {
            GPIO_ResetBits(GPIOG, GPIO_Pin_4);
        }
        break;
    case 13: // DCF5
        if (action == 0)
        {
            GPIO_SetBits(GPIOF, GPIO_Pin_0);
        }
        else
        {
            GPIO_ResetBits(GPIOF, GPIO_Pin_0);
        }
        break;
    case 14: // DCF6
        if (action == 0)
        {
            GPIO_SetBits(GPIOF, GPIO_Pin_1);
        }
        else
        {
            GPIO_ResetBits(GPIOF, GPIO_Pin_1);
        }
        break;
    case 15: // DCF7
        if (action == 0)
        {
            GPIO_SetBits(GPIOF, GPIO_Pin_2);
        }
        else
        {
            GPIO_ResetBits(GPIOF, GPIO_Pin_2);
        }
        break;
    case 16: // DCF8
        if (action == 0)
        {
            GPIO_SetBits(GPIOF, GPIO_Pin_3);
        }
        else
        {
            GPIO_ResetBits(GPIOF, GPIO_Pin_3);
        }
        break;
    case 17: // DCF9
        if (action == 0)
        {
            GPIO_SetBits(GPIOF, GPIO_Pin_4);
        }
        else
        {
            GPIO_ResetBits(GPIOF, GPIO_Pin_4);
        }
        break;
    case 18: // DCF10
        if (action == 0)
        {
            GPIO_SetBits(GPIOF, GPIO_Pin_5);
        }
        else
        {
            GPIO_ResetBits(GPIOF, GPIO_Pin_5);
        }
        break;
    case 19: // JBJ1
        if (action == 0)
        {
            GPIO_SetBits(GPIOE, GPIO_Pin_2);
        }
        else
        {
            GPIO_ResetBits(GPIOE, GPIO_Pin_2);
        }
        break;
    case 20: // JBJ2
        if (action == 0)
        {
            GPIO_SetBits(GPIOE, GPIO_Pin_3);
        }
        else
        {
            GPIO_ResetBits(GPIOE, GPIO_Pin_3);
        }
        break;
    case 21: // FLJ1
        if (action == 0)
        {
            GPIO_SetBits(GPIOE, GPIO_Pin_4);
        }
        else
        {
            GPIO_ResetBits(GPIOE, GPIO_Pin_4);
        }
        break;
    case 22: // FLJ2
        if (action == 0)
        {
            GPIO_SetBits(GPIOE, GPIO_Pin_5);
        }
        else
        {
            GPIO_ResetBits(GPIOE, GPIO_Pin_5);
        }
        break;
    case 23: // RDB1
        if (action == 0)
        {
            TIM3->CCR1 = 7000;
        }
        else
        {
            TIM3->CCR1 = 0;
        }
        break;
    case 24: // RDB2
        if (action == 0)
        {
            TIM3->CCR2 = 7000;
        }
        else
        {
            TIM3->CCR2 = 0;
        }
        break;
    case 25: // RDB3
        if (action == 0)
        {
            TIM3->CCR3 = 7000;
        }
        else
        {
            TIM3->CCR3 = 0;
        }
        break;
    case 26: // RDB4
        if (action == 0)
        {
            TIM3->CCR4 = 7000;
        }
        else
        {
            TIM3->CCR4 = 0;
        }
        break;
    case 27: // RDB5
        if (action == 0)
        {
            TIM4->CCR1 = 7000;
        }
        else
        {
            TIM4->CCR3 = 0;
        }
        break;
    case 28: // RDB6
        if (action == 0)
        {
            TIM4->CCR2 = 7000;
        }
        else
        {
            TIM4->CCR3 = 0;
        }
        break;
    case 29: // RDB7
        if (action == 0)
        {
            TIM4->CCR3 = 7000;
        }
        else
        {
            TIM4->CCR3 = 0;
        }
        break;
    case 30: // DJ
        if (action == 0)
        {
            TIM4->CCR4 = DJ_POS1;
        }
        else
        {
            TIM4->CCR4 = DJ_POS2;
        }
        break;
    case 31: // ZYB
        if (action == 0)
        {
            DAC_SetChannel2Data(DAC_Align_12b_R,3000);
        }
        else if(action == 1)
        {
            DAC_SetChannel2Data(DAC_Align_12b_R,1600);
        }
        else
        {
            DAC_SetChannel2Data(DAC_Align_12b_R,0);
        }
        break;
    }
}