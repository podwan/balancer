#include "usart.h"

u8 U1_IDLE_Flag = 0;
u8 U2_IDLE_Flag = 0;
u8 U3_IDLE_Flag = 0;
u8 U4_IDLE_Flag = 0;

uint8_t Tx1_buffer[BUFFER_SIZE];
uint8_t Rx1_buffer[BUFFER_SIZE];

uint8_t Tx2_buffer[BUFFER_SIZE];
uint8_t Rx2_buffer[BUFFER_SIZE];

uint8_t Tx3_buffer[BUFFER_SIZE];
uint8_t Rx3_buffer[BUFFER_SIZE];

uint8_t Tx4_buffer[BUFFER_SIZE];
uint8_t Rx4_buffer[BUFFER_SIZE];

u8 Get_usart1_data[BUFFER_SIZE];
u8 Get_usart2_data[BUFFER_SIZE];
u8 Get_usart3_data[BUFFER_SIZE];
u8 Get_usart4_data[BUFFER_SIZE];

u8 Tx1_Flag = 0;//0:完成 1：正在发送
u8 Tx2_Flag = 0;//0:完成 1：正在发送
u8 Tx3_Flag = 0;//0:完成 1：正在发送
u8 Tx4_Flag = 0;//0:完成 1：正在发送

void Dma_rx1(void)
{
	dma_init_type dma_init_struct;
	crm_periph_clock_enable(CRM_DMA2_PERIPH_CLOCK, TRUE);
	dma_reset(DMA2_CHANNEL1);
  dma_default_para_init(&dma_init_struct);
  dma_init_struct.buffer_size = BUFFER_SIZE;
  dma_init_struct.direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
  dma_init_struct.memory_base_addr = (uint32_t)Rx1_buffer;
  dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
  dma_init_struct.memory_inc_enable = TRUE;
  dma_init_struct.peripheral_base_addr = (uint32_t)&USART1->dt;
  dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
  dma_init_struct.peripheral_inc_enable = FALSE;
  dma_init_struct.priority = DMA_PRIORITY_MEDIUM;
  dma_init_struct.loop_mode_enable = FALSE;
  dma_init(DMA2_CHANNEL1, &dma_init_struct);

  /* config flexible dma for usart3 rx */
  dma_flexible_config(DMA2, FLEX_CHANNEL1, DMA_FLEXIBLE_UART1_RX);
	dma_channel_enable(DMA2_CHANNEL1, TRUE); /* usart3 rx begin dma receiving */
}

void Dma_tx1(void)
{
	dma_init_type dma_init_struct;
	crm_periph_clock_enable(CRM_DMA2_PERIPH_CLOCK, TRUE);
	dma_reset(DMA2_CHANNEL2);
  dma_default_para_init(&dma_init_struct);
  dma_init_struct.buffer_size = BUFFER_SIZE;
  dma_init_struct.direction = DMA_DIR_MEMORY_TO_PERIPHERAL;
  dma_init_struct.memory_base_addr = (uint32_t)Tx1_buffer;
  dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
  dma_init_struct.memory_inc_enable = TRUE;
  dma_init_struct.peripheral_base_addr = (uint32_t)&USART1->dt;
  dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
  dma_init_struct.peripheral_inc_enable = FALSE;
  dma_init_struct.priority = DMA_PRIORITY_MEDIUM;
  dma_init_struct.loop_mode_enable = FALSE;
  dma_init(DMA2_CHANNEL2, &dma_init_struct);

  /* config flexible dma for usart3 tx */
  dma_flexible_config(DMA2, FLEX_CHANNEL2, DMA_FLEXIBLE_UART1_TX);
	
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(DMA2_Channel2_IRQn, 3, 0);
	
	dma_interrupt_enable(DMA2_CHANNEL2,DMA_FDT_INT,TRUE); // 开启发送中断
} 

