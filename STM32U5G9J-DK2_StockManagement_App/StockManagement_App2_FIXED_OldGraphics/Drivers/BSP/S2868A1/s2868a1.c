
 /*******************************************************************************
  * @file    S2868A1.c
  * @author  SRA Team
  * @brief   driver s2868A1 board
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
 */
  
/* Includes ------------------------------------------------------------------*/
#include "s2868a1.h"
#include "s2lp.h"
#include "spi.h"
    
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BOARD_WAKEUP_TIME  0
    
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile int irq_disable_cnt = 0;

EXTI_HandleTypeDef S2868A1_RADIO_GPIO_hexti = {.Line = S2868A1_RADIO_GPIO_EXTI_LINE};

/* Private function prototypes -----------------------------------------------*/
static int32_t S2868A1_SPI_SendRecvWrapper(uint8_t *pHeader, uint8_t *pBuff, uint16_t Length);
static int32_t EEPROM_WaitEndWriteOperation(uint32_t Instance);

/* Exported functions ---------------------------------------------------------*/


/**
  * @brief  Initializes SPI MSP.
  * @param  hspi  SPI handler
  * @retval None
  */
static void S2868A1_SPI_CS_Init()
{
  S2868A1_RADIO_SPI_NSS_PIN_HIGH();
}


/**
  * @brief  Wrapper Function for S2868A1 SPI.
  * @param  pHeader is the header to send/receive
  * @param  pBuff is the buffer to write/read
  * @param  Length of data to be read
  * @retval TBD
  */
int32_t S2868A1_SPI_SendRecvWrapper(uint8_t *pHeader, uint8_t *pBuff, uint16_t Length)
{
  int32_t status;
  S2868A1_ENTER_CRITICAL();
  S2868A1_RADIO_SPI_NSS_PIN_LOW();
  //GPIO_PinState S2LPCSpin = HAL_GPIO_ReadPin(S2868A1_S2LP_CS_GPIO_Port, S2868A1_S2LP_CS_Pin);
  //platformLog("S2LP cs pin: 0x%08X\r\n", S2LPCSpin);
  status = S2868A1_SPI_SendRecv( pHeader, pHeader, 2 );
  if (!status)
  {
    if(Length)
    {
      status = S2868A1_SPI_SendRecv( pBuff, pBuff, Length );
    }
  }
  S2868A1_RADIO_SPI_NSS_PIN_HIGH();
  S2868A1_EXIT_CRITICAL();
  return status;  
}

/**
* @brief  Wait polling the SPI until the internal WIP flag is RESET.
*         The flag is SET when a write operation is running.
* @param  Instance
* @retval None
*/
static int32_t EEPROM_WaitEndWriteOperation(uint32_t Instance)
{
  
  UNUSED(Instance);    
  uint8_t cmd = EEPROM_CMD_RDSR;
  uint8_t dummy = 0xFF;
  uint8_t status;
  
  /* Put the SPI chip select low to start the transaction */
  EEPROM_NSS_PIN_LOW();
  
  /* Send command */
  EEPROM_SPI_SendRecv(&cmd, &status, 1);
  
  /* Polling on status register */
  do{
    EEPROM_SPI_SendRecv(&dummy, &status, 1);
  }while(status&EEPROM_STATUS_WIP);
  
  /* Put the SPI chip select high to end the transaction */
  EEPROM_NSS_PIN_HIGH();
  
  return S2868A1_ERROR_NONE;    
}


/******************************* S2LP Radio Low level Services *****************/

/**
  * @brief  Radio Initialization 
  * @retval None
  */
int32_t S2868A1_RADIO_Init( void )
{
 S2LP_IO_t  IOCtx;
   
   /*register SPI bus function to the component */
   
   IOCtx.WriteBuffer = S2868A1_SPI_SendRecvWrapper;
   IOCtx.Delay = S2868A1_Delay;
   
   S2LP_RegisterBusIO(&IOCtx);

   HAL_SPI_MspInit(&SPI_HANDLE);
   S2868A1_SPI_CS_Init();
  
  return S2868A1_ERROR_NONE;
}

/**
  * @brief  FunctionDescription
  * @retval Error Code
  */
int32_t S2868A1_RADIO_DeInit( void )
{
	HAL_SPI_MspDeInit(&SPI_HANDLE);
	return S2868A1_ERROR_NONE;
}

/**
  * @brief  FunctionDescription
  * @retval None
  */
int32_t S2868A1_RADIO_GetWakeUpTime( void )
{
  return  BOARD_WAKEUP_TIME;
}

/**
  * @brief  FunctionDescription
  * @retval None
  */
