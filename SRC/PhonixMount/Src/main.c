#include "main.h"

int main(void)
{
  
  RCC->AHB1ENR |= (0x1U<<0); //enable GPIOA RCC clock access
  RCC->APB1ENR |= (0x1U<<0); //enable TIM2 RCC clock access
  /*
  //Setup for alt function mode (0x10) pin 5
  GPIOA->MODER |= (0x1U<<11);
  GPIOA->MODER &= ~(0x1U<<10);

  //Setup alt function for pin 5 to AF1 for TIM2_CH1
  GPIOA->AFRL &= ~(0xFU<<20); //reset pin 4 AF
  GPIOA->AFRL |= (0x1U<<20); //set AF1

  //Setup TIM2_CH1 PWM output
  TIM2->CR1 |= (0x1U<<7); //set ARPE auto-reload preload register to enable (1)
  TIM2->CR1 &= ~(0x3U<<5); //set CMS to edge aligned mode (0)
  TIM2->CR1 &= ~(0x1U<<4); //set DIR register to upcounting (0)
  TIM2->CR1 |= (0x1U<<0); //set CEN register to enable the counter (1)

  TIM2->CCMR1 &= ~(0x7U<<4); //reset OC1M output compare mode to (0)
  TIM2->CCMR1 |= (0x6U<<4); //set OC1M to PWM mode to mode 1 (110)
  TIM2->CCMR1 |= (0x1U<<3); //enable preload register in OC1PE bit

  TIM2->CCER |= (0x1U<<0); //enable channel 1 for CCER
*/

  //Configure PA5 for PWM mode TIM2_CH1
  __Config_PWM(GPIOA, TIM2, 5, 1, 1);

  //Set the duty cycle and frequency
  __Set_PWM(TIM2, 10, 50);
  while(1)
  {
  
  }
  return 0;
}