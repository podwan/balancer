#include "app.h"

void W25Qxx_Init(void)
{
	spi_init_type spi_init_struct;
	gpio_init_type gpio_initstructure;
	crm_periph_clock_enable(CRM_GPIOE_PERIPH_CLOCK, TRUE);
	gpio_default_para_init(&gpio_initstructure);

	gpio_initstructure.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_initstructure.gpio_pull = GPIO_PULL_UP;
	gpio_initstructure.gpio_mode = GPIO_MODE_MUX;
	gpio_initstructure.gpio_pins = GPIO_PINS_2 | GPIO_PINS_5 | GPIO_PINS_6;
	gpio_init(GPIOE, &gpio_initstructure);

	gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_initstructure.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_initstructure.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_initstructure.gpio_pins = GPIO_PINS_4;
	gpio_initstructure.gpio_pull = GPIO_PULL_NONE;
	gpio_init(GPIOE, &gpio_initstructure);

	gpio_bits_set(GPIOE, GPIO_PINS_4);

	spi_enable(SPI4, FALSE);

	crm_periph_clock_enable(CRM_SPI4_PERIPH_CLOCK, TRUE);
	spi_default_para_init(&spi_init_struct);
	spi_init_struct.transmission_mode = SPI_TRANSMIT_FULL_DUPLEX;
	spi_init_struct.master_slave_mode = SPI_MODE_MASTER;
	spi_init_struct.mclk_freq_division = SPI_MCLK_DIV_8;
	spi_init_struct.first_bit_transmission = SPI_FIRST_BIT_MSB;
	spi_init_struct.frame_bit_num = SPI_FRAME_8BIT;
	spi_init_struct.clock_polarity = SPI_CLOCK_POLARITY_HIGH; // SPI_CLOCK_POLARITY_LOW SPI_CLOCK_POLARITY_HIGH
	spi_init_struct.clock_phase = SPI_CLOCK_PHASE_2EDGE;	  // SPI_CLOCK_PHASE_1EDGE SPI_CLOCK_PHASE_2EDGE
	spi_init_struct.cs_mode_selection = SPI_CS_SOFTWARE_MODE;
	spi_init(SPI4, &spi_init_struct);

	spi_enable(SPI4, TRUE);
	delay_ms(1);

	//	while(ReadW25Qxx_ID() != 0XC815)
	while (ReadW25Qxx_ID() != 0XEF16)
	{
		delay_ms(1);
		R_LED(2);
	}
	R_LED(0);
}

static uint8_t SPI4_ReadWriteByte(uint8_t data)
{
	uint8_t retry = 0;
	while (spi_i2s_flag_get(SPI4, SPI_I2S_TDBE_FLAG) == RESET) // 等待SPI发送标志位空
	{
		retry++;
		if (retry > 200)
			return 0;
	}
	SPI4->dt = data;
	retry = 0;

	while (spi_i2s_flag_get(SPI4, SPI_I2S_RDBF_FLAG) == RESET) // 等待SPI接收标志位空
	{
		retry++;
		if (retry > 200)
			return 0;
	}
	return SPI4->dt; // 接收数据
}

uint16_t ReadW25Qxx_ID(void)
{
	uint8_t data1 = 0, data2 = 0;
	W25Qxx_CS0;
	SPI4_ReadWriteByte(0x90);
	SPI4_ReadWriteByte(0x00);
	SPI4_ReadWriteByte(0x00);
	SPI4_ReadWriteByte(0x00);
	data1 = SPI4_ReadWriteByte(0);
	data2 = SPI4_ReadWriteByte(0);
	W25Qxx_CS1;
	return data1 << 8 | data2;
}

void W25Qxx_WriteEnable(void)
{
	W25Qxx_CS0;
	SPI4_ReadWriteByte(0x06);
	W25Qxx_CS1;
}

uint8_t W25Qxx_ReadStatus(void)
{
	uint8_t data = 0;
	W25Qxx_CS0;
	SPI4_ReadWriteByte(0x05);
	data = SPI4_ReadWriteByte(0);
	W25Qxx_CS1;
	return data;
}

void W25Qxx_WaitBusy(void)
{
	while ((W25Qxx_ReadStatus() & 1) == 1)
		;
}

void W25Qxx_ErasePage(uint32_t addr)
{
	uint8_t data1, data2, data3;
	addr *= 4096;
	data1 = addr >> 16;
	data2 = addr >> 8;
	data3 = addr;

	W25Qxx_WriteEnable();
	W25Qxx_WaitBusy();
	W25Qxx_CS0;
	SPI4_ReadWriteByte(0x20);
	SPI4_ReadWriteByte(data1);
	SPI4_ReadWriteByte(data2);
	SPI4_ReadWriteByte(data3);
	W25Qxx_CS1;
	W25Qxx_WaitBusy();
}

void W25Qxx_WritePage(uint8_t *Buffer, uint32_t addr, uint16_t len) // 在指定地址开始写入最大256字节的数据
{
	uint8_t i;
	uint8_t data1, data2, data3;

	if (len > 256)
		len = 256;
	data1 = addr >> 16;
	data2 = addr >> 8;
	data3 = addr;

	W25Qxx_WriteEnable();
	W25Qxx_CS0;
	SPI4_ReadWriteByte(0x02);
	SPI4_ReadWriteByte(data1);
	SPI4_ReadWriteByte(data2);
	SPI4_ReadWriteByte(data3);
	for (i = 0; i < len; i++)
	{
		SPI4_ReadWriteByte(Buffer[i]);
	}
	W25Qxx_CS1;
	W25Qxx_WaitBusy();
}

void W25Qxx_Read(uint8_t *Buffer, uint32_t addr, uint16_t len) // 在指定地址开始读取指定长度的数据
{
	uint16_t i;
	uint8_t data1, data2, data3;
	data1 = addr >> 16;
	data2 = addr >> 8;
	data3 = addr;

	W25Qxx_CS0;
	SPI4_ReadWriteByte(0x03);
	SPI4_ReadWriteByte(data1);
	SPI4_ReadWriteByte(data2);
	SPI4_ReadWriteByte(data3);
	for (i = 0; i < len; i++)
	{
		Buffer[i] = SPI4_ReadWriteByte(0);
	}
	W25Qxx_CS1;
}
