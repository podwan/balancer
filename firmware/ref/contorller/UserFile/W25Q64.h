#ifndef __W25Q64_H
#define __W25Q64_H			    
#include "app.h" 

#define W25Qxx_CS1  gpio_bits_set(GPIOE,GPIO_PINS_4)
#define W25Qxx_CS0  gpio_bits_reset(GPIOE,GPIO_PINS_4)

void W25Qxx_Init(void);
uint16_t ReadW25Qxx_ID(void);
void W25Qxx_ErasePage(uint32_t addr);
void W25Qxx_WritePage(uint8_t* Buffer,uint32_t addr,uint16_t len);
void W25Qxx_Read(uint8_t* Buffer,uint32_t addr,uint16_t len);

#endif
















