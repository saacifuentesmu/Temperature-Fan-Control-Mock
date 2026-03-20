/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    led_status.h
  * @brief   Status LED driver interface.
  ******************************************************************************
  */
/* USER CODE END Header */

#ifndef LED_STATUS_H
#define LED_STATUS_H

#include <stdint.h>

typedef enum
{
  LED_PATTERN_SOLID,      /* Auto mode, normal operation */
  LED_PATTERN_SLOW_BLINK, /* Manual mode                */
  LED_PATTERN_FAST_BLINK  /* Sensor error / invalid data */
} LedPattern;

void LedStatus_Init(void);
void LedStatus_SetPattern(LedPattern pattern);
void LedStatus_Tick(uint32_t now_ms);

#endif /* LED_STATUS_H */
