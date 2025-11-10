
/**
  ******************************************************************************
  * File Name          :  app_x-cube-nfcx.c
  * Description        : This file provides code for the configuration
  *                      of the STMicroelectronics.X-CUBE-NFC6.3.1.0 instances.
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

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "rfal_platform.h"
#include "nfc_conf.h"
#include "app_x-cube-nfcx.h"
#include "app_x-cube-subg2.h"

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

/** @defgroup App NFC6
  * @{
  */

/** @defgroup Main
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Global variables ----------------------------------------------------------*/

uint8_t globalCommProtectCnt = 0;   /*!< Global Protection counter     */

// FreeRTOS variables
NFCtask_messages_t NFCmessage;
/* Private functions ---------------------------------------------------------*/


void MX_X_CUBE_NFC6_Init(void)
{
  /* USER CODE BEGIN SV */

  /* USER CODE END SV */

  /* USER CODE BEGIN NFC8_Library_Init_PreTreatment */
  /* USER CODE END NFC8_Library_Init_PreTreatment */

  /* Initialize the peripherals and the NFC8 components */
  MX_NFC8_PollingTagDetectNDEF_Init();
   /* USER CODE BEGIN SV */

  /* USER CODE END SV */

  /* USER CODE BEGIN NFC8_Library_Init_PostTreatment */

  /* USER CODE END NFC8_Library_Init_PostTreatment */

}
/*
 * LM background task
 */
void MX_X_CUBE_NFC6_Process(void)
{

    /* USER CODE BEGIN NFC8_Library_Process */

    /* USER CODE END NFC8_Library_Process */
    /* Run Demo Application */
    demoCycle();

}

/**
  * @brief  Initialize the I2CProtection  feature Example
  * @retval None
  */
void MX_NFC8_PollingTagDetectNDEF_Init(void)
{
   USR_INT_LINE.Line = USR_INT_LINE_NUM;

   /* Configure interrupt callback */
  (void)HAL_EXTI_GetHandle(&USR_INT_LINE, USR_INT_LINE.Line);
  (void)HAL_EXTI_RegisterCallback(&USR_INT_LINE, HAL_EXTI_COMMON_CB_ID, BSP_NFC0XCOMM_IRQ_Callback);

  platformLog("Welcome to T.O.M.A.S Stock Management Demo\r\n");
  //SendToTouchGFX(WELCOME_MESSAGE);
  /* Initalize RFAL */
  if( !demoIni() )
  {
    /*
    * in case the rfal initalization failed signal it by flashing all LED
    * and stoping all operations
    */
    platformLog("Initialization failed..\r\n");
  }
  else
  {
    platformLog("Initialization succeeded..\r\n");
  }
  platformLog("Tap a board tag to scan it\r\n");
//  SendToTouchGFX(WELCOME_MESSAGE);
}

/**
 * @brief   This function sends data on the uart
 * @param   puartmsg:
 * @retval  HAL_StatusTypeDef
 */
HAL_StatusTypeDef UARTConsolePrint( char *puartmsg )
{
  return HAL_UART_Transmit( &huart1, (uint8_t *)puartmsg, strlen( puartmsg ), 500);
}

/**
 * @brief   This function wait a data on the uart
 * @param   uartchar received character
 * @retval  HAL_StatusTypeDef
 */
HAL_StatusTypeDef UARTConsoleScan( uint8_t uartchar )
{
  while( HAL_UART_Receive( &huart1, &uartchar, 1, 500) == HAL_TIMEOUT );

  return HAL_OK;
}

/**
  * @brief     This method transmits sequentially in master I2C mode an amount of data in blocking mode with Interrupt.
  * @param[in] address : Target device address: The device 7 bits address value
  *                      in datasheet must be shifted to the left before calling the interface
  * @param[in] txBuf   : Pointer to data buffer
  * @param[in] txLen   : Amount of data to be sent
  * @param[in] last    : true if last data to be transmitted
  * @param[in] txOnly  : true if no reception is to be performed after (STOP)
  *                      false if a reception should happen afterwards with repeated START
  * @return    HAL Error code
  */
int32_t BSP_NFC0XCOMM_SequencialSend(const uint16_t DevAddr, const uint8_t * const pData, const uint16_t Length, const uint8_t last, const uint8_t txOnly)
{
  HAL_StatusTypeDef ret;
  uint32_t txFlag;

  if ((last != 0) && (txOnly != 0))
  {
    txFlag = I2C_LAST_FRAME;
  }
  else
  {
    txFlag = (last ? /*I2C_LAST_FRAME_NO_STOP*/ I2C_FIRST_FRAME : I2C_FIRST_AND_NEXT_FRAME);
  }

  ret = HAL_I2C_Master_Seq_Transmit_IT(&I2C_HANDLE, DevAddr, (uint8_t*)pData, Length, txFlag);
  if (ret != HAL_OK)
  {
    return ret;
  }

  while (HAL_I2C_GetState(&I2C_HANDLE) != HAL_I2C_STATE_READY);

  if (HAL_I2C_GetError(&I2C_HANDLE) != HAL_I2C_ERROR_NONE)
  {
    return HAL_ERROR;
  }
  return HAL_OK;
}

/**
  * @brief      This method receives sequentially in master I2C mode an amount of data in blocking mode with Interrupt.
  * @param[in]  address : Target device address: The device 7 bits address value
  *                       in datasheet must be shifted to the left before calling the interface
  * @param[out] rxBuf   : Pointer to data buffer
  * @param[in]  rxLen   : Amount of data to read
  * @return     HAL Error code
  */
int32_t BSP_NFC0XCOMM_SequencialRecv(const uint16_t DevAddr, uint8_t * const pData, uint16_t Length)
{
  HAL_StatusTypeDef ret;

  ret = HAL_I2C_Master_Seq_Receive_IT(&I2C_HANDLE, DevAddr, (uint8_t*)pData, Length, I2C_LAST_FRAME);
  if (ret != HAL_OK)
  {
    return ret;
  }

  while (HAL_I2C_GetState(&I2C_HANDLE) != HAL_I2C_STATE_READY);

  if (HAL_I2C_GetError(&I2C_HANDLE) != HAL_I2C_ERROR_NONE)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  BSP SPI callback
  * @param  None
  * @return None
  */
void BSP_NFC0XCOMM_IRQ_Callback(void)
{
  /* Prevent unused argument(s) compilation warning */

  /* This function should be implemented by the user application.
   * It is called into this driver when an event from ST25R3916 is triggered.
   */
  st25r3916Isr();
}

#ifdef __cplusplus
}
#endif

