/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    control.c
  * @brief   Control logic placeholder for interview starter project.
  ******************************************************************************
  */
/* USER CODE END Header */

#include "control.h"

static uint8_t clamp_u8(int32_t val, int32_t lo, int32_t hi)
{
  if (val < lo) return (uint8_t)lo;
  if (val > hi) return (uint8_t)hi;
  return (uint8_t)val;
}

uint8_t Control_ComputeAutoDuty(const ControlInputs *inputs)
{
  if (!inputs->sensor_valid)
    return FAILSAFE_DUTY;

  /* P controller: duty = Kp * (temp - setpoint), clamped to [0, 100] */
  int32_t p_duty = (int32_t)(inputs->kp * (inputs->temperature_c - inputs->setpoint_c));
  uint8_t duty = clamp_u8(p_duty, 0, 100);

  /* AQI override: impose minimum duty based on air quality */
  if (inputs->air_quality_index > 220U)
  {
    if (duty < 100U) duty = 100U;
  }
  else if (inputs->air_quality_index > 150U)
  {
    if (duty < 60U) duty = 60U;
  }

  return duty;
}