int32_t S2868A1_RADIO_EnterShutdown( void )     
{
  HAL_GPIO_WritePin( S2868A1_RADIO_GPIO_SDN_PORT, S2868A1_RADIO_GPIO_SDN_PIN, GPIO_PIN_SET);
  return S2868A1_ERROR_NONE;       
}

/**
  * @brief  FunctionDescription
  * @retval None
  */
int32_t S2868A1_RADIO_ExitShutdown( void )     /* Equivalent to RadioEnterShutdown and RadioExitShutdown*/
{
  HAL_GPIO_WritePin( S2868A1_RADIO_GPIO_SDN_PORT, S2868A1_RADIO_GPIO_SDN_PIN, GPIO_PIN_RESET);

  /* Delay to allow the circuit POR */
  HAL_Delay(2);
  return S2868A1_ERROR_NONE;
}

/**
  * @brief  FunctionDescription                                                                                        
  * @retval None
  */
uint8_t S2868A1_RADIO_CheckShutdown( void )     
{
  uint8_t pinState;
  pinState = (uint8_t)HAL_GPIO_ReadPin( S2868A1_RADIO_GPIO_SDN_PORT, S2868A1_RADIO_GPIO_SDN_PIN);
  return pinState;       
}

/**
  * @brief  FunctionDescription
  * @retval None
  */
int32_t S2868A1_RADIO_CheckRfFrequency( uint32_t frequency )
{
  return S2868A1_ERROR_NONE; 
}

/**
* @brief  Enables the interrupt on GPIO .
* @param  xGpio Specifies the GPIO whose priority shall be changed.
*         This parameter can be one of following parameters:
*         @arg M2S_GPIO_0: GPIO_0
*         @arg M2S_GPIO_1: GPIO_1
*         @arg M2S_GPIO_2: GPIO_2
*         @arg M2S_GPIO_3: GPIO_3
* @param  nPreemption Specifies Preemption Priority.
* @param  nSubpriority Specifies Subgroup Priority.
* @param  xNewState Specifies the State.
*         This parameter can be one of following parameters:
*         @arg ENABLE: Interrupt is enabled
*         @arg DISABLE: Interrupt is disabled
* @retval None.
*/
int32_t S2868A1_RADIO_IoIrqEnable(GpioIrqHandler **irqHanlder)
{

  HAL_EXTI_GetHandle(&S2868A1_RADIO_GPIO_hexti, S2868A1_RADIO_GPIO_EXTI_LINE);
  HAL_EXTI_RegisterCallback(&S2868A1_RADIO_GPIO_hexti,  HAL_EXTI_COMMON_CB_ID, irqHanlder[0]);

  return S2868A1_ERROR_NONE;     
} 

/**
* @brief  Disables the interrupt on GPIO .
* ...
*/
int32_t S2868A1_RADIO_IoIrqDisable(GpioIrqHandler **irqHanlder)
{
	HAL_NVIC_DisableIRQ( S2868A1_RADIO_GPIO_IRQn);
	return S2868A1_ERROR_NONE;
} 

/**
* @brief  Initializes the SPI for the EEPROM.
* @param  Instance of EEPROM
* @retval Error Code
*/
int32_t S2868A1_EEPROM_Init(uint32_t Instance)
{
  UNUSED(Instance);

  /* Put the SPI chip select high to end the transaction */
  EEPROM_NSS_PIN_HIGH();
  
  return S2868A1_ERROR_NONE;   
}

/**
* @brief  Set the ERSR status bit.
* @param  None
* @retval Status
*/
uint8_t BSP_EEPROM_SetSrwd(uint32_t Instance)
{
  uint8_t status[2];
  uint8_t cmd[] = {EEPROM_CMD_WRSR, EEPROM_STATUS_SRWD};
  
  /* Put the SPI chip select low to start the transaction */
  EEPROM_NSS_PIN_LOW();
  
  /* Send command */
  EEPROM_SPI_SendRecv(cmd, status, 2);
  
  /* Put the SPI chip select high to end the transaction */
  EEPROM_NSS_PIN_HIGH();
  
  return status[1];
}

/**
* @brief  Reset the ERSR status bit.
* @param  None
* @retval Status
*/
uint8_t BSP_EEPROM_ResetSrwd(uint32_t Instance)
{
  uint8_t status[2];
  uint8_t cmd[] = {EEPROM_CMD_WRSR, 0};
  
  BSP_EEPROM_WriteEnable(Instance);
  EEPROM_WaitEndWriteOperation(Instance);
  /* Put the SPI chip select low to start the transaction */
  EEPROM_NSS_PIN_LOW();
  
  /* Send command */
  EEPROM_SPI_SendRecv(cmd, status, 2);
  
  /* Put the SPI chip select high to end the transaction */
  EEPROM_NSS_PIN_HIGH();
  EEPROM_WaitEndWriteOperation(Instance);
  
  return status[1];
}

