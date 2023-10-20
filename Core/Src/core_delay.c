/**
  ******************************************************************************
  * @file    core_delay.c
  * @author  Leo
  * @date    2023/10/18
  * @version v1
  * @brief
  ******************************************************************************
  */

#include "core_delay.h"
void SysTick_Delay_Ms( __IO uint32_t ms)
{
    uint32_t i;
    SysTick_Config(SystemCoreClock/1000);

    for(i=0;i<ms;i++)
    {
        // 当计数器的值减小到0的时候，CRTL寄存器的位16会置1
        // 当置1时，读取该位会清0
        while( !((SysTick->CTRL)&(1<<16)) );
    }
    // 关闭SysTick定时器
    SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;
}


void SysTick_Delay_us( __IO uint32_t us)
{
    uint32_t i;
    SysTick_Config(SystemCoreClock/1000000);

    for(i=0;i<us;i++)
    {
        // 当计数器的值减小到0的时候，CRTL寄存器的位16会置1
        // 当置1时，读取该位会清0
        while( !((SysTick->CTRL)&(1<<16)) );
    }
    // 关闭SysTick定时器
    SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;
}

void delay_ms(uint32_t nms)
{
    uint32_t tmp;
    while(nms--)
    {
        SysTick->LOAD = 168000000/8/1000;
        SysTick->VAL = 0;
        SysTick->CTRL |= 0x1;
        do
        {
            tmp = SysTick->CTRL;
        }while((tmp&0x1) && !(0x1<<16));
        SysTick->VAL = 0;
        SysTick->CTRL &= 0;
    }
}

void delay_us(uint32_t nus)
{
    uint32_t tmp;
    while(nus--)
    {
        SysTick->LOAD = 168000000/8/1000000;
        SysTick->VAL = 0;
        SysTick->CTRL |= 0x1;
        do
        {
            tmp = SysTick->CTRL;
        }while((tmp&0x1) && !(0x1<<16));
        SysTick->VAL = 0;
        SysTick->CTRL &= 0;
    }
}
