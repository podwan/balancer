#include "ws2812b.h"

#define MAX_LED 1	//灯的数量

#define USE_BRIGHTNESS 0	//亮度

uint8_t LED_Data[MAX_LED][4];
uint8_t LED_Mod[MAX_LED][4];  // for brightness

void Set_LED (int LEDnum, int Red, int Green, int Blue)//RGB
{
	LED_Data[LEDnum][0] = LEDnum;
	LED_Data[LEDnum][1] = Green;
	LED_Data[LEDnum][2] = Red;
	LED_Data[LEDnum][3] = Blue;
}
void Set_LED_HEX(int LEDnum, uint32_t colorValue) //十六进制
{
	LED_Data[LEDnum][0] = LEDnum;
	LED_Data[LEDnum][2] = (colorValue >> 16) & 0xFF;  // R
	LED_Data[LEDnum][1] = (colorValue >> 8) & 0xFF;   // G
	LED_Data[LEDnum][3] = colorValue & 0xFF;          // Blue
}

#define PI 3.14159265
void Set_Brightness (int brightness)  // 0-45
{
#if USE_BRIGHTNESS

	if (brightness > 45) brightness = 45;
	for (int i=0; i<MAX_LED; i++)
	{
		LED_Mod[i][0] = LED_Data[i][0];
		for (int j=1; j<4; j++)
		{
			float angle = 90-brightness;  // in degrees
			angle = angle*PI / 180;  // in rad
			LED_Mod[i][j] = (LED_Data[i][j])/(tan(angle));
		}
	}

#endif

}


uint16_t pwmData[(24*MAX_LED)+50];

void WS2812_Send (void)
{
	uint32_t indx=0;
	uint32_t color;


	for (int i= 0; i<MAX_LED; i++)
	{
#if USE_BRIGHTNESS
		color = ((LED_Mod[i][1]<<16) | (LED_Mod[i][2]<<8) | (LED_Mod[i][3]));
#else
		color = ((LED_Data[i][1]<<16) | (LED_Data[i][2]<<8) | (LED_Data[i][3]));
#endif
		//手动设置
		for (int i=23; i>=0; i--)
		{
			if (color&(1<<i))
			{
				pwmData[indx] = 83;  // 2/3 of 125
			}

			else pwmData[indx] = 42;  // 1/3 of 125

			indx++;
		}
		//自动获取
//		for (int i=23; i>=0; i--)
//		{
//			if (color&(1<<i))
//			{
//				cc = __HAL_TIM_GET_AUTORELOAD(&htim1);
//				pwmData[indx] = (2.0/3.0*(__HAL_TIM_GET_AUTORELOAD(&htim1)+1));  // 2/3 of 125
//			}

//			else pwmData[indx] = (1.0/3.0*(__HAL_TIM_GET_AUTORELOAD(&htim1)+1));  // 1/3 of 90

//			indx++;
//		}		

	}

	for (int i=0; i<50; i++)
	{
		pwmData[indx] = 0;
		indx++;
	}

	HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, (uint32_t *)pwmData, indx);

}


