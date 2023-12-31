#include "MPU6500.h"

#define SPI3_CS1  gpio_bits_set(GPIOA,GPIO_PINS_15)
#define SPI3_CS0  gpio_bits_reset(GPIOA,GPIO_PINS_15)

u8 MPU6500_data[14];

void SPI3_Init(void)
{
	spi_init_type spi_init_struct;
	gpio_init_type gpio_initstructure;
  crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
	gpio_default_para_init(&gpio_initstructure);	
	
	gpio_pin_remap_config(SPI3_GMUX_0011,TRUE);
	gpio_pin_remap_config(SWJTAG_GMUX_010,TRUE);
	
	gpio_initstructure.gpio_out_type       = GPIO_OUTPUT_PUSH_PULL;
  gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_initstructure.gpio_pull           = GPIO_PULL_UP;
	gpio_initstructure.gpio_mode           = GPIO_MODE_MUX;
	gpio_initstructure.gpio_pins           = GPIO_PINS_10 | GPIO_PINS_11 | GPIO_PINS_12;
  gpio_init(GPIOC, &gpio_initstructure);
	
	gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_initstructure.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_initstructure.gpio_mode = GPIO_MODE_OUTPUT;
  gpio_initstructure.gpio_pins = GPIO_PINS_15;
  gpio_initstructure.gpio_pull = GPIO_PULL_NONE;
  gpio_init(GPIOA, &gpio_initstructure);

	gpio_bits_set(GPIOA,GPIO_PINS_15);
	
	spi_enable(SPI3, FALSE);
	
	crm_periph_clock_enable(CRM_SPI3_PERIPH_CLOCK, TRUE);
  spi_default_para_init(&spi_init_struct);
  spi_init_struct.transmission_mode = SPI_TRANSMIT_FULL_DUPLEX;
  spi_init_struct.master_slave_mode = SPI_MODE_MASTER;
  spi_init_struct.mclk_freq_division = SPI_MCLK_DIV_4;
  spi_init_struct.first_bit_transmission = SPI_FIRST_BIT_MSB;
  spi_init_struct.frame_bit_num = SPI_FRAME_8BIT;
  spi_init_struct.clock_polarity = SPI_CLOCK_POLARITY_HIGH; // SPI_CLOCK_POLARITY_LOW SPI_CLOCK_POLARITY_HIGH
  spi_init_struct.clock_phase = SPI_CLOCK_PHASE_2EDGE;      // SPI_CLOCK_PHASE_1EDGE SPI_CLOCK_PHASE_2EDGE
  spi_init_struct.cs_mode_selection = SPI_CS_SOFTWARE_MODE;
  spi_init(SPI3, &spi_init_struct);
	
  spi_enable(SPI3, TRUE);
	delay_ms(10);
} 



/***************************************************************/
static u8 SPI3_ReadWriteByte(u8 TxData)
{		
	u8 cnt=0;				 	
	while(spi_i2s_flag_get(SPI3, SPI_I2S_TDBE_FLAG) == RESET) //等待SPI发送标志位空
	{
		cnt++;
		if(cnt>200)return 0;
	}		
  SPI3->dt = TxData;	
	
	cnt=0;

	while(spi_i2s_flag_get(SPI3, SPI_I2S_RDBF_FLAG) == RESET) //等待SPI接收标志位空
	{
		cnt++;
		if(cnt>200)return 0;
	}	  						    
	return SPI3->dt; //接收数据					    
}
/***************************************************************/

u8 IMU_Write_Reg(u8 reg,u8 value)
{
	u8 status;
	SPI3_CS0;
	status = SPI3_ReadWriteByte(reg);
	SPI3_ReadWriteByte(value);
	SPI3_CS1;
	return(status);
}

u8 IMU_Read_Reg(u8 reg)
{
	u8 reg_val;
	SPI3_CS0;
	SPI3_ReadWriteByte(reg|0x80);
	reg_val=SPI3_ReadWriteByte(0xff);
	SPI3_CS1;
	return(reg_val);
}

u8 Who_Am_I = 0;

void IMU_Init(void)
{
	SPI3_Init();
	while(Who_Am_I != 0x70)
	{
	  Who_Am_I = IMU_Read_Reg(MPU6500_WHO_AM_I); // 读取MPU6500地址
		delay_ms(1);
		R_LED(3);
	}
	R_LED(0);
	if(Who_Am_I != 0x70)
	{
		FaultBit.bit.IMU = 1; // IMU错误
		R_LED(1);
	}
	else
	{
		delay_ms(10);
		IMU_Write_Reg(MPU6500_PWR_MGMT_1,0X80);   		
		delay_ms(10);
		IMU_Write_Reg(MPU6500_PWR_MGMT_1,0X01);   		
		delay_ms(10);
		IMU_Write_Reg(MPU6500_SIGNAL_PATH_RESET,0X07);
		delay_ms(10);
		IMU_Write_Reg(MPU6500_CONFIG,0X0);					
		delay_ms(10);
		IMU_Write_Reg(MPU6500_GYRO_CONFIG,0x18);  		
		delay_ms(10);
		IMU_Write_Reg(MPU6500_ACCEL_CONFIG,0x10); 		
		delay_ms(10);
	}
}

void Get_mpu6500(u8 *data)
{
	u8 i;
	SPI3_CS0;
	SPI3_ReadWriteByte(MPU6500_ACCEL_XOUT_H|0x80);
	for(i = 0;i < 14;i++)
	{
		data[i] = SPI3_ReadWriteByte(0xff);
	}
	SPI3_CS1;
}
