#ifndef __adc_H
#define __adc_H
#include "app.h"

extern uint16_t ADC_ConvertedValue[3];

void TriggerADC_Init(void);
void ADC_Config(void);
void Get_ADCTemp(void);
void Get_InputVolt(void);

#endif
