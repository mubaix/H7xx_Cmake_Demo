/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define LCD_Backlight_PIN                   GPIO_PIN_15                         // 背光  引脚
#define LCD_Backlight_PORT                  GPIOD                               // 背光 GPIO端口
#define GPIO_LDC_Backlight_CLK_ENABLE       __HAL_RCC_GPIOD_CLK_ENABLE()    	// 背光 GPIO时钟

#define LCD_Backlight_OFF        			HAL_GPIO_WritePin(LCD_Backlight_PORT, LCD_Backlight_PIN, GPIO_PIN_RESET);    // 低电平，关闭背光
#define LCD_Backlight_ON        			HAL_GPIO_WritePin(LCD_Backlight_PORT, LCD_Backlight_PIN, GPIO_PIN_SET);      // 高电平，开启背光

#define LCD_DC_PIN                        	GPIO_PIN_15                         // 数据指令选择  引脚
#define LCD_DC_PORT                        	GPIOE                               // 数据指令选择  GPIO端口
#define GPIO_LDC_DC_CLK_ENABLE     			__HAL_RCC_GPIOE_CLK_ENABLE()    	// 数据指令选择  GPIO时钟

#define LCD_DC_Command           			HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);       	// 低电平，指令传输
#define LCD_DC_Data              			HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);        	// 高电平，数据传输

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

