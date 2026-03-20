/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    buttons.c
  * @brief   Button event handling placeholder for interview starter project.
  ******************************************************************************
  */
/* USER CODE END Header */

#include "buttons.h"
#include "app.h"

static const uint8_t manual_duty_steps[] = { 0U, 50U, 100U };
#define MANUAL_DUTY_COUNT  (sizeof(manual_duty_steps) / sizeof(manual_duty_steps[0]))
static uint8_t manual_duty_index = 0U;

void Buttons_Init(void)
{
  manual_duty_index = 0U;
}

void Buttons_OnModeButtonPressed(void)
{
  if (App_GetMode() == MODE_AUTO)
  {
    manual_duty_index = 0U;
    App_SetManualDuty(manual_duty_steps[0]);
    App_SetMode(MODE_MANUAL);
  }
  else
  {
    App_SetMode(MODE_AUTO);
  }
}

void Buttons_OnDutyButtonPressed(void)
{
  if (App_GetMode() != MODE_MANUAL)
    return;

  manual_duty_index = (manual_duty_index + 1U) % MANUAL_DUTY_COUNT;
  App_SetManualDuty(manual_duty_steps[manual_duty_index]);
}