void Dma_rx2(void)
{
	dma_init_type dma_init_struct;
	crm_periph_clock_enable(CRM_DMA2_PERIPH_CLOCK, TRUE);
	dma_reset(DMA2_CHANNEL3);
  dma_default_para_init(&dma_init_struct);
  dma_init_struct.buffer_size = BUFFER_SIZE;
  dma_init_struct.direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
  dma_init_struct.memory_base_addr = (uint32_t)Rx2_buffer;
  dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
  dma_init_struct.memory_inc_enable = TRUE;
  dma_init_struct.peripheral_base_addr = (uint32_t)&USART2->dt;
  dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
  dma_init_struct.peripheral_inc_enable = FALSE;
  dma_init_struct.priority = DMA_PRIORITY_MEDIUM;
  dma_init_struct.loop_mode_enable = FALSE;
  dma_init(DMA2_CHANNEL3, &dma_init_struct);

  /* config flexible dma for usart3 rx */
  dma_flexible_config(DMA2, FLEX_CHANNEL3, DMA_FLEXIBLE_UART2_RX);
	dma_channel_enable(DMA2_CHANNEL3, TRUE); /* usart3 rx begin dma receiving */
}

void Dma_rx3(void)
{
	dma_init_type dma_init_struct;
	crm_periph_clock_enable(CRM_DMA2_PERIPH_CLOCK, TRUE);
	dma_reset(DMA2_CHANNEL5);
  dma_default_para_init(&dma_init_struct);
  dma_init_struct.buffer_size = BUFFER_SIZE;
  dma_init_struct.direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
  dma_init_struct.memory_base_addr = (uint32_t)Rx3_buffer;
  dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
  dma_init_struct.memory_inc_enable = TRUE;
  dma_init_struct.peripheral_base_addr = (uint32_t)&USART3->dt;
  dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
  dma_init_struct.peripheral_inc_enable = FALSE;
  dma_init_struct.priority = DMA_PRIORITY_MEDIUM;
  dma_init_struct.loop_mode_enable = FALSE;
  dma_init(DMA2_CHANNEL5, &dma_init_struct);

  /* config flexible dma for usart3 rx */
  dma_flexible_config(DMA2, FLEX_CHANNEL5, DMA_FLEXIBLE_UART3_RX);
	dma_channel_enable(DMA2_CHANNEL5, TRUE); /* usart3 rx begin dma receiving */
}

void Dma_tx3(void)
{
	dma_init_type dma_init_struct;
	crm_periph_clock_enable(CRM_DMA2_PERIPH_CLOCK, TRUE);
	
	dma_reset(DMA2_CHANNEL6);
  dma_default_para_init(&dma_init_struct);
  dma_init_struct.buffer_size = BUFFER_SIZE;
  dma_init_struct.direction = DMA_DIR_MEMORY_TO_PERIPHERAL;
  dma_init_struct.memory_base_addr = (uint32_t)Tx3_buffer;
  dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
  dma_init_struct.memory_inc_enable = TRUE;
  dma_init_struct.peripheral_base_addr = (uint32_t)&USART3->dt;
  dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
  dma_init_struct.peripheral_inc_enable = FALSE;
  dma_init_struct.priority = DMA_PRIORITY_MEDIUM;
  dma_init_struct.loop_mode_enable = FALSE;
  dma_init(DMA2_CHANNEL6, &dma_init_struct);
	
  /* config flexible dma for usart3 tx */
  dma_flexible_config(DMA2, FLEX_CHANNEL6, DMA_FLEXIBLE_UART3_TX);
	
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(DMA2_Channel6_7_IRQn, 3, 2);

	dma_interrupt_enable(DMA2_CHANNEL6,DMA_FDT_INT,TRUE); // 开启发送中断
}

