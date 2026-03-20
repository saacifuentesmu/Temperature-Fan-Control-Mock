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

/** @brief Start PWM and set fan duty to 0%. */
void Fan_Init(void)
{
  current_duty = 0U;
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0U);
}

/** @brief Set fan duty cycle (0-100%), clamped. */
void Fan_SetDuty(uint8_t duty_percent)
{
  if (duty_percent > 100U)
    duty_percent = 100U;

  current_duty = duty_percent;
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, duty_percent);
}

/** @brief Return the current fan duty percentage. */
uint8_t Fan_GetDuty(void)
{
  return current_duty;
}
