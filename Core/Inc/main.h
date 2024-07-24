/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KEY_6_EXTI2_Pin GPIO_PIN_2
#define KEY_6_EXTI2_GPIO_Port GPIOE
#define KEY_6_EXTI2_EXTI_IRQn EXTI2_IRQn
#define KEY_5_EXTI3_Pin GPIO_PIN_3
#define KEY_5_EXTI3_GPIO_Port GPIOE
#define KEY_5_EXTI3_EXTI_IRQn EXTI3_IRQn
#define KEY_4_EXTI4_Pin GPIO_PIN_4
#define KEY_4_EXTI4_GPIO_Port GPIOE
#define KEY_4_EXTI4_EXTI_IRQn EXTI4_IRQn
#define KEY_3_EXTI5_Pin GPIO_PIN_5
#define KEY_3_EXTI5_GPIO_Port GPIOE
#define KEY_3_EXTI5_EXTI_IRQn EXTI9_5_IRQn
#define KEY_2_EXTI6_Pin GPIO_PIN_6
#define KEY_2_EXTI6_GPIO_Port GPIOE
#define KEY_2_EXTI6_EXTI_IRQn EXTI9_5_IRQn
#define KEY_1_EXTI7_Pin GPIO_PIN_7
#define KEY_1_EXTI7_GPIO_Port GPIOE
#define KEY_1_EXTI7_EXTI_IRQn EXTI9_5_IRQn
#define LED1_Pin GPIO_PIN_8
#define LED1_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
