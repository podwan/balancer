#include "app.h"

#define I2C_TIMEOUT                      0xFFFFFFFF

#define I2Cx_SPEED                       100000
#define I2Cx_ADDRESS                     0x66

#define I2Cx_PORT                        I2C2
#define I2Cx_CLK                         CRM_I2C2_PERIPH_CLOCK

#define I2Cx_SCL_PIN                     GPIO_PINS_10
#define I2Cx_SCL_GPIO_PORT               GPIOB
#define I2Cx_SCL_GPIO_CLK                CRM_GPIOB_PERIPH_CLOCK

#define I2Cx_SDA_PIN                     GPIO_PINS_11
#define I2Cx_SDA_GPIO_PORT               GPIOB
#define I2Cx_SDA_GPIO_CLK                CRM_GPIOB_PERIPH_CLOCK

#define I2Cx_DMA_CLK                     CRM_DMA1_PERIPH_CLOCK
#define I2Cx_DMA_TX_CHANNEL              DMA1_CHANNEL6
#define I2Cx_DMA_TX_IRQn                 DMA1_Channel6_IRQn

#define I2Cx_DMA_RX_CHANNEL              DMA1_CHANNEL7
#define I2Cx_DMA_RX_IRQn                 DMA1_Channel7_IRQn

#define I2Cx_EVT_IRQn                    I2C2_EVT_IRQn
#define I2Cx_ERR_IRQn                    I2C2_ERR_IRQn

#define I2Cx_DMA_TX_IRQHandler           DMA1_Channel6_IRQHandler
#define I2Cx_DMA_RX_IRQHandler           DMA1_Channel7_IRQHandler
#define I2Cx_EVT_IRQHandler              I2C1_EVT_IRQHandler
#define I2Cx_ERR_IRQHandler              I2C1_ERR_IRQHandler

#define BUF_SIZE                         8

