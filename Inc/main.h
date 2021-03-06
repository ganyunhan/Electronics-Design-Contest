/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "servo.h"
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
#define K2_Pin GPIO_PIN_4
#define K2_GPIO_Port GPIOE
#define K1_Pin GPIO_PIN_5
#define K1_GPIO_Port GPIOE
#define K3_Pin GPIO_PIN_6
#define K3_GPIO_Port GPIOE
#define Encoder_L_Pin GPIO_PIN_0
#define Encoder_L_GPIO_Port GPIOC
#define Encoder_L_EXTI_IRQn EXTI0_IRQn
#define Encoder_R_Pin GPIO_PIN_1
#define Encoder_R_GPIO_Port GPIOC
#define Encoder_R_EXTI_IRQn EXTI1_IRQn
#define OpenMV_Pin GPIO_PIN_2
#define OpenMV_GPIO_Port GPIOC
#define OpenMV_EXTI_IRQn EXTI2_IRQn
#define K4_Pin GPIO_PIN_7
#define K4_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */
#define debug_log 	printf
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
