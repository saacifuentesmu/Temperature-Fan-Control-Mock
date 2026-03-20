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
#include "fan.h"
#include "led_status.h"
#include "mock_sensors.h"
#include "uart_log.h"

#define SENSOR_PERIOD_MS  500U
#define UART_PERIOD_MS    1000U

#define SETPOINT_C  28.0f
#define KP          10.0f

static ControlMode current_mode = MODE_AUTO;
static uint8_t     manual_duty  = 0U;

static uint32_t last_sensor_ms = 0U;
static uint32_t last_uart_ms   = 0U;

/** @brief Initialise all application modules and set default state. */
void App_Init(void)
{
  Buttons_Init();
  MockSensors_Init();
  UartLog_Init();
  LedStatus_Init();
  Fan_Init();

  current_mode = MODE_AUTO;
  manual_duty  = 0U;
  LedStatus_SetPattern(LED_PATTERN_SOLID);
}

/** @brief Main loop tick - sensors, control, LED and UART scheduling. */
void App_Process(void)
{
  uint32_t now = HAL_GetTick();

  LedStatus_Tick(now);

  /* --- 500 ms: update mock sensors --- */
  if (now - last_sensor_ms >= SENSOR_PERIOD_MS)
  {
    last_sensor_ms = now;
    MockSensors_Step500ms();

    MockSensorSample sample = MockSensors_GetLatest();

    /* Update LED for sensor error (overrides mode pattern) */
    if (!sample.valid)
    {
      LedStatus_SetPattern(LED_PATTERN_FAST_BLINK);
    }
    else
    {
      LedStatus_SetPattern((current_mode == MODE_AUTO)
        ? LED_PATTERN_SOLID : LED_PATTERN_SLOW_BLINK);
    }

    /* Compute and apply fan duty */
    if (!sample.valid)
    {
      Fan_SetDuty(FAILSAFE_DUTY);
    }
    else if (current_mode == MODE_AUTO)
    {
      ControlInputs inputs = {
        .temperature_c     = sample.temperature_c,
        .air_quality_index = sample.air_quality_index,
        .sensor_valid      = sample.valid,
        .setpoint_c        = SETPOINT_C,
        .kp                = KP
      };
      Fan_SetDuty(Control_ComputeAutoDuty(&inputs));
    }
    else
    {
      Fan_SetDuty(manual_duty);
    }
  }

  /* --- 1000 ms: UART status report --- */
  if (now - last_uart_ms >= UART_PERIOD_MS)
  {
    last_uart_ms = now;

    MockSensorSample sample = MockSensors_GetLatest();
    UartLogStatus log = {
      .mode_auto         = (current_mode == MODE_AUTO) ? 1U : 0U,
      .temperature_c     = sample.temperature_c,
      .air_quality_index = sample.air_quality_index,
      .fan_duty_percent  = Fan_GetDuty(),
      .sensor_valid      = sample.valid
    };
    UartLog_PrintStatus(&log);
  }
}

/** @brief Return the current operating mode. */
ControlMode App_GetMode(void)
{
  return current_mode;
}

/** @brief Switch operating mode and update LED pattern. */
void App_SetMode(ControlMode mode)
{
  current_mode = mode;
  LedStatus_SetPattern((mode == MODE_AUTO) ? LED_PATTERN_SOLID : LED_PATTERN_SLOW_BLINK);
}

/** @brief Return the current manual duty percentage. */
uint8_t App_GetManualDuty(void)
{
  return manual_duty;
}

/** @brief Store a new manual duty percentage. */
void App_SetManualDuty(uint8_t duty)
{
  manual_duty = duty;
}

/** @brief Called from EXTI ISR when the mode button is pressed. */
void App_OnButtonModePressed(void)
{
  Buttons_OnModeButtonPressed();
}

/** @brief Called from EXTI ISR when the duty button is pressed. */
void App_OnButtonDutyPressed(void)
{
  Buttons_OnDutyButtonPressed();
}

