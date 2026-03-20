/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app.c
  * @brief   Application orchestration module for interview starter project.
  ******************************************************************************
  */
/* USER CODE END Header */

#include "app.h"

#include "buttons.h"
#include "control.h"
#include "mock_sensors.h"
#include "uart_log.h"

void App_Init(void)
{
  Buttons_Init();
  MockSensors_Init();
  UartLog_Init();
}

void App_Process(void)
{

  /* TODO(candidates): implement periodic sensor update, control loop, and UART status logic. */
}

void App_OnButtonModePressed(void)
{
  Buttons_OnModeButtonPressed();
}

void App_OnButtonDutyPressed(void)
{
  Buttons_OnDutyButtonPressed();
}

