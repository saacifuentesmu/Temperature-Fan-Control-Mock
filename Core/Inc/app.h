/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app.h
  * @brief   Application entry points for interview starter project.
  ******************************************************************************
  */
/* USER CODE END Header */

#ifndef APP_H
#define APP_H

#include "control.h"

#ifdef __cplusplus
extern "C" {
#endif

void App_Init(void);
void App_Process(void);

ControlMode App_GetMode(void);
void        App_SetMode(ControlMode mode);
uint8_t     App_GetManualDuty(void);
void        App_SetManualDuty(uint8_t duty);

void App_OnButtonModePressed(void);
void App_OnButtonDutyPressed(void);

#ifdef __cplusplus
}
#endif

#endif /* APP_H */

