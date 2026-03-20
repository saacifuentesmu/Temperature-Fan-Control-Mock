/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    mock_sensors.h
  * @brief   Mock sensor interface for interview starter project.
  ******************************************************************************
  */
/* USER CODE END Header */

#ifndef MOCK_SENSORS_H
#define MOCK_SENSORS_H

#include <stdint.h>

typedef struct
{
  float temperature_c;
  uint16_t air_quality_index;
  uint8_t valid;
} MockSensorSample;

void MockSensors_Init(void);
void MockSensors_Step500ms(void);
MockSensorSample MockSensors_GetLatest(void);

#endif /* MOCK_SENSORS_H */

