/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    control.h
  * @brief   Control logic interface for interview starter project.
  ******************************************************************************
  */
/* USER CODE END Header */

#ifndef CONTROL_H
#define CONTROL_H

#include <stdint.h>

typedef struct
{
  float temperature_c;
  uint16_t air_quality_index;
  uint8_t sensor_valid;
  float setpoint_c;
  float kp;
} ControlInputs;

uint8_t Control_ComputeAutoDuty(const ControlInputs *inputs);

#endif /* CONTROL_H */

