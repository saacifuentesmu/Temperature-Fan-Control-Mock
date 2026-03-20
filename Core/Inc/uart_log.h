/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    uart_log.h
  * @brief   UART logging interface for interview starter project.
  ******************************************************************************
  */
/* USER CODE END Header */

#ifndef UART_LOG_H
#define UART_LOG_H

#include <stdint.h>

typedef struct
{
  uint8_t mode_auto;
  float temperature_c;
  uint16_t air_quality_index;
  uint8_t fan_duty_percent;
  uint8_t sensor_valid;
} UartLogStatus;

void UartLog_Init(void);
void UartLog_PrintStatus(const UartLogStatus *status);
void UartLog_PrintError(const char *message);

#endif /* UART_LOG_H */

