#include "pwm_config.h"

void __Config_PWM(volatile GPIO_DataType *perif1, volatile TIM2_5_DataType *perif2, uint16_t pin,uint8_t AF, uint8_t CH)
{
    //Error handling for wrong values
    if((pin>15 || pin<0) || (AF>15 || AF<0) || (CH>4 || CH<0))
    {
        //error handling for user error. turn this into a message later for during compilation.
    }

    //Configure MODER pin
    perif1->MODER &= ~(0x3U<<(pin*2)); //reset current bits in pin
    perif1->MODER |= (0x2U<<(pin*2)); //set pin to alt function mode (10)

    //Configure AFR pin
    if (pin<=7)
    {
        //AFRL
        perif1->AFRL &= ~(0xFU<<(pin*4)); //reset current bits in pin
        perif1->AFRL |= (AF<<(pin*4)); //set pin to alt function mode
    }
    else
    {
        //AFRH
        perif1->AFRH &= ~(0xFU<<((pin-8)*4)); //reset current bits in pin
        perif1->AFRH |= (AF<<((pin-8)*4)); //set pin to alt function mode
    }

    //Configure CR register
    perif2->CR1 |= (0x1U<<7); //set ARPE auto-reload preload register to enable (1)
    perif2->CR1 &= ~(0x3U<<5); //set CMS to edge aligned mode (0)
    perif2->CR1 &= ~(0x1U<<4); //set DIR register to upcounting (0)
    perif2->CR1 |= (0x1U<<0); //set CEN register to enable the counter (1)

    //Configure CCMR register
    if(CH==1)
    {
        //configure for channel 1 on CCRM1
        perif2->CCMR1 &= ~(0x7U<<4); //reset OC1M output compare mode to (0)
        perif2->CCMR1 |= (0x6U<<4); //set OC1M to PWM mode to mode 1 (110)
        perif2->CCMR1 |= (0x1U<<3); //enable preload register in OC1PE bit
        perif2->CCER |= (0x1U<<0); //enable channel 1 for CCER
    }
    else if (CH==1)
    {
        //configure for channel 2 on CCRM1
        perif2->CCMR1 &= ~(0x7U<<12); //reset OC2M output compare mode to (0)
        perif2->CCMR1 |= (0x6U<<12); //set OC2M to PWM mode to mode 1 (110)
        perif2->CCMR1 |= (0x1U<<11); //enable preload register in OC2PE bit
        perif2->CCER |= (0x1U<<4); //enable channel 2 for CCER
    }
    else if(CH==3)
    {
        //configure for channel 3 on CCRM2
        perif2->CCMR2 &= ~(0x7U<<4); //reset OC3M output compare mode to (0)
        perif2->CCMR2 |= (0x6U<<4); //set OC3M to PWM mode to mode 1 (110)
        perif2->CCMR2 |= (0x1U<<3); //enable preload register in OC3PE bit
        perif2->CCER |= (0x1U<<8); //enable channel 3 for CCER
    }
    else
    {
        //configure for channel 4 on CCRM2
        perif2->CCMR2 &= ~(0x7U<<12); //reset OC4M output compare mode to (0)
        perif2->CCMR2 |= (0x6U<<12); //set OC4M to PWM mode to mode 1 (110)
        perif2->CCMR2 |= (0x1U<<11); //enable preload register in OC4PE bit
        perif2->CCER |= (0x1U<<12); //enable channel 4 for CCER
    }
}

void __Set_PWM(volatile TIM2_5_DataType *perif, uint32_t Hz_freqReq, uint32_t DC_dutyReq)
{
    uint32_t Hz_baseClock = 16000000;
    uint16_t Cnt_maxCounter = 999;
    uint32_t Cnt_PSC;

    //Determine duty cycle
    if (DC_dutyReq>= 100)
    {
        //limit max duty cycle to 100%
        DC_dutyReq = 100;
    }

    uint16_t DC_dutyCycle = (DC_dutyReq * Cnt_maxCounter) / 100;

    //Determine frequency
    // f_PWM = Hz_baseClock / ((PSC + 1) * (ARR + 1))
    Cnt_PSC = (Hz_baseClock/(Hz_freqReq*(Cnt_maxCounter+1)))-1;

    perif->ARR = Cnt_maxCounter; //allow the ARR counter to be semi-course
    perif->PSC = Cnt_PSC;
    perif->CCR1 = DC_dutyCycle;

    perif->EGR |= (0x1U<<0); //enable TIM2 event generation register to re-init on completion
    }