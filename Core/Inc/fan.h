/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    fan.h
  * @brief   Fan PWM driver interface.
  ******************************************************************************
  */
/* USER CODE END Header */

#ifndef FAN_H
#define FAN_H

#include <stdint.h>

void    Fan_Init(void);
void    Fan_SetDuty(uint8_t duty_percent);
uint8_t Fan_GetDuty(void);

#endif /* FAN_H */
