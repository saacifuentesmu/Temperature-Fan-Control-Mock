/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    led_status.c
  * @brief   Status LED driver – solid / slow blink / fast blink.
  ******************************************************************************
  */
/* USER CODE END Header */

#include "led_status.h"
#include "main.h"

#define SLOW_BLINK_PERIOD_MS  1000U
#define FAST_BLINK_PERIOD_MS  200U

static LedPattern current_pattern = LED_PATTERN_SOLID;
static uint32_t   last_toggle_ms  = 0U;

void LedStatus_Init(void)
{
  current_pattern = LED_PATTERN_SOLID;
  last_toggle_ms  = 0U;
  HAL_GPIO_WritePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin, GPIO_PIN_RESET);
}

void LedStatus_SetPattern(LedPattern pattern)
{
  if (pattern == current_pattern)
    return;

  current_pattern = pattern;
  last_toggle_ms  = 0U;

  if (pattern == LED_PATTERN_SOLID)
    HAL_GPIO_WritePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin, GPIO_PIN_SET);
}

void LedStatus_Tick(uint32_t now_ms)
{
  uint32_t period;

  switch (current_pattern)
  {
    case LED_PATTERN_SOLID:
      return;

    case LED_PATTERN_SLOW_BLINK:
      period = SLOW_BLINK_PERIOD_MS;
      break;

    case LED_PATTERN_FAST_BLINK:
      period = FAST_BLINK_PERIOD_MS;
      break;

    default:
      return;
  }

  if (now_ms - last_toggle_ms >= period)
  {
    HAL_GPIO_TogglePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin);
    last_toggle_ms = now_ms;
  }
}
