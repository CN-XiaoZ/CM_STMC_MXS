 /**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ���� 8M����flash���ԣ�����������Ϣͨ������1�ڵ��Եĳ����ն��д�ӡ����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-�Ե� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
#include "stm32f10x.h"
#include "./usart/usart.h"
#include "delay.h"
#include "./flash/W25Q16.h"


enum Sys_status 
{   
  Sys_WAITING=0,//�ȴ�
  Sys_WASHING,  //��ϴ
  Sys_WAITING_LOAD,//�ȴ�װ��
  Sys_PAYING,//֧���׶�
  Sys_WORKING,//�����׶�
}; 

/*
 * ��������main
 * ����  ��������
 * ����  ����
 * ���  ����
 */
int main(void)
{ 
  sys_init();
  while(1)
  {
    if(Sys_status==WAITING)
    {
      //���״̬���������ж�,һ��TIM�жϼ���ʱ��,���30����û�����Ϳ�һ����ϴ
      //��һ���ж�Ϊ�����ж�,�ȴ���λ����������,�趨���ȼ�Ϊ�����жϸ���TIM�ж�
      if(WORKING_FLAG==WASHING)
      {
        Start_Washing();
      }
      //����ȵ�֧���źžͽ�״̬�л�ΪPAYING״̬,���ҽ�����TIM�жϹر�,��������,
      //��λ�������жϹر�
    }
    else if(sys_status==PAYING)
    {
        GM65_SCAN();//��ɨ������֮ǰ��UART4�жϺ�TIM�ж�
        //20s��û��֧����ֹͣ,ֹͣ��ʱ���PAY_FLAG��1
        //�ȴ���λ����֤
        //��λ������OK�Ļ���sys_status��ΪWORKING,����WORKING״̬
        if(PAY_FLAG==1)
        {
          sys_status=WAITING;//����
          break;
        }


    }
    else//WORKING
    {
        Start_Working();
        //�ر�UART4�жϺ�TIM�ж�
        //���ؽṹ��
    }
  }

}


/*********************************************END OF FILE**********************/
