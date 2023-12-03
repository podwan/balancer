#ifndef __Encoder_H
#define __Encoder_H
#include "app.h"

#define SPI1_CS1_0  gpio_bits_reset(GPIOD,GPIO_PINS_5)
#define SPI1_CS1_1  gpio_bits_set(GPIOD,GPIO_PINS_5)
#define SPI1_CS2_0  gpio_bits_reset(GPIOD,GPIO_PINS_7);
#define SPI1_CS2_1  gpio_bits_set(GPIOD,GPIO_PINS_7);

void Check_Encoder(void);
void MT6701_Init(void);
void TLE5012B_Init(void);
void MA732_Init(void);
u16 MA732_Read_Reg(u8 Select,u8 reg,u8 value);
u16 MA732_Write_Reg(u8 Select,u8 reg,u8 value);

u16 Read_M1_Encoder(void);
u16 Read_M2_Encoder(void);

#endif
