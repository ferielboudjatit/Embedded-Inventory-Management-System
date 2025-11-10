/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : custom_bus.h
  * @brief          : header file for the BSP BUS IO driver
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CUSTOM_BUS_H
#define CUSTOM_BUS_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "custom_errno.h"
#include <stdint.h>

/** @defgroup CUSTOM_LOW_LEVEL_Exported_Variables LOW LEVEL Exported Constants
  * @{
  */

#define BUS_SPI_POLL_TIMEOUT					0x1000U
#define BUS_I2C_POLL_TIMEOUT          0x1000U

#define  I2C_HANDLE										hi2c1
#define  SPI_HANDLE										hspi1

/**
  * @}
  */

/** @addtogroup CUSTOM_BUS_Exported_Functions
  * @{
  */

int32_t BSP_I2C_Send(uint16_t DevAddr, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C_Recv(uint16_t DevAddr, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C_SendRecv(uint16_t DevAddr, uint8_t *pTxdata, uint8_t *pRxdata, uint16_t Length);

int32_t BSP_SPI_Send(uint8_t *pData, uint16_t Length);
int32_t BSP_SPI_Recv(uint8_t *pData, uint16_t Length);
int32_t BSP_SPI_SendRecv(uint8_t *pTxData, uint8_t *pRxData, uint16_t Length);

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif /* CUSTOM_BUS_H */

