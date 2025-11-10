
/**
  ******************************************************************************
  * @file    s2868a1_conf.h
  * @author  SRA Application Team
  * @brief   This file contains definitions for the S2868A1 components bus interfaces
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
#ifndef __S2868A1_CONF_H__
#define __S2868A1_CONF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32u5xx_hal.h"
#include "custom_bus.h"
#include "custom_errno.h"

#include "stm32u5xx_hal_exti.h"
#include "RTE_Components.h"

/* Global configuration ---------------------------------------------------*/
extern volatile int irq_disable_cnt;

/* Defines ---------------------------------------------------------------*/


/* S2868A1_RADIO_GPIO is set as EXTI */
#define S2LP_NVIC_GPIO_DisableIRQ()	HAL_NVIC_DisableIRQ( S2868A1_RADIO_GPIO_IRQn)
#define S2LP_NVIC_GPIO_EnableIRQ()	HAL_NVIC_EnableIRQ( S2868A1_RADIO_GPIO_IRQn)

#define S2868A1_ENTER_CRITICAL()	\
   do{                                                                \
		 irq_disable_cnt++;		\
		 S2LP_NVIC_GPIO_DisableIRQ();        \
   }while(0)
#define S2868A1_EXIT_CRITICAL()                             \
   do{                                                                \
     if (irq_disable_cnt > 0)                                         \
       irq_disable_cnt--;                                             \
     if (irq_disable_cnt==0)                                          \
	 {	\
		S2LP_NVIC_GPIO_EnableIRQ();        \
	}	\
   }while(0)


#define S2868A1_SPI_SendRecv                                BSP_SPI_SendRecv
#define EEPROM_SPI_SendRecv                                 BSP_SPI_SendRecv
#define S2868A1_Delay                                       HAL_Delay

#define EEPROM_INSTANCE                                     (0)

#define S2868A1_EEPROM_SPI_CS_PORT                          S2868A1_EEPROM_CS_GPIO_Port
#define S2868A1_EEPROM_SPI_CS_PIN                           S2868A1_EEPROM_CS_Pin

/* SPIx Bus Pin mapping */
#define S2868A1_RADIO_SPI_NSS_PORT                          S2868A1_S2LP_CS_GPIO_Port
#define S2868A1_RADIO_SPI_NSS_PIN                           S2868A1_S2LP_CS_Pin


/* GPIO3 as EXTI */
#define S2868A1_RADIO_GPIO_EXTI_LINE                       EXTI_LINE_7
#define S2868A1_RADIO_GPIO_IRQn                            S2868A1_GPIO_EXTI_EXTI_IRQn

extern  EXTI_HandleTypeDef   S2868A1_RADIO_GPIO_hexti;

#define S2868A1_RADIO_GPIO_SDN_PORT                          S2868A1_SDN_GPIO_Port
#define S2868A1_RADIO_GPIO_SDN_PIN                           S2868A1_SDN_Pin


#ifdef __cplusplus
}
#endif

#endif /* __S2868A1_CONF_H__*/