/**
* @brief  Set the internal WEL flag to allow write operation.
* @param  None
* @retval None
*/
int32_t BSP_EEPROM_WriteEnable(uint32_t Instance)
{
  UNUSED(Instance); 
  uint8_t cmd = EEPROM_CMD_WREN;
  uint8_t status;
  
  /* Put the SPI chip select low to start the transaction */
  EEPROM_NSS_PIN_LOW();
  
   /* Send command */
  EEPROM_SPI_SendRecv(&cmd, &status, 1);
  
  /* Put the SPI chip select high to end the transaction */
  EEPROM_NSS_PIN_HIGH();
  
  return S2868A1_ERROR_NONE; 
  
}

/**
* @brief  Write a page of the EEPROM.
*         A page size is 32 bytes.
*         The pages are 256.
*         Page 0 address: 0x0000
*         Page 1 address: 0x0020
*         ...
*         Page 255 address: 0x1FE0
*         It is allowed to write only a page for each operation. If the bytes
*         exceed the single page location, the other bytes are written at the 
*         beginning.
* @param  None
* @retval None
*/
int32_t S2868A1_EEPROM_WritePage(uint32_t Instance, uint16_t nAddress, uint16_t cNbBytes, uint8_t* pcBuffer)
{
  uint8_t cmd = EEPROM_CMD_WRITE, tmp[255];
  uint8_t address[2];
  UNUSED(Instance);
  
  /* Wait the end of a previous write operation */
  EEPROM_WaitEndWriteOperation(Instance);
  
  /* SET the WREN flag */
  BSP_EEPROM_WriteEnable(Instance);
  
   for(uint8_t k=0; k<2; k++) {
    address[k] = (uint8_t)(nAddress>>((1-k)*8));
  }
  
  
  /* Put the SPI chip select low to start the transaction */
  EEPROM_NSS_PIN_LOW();
  
  /* Write the header bytes and read the SPIRIT status bytes */
  EEPROM_SPI_SendRecv(&cmd,tmp, 1);
  EEPROM_SPI_SendRecv(address, tmp,2);
  EEPROM_SPI_SendRecv(pcBuffer, tmp, cNbBytes);
  
  /* Put the SPI chip select high to end the transaction */
  EEPROM_NSS_PIN_HIGH();
  return S2868A1_ERROR_NONE;
}

/**
* @brief  Read a page of the EEPROM.
*         A page size is 32 bytes.
*         The pages are 256.
*         Page 0 address: 0x0000
*         Page 1 address: 0x0020
*         ...
*         Page 255 address: 0x1FE0
* @param  None
* @retval None
*/
int32_t S2868A1_EEPROM_ReadPage(uint32_t Instance, uint16_t nAddress, uint16_t cNbBytes, uint8_t* pcBuffer)
{
  uint8_t cmd[3];
  uint8_t dummy[255];
  cmd[0] = EEPROM_CMD_READ;
  UNUSED(Instance);
  
  for(uint8_t k=0; k<2; k++) {
    cmd[k+1] = (uint8_t)(nAddress>>((1-k)*8));
  }  
  
  /* Wait the end of a previous write operation */
  EEPROM_WaitEndWriteOperation(Instance);
  
  /* Put the SPI chip select low to start the transaction */
  EEPROM_NSS_PIN_LOW();
  
  /* Write the header bytes and read status bytes */
  EEPROM_SPI_SendRecv(cmd, dummy, 3);
  
  /* Read the registers according to the number of bytes */
  EEPROM_SPI_SendRecv(dummy, pcBuffer, cNbBytes);
  
  /* Put the SPI chip select high to end the transaction */
  EEPROM_NSS_PIN_HIGH();
  return S2868A1_ERROR_NONE;
  
}
/**
* @brief  Read the status register.
* @param  None
* @retval Status
*/
int32_t S2868A1_EEPROM_IsReady(uint32_t Instance)
{
  int32_t errno = 0;
  
  uint8_t status[2];
  uint8_t cmd[] = {EEPROM_CMD_RDSR, 0xFF};
  
  /* Put the SPI chip select low to start the transaction */
  EEPROM_NSS_PIN_LOW();
  
  /* Send command */
  EEPROM_SPI_SendRecv(cmd, status, 2);
  
  /* Put the SPI chip select high to end the transaction */
  EEPROM_NSS_PIN_HIGH();
  
  if((status[1] & 0xF0) == EEPROM_STATUS_SRWD) {
    /* if it is EEPROM_STATUS_SRWD, ok the EEPROM is present and ready to work */
    errno = 1;
  }
  return errno;
}


__weak void FEM_Operation(FEM_OperationType operation)
{
	
}
