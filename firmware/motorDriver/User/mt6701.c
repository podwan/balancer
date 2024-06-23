#include "mt6701.h"
#include "focLib.h"
#include "time_utils.h"
// static unsigned int rotationCount, rotationCount_Last;

uint16_t _1_MT6701_GetRawData(void)
{
    uint16_t rawData;
    uint16_t txData = 0xFFFF;
    uint16_t timeOut = 200;

    while (HAL_SPI_GetState(&hspi3) != HAL_SPI_STATE_READY)
    {
        if (timeOut-- == 0)
        {
            printLog("SPI state error!\r\n");
            return 0; // 在超时时直接返回，避免继续执行后续代码
        }
    }

    _1_MT6701_CS_Enable;

    HAL_StatusTypeDef spiStatus = HAL_SPI_TransmitReceive(&hspi3, (uint8_t *)&txData, (uint8_t *)&rawData, 1, HAL_MAX_DELAY);
    if (spiStatus != HAL_OK)
    {
        _1_MT6701_CS_Disable;
        printLog("MT6701 read data error!\r\n");
        return 0; // 在SPI传输错误时直接返回，避免继续执行后续代码
    }

    _1_MT6701_CS_Disable;

    return rawData >> 2; // 取高14位的角度数据
}

// 将传感器原始数据转化为弧度
float _1_MT6701_GetRawAngle(void)
{
    uint16_t rawData = _1_MT6701_GetRawData();
    return (float)rawData / 16384.0f * _2PI;
}

uint16_t _2_MT6701_GetRawData(void)
{
    uint16_t rawData;
    uint16_t txData = 0xFFFF;
    uint16_t timeOut = 200;

    while (HAL_SPI_GetState(&hspi3) != HAL_SPI_STATE_READY)
    {
        if (timeOut-- == 0)
        {
            printLog("SPI state error!\r\n");
            return 0; // 在超时时直接返回，避免继续执行后续代码
        }
    }

    _2_MT6701_CS_Enable;

    HAL_StatusTypeDef spiStatus = HAL_SPI_TransmitReceive(&hspi3, (uint8_t *)&txData, (uint8_t *)&rawData, 1, HAL_MAX_DELAY);
    if (spiStatus != HAL_OK)
    {
        _2_MT6701_CS_Disable;
        printLog("MT6701 read data error!\r\n");
        return 0; // 在SPI传输错误时直接返回，避免继续执行后续代码
    }

    _2_MT6701_CS_Disable;

    return rawData >> 2; // 取高14位的角度数据
}

// 将传感器原始数据转化为弧度
float _2_MT6701_GetRawAngle(void)
{
    uint16_t rawData = _2_MT6701_GetRawData();
    return (float)rawData / 16384.0f * _2PI;
}
