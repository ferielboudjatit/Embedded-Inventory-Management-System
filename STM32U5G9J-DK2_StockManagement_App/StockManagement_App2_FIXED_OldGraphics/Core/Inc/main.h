/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32u5xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "custom_bus.h"
#include "../../X-CUBE-NFC6/Target/nfc_conf.h"
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
#define LCD_DISP_EN_Pin GPIO_PIN_4
#define LCD_DISP_EN_GPIO_Port GPIOE
#define TP_IRQ_Pin GPIO_PIN_5
#define TP_IRQ_GPIO_Port GPIOE
#define TP_IRQ_EXTI_IRQn EXTI5_IRQn
#define LCD_BL_CTRL_Pin GPIO_PIN_6
#define LCD_BL_CTRL_GPIO_Port GPIOE
#define USER_BUTTON_Pin GPIO_PIN_13
#define USER_BUTTON_GPIO_Port GPIOC
#define VSYNC_FREQ_Pin GPIO_PIN_0
#define VSYNC_FREQ_GPIO_Port GPIOC
#define NFC08A1_INT_EXTI_Pin GPIO_PIN_2
#define NFC08A1_INT_EXTI_GPIO_Port GPIOC
#define NFC08A1_INT_EXTI_EXTI_IRQn EXTI2_IRQn
#define S2868A1_S2LP_CS_Pin GPIO_PIN_3
#define S2868A1_S2LP_CS_GPIO_Port GPIOC
#define S2868A1_SPI_SCK_Pin GPIO_PIN_5
#define S2868A1_SPI_SCK_GPIO_Port GPIOA
#define S2868A1_SPI_MISO_Pin GPIO_PIN_6
#define S2868A1_SPI_MISO_GPIO_Port GPIOA
#define S2868A1_GPIO_EXTI_Pin GPIO_PIN_7
#define S2868A1_GPIO_EXTI_GPIO_Port GPIOA
#define S2868A1_GPIO_EXTI_EXTI_IRQn EXTI7_IRQn
#define S2868A1_EEPROM_CS_Pin GPIO_PIN_10
#define S2868A1_EEPROM_CS_GPIO_Port GPIOB
#define S2868A1_SDN_Pin GPIO_PIN_14
#define S2868A1_SDN_GPIO_Port GPIOB
#define COM_USART_TX_Pin GPIO_PIN_9
#define COM_USART_TX_GPIO_Port GPIOA
#define COM_USART_RX_Pin GPIO_PIN_10
#define COM_USART_RX_GPIO_Port GPIOA
#define RENDER_TIME_Pin GPIO_PIN_10
#define RENDER_TIME_GPIO_Port GPIOC
#define FRAME_RATE_Pin GPIO_PIN_11
#define FRAME_RATE_GPIO_Port GPIOC
#define MCU_ACTIVE_Pin GPIO_PIN_12
#define MCU_ACTIVE_GPIO_Port GPIOC
#define S2868A1_LED_Pin GPIO_PIN_2
#define S2868A1_LED_GPIO_Port GPIOD
#define USER_LD3_GREEN_Pin GPIO_PIN_4
#define USER_LD3_GREEN_GPIO_Port GPIOD
#define NFC08A1_I2C_SDA_Pin GPIO_PIN_13
#define NFC08A1_I2C_SDA_GPIO_Port GPIOG
#define NFC08A1_I2C_SCL_Pin GPIO_PIN_14
#define NFC08A1_I2C_SCL_GPIO_Port GPIOG
#define S2868A1_SPI_MOSI_Pin GPIO_PIN_5
#define S2868A1_SPI_MOSI_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
