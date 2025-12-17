#include "main.h"

//temp definition for proof of concept of NVIC modification
void enable_PC13_interrupt(void)
{
  NVIC->ISER1 |= (0x1U<<8);
}

void EXTI15_10_IRQHandler(void)
{
  if(EXTI->PR & (0x1U<<13))
  {
    EXTI->PR = (0x1U<<13);

    __Set_PWM(TIM2, 10, 90);
    for(volatile int i = 0; i < 100; i++); 
  }
}

int main(void)
{
  //Clock access
  RCC->AHB1ENR |= (0x5U<<0); //enable GPIOA + GPIOC RCC clock access
  RCC->APB1ENR |= (0x1U<<0); //enable TIM2 RCC clock access
  RCC->APB2ENR |= (0x1U<<14); //enable EXTI + SYSCFG RCC clock access

  //Configure PA5 for PWM mode TIM2_CH1
  __Config_PWM(GPIOA, TIM2, 5, 1, 1);

  /*PC13 GP input
  AHB1
    - RCC - 0x4002 3800
    - GPIOC - 0x4002 0800
  APB2
    - EXTI - 0x4001 3C00
    - SYSCFG - 0x4001 3800
  */

  GPIOC->MODER &= ~(0x3U<<26); //set pin13 to 00 input
  GPIOC->PUPDR &= ~(0x3U<<26); //setting no PU/PD as the internal button has it's own pull up internally (see wiring schematic)
  
  // config the PC13 for external interrupt mode
  SYSCFG->EXTICR4 &= ~(0xFU<<4); //first reset the register for pin 13
  SYSCFG->EXTICR4 |= (0x2U<<4); //the configure it for port C (0010)

  //setup the EXTI registers
  EXTI->IMR |= (0x1U<<13); //remove the mask on pin 13 interrupt event
  EXTI->RTSR |= (0x1U<<13); //enable rising trigger for pin 13

  /*
  Now the hard part... need the STM32 cortex-M4 core to comprehend the NVIC function for EXTI setup... This is is done in block 7 of the memory mapping

  1. using the reference manual, locate in vector Table 38 the STM32F446xx position for the EXTI Line of interest (line 13 is ours). This is:
    - Pos = 40 (IQR Number)
    - Acronym = EXTI15_10
    - Address = 0x0000 00E0

  2. Calculate the bit and register
    - need to manipulate the ISERx register in NVIC. To do this determine the ISER register using IQR/32 = ISER[x] choice.
    - For us, IQR 40 lands us in ISER[1] register with 8 bits shifted in being the ISER address needing to be enabled for interrupt

  3. Finally, generate the interrupt routine function. Note this must be same name as defined in the startup_stm32f446xx.s assembly file.
    - EXTI15_10_IRQHandler in our case.
  */
  enable_PC13_interrupt();
  

  while(1)
  {
  __Set_PWM(TIM2, 10, 10);
  for(int i=0; i<1000000;i++);
  }
  return 0;
}