uint8_t I2C2_tx_buf[BUF_SIZE] = {0x9f, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
uint8_t I2C2_rx_buf[BUF_SIZE] = {0};

i2c_handle_type hi2cx;

void I2C_Init(void)
{
	hi2cx.i2cx = I2Cx_PORT;
  i2c_config(&hi2cx);
}

void test_bank(void)
{
	i2c_status_type i2c_status;

	/* 启动请求发送流程 */
	if((i2c_status = i2c_master_transmit_dma(&hi2cx, I2Cx_ADDRESS, I2C2_tx_buf, 1, I2C_TIMEOUT)) != I2C_OK)
	{
		error_handler(i2c_status);
	}

	/* 等待通信结束 */
	if(i2c_wait_end(&hi2cx, I2C_TIMEOUT) != I2C_OK)
	{
		error_handler(i2c_status);
	}

//	delay_ms(10);

//	/* 启动请求接收流程 */
//	if((i2c_status = i2c_master_receive_dma(&hi2cx, I2Cx_ADDRESS, I2C2_rx_buf, BUF_SIZE, I2C_TIMEOUT)) != I2C_OK)
//	{
//		error_handler(i2c_status);
//	}

//	/* 等待通信结束 */
//	if(i2c_wait_end(&hi2cx, I2C_TIMEOUT) != I2C_OK)
//	{
//		error_handler(i2c_status);
//	}
}

/**
  * @brief  initializes peripherals used by the i2c.
  * @param  none
  * @retval none
  */
void i2c_lowlevel_init(i2c_handle_type* hi2c)
{
  gpio_init_type gpio_initstructure;

  if(hi2c->i2cx == I2Cx_PORT)
  {
    /* i2c periph clock enable */
    crm_periph_clock_enable(I2Cx_CLK, TRUE);
    crm_periph_clock_enable(I2Cx_SCL_GPIO_CLK, TRUE);
    crm_periph_clock_enable(I2Cx_SDA_GPIO_CLK, TRUE);

    /* gpio configuration */
    gpio_initstructure.gpio_out_type       = GPIO_OUTPUT_OPEN_DRAIN;
    gpio_initstructure.gpio_pull           = GPIO_PULL_UP;
    gpio_initstructure.gpio_mode           = GPIO_MODE_MUX;
    gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;

    /* configure i2c pins: scl */
    gpio_initstructure.gpio_pins = I2Cx_SCL_PIN;
    gpio_init(I2Cx_SCL_GPIO_PORT, &gpio_initstructure);

    /* configure i2c pins: sda */
    gpio_initstructure.gpio_pins = I2Cx_SDA_PIN;
    gpio_init(I2Cx_SDA_GPIO_PORT, &gpio_initstructure);

    /* 配置并启用i2c dma通道中断 */
    nvic_irq_enable(I2Cx_DMA_TX_IRQn, 3, 1);
    nvic_irq_enable(I2Cx_DMA_RX_IRQn, 3, 2);

    /* 配置并启用i2c中断 */
    nvic_irq_enable(I2Cx_EVT_IRQn, 3, 3);
    nvic_irq_enable(I2Cx_ERR_IRQn, 3, 4);

    /* i2c dma tx and rx channels configuration */
    /* enable the dma clock */
    crm_periph_clock_enable(I2Cx_DMA_CLK, TRUE);

    /* i2c dma channel configuration */
    dma_reset(hi2c->dma_tx_channel);
    dma_reset(hi2c->dma_rx_channel);

    hi2c->dma_tx_channel = I2Cx_DMA_TX_CHANNEL;
    hi2c->dma_rx_channel = I2Cx_DMA_RX_CHANNEL;
    
		dma_flexible_config(DMA1, FLEX_CHANNEL6, DMA_FLEXIBLE_I2C2_TX);
		dma_flexible_config(DMA1, FLEX_CHANNEL7, DMA_FLEXIBLE_I2C2_RX);
		
    dma_default_para_init(&hi2c->dma_init_struct);
    hi2c->dma_init_struct.peripheral_inc_enable    = FALSE;
    hi2c->dma_init_struct.memory_inc_enable        = TRUE;
    hi2c->dma_init_struct.peripheral_data_width    = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
    hi2c->dma_init_struct.memory_data_width        = DMA_MEMORY_DATA_WIDTH_BYTE;
    hi2c->dma_init_struct.loop_mode_enable         = FALSE;
    hi2c->dma_init_struct.priority                 = DMA_PRIORITY_LOW;
    hi2c->dma_init_struct.direction                = DMA_DIR_MEMORY_TO_PERIPHERAL;
     
    dma_init(hi2c->dma_tx_channel, &hi2c->dma_init_struct);
    dma_init(hi2c->dma_rx_channel, &hi2c->dma_init_struct);

    i2c_init(hi2c->i2cx, I2C_FSMODE_DUTY_2_1, I2Cx_SPEED);

    i2c_own_address1_set(hi2c->i2cx, I2C_ADDRESS_MODE_7BIT, I2Cx_ADDRESS);
  }
}

/**
  * @brief  error handler program
  * @param  i2c_status
  * @retval none
  */
void error_handler(uint32_t error_code)
{
//  while(1)
//  {

//  }
}

/**
  * @brief  this function handles dma interrupt request.
  * @param  none
  * @retval none
  */
void I2Cx_DMA_RX_IRQHandler(void)
{
  i2c_dma_rx_irq_handler(&hi2cx);
}

/**
  * @brief  this function handles dma interrupt request.
  * @param  none
  * @retval none
  */
void I2Cx_DMA_TX_IRQHandler(void)
{
  i2c_dma_tx_irq_handler(&hi2cx);
}

/**
  * @brief  this function handles i2c event interrupt request.
  * @param  none
  * @retval none
  */
void I2Cx_EVT_IRQHandler(void)
{
  i2c_evt_irq_handler(&hi2cx);
}

/**
  * @brief  this function handles i2c error interrupt request.
  * @param  none
  * @retval none
  */
void I2Cx_ERR_IRQHandler(void)
{
  i2c_err_irq_handler(&hi2cx);
}

/**
  * @}
  */

/**
  * @}
  */


