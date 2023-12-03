#ifndef __LED_H
#define __LED_H	 
#include "app.h"

#define RED_1  gpio_bits_set(GPIOC,GPIO_PINS_13)
#define RED_0  gpio_bits_reset(GPIOC,GPIO_PINS_13)
#define GREEN_1  gpio_bits_set(GPIOC,GPIO_PINS_14)
#define GREEN_0  gpio_bits_reset(GPIOC,GPIO_PINS_14)
#define BLUE_1  gpio_bits_set(GPIOC,GPIO_PINS_15)
#define BLUE_0  gpio_bits_reset(GPIOC,GPIO_PINS_15)

void LED_Init(void);
void R_LED(u8 data);
void G_LED(u8 data);
void B_LED(u8 data);		 				    
#endif
