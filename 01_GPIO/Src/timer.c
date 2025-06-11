/*
 * timer.c
 *
 *  Created on: Jun 11, 2025
 *      Author: jaecho01
 */

#include "timer.h"
#include <stdint.h>

#define RCC_HSIRDY	(1U<<10)
#define RCC_HSION   (1U<<8)
#define TIM15EN     (1U<<16)
#define TIM15_CEN   (1U<<0)
#define TIM15_UIF   (1U<<0)      

void SystemClock_16Mhz(void){
	// Enable HSI clock if not enabled and ready
	if ((RCC->CR & RCC_HSIRDY) == 0) {
	    // HSI16 clock enable (16MHz Frequency)
	    RCC->CR |= RCC_HSION;

	    // Wait until HSI clock is ready
	    while((RCC->CR & RCC_HSIRDY) == 0);
	}

    // Set AHB prescaler to 1
    RCC->CFGR &= ~(1U<<4);
    RCC->CFGR &= ~(1U<<5);
    RCC->CFGR &= ~(1U<<6);
    RCC->CFGR &= ~(1U<<7);

    RCC->CFGR |= RCC_CFGR_PPRE1_DIV1;

    // Set APB2 prescaler to 1
    RCC->CFGR &= ~(1U<<8);
    RCC->CFGR &= ~(1U<<9);
    RCC->CFGR &= ~(1U<<10);

    // Use HSI as the system clock source (Bit 1:0 -> 01)
    RCC->CFGR |= (1U<<0);
    RCC->CFGR &= ~(1U<<1);
}

void TIM15_Init(void) {
	// Set the System Clock to 16MHz
	SystemClock_16Mhz();

    // Enable TIM15 Clock
    RCC->APB2ENR |= TIM15EN;

    // Tim15 Prescaler
    TIM15->PSC = 16 - 1; // Freq = CLK / (PSC + 1) = 16MHz / 16 = 1MHz
    
    // Tim15 Auto Reload Register
    TIM15->ARR = 1000 - 1; // 1MHz / 1000 = 1KHz (= 1ms)

    // Enable the Timer Module
    TIM15->CR1 |= TIM15_CEN;
}

void delay_ms(uint32_t delay) {
    for (uint32_t i=0; i<delay; i++) {
        // Clear the count
        TIM15->CNT = 0;

        // Wait UIF to be set
        while((TIM15->SR & TIM15_UIF) == 0);
        
        // Reset UIF
        TIM15->SR &= ~(TIM15_UIF);
    }
}