void Dma_rx4(void)
{
	dma_init_type dma_init_struct;
	crm_periph_clock_enable(CRM_DMA2_PERIPH_CLOCK, TRUE);
	dma_reset(DMA2_CHANNEL4);
  dma_default_para_init(&dma_init_struct);
  dma_init_struct.buffer_size = BUFFER_SIZE;
  dma_init_struct.direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
  dma_init_struct.memory_base_addr = (uint32_t)Rx4_buffer;
  dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
  dma_init_struct.memory_inc_enable = TRUE;
  dma_init_struct.peripheral_base_addr = (uint32_t)&UART4->dt;
  dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
  dma_init_struct.peripheral_inc_enable = FALSE;
  dma_init_struct.priority = DMA_PRIORITY_MEDIUM;
  dma_init_struct.loop_mode_enable = FALSE;
  dma_init(DMA2_CHANNEL4, &dma_init_struct);

  /* config flexible dma for usart3 rx */
  dma_flexible_config(DMA2, FLEX_CHANNEL4, DMA_FLEXIBLE_UART4_RX);
	dma_channel_enable(DMA2_CHANNEL4, TRUE); /* usart3 rx begin dma receiving */
}

void Dma_tx4(void)
{
	dma_init_type dma_init_struct;
	crm_periph_clock_enable(CRM_DMA2_PERIPH_CLOCK, TRUE);
	
	dma_reset(DMA2_CHANNEL7);
  dma_default_para_init(&dma_init_struct);
  dma_init_struct.buffer_size = BUFFER_SIZE;
  dma_init_struct.direction = DMA_DIR_MEMORY_TO_PERIPHERAL;
  dma_init_struct.memory_base_addr = (uint32_t)Tx4_buffer;
  dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
  dma_init_struct.memory_inc_enable = TRUE;
  dma_init_struct.peripheral_base_addr = (uint32_t)&UART4->dt;
  dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
  dma_init_struct.peripheral_inc_enable = FALSE;
  dma_init_struct.priority = DMA_PRIORITY_MEDIUM;
  dma_init_struct.loop_mode_enable = FALSE;
  dma_init(DMA2_CHANNEL7, &dma_init_struct);
	
  /* config flexible dma for usart3 tx */
  dma_flexible_config(DMA2, FLEX_CHANNEL7, DMA_FLEXIBLE_UART4_TX);
	
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(DMA2_Channel6_7_IRQn, 3, 3);

	dma_interrupt_enable(DMA2_CHANNEL7,DMA_FDT_INT,TRUE); // 开启发送中断
}

