#include "main.h"

int main(void) {
  GPIO_Init();
  TIM15_Init();

  while (1) {
    LED_Toggle();
    delay_ms(100);
  }
}
