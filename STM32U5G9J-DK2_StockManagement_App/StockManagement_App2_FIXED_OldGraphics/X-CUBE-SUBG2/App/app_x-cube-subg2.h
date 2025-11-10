/**
  ******************************************************************************
  * @file    app_x-cube-subg2.h
  * @author  SRA Application Team
  * @brief   Applicative interface with ST32CubeMX
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
#ifndef __INIT_H
#define __INIT_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <st_errno.h>

#include "s2lp.h"
#include "main.h"
#include "spi.h"
#include "p2p_demo_settings.h"
/* Exported Functions --------------------------------------------------------*/
void MX_X_CUBE_SUBG2_Init(void);
void MX_X_CUBE_SUBG2_Process(void);
void S2LPInterfaceInit(void);
void MX_SUBG2_P2P_NFC_Comm(uint8_t *pTxBuff, uint8_t cTxlen);
//void P2PInterruptHandler(void);



#ifdef __cplusplus
}
#endif
#endif /* __INIT_H */
