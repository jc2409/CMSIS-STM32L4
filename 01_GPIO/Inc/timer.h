/*
 * timer.h
 *
 *  Created on: Jun 11, 2025
 *      Author: jaecho01
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "stm32l475xx.h"

void SystemClock_16Mhz(void);
void TIM15_Init(void);
void delay_ms(uint32_t delay);

#endif /* TIMER_H_ */
