/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    uart_log.c
  * @brief   UART logging placeholder for interview starter project.
  ******************************************************************************
  */
/* USER CODE END Header */

#include "uart_log.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>

static char tx_buf[128];

static void uart_send(const char *str)
{
  HAL_UART_Transmit(&huart2, (const uint8_t *)str, (uint16_t)strlen(str), 50U);
}

void UartLog_Init(void)
{
  uart_send("== Fan Control Started ==\r\n");
}

void UartLog_PrintStatus(const UartLogStatus *status)
{
  int len = snprintf(tx_buf, sizeof(tx_buf),
    "[%s] T=%.1fC AQI=%u Duty=%u%% Sensor=%s\r\n",
    status->mode_auto ? "AUTO" : "MANUAL",
    (double)status->temperature_c,
    status->air_quality_index,
    status->fan_duty_percent,
    status->sensor_valid ? "OK" : "ERR");

  if (len > 0)
    HAL_UART_Transmit(&huart2, (const uint8_t *)tx_buf, (uint16_t)len, 50U);
}

void UartLog_PrintError(const char *message)
{
  uart_send("[ERROR] ");
  uart_send(message);
  uart_send("\r\n");
}

