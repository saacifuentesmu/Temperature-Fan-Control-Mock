/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app.c
  * @brief   Application orchestration module for interview starter project.
  ******************************************************************************
  */
/* USER CODE END Header */

#include "app.h"
#include "main.h"

#include "buttons.h"
#include "control.h"
#include "led_status.h"
#include "mock_sensors.h"
#include "uart_log.h"

static ControlMode current_mode = MODE_AUTO;
static uint8_t     manual_duty  = 0U;

void App_Init(void)
{
  Buttons_Init();
  MockSensors_Init();
  UartLog_Init();
  LedStatus_Init();

  current_mode = MODE_AUTO;
  manual_duty  = 0U;
  LedStatus_SetPattern(LED_PATTERN_SOLID);
}

void App_Process(void)
{
  LedStatus_Tick(HAL_GetTick());

  /* TODO(candidates): implement periodic sensor update, control loop, and UART status logic. */
}

ControlMode App_GetMode(void)
{
  return current_mode;
}

void App_SetMode(ControlMode mode)
{
  current_mode = mode;
  LedStatus_SetPattern((mode == MODE_AUTO) ? LED_PATTERN_SOLID : LED_PATTERN_SLOW_BLINK);
}

uint8_t App_GetManualDuty(void)
{
  return manual_duty;
}

void App_SetManualDuty(uint8_t duty)
{
  manual_duty = duty;
}

void App_OnButtonModePressed(void)
{
  Buttons_OnModeButtonPressed();
}

void App_OnButtonDutyPressed(void)
{
  Buttons_OnDutyButtonPressed();
}

