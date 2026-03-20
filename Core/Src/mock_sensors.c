/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    mock_sensors.c
  * @brief   Mock sensor implementation placeholder for interview starter project.
  ******************************************************************************
  */
/* USER CODE END Header */

#include "mock_sensors.h"

static MockSensorSample g_sample;
static uint16_t g_step;

/* Deterministic profile: 20 steps (10 s), then repeats.
 * Steps 0-7:   temperature ramps 22 -> 36, AQI ramps 40 -> 180, valid
 * Steps 8-9:   sensor invalid window
 * Steps 10-17: temperature ramps 36 -> 22, AQI ramps 250 -> 50, valid
 * Steps 18-19: sensor invalid window
 */
#define PROFILE_LEN 20U

static const float    temp_profile[PROFILE_LEN]  = {
  22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f, 34.0f, 36.0f,  /* ramp up   */
  0.0f, 0.0f,                                                 /* invalid   */
  36.0f, 34.0f, 32.0f, 30.0f, 28.0f, 26.0f, 24.0f, 22.0f,   /* ramp down */
  0.0f, 0.0f                                                   /* invalid   */
};

static const uint16_t aqi_profile[PROFILE_LEN]   = {
  40, 60, 80, 100, 120, 140, 160, 180,   /* ramp up   */
  0, 0,                                    /* invalid   */
  250, 220, 190, 160, 130, 100, 70, 50,   /* ramp down */
  0, 0                                     /* invalid   */
};

static const uint8_t  valid_profile[PROFILE_LEN] = {
  1, 1, 1, 1, 1, 1, 1, 1,
  0, 0,
  1, 1, 1, 1, 1, 1, 1, 1,
  0, 0
};

void MockSensors_Init(void)
{
  g_step = 0U;
  g_sample.temperature_c     = temp_profile[0];
  g_sample.air_quality_index = aqi_profile[0];
  g_sample.valid             = valid_profile[0];
}

void MockSensors_Step500ms(void)
{
  g_step = (g_step + 1U) % PROFILE_LEN;
  g_sample.temperature_c     = temp_profile[g_step];
  g_sample.air_quality_index = aqi_profile[g_step];
  g_sample.valid             = valid_profile[g_step];
}

MockSensorSample MockSensors_GetLatest(void)
{
  return g_sample;
}

