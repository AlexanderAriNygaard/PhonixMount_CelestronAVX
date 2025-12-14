#include <stdint.h>
#include "registers.h"

void __Config_PWM(volatile GPIO_DataType *perif1, volatile TIM2_5_DataType *perif2, uint16_t pin,uint8_t AF, uint8_t CH);
void __Set_PWM(volatile TIM2_5_DataType *perif, uint32_t Hz_freqReq, uint32_t DC_dutyReq);