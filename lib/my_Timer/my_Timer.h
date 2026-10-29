#ifndef _Timer_H_
#define _Timer_H_

#include "stm32f1xx_hal.h"
extern TIM_HandleTypeDef htim2;

void delay_us(uint16_t time_us);
void delay_ms(uint16_t time_ms);

#endif
