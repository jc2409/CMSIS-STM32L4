/*
 * gpio.c
 *
 *  Created on: Jun 11, 2025
 *      Author: jaecho01
 */


#include "gpio.h"

#define GPIOAEN     (1U<<0)

void GPIO_Init(void) {
    // Enable AHB2 peripheral clock to toggle LD1 (PA5)
    RCC->AHB2ENR |= GPIOAEN;

    // Set GPIO port mode to General purpose output mode (01)
    GPIOA->MODER |= (1U<<10);
    GPIOA->MODER &= ~(1U<<11);
}

void LED_Toggle(void) {
    GPIOA->ODR ^= (1U<<5);
}
