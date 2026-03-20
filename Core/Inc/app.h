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

#ifdef __cplusplus
extern "C" {
#endif

void App_Init(void);
void App_Process(void);

void App_OnButtonModePressed(void);
void App_OnButtonDutyPressed(void);

#ifdef __cplusplus
}
#endif

#endif /* APP_H */

