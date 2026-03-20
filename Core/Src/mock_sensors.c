/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    mock_sensors.c
  * @brief   Mock sensor implementation placeholder for interview starter project.
  ******************************************************************************
  */
/* USER CODE END Header */

#include "mock_sensors.h"

static MockSensorSample g_sample = {25.0f, 40U, 1U};

void MockSensors_Init(void)
{
  g_sample.temperature_c = 25.0f;
  g_sample.air_quality_index = 40U;
  g_sample.valid = 1U;
}

void MockSensors_Step500ms(void)
{
  /* TODO(candidates): replace with deterministic mocked profile and invalid-data cases. */
}

MockSensorSample MockSensors_GetLatest(void)
{
  return g_sample;
}

