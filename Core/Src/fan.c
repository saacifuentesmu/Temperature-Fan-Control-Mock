/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    fan.c
  * @brief   Fan PWM driver using TIM3 CH1.
  ******************************************************************************
  */
/* USER CODE END Header */

#include "fan.h"
#include "tim.h"

static uint8_t current_duty = 0U;

void Fan_Init(void)
{
  current_duty = 0U;
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0U);
}

void Fan_SetDuty(uint8_t duty_percent)
{
  if (duty_percent > 100U)
    duty_percent = 100U;

  current_duty = duty_percent;
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, duty_percent);
}

uint8_t Fan_GetDuty(void)
{
  return current_duty;
}