void USART1_init(u32 bound)
{
	gpio_init_type gpio_init_struct;

	/* enable the usart3 and gpio clock */
	crm_periph_clock_enable(CRM_USART1_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

	gpio_default_para_init(&gpio_init_struct);

	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_pins = GPIO_PINS_9;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init(GPIOA, &gpio_init_struct);

	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
	gpio_init_struct.gpio_pins = GPIO_PINS_10;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init(GPIOA, &gpio_init_struct);

	usart_init(USART1, bound, USART_DATA_8BITS, USART_STOP_1_BIT);
	usart_transmitter_enable(USART1, TRUE);
	usart_receiver_enable(USART1, TRUE);
	
	usart_dma_transmitter_enable(USART1, TRUE);
	usart_dma_receiver_enable(USART1, TRUE);
	usart_enable(USART1, TRUE);
	
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(USART1_IRQn, 3, 4);
	
	usart_interrupt_enable(USART1,USART_IDLE_INT,TRUE); // 串口空闲中断
//	usart_interrupt_enable(USART3, USART_RDBF_INT, FALSE);
	
	Dma_tx1();
	Dma_rx1();
}

void USART2_init(u32 bound)
{
	gpio_init_type gpio_init_struct;

	/* enable the usart3 and gpio clock */
	crm_periph_clock_enable(CRM_USART2_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
	gpio_pin_remap_config(USART2_GMUX_0001,TRUE);
	
	gpio_default_para_init(&gpio_init_struct);

	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
	gpio_init_struct.gpio_pins = GPIO_PINS_6;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init(GPIOD, &gpio_init_struct);

	usart_init(USART2, bound, USART_DATA_8BITS, USART_STOP_1_BIT);
//	usart_transmitter_enable(USART2, TRUE);
	usart_receiver_enable(USART2, TRUE);
	
//	usart_dma_transmitter_enable(USART2, TRUE);
	usart_dma_receiver_enable(USART2, TRUE);
	usart_enable(USART2, TRUE);
	
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(USART2_IRQn, 3, 5);
	
	usart_interrupt_enable(USART2,USART_IDLE_INT,TRUE); // 串口空闲中断
//	usart_interrupt_enable(USART3, USART_RDBF_INT, TRUE);
	
	Dma_rx2();
}

void USART3_init(u32 bound)
{
	gpio_init_type gpio_init_struct;

	/* enable the usart3 and gpio clock */
	crm_periph_clock_enable(CRM_USART3_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
	gpio_pin_remap_config(USART3_GMUX_0011,TRUE);
	
	gpio_default_para_init(&gpio_init_struct);

	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_pins = GPIO_PINS_8;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init(GPIOD, &gpio_init_struct);

	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
	gpio_init_struct.gpio_pins = GPIO_PINS_9;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init(GPIOD, &gpio_init_struct);

	usart_init(USART3, bound, USART_DATA_8BITS, USART_STOP_1_BIT);
	usart_transmitter_enable(USART3, TRUE);
	usart_receiver_enable(USART3, TRUE);
	
	usart_dma_transmitter_enable(USART3, TRUE);
	usart_dma_receiver_enable(USART3, TRUE);
	usart_enable(USART3, TRUE);
	
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(USART3_IRQn, 3, 6);
	
	usart_interrupt_enable(USART3,USART_IDLE_INT,TRUE); // 串口空闲中断
//	usart_interrupt_enable(USART3, USART_RDBF_INT, FALSE);
  Dma_tx3();
	Dma_rx3();
}


void USART4_init(u32 bound)
{
	gpio_init_type gpio_init_struct;

	/* enable the usart3 and gpio clock */
	crm_periph_clock_enable(CRM_UART4_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
	gpio_pin_remap_config(UART4_GMUX_0010,TRUE);
	
	gpio_default_para_init(&gpio_init_struct);

	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_pins = GPIO_PINS_0;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init(GPIOA, &gpio_init_struct);

	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
	gpio_init_struct.gpio_pins = GPIO_PINS_1;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init(GPIOA, &gpio_init_struct);

	usart_init(UART4, bound, USART_DATA_8BITS, USART_STOP_1_BIT);
	usart_transmitter_enable(UART4, TRUE);
	usart_receiver_enable(UART4, TRUE);
	
	usart_dma_transmitter_enable(UART4, TRUE);
	usart_dma_receiver_enable(UART4, TRUE);
	usart_enable(UART4, TRUE);
	
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(UART4_IRQn, 3, 7);
	
	usart_interrupt_enable(UART4,USART_IDLE_INT,TRUE); // 串口空闲中断

  Dma_tx4();
	Dma_rx4();
}

uint32_t UART1_SendDataDMA(uint8_t *data, uint16_t len)
{  
	memcpy((void*)Tx1_buffer,data,len);
	usart_dma_transmitter_enable(USART1, TRUE);
	dma_channel_enable(DMA2_CHANNEL2, FALSE);
	dma_data_number_set(DMA2_CHANNEL2,len);
	dma_channel_enable(DMA2_CHANNEL2, TRUE);
  return len;
}

uint32_t UART2_SendDataDMA(uint8_t *data, uint16_t len)
{  
	memcpy((void*)Tx2_buffer,data,len);
	usart_dma_transmitter_enable(USART2, TRUE);
	dma_channel_enable(DMA2_CHANNEL4, FALSE);
	dma_data_number_set(DMA2_CHANNEL4,len);
	dma_channel_enable(DMA2_CHANNEL4, TRUE);
  return len;
}

uint32_t UART3_SendDataDMA(uint8_t *data, uint16_t len)
{  
	memcpy((void*)Tx3_buffer,data,len);
	usart_dma_transmitter_enable(USART3, TRUE);
	dma_channel_enable(DMA2_CHANNEL6, FALSE);
	dma_data_number_set(DMA2_CHANNEL6,len);
	dma_channel_enable(DMA2_CHANNEL6, TRUE);
  return len;
}

uint32_t UART4_SendDataDMA(uint8_t *data, uint16_t len)
{  
	memcpy((void*)Tx4_buffer,data,len);
	usart_dma_transmitter_enable(UART4, TRUE);
	dma_channel_enable(DMA2_CHANNEL7, FALSE);
	dma_data_number_set(DMA2_CHANNEL7,len);
	dma_channel_enable(DMA2_CHANNEL7, TRUE);
  return len;
}

void USART1_IRQHandler(void)//rx_buffer
{
  u16 len = 0;
  if(usart_flag_get(USART1, USART_IDLEF_FLAG)  != RESET)  
	{ 					
		usart_flag_clear(USART1, USART_IDLEF_FLAG);
		len = BUFFER_SIZE - dma_data_number_get(DMA2_CHANNEL1);	
		
    if(len < BUFFER_SIZE)memcpy(Get_usart1_data,Rx1_buffer,len);
		dma_channel_enable(DMA2_CHANNEL1, FALSE);
		dma_data_number_set(DMA2_CHANNEL1,BUFFER_SIZE);
		dma_channel_enable(DMA2_CHANNEL1, TRUE);
	
		U1_IDLE_Flag = 1;					
	}     
}


void USART2_IRQHandler(void)//rx_buffer
{
  u16 len = 0;
  if(usart_flag_get(USART2, USART_IDLEF_FLAG)  != RESET)  
	{ 					
		usart_flag_clear(USART2, USART_IDLEF_FLAG);
		len = BUFFER_SIZE - dma_data_number_get(DMA2_CHANNEL3);	
		
    if(len < BUFFER_SIZE)memcpy(Get_usart2_data,Rx2_buffer,len);
		dma_channel_enable(DMA2_CHANNEL3, FALSE);
		dma_data_number_set(DMA2_CHANNEL3,BUFFER_SIZE);
		dma_channel_enable(DMA2_CHANNEL3, TRUE);
	
		U2_IDLE_Flag = 1;			
	}     
}

void USART3_IRQHandler(void)//rx_buffer
{
  u16 len = 0;
  if(usart_flag_get(USART3, USART_IDLEF_FLAG)  != RESET)  
	{ 					
		usart_flag_clear(USART3, USART_IDLEF_FLAG);
		len = BUFFER_SIZE - dma_data_number_get(DMA2_CHANNEL5);	
		
    if(len < BUFFER_SIZE)memcpy(Get_usart3_data,Rx3_buffer,len);
		dma_channel_enable(DMA2_CHANNEL5, FALSE);
		dma_data_number_set(DMA2_CHANNEL5,BUFFER_SIZE);
		dma_channel_enable(DMA2_CHANNEL5, TRUE);
	
		U3_IDLE_Flag = 1;			
	}     
}

void UART4_IRQHandler(void)//rx_buffer
{
  u16 len = 0;
  if(usart_flag_get(UART4, USART_IDLEF_FLAG)  != RESET)  
	{ 					
		usart_flag_clear(UART4, USART_IDLEF_FLAG);
		len = BUFFER_SIZE - dma_data_number_get(DMA2_CHANNEL4);	
		
    if(len < BUFFER_SIZE)memcpy(Get_usart4_data,Rx4_buffer,len);
		dma_channel_enable(DMA2_CHANNEL4, FALSE);
		dma_data_number_set(DMA2_CHANNEL4,BUFFER_SIZE);
		dma_channel_enable(DMA2_CHANNEL4, TRUE);
	
		U4_IDLE_Flag = 1;			
	}     
}

void DMA2_Channel2_IRQHandler(void)
{
	if(dma_flag_get(DMA2_FDT2_FLAG))
	{
		dma_flag_clear(DMA2_FDT2_FLAG); //清除全部中断标志
		Tx1_Flag = 0;
	}
}

void DMA2_Channel6_7_IRQHandler(void)
{
	if(dma_flag_get(DMA2_FDT6_FLAG))
	{
		dma_flag_clear(DMA2_FDT6_FLAG); //清除全部中断标志
		Tx3_Flag = 0;
	}
	else if(dma_flag_get(DMA2_FDT7_FLAG))
	{
		dma_flag_clear(DMA2_FDT7_FLAG); //清除全部中断标志
		Tx4_Flag = 0;
	}
}
