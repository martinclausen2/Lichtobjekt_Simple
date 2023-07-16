/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "settings.h"
#include "mainmenu.h"
#include "encoder.h"
#include "keys.h"
#include "RC5.h"
#include "extbrightness.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void MainTimerCallback(TIM_HandleTypeDef *htim);
void SystemClock_Config(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ENC_SW_Pin GPIO_PIN_0
#define ENC_SW_GPIO_Port GPIOA
#define IR_IN_Pin GPIO_PIN_2
#define IR_IN_GPIO_Port GPIOA
#define LED_1_PWM_Pin GPIO_PIN_5
#define LED_1_PWM_GPIO_Port GPIOA
#define STATUS_LED_R_PWM_Pin GPIO_PIN_6
#define STATUS_LED_R_PWM_GPIO_Port GPIOA
#define STATUS_LED_G_PWM_Pin GPIO_PIN_7
#define STATUS_LED_G_PWM_GPIO_Port GPIOA
#define STATUS_LED_B_PWM_Pin GPIO_PIN_0
#define STATUS_LED_B_PWM_GPIO_Port GPIOB
#define PERIP_PWR_Pin GPIO_PIN_2
#define PERIP_PWR_GPIO_Port GPIOB
#define IR_OUT_Pin GPIO_PIN_12
#define IR_OUT_GPIO_Port GPIOB
#define BRIGHT_IN_Pin GPIO_PIN_14
#define BRIGHT_IN_GPIO_Port GPIOB
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define BRIGHT_LOW_Pin GPIO_PIN_15
#define BRIGHT_LOW_GPIO_Port GPIOA
#define BRIGHT_HIGH_Pin GPIO_PIN_3
#define BRIGHT_HIGH_GPIO_Port GPIOB
#define ENC_B_Pin GPIO_PIN_6
#define ENC_B_GPIO_Port GPIOB
#define ENC_A_Pin GPIO_PIN_7
#define ENC_A_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
