//
// Created by aoc11 on 2023/10/18.
//

#ifndef CPROJECT_CORE_DELAY_H
#define CPROJECT_CORE_DELAY_H

#include "stm32f4xx.h"

void SysTick_Init(void);
void SysTick_Delay_Ms( __IO uint32_t ms);
void SysTick_Delay_us( __IO uint32_t us);
void delay_ms(uint32_t nms);
void delay_us(uint32_t nus);

#endif //CPROJECT_CORE_DELAY_H
