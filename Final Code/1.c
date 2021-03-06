/**
 ******************************************************************************
 * @file    motor.c
 * @author  MXS-Xizo
 * @version V2.0
 * @date    2018-04-24
 * @brief   Motor的初始化函数和各部件调用函数
 ******************************************************************************
 */

/*TODO： 时钟函数都注释了，记得还原*/
#include "sys_config.h"

void Motor_Config(void)
{
    float DAC1VAL, DAC2VAL;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    DAC_InitTypeDef DAC_InitStructure;
    /*
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4|RCC_APB1Periph_TIM5|RCC_APB1Periph_DAC,ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|\
                               RCC_APB2Periph_GPIOB|\
                               RCC_APB2Periph_GPIOC|\
                               RCC_APB2Periph_GPIOD|\
                               RCC_APB2Periph_GPIOE|\
                               RCC_APB2Periph_GPIOF|\
                               RCC_APB2Periph_GPIOG,ENABLE);
    */
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

    DAC1VAL = 0;
    DAC2VAL = 0;
    DAC_SetChannel1Data(DAC_Align_12b_R, DAC1VAL);
    DAC_SetChannel2Data(DAC_Align_12b_R, DAC2VAL);
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
            Motor_Step1();
        else
            Motor_Step2();
        break;
    case 1: // JRS1
        if (action == 0)
        {
            GPIO_ResetBits(JRS1);
            GPIO_ResetBits(JRS2);
        }
        else //关闭
        {
            GPIO_SetBits(JRS1);
            GPIO_SetBits(JRS2);
        }
        break;
    case 1: // JRS2
        if (action == 0)
        {
            GPIO_ResetBits(JRS1);
            GPIO_ResetBits(JRS2);
        }
        else //关闭
        {
            GPIO_SetBits(JRS1);
            GPIO_SetBits(JRS2);
        }
        break;
    case 2: // MDJ1
        if (action == 0)
            GPIO_ResetBits(MDJ1);
        else
            GPIO_SetBits(MDJ1);
        break;
    case 3: // MDJ2
        if (action == 0)
            GPIO_ResetBits(MDJ2);
        else
            GPIO_SetBits(MDJ2);
        break;
    case 4: // CSB
        if (action == 0)
            GPIO_SetBits(CSB);
        else
            GPIO_ResetBits(CSB);
        break;
    case 5: // DCF1
        if (action == 0)
            GPIO_SetBits(DCF1);
        else
            GPIO_ResetBits(DCF1);
        break;
    case 6: // DCF2
        if (action == 0)
            GPIO_SetBits(DCF2);
        else
            GPIO_ResetBits(DCF2);
        break;
    case 7: // DCF3
        if (action == 0)
            GPIO_SetBits(DCF3);
        else
            GPIO_ResetBits(DCF3);
        break;
    case 8: // DCF4
        if (action == 0)
            GPIO_SetBits(DCF4);
        else
            GPIO_ResetBits(DCF4);
        break;
    case 9: // DCF5
        if (action == 0)
            GPIO_SetBits(DCF5);
        else
            GPIO_ResetBits(DCF5);
        break;
    case 10: // DCF6
        if (action == 0)
            GPIO_SetBits(DCF6);
        else
            GPIO_ResetBits(DCF6);
        break;
    case 11: // DCF7
        if (action == 0)
            GPIO_SetBits(DCF7);
        else
            GPIO_ResetBits(DCF7);
        break;
    case 12: // DCF8
        if (action == 0)
            GPIO_SetBits(DCF8);
        else
            GPIO_ResetBits(DCF8);
        break;
    case 13: // NDB1
        if (action == 0)
            TIM4->CCR3 = 9000;
        else
            TIM4->CCR3 = 0;
        break;
    case 14: // NDB2
        if (action == 0)
            TIM4->CCR4 = 9000;
        else
            TIM4->CCR4 = 0;
        break;
    case 15: // ZYB-ZQ
        if (action == 0)
            DAC_SetChannel2Data(DAC_Align_12b_R, 1600);
        else
            DAC_SetChannel2Data(DAC_Align_12b_R, 0);
        break;
    case 16: // ZYB-RS
        if (action == 0)
            DAC_SetChannel2Data(DAC_Align_12b_R, 1600);
        else
            DAC_SetChannel2Data(DAC_Align_12b_R, 0);
        break;
    case 17:
        if (action == 0)
            GPIO_SetBits() else

                break;
    case 18:
        if (action == 0)

            else

                break;
    case 19:
        if (action == 0)

            else

                break;
    case 20:
        if (action == 0)

            else

                break;
    case 8:
        if (action == 0)

            else

                break;
    case 9:
        if (action == 0)

            else

                break;
    case 8:
        if (action == 0)

            else

                break;
    case 9:
        if (action == 0)

            else

                break;
    case 8:
        if (action == 0)

            else

                break;
    case 9:
        if (action == 0)

            else

                break;

    case 8:
        if (action == 0)

            else

                break;
    case 9:
        if (action == 0)

            else

                break;
    case 8:
        if (action == 0)

            else

                break;
    case 9:
        if (action == 0)

            else

                break;
    }
}