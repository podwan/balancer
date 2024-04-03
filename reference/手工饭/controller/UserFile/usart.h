#ifndef __USART_H
#define __USART_H
#include "app.h"

#define BUFFER_SIZE   (128)

extern uint8_t Tx1_buffer[BUFFER_SIZE];
extern uint8_t Rx1_buffer[BUFFER_SIZE];
extern u8 Tx1_Flag;
extern u8 U1_IDLE_Flag;

extern uint8_t Tx2_buffer[BUFFER_SIZE];
extern uint8_t Rx2_buffer[BUFFER_SIZE];
extern u8 Tx2_Flag;
extern u8 U2_IDLE_Flag;

extern uint8_t Tx3_buffer[BUFFER_SIZE];
extern uint8_t Rx3_buffer[BUFFER_SIZE];
extern u8 Tx3_Flag;
extern u8 U3_IDLE_Flag;

extern uint8_t Tx4_buffer[BUFFER_SIZE];
extern uint8_t Rx4_buffer[BUFFER_SIZE];
extern u8 Tx4_Flag;
extern u8 U4_IDLE_Flag;

extern u8 Get_usart1_data[BUFFER_SIZE];
extern u8 Get_usart2_data[BUFFER_SIZE];
extern u8 Get_usart3_data[BUFFER_SIZE];
extern u8 Get_usart4_data[BUFFER_SIZE];

void USART1_init(u32 bound);
void USART2_init(u32 bound);
void USART3_init(u32 bound);
void USART4_init(u32 bound);

uint32_t UART1_SendDataDMA(uint8_t *data, uint16_t len);
uint32_t UART2_SendDataDMA(uint8_t *data, uint16_t len);
uint32_t UART3_SendDataDMA(uint8_t *data, uint16_t len);
uint32_t UART4_SendDataDMA(uint8_t *data, uint16_t len);
#endif
