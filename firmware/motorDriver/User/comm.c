
#include "comm.h"
#include "mt6701.h"
#include "pid.h"
#include "app.h"

extern PidController balancePid;
// 串口采用DMA 空闲中断模式，参考keysking@bilibili
char txBuffer[USART_BUFFER_SIZE];
char rxBuffer[USART_BUFFER_SIZE];
bool toProcessData;
uint8_t aRxBuffer;
float comm1, comm2, comm3, comm4, comm5, comm6, comm7, comm8, comm9, comm10, comm11;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart3_rx;
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  // memset(rxBuffer, '\0', sizeof(rxBuffer));
  if (huart == &huart2)
  {
    HAL_UARTEx_ReceiveToIdle_DMA(&huart2, rxBuffer, sizeof(rxBuffer));
    __HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);
    toProcessData = 1;
  }
  else if (huart == &huart3)
  {
    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, rxBuffer, sizeof(rxBuffer));
    __HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);
    toProcessData = 1;
  }
}

// DMA模式
void printLog(const char *format, ...)
{

  va_list args;           // 定义参数列表变量
  va_start(args, format); // 从format位置开始接收参数表，放在arg里面

  char strBuf[256];               // 定义输出的字符串
  vsprintf(strBuf, format, args); // 使用vsprintf将格式化的数据写入缓冲区
  va_end(args);                   // 结束可变参数的使用

  // 等待上次的数据发送完成，避免新的数据覆盖正在传输的数据，导致混乱
  // while (HAL_UART_GetState(&huart3) == HAL_UART_STATE_BUSY_TX)
  // {
  //   // Wait for DMA transfer to complete
  // }
  // HAL_UART_Transmit(&huart3, (uint8_t *)strBuf, strlen(strBuf));
  HAL_UART_Transmit(&huart3, (uint8_t *)strBuf, strlen(strBuf), 1000);
}
// void t_log(const char *s)
// {
//   strcpy(txBuffer, s);

//   HAL_UART_Transmit_DMA(&huart3, (uint8_t *)txBuffer, sizeof(txBuffer));
// }

void uartTx()
{

#if SHOW_WAVE == 0
  txDataProcess();
  // HAL_UART_Transmit_DMA(&huart2, (uint8_t *)txBuffer, 10);
  // HAL_UART_Transmit_DMA(&huart3, (uint8_t *)txBuffer, 10);
  HAL_UART_Transmit_DMA(&huart3, (uint8_t *)txBuffer, sizeof(txBuffer));
#endif
}

void commander_run(BldcMotor *motor1, BldcMotor *motor2)
{
  if (toProcessData == 1)
  {
    memset(txBuffer, '\0', sizeof(txBuffer));
    // printLog(rxBuffer);
    switch (rxBuffer[0])
    {
      // case 'S':
      //   sprintf(txBuffer, "engine start!\r\n");
      //   HAL_UART_Transmit_DMA(&huart3, (uint8_t *)txBuffer, sizeof(txBuffer));
      //   break;

    case 'H':
      sprintf(txBuffer, "Hello World!\r\n");
      break;

    case 'T': // T6.28
      motor1->target = atof((const char *)(rxBuffer + 1));
      sprintf(txBuffer, "Target=%.2f\r\n", motor1->target);
      // HAL_UART_Transmit_DMA(&huart3, (uint8_t *)txBuffer, sizeof(txBuffer));
      break;

    case 'P': // P0.5
      balancePid.P = atof((const char *)(rxBuffer + 1));
      sprintf(txBuffer, "P=%.2f\r\n", balancePid.P);
      //   HAL_UART_Transmit_DMA(&huart3, (uint8_t *)txBuffer, sizeof(txBuffer));

      break;
    case 'I': // I0.2
      balancePid.I = atof((const char *)(rxBuffer + 1));
      sprintf(txBuffer, "I=%.2f\r\n", balancePid.I);

      break;

    case 'D': // I0.2
      balancePid.D = atof((const char *)(rxBuffer + 1));
      sprintf(txBuffer, "D=%.2f\r\n", balancePid.D);
      break;
      // case 'V': // V
      //   sprintf(sndBuff, "Vel=%.2f\r\n", shaftVelocity);
      //   printf("%s", sndBuff);
      //   break;
      // case 'A': // A
      //   sprintf(sndBuff, "Ang=%.2f\r\n", shaftAngle);
      //   printf("%s", sndBuff);
      //   break;
    }
    HAL_UART_Transmit_DMA(&huart3, (uint8_t *)txBuffer, sizeof(txBuffer));
    memset(rxBuffer, '\0', sizeof(rxBuffer));
    toProcessData = 0;
  }
}
