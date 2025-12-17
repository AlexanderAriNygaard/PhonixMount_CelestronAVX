#include "pwm_config.h"
#include "registers.h"

#ifndef __MAIN_H
void enable_PC13_interrupt(void);
void EXTI15_10_IRQHandler(void);
#define __MAIN_H
#endif