/********************************************************************************
  * @file           : nfc_conf.h
  * @brief          : This file contains definitions for the NFC6/8 components bus interfaces
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __NFC0XA1_CONF_H__
#define __NFC0XA1_CONF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32u5xx_hal.h"
#include "custom_bus.h"
#include "custom_errno.h"
#include "stm32u5xx_hal_exti.h"
#include "RTE_Components.h"
#include "rfal_defConfig.h"
#include "../../Drivers/BSP/Components/ST25R3916/st25r3916_irq.h"
#include "i2c.h"
#include "../App/app_x-cube-nfcx.h"


/******************************************************************************
* GLOBAL VARIABLES
******************************************************************************
*/

/* Exported variables --------------------------------------------------------*/


extern uint8_t globalCommProtectCnt;
extern  EXTI_HandleTypeDef H_EXTI_2;

/* Exported constants --------------------------------------------------------*/
/** @defgroup PTD_Platform_Exported_Constants
 *  @{
 */
#define RFAL_USE_I2C  1

#define USE_LOGGER 1

#define ST25R_INT_PIN            NFC08A1_INT_EXTI_Pin    /*!< GPIO pin used for ST25R IRQ                   */
#define ST25R_INT_PORT           NFC08A1_INT_EXTI_GPIO_Port   /*!< GPIO port used for ST25R IRQ port             */

#define IRQ_ST25R_EXTI_IRQn      NFC08A1_INT_EXTI_EXTI_IRQn

#define USR_INT_LINE             H_EXTI_2
#define USR_INT_LINE_NUM         EXTI_LINE_2



/**
  * @}
  */

/**
  * @}
  */



/* Exported functions ------------------------------------------------------- */




void _Error_Handler(char * file, int line);

#ifdef __cplusplus
}
#endif

#endif /* __NFC0XA1_CONF_H__*/

