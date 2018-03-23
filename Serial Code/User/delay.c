#include "delay.h"

void delay_ms(int nms)
{
	uint32_t i;
  	SysTick_Config(SystemCoreClock/1000);
  	for (i=0;i<nms;i++)
    {
      	while(!((SysTick->CTRL)&(1<<16)));
    }
  	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}
void delay_us(int nus)
{
	uint32_t i;
  	SysTick_Config(SystemCoreClock/1000000);
  	for (i=0;i<nus;i++)
    {
      	while(!((SysTick->CTRL)&(1<<16)));
    }
  	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}
void delay_s(float time_s)
{
	int time,time_spart,time_mspart,count;
	time=time_s*1000;
	time_spart=time/1000;
	time_mspart=time%1000;
	for(count=0;count<time_spart;count++)
		delay_ms(1000);
	delay_ms(time_mspart);
}
