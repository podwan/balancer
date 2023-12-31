#ifndef __I2C_H
#define __I2C_H	 
#include "app.h" 

void I2C_Init(void);
void error_handler(uint32_t error_code);
void test_bank(void);
//void i2c_lowlevel_init(i2c_handle_type* hi2c);

#endif
