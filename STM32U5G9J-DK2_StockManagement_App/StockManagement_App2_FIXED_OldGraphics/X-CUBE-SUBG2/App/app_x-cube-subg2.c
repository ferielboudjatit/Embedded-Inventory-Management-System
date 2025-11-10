
/**
  ******************************************************************************
  * @file    p2p_demo.c (-> app_x-cube-subg2.c)
  * @author  SRA Application Team
  * @brief   P2P demo applicative code.
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

#include "app_x-cube-subg2.h"
#include "s2868a1.h"
#include "s2lp.h"
#include "p2p_demo_settings.h"

#include "S2LP_PktBasic.h"
#include "s2lp_sdkapi_mapping.h"
#include "s2lp_management.h"
#include "logger.h"
#include "rfal_nfc.h"
/** @defgroup S2LP_Nucleo
  * @{
  */

/** @defgroup Main
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TX_BUFFER_SIZE   20
#define TIME_UP                                         0x01
/*Source address of one node should be destination for other node & vice-versa*/
#define MY_ADDRESS                  0x44  //0x44
#define DESTINATION_ADDRESS         0x44  //0x34

#if defined (USE_LOW_POWER_MODE)
	#define MCU_SLEEP_MODE
	#define MCU_STOP_MODE
#endif

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern SRadioInit xRadioInit;
/* Global variables ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

typedef struct sRadioDriver
{
    void ( *Init )( void );
    void ( *GpioIrq )( SGpioInit *pGpioIRQ );
    void ( *RadioInit )( SRadioInit *pRadioInit );
    void ( *SetRadioPower )( uint8_t cIndex, float fPowerdBm );
    void ( *PacketConfig )( void );
    void ( *SetPayloadLen )( uint8_t length);
    void ( *SetDestinationAddress )( uint8_t address);
    void ( *EnableTxIrq )( void );
    void ( *DisableIrq )(void);
    void ( *EnableSQI )(void);
    void ( *SetRssiThreshold)(int dbmValue);
    void ( *ClearIrqStatus )(void);
    void ( *StartTx )( uint8_t *buffer, uint8_t size );
}RadioDriver_t;

typedef struct sMCULowPowerMode
{
    void ( *McuStopMode )( void );
    void ( *McuStandbyMode )( void );
    void ( *McuSleepMode )( void );
}MCULowPowerMode_t;

typedef struct sRadioLowPowerMode
{
    void ( *RadioShutDown )( void );
    void ( *RadioStandBy )( void );
    void ( *RadioSleep ) ( void );
    void ( *RadioPowerON )( void );
}RadioLowPowerMode_t;

typedef struct
{
  uint8_t Cmdtag;
  uint8_t CmdType;
  uint8_t CmdLen;
  uint8_t Cmd;
  uint8_t DataLen;
  uint8_t* DataBuff;
}AppliFrame_t;

#ifdef CSMA_ENABLE
typedef struct
{
  int32_t RxRSSIThreshold;
  uint8_t CsmaEnabled;
  int32_t CsmaRSSIThreshold;/*!<RSSI Threshold for CSMA*/
  uint8_t CsmaOverrideFail;
  uint8_t CsmaCcaPeriod; /*!< RSSI meas cycle = (CsmaCcaPeriod+1)*64*TBIT*/
  uint8_t CsmaCcaLength; /*!<times of CsmaCcaPeriod for ch assesment */
  uint8_t CsmaMaxNb; /*!<Max N backoff */
  uint16_t CsmaBuSeed; /*!<seed for rand in (2^rand)* presc */
  uint8_t CsmaBuPrescaler; /*!<presc for (2^rand)*presc */
}CSMA_Attr_typedef;
#endif

/* Exported functions ------------------------------------------------------- */

void Enter_LP_mode(void);
void Exit_LP_mode(void);
void MCU_Enter_StopMode(void);
void MCU_Enter_StandbyMode(void);
void MCU_Enter_SleepMode(void);
void RadioPowerON(void);
void RadioPowerOFF(void);
void RadioStandBy(void);
void RadioSleep(void);
void AppliSendBuff(AppliFrame_t *xTxFrame, uint8_t cTxlen);
void STackProtocolInit(void);
void BasicProtocolInit(void);
static void P2PInterruptHandler(void);
void S2LPInterfaceInit(void);
void S2LP_ManagementSetBand(uint8_t value);
uint8_t S2LP_ManagementGetBand(void);
void S2LP_ManagementSetOffset(int32_t value);
int32_t S2LP_ManagementGetOffset(void);
S2LPCutType S2LP_ManagementGetCut(void);
void S2LP_ManagementRangeExtInit(void);
void S2LP_ManagementSetRangeExtender(RangeExtType xRangeType);
RangeExtType S2LP_ManagementGetRangeExtender(void);
void S2LP_ManagementIdentificationRFBoard(void);
uint32_t S2LP_ManagementComputeXtalFrequency(void);
uint8_t EepromIdentification(void);
void S2LP_PacketConfig(void);
void S2LP_SetPayloadlength(uint8_t length);
void S2LP_SetDestinationAddress(uint8_t address);
void S2LP_EnableTxIrq(void);
void S2LP_EnableSQI(void);
float S2LP_GetRssiTH(void);
void S2LP_StartTx(uint8_t *buffer, uint8_t size);
void HAL_SYSTICK_Callback(void);
void MX_SUBG2_P2P_Init(void);
void MX_SUBG2_P2P_NFC_Comm(uint8_t *pTxBuff, uint8_t cTxlen);

static GpioIrqHandler *GpioIrq[] = {P2PInterruptHandler};

/**
* @brief RadioDriver_t structure fitting
*/

RadioDriver_t radio_cb =
{
  .PacketConfig = RadioPacketConfig,
  .SetPayloadLen = RadioSetPayloadlength,
  .SetDestinationAddress = RadioSetDestinationAddress,
  .EnableTxIrq = RadioEnableTxIrq,
  .EnableSQI = RadioEnableSQI,
  .StartTx = RadioStartTx,
};

/**
* @brief MCULowPowerMode_t structure fitting
*/
MCULowPowerMode_t MCU_LPM_cb =
{
  .McuStopMode = MCU_Enter_StopMode,
  .McuStandbyMode = MCU_Enter_StandbyMode,
  .McuSleepMode = MCU_Enter_SleepMode
};

/**
* @brief RadioLowPowerMode_t structure fitting
*/
RadioLowPowerMode_t Radio_LPM_cb =
{
  .RadioShutDown = RadioPowerOFF,
  .RadioStandBy = RadioStandBy,
  .RadioSleep = RadioSleep,
  .RadioPowerON = RadioPowerON
};

/**
* @brief GPIO structure fitting
*/
SGpioInit xGpioIRQ={
  S2LP_GPIO_3,
  RADIO_GPIO_MODE_DIGITAL_OUTPUT_LP,
  RADIO_GPIO_DIG_OUT_IRQ

};

/**
* @brief Radio structure fitting
*/
SRadioInit xRadioInit = {

  BASE_FREQUENCY,
  MODULATION_SELECT,
  DATARATE,
  FREQ_DEVIATION,
  BANDWIDTH
};

#if defined(USE_STack_PROTOCOL)
/**
* @brief Packet Basic structure fitting
*/
PktStackInit xStackInit={
  PREAMBLE_LENGTH,
  SYNC_LENGTH,
  SYNC_WORD,
  LENGTH_WIDTH,
  CRC_MODE,
  CONTROL_LENGTH,
  EN_FEC,
  EN_WHITENING
};

/* LLP structure fitting */
PktStackLlpInit xStackLLPInit ={
  EN_AUTOACK,
  EN_PIGGYBACKING,
  MAX_RETRANSMISSIONS
};

/**
* @brief Address structure fitting
*/
PktStackAddressesInit xAddressInit={
  EN_FILT_MY_ADDRESS,
  MY_ADDRESS,
  EN_FILT_MULTICAST_ADDRESS,
  MULTICAST_ADDRESS,
  EN_FILT_BROADCAST_ADDRESS,
  BROADCAST_ADDRESS
};

#elif defined(USE_BASIC_PROTOCOL)

/**
* @brief Packet Basic structure fitting
*/

PktBasicInit xBasicInit={

  PREAMBLE_LENGTH,
  SYNC_LENGTH,
  SYNC_WORD,
  VARIABLE_LENGTH,
  EXTENDED_LENGTH_FIELD,
  CRC_MODE,
  EN_ADDRESS,
  EN_FEC,
  EN_WHITENING
};

/**
* @brief Address structure fitting
*/
PktBasicAddressesInit xAddressInit={
  EN_FILT_MY_ADDRESS,
  MY_ADDRESS,
  EN_FILT_MULTICAST_ADDRESS,
  MULTICAST_ADDRESS,
  EN_FILT_BROADCAST_ADDRESS,
  BROADCAST_ADDRESS
};
#endif

#ifdef CSMA_ENABLE
/**
* @brief CSMA structure fitting
*/
RadioCsmaInit xCsmaInit={

  PERSISTENT_MODE_EN,
  CS_PERIOD,
  CS_TIMEOUT,
  MAX_NB,
  BU_COUNTER_SEED,
  CU_PRESCALER
};
#endif

/* Private define ------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
RadioDriver_t *pRadioDriver;
MCULowPowerMode_t *pMCU_LPM_Comm;
RadioLowPowerMode_t  *pRadio_LPM_Comm;
/*IRQ status struct declaration*/
RadioIrqs xIrqStatus;

__IO uint32_t KEYStatusData = 0x00;
static AppliFrame_t xTxFrame;
uint8_t TxFrameBuff[MAX_BUFFER_LEN] = {0x00};
uint16_t txCounter = 0;


void MX_X_CUBE_SUBG2_Init(void)
{
  /* USER CODE BEGIN SV */

  /* USER CODE END SV */

  /* USER CODE BEGIN S2LP_Library_Init_PreTreatment */

  /* USER CODE END S2LP_Library_Init_PreTreatment */

  /* Initialize the peripherals and the SUBG2 components */
  MX_SUBG2_P2P_Init();

  /* USER CODE BEGIN SV */

  /* USER CODE END SV */

  /* USER CODE BEGIN S2LP_Library_Init_PostTreatment */

  /* USER CODE END S2LP_Library_Init_PostTreatment */
}
  /**
  * @brief  Initialize the EnergyHarvesting Example
  * @retval None
  */

void MX_SUBG2_P2P_Init(void)
{


  /* Configure USER Key Button */

  S2LPInterfaceInit();

   pRadioDriver = &radio_cb;

  /* S2LP IRQ config */
  S2LP_GPIO_Init(&xGpioIRQ);

  /* S2LP Radio config */
  S2LP_RADIO_Init(&xRadioInit);

//  S2LPGpioIrqInit(IRQ_TX_DATA_SENT);

  /* S2LP Radio set power */
  S2LP_RADIO_SetMaxPALevel(S_DISABLE);

  if(!S2LP_ManagementGetRangeExtender())
  {
    /* if we haven't an external PA, use the library function */
    S2LP_RADIO_SetPALeveldBm(POWER_INDEX,POWER_DBM);
  }
  else
  {
    /* in case we are using the PA board, the S2LPRadioSetPALeveldBm will be not functioning because
    the output power is affected by the amplification of this external component.
    Set the raw register. */
    uint8_t paLevelValue=0x25; /* for example, this value will give 23dBm about */
    S2LP_WriteRegister(PA_POWER8_ADDR, 1, &paLevelValue);
  }
  S2LP_RADIO_SetPALevelMaxIndex(POWER_INDEX);

  /* S2LP Packet config */
  pRadioDriver->PacketConfig();

  pRadioDriver->EnableSQI();

  S2LP_RADIO_QI_SetRssiThreshdBm(RSSI_THRESHOLD);

}

/**
  * @brief  NFC data P2P communication
  * @retval None
  */

void MX_SUBG2_P2P_NFC_Comm(uint8_t *pTxBuff, uint8_t cTxlen)
{

	xTxFrame.Cmd = LED_TOGGLE;
	xTxFrame.CmdLen = 0x01;
	xTxFrame.Cmdtag = txCounter++;
	xTxFrame.CmdType = APPLI_CMD;
	xTxFrame.DataBuff = pTxBuff; //hex2Str(boardUID, RFAL_NFCV_UID_LEN);
	xTxFrame.DataLen = cTxlen; //RFAL_NFCV_UID_LEN;

	HAL_Delay(100);
	AppliSendBuff(&xTxFrame, xTxFrame.DataLen);
}


/**
* @brief  This function handles the point-to-point packet transmission
* @param  AppliFrame_t *xTxFrame = Pointer to AppliFrame_t structure
*         uint8_t cTxlen = Length of aTransmitBuffer
* @retval None
*/
void AppliSendBuff(AppliFrame_t *xTxFrame, uint8_t cTxlen)
{
  uint8_t xIndex = 0;
  uint8_t trxLength = 0;
  pRadioDriver = &radio_cb;


#ifdef USE_STack_PROTOCOL

  PktStackAddressesInit xAddressInit=
  {
    .xFilterOnMyAddress = S_ENABLE,
    .cMyAddress = MY_ADDRESS,
    .xFilterOnMulticastAddress = S_DISABLE,
    .cMulticastAddress = MULTICAST_ADDRESS,
    .xFilterOnBroadcastAddress = S_ENABLE,
    .cBroadcastAddress = BROADCAST_ADDRESS
  };
  S2LP_PCKT_STACK_AddressesInit(&xAddressInit);

#ifdef USE_STack_LLP

  /* LLP structure fitting */
  PktStackLlpInit xStackLLPInit=
  {
    .xAutoAck = S_DISABLE,
    .xPiggybacking = S_DISABLE,
    .xNMaxRetx = PKT_N_RETX_2
  };

#else

  /* LLP structure fitting */
  PktStackLlpInit xStackLLPInit=
  {
    .xAutoAck = S_DISABLE,
    .xPiggybacking = S_DISABLE,
    .xNMaxRetx = PKT_DISABLE_RETX
  };
#endif

  Radio_PktStackLlpInit(&xStackLLPInit);

#endif

#ifdef USE_BASIC_PROTOCOL
  S2LP_PCKT_BASIC_AddressesInit(&xAddressInit);
#endif

  TxFrameBuff[0] = xTxFrame->Cmd;
  TxFrameBuff[1] = xTxFrame->CmdLen;
  TxFrameBuff[2] = xTxFrame->Cmdtag;
  TxFrameBuff[3] = xTxFrame->CmdType;
  TxFrameBuff[4] = xTxFrame->DataLen;

  for(; xIndex < xTxFrame->DataLen; xIndex++)
  {
    TxFrameBuff[xIndex+5] =  xTxFrame->DataBuff[xIndex];
  }

  trxLength = (xIndex+5);
  S2LP_GPIO_IrqDeInit(NULL);

  pRadioDriver->EnableTxIrq();
  /* payload length config */
  pRadioDriver->SetPayloadLen(trxLength);
  /* IRQ registers blanking */
  S2LP_GPIO_IrqClearStatus();
  /* destination address */
  pRadioDriver->SetDestinationAddress(DESTINATION_ADDRESS);
  /* send the TX command */
  //HAL_Delay(100);
  pRadioDriver->StartTx(TxFrameBuff, trxLength);


//  while(xIrqStatus.IRQ_TX_DATA_SENT == S_RESET);
//  {
//	  platformLog("TX Error!\r\n");
//	  return;
//  }

  //vTaskDelay(pdMS_TO_TICKS(4000));
//  HAL_Delay(4000);
//  S2LPRefreshStatus();
//  S2LP_GPIO_IrqGetStatus(&xIrqStatus);
//  platformLog("IRQ status after message sent: 0x%08X\r\n", *(uint32_t*)&xIrqStatus);
//  platformLog("Radio status after message sent: 0x%08X\r\n", *(uint32_t*)&g_xStatus);

//  while(xIrqStatus.IRQ_TX_DATA_SENT == S_RESET);

//  if(xIrqStatus.IRQ_TX_DATA_SENT == S_SET)
//  {
//	  platformLog("TX completed via IRQ_TX_DATA_SENT\r\n");
//	  S2LP_GPIO_IrqClearStatus();
//  } else
//  {
//	  platformLog("TX Error!\r\n");
//	  S2LP_GPIO_IrqClearStatus();
//	  //S2LP_CMD_StrobeSabort();
//  }


}

/**
* @brief  This function initializes the STack Packet handler of S2LP
* @param  None
* @retval None
*/
void STackProtocolInit(void)
{

  PktStackInit xStackInit=
  {
    .xPreambleLength = PREAMBLE_LENGTH,
    .xSyncLength = SYNC_LENGTH,
    .lSyncWords = SYNC_WORD,

    .xFixVarLength = S_ENABLE,
    .cExtendedPktLenField = S_DISABLE,

    .xCrcMode = CRC_MODE,
    .xFec = EN_FEC,
    .xDataWhitening = EN_WHITENING
  };
  /* Radio Packet config */
  S2LP_PCKT_STACK_Init(&xStackInit);
}

/*xDataWhitening;  *
* @brief  This function initializes the BASIC Packet handler of S2LP
* @param  None
* @retval None
*/
void BasicProtocolInit(void)
{
  /* RAdio Packet config */
 S2LP_PCKT_BASIC_Init(&xBasicInit);
}

/**
* @brief  This routine will put the radio and mcu in LPM
* @param  None
* @retval None
*/
void Enter_LP_mode(void)
{
  pMCU_LPM_Comm = &MCU_LPM_cb;
  pRadio_LPM_Comm = &Radio_LPM_cb;

#if defined(MCU_SLEEP_MODE)&&defined(RF_SHUTDOWN)
  {
    pRadio_LPM_Comm->RadioShutDown();
    pMCU_LPM_Comm->McuSleepMode();
  }
#elif defined(MCU_SLEEP_MODE)&&defined(RF_STANDBY)
  {
    pRadio_LPM_Comm->RadioStandBy();
    pMCU_LPM_Comm->McuSleepMode();
  }
#elif defined(MCU_SLEEP_MODE)&&defined(RF_SLEEP)
  {
    pRadio_LPM_Comm->RadioSleep();
    pMCU_LPM_Comm->McuSleepMode();
  }
#elif defined(MCU_STOP_MODE)&&defined(RF_SHUTDOWN)
  {
    pRadio_LPM_Comm->RadioShutDown();
    pMCU_LPM_Comm->McuStopMode();
  }
#elif defined(MCU_STOP_MODE)&&defined(RF_STANDBY)
  {
    pRadio_LPM_Comm->RadioStandBy();
    pMCU_LPM_Comm->McuStopMode();
  }
#elif defined(MCU_STOP_MODE)&&defined(RF_SLEEP)
  {
    pRadio_LPM_Comm->RadioSleep();
    pMCU_LPM_Comm->McuStopMode();
  }
#else
  pMCU_LPM_Comm->McuSleepMode();
#endif
}

/**
* @brief  This routine wake-up the mcu and radio from LPM
* @param  None
* @retval None
*/
void Exit_LP_mode(void)
{
  pRadio_LPM_Comm = &Radio_LPM_cb;
  pRadio_LPM_Comm->RadioPowerON();
}

/**
* @brief  This routine puts the MCU in stop mode
* @param  None
* @retval None
*/
void MCU_Enter_StopMode(void)
{

  /*## Enter Stop Mode #######################################################*/
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);

}

/**
* @brief  This routine puts the MCU in standby mode
* @param  None
* @retval None
*/
void MCU_Enter_StandbyMode(void)
{
    /*## Enter Standby Mode ####################################################*/
  /* Request to enter STANDBY mode  */
  HAL_PWR_EnterSTANDBYMode();
}

/**
* @brief  This routine puts the MCU in sleep mode
* @param  None
* @retval None
*/
void MCU_Enter_SleepMode(void)
{
  /*Suspend Tick increment to prevent wakeup by Systick interrupt.
  Otherwise the Systick interrupt will wake up the device within 1ms (HAL time base)*/


  /* Suspend Tick increment to prevent wakeup by Systick interrupt.
  Otherwise the Systick interrupt will wake up the device within 1ms (HAL time base) */
  HAL_SuspendTick();

  /* Request to enter SLEEP mode */
  HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}

/**
* @brief  This function will turn on the radio and waits till it enters the Ready state.
* @param  Param:None.
* @retval None
*
*/
void RadioPowerON(void)
{

  S2LP_CMD_StrobeReady();

  do{
    /* Delay for state transition */
    for(volatile uint8_t i=0; i!=0xFF; i++);

    /* Reads the MC_STATUS register */

    S2LP_RefreshStatus();

  }
  while(g_xStatus.MC_STATE!=MC_STATE_READY);
}

/**
* @brief  This function will Shut Down the radio.
* @param  Param:None.
* @retval None
*
*/
void RadioPowerOFF(void)
{
  S2868A1_RADIO_EnterShutdown();
}

/**
* @brief  This function will put the radio in standby state.
* @param  None.
* @retval None
*
*/
void RadioStandBy(void)
{
  S2LP_CMD_StrobeStandby();
}

/**
* @brief  This function will put the radio in sleep state.
* @param  None.
* @retval None
*
*/
void RadioSleep(void)
{
  S2LP_CMD_StrobeSleep();
}

/**
* @brief  This function handles External interrupt request. In this application it is used
*         to manage the S2LP IRQ configured to be notified on the S2LP GPIO_3.
* @param  None
* @retval None
*/
void P2PInterruptHandler(void)
{
  S2LP_GPIO_IrqGetStatus(&xIrqStatus);

  /* Check the S2LP TX_DATA_SENT IRQ flag */
  if(
     (xIrqStatus.IRQ_TX_DATA_SENT)

#ifdef CSMA_ENABLE
       ||(xIrqStatus.IRQ_MAX_BO_CCA_REACH)
#endif
         )
  {
#ifdef CSMA_ENABLE
    S2LP_CSMA_Enable(S_DISABLE);
    S2LP_PCKT_HNDL_SetRxPersistentMode(S_ENABLE);
    S2LP_RADIO_QI_CsBlanking(S_ENABLE);

    if(xIrqStatus.IRQ_MAX_BO_CCA_REACH)
    {
      S2LP_CMD_StrobeSabort();
    }
    S2LP_RADIO_QI_SetRssiThreshdBm(RSSI_THRESHOLD);

#endif

  }

}

/**
* @brief  Read the status register.
* @param  None
* @retval Status
*/
void S2LPInterfaceInit(void)
{
  /* Initialize the SDN pin micro side */
  S2868A1_RADIO_Init();

  /* EepromSpiInitialization(); */
  S2868A1_EEPROM_Init(EEPROM_INSTANCE);

  /* S2LP ON */
  S2868A1_RADIO_EnterShutdown();
  S2868A1_RADIO_ExitShutdown();

  S2LP_ManagementIdentificationRFBoard();

  /* if the board has eeprom, we can compensate the offset calling S2LP_ManagementGetOffset
  (if eeprom is not present this fcn will return 0) */
  xRadioInit.lFrequencyBase = (uint32_t) BASE_FREQUENCY + S2LP_ManagementGetOffset();

  /* if needed this will set the range extender pins */
  S2LP_ManagementRangeExtInit();


  /* uC IRQ enable */
  S2868A1_RADIO_IoIrqEnable(GpioIrq);
}

/**
* @brief  this function sets the packet configuration according to the protocol used
* @param  None
* @retval None
*/
void S2LP_PacketConfig(void)
{
#if defined(USE_STack_PROTOCOL)

  STackProtocolInit();

#elif defined(USE_BASIC_PROTOCOL)

  BasicProtocolInit();

#endif
}

/**
* @brief  this function sets the payload length
* @param  uint8_t length
* @retval None
*/
void S2LP_SetPayloadlength(uint8_t length)
{
#if defined(USE_STack_PROTOCOL)
  /* Payload length config */
  S2LP_PCKT_STACK_SetPayloadLength(length);

#elif defined(USE_BASIC_PROTOCOL)
  /* payload length config */
  S2LP_PCKT_BASIC_SetPayloadLength(length);
#endif
}

/**
* @brief  this function sets the destination address
* @param  uint8_t adress
* @retval None
*/
void S2LP_SetDestinationAddress(uint8_t address)
{
#if defined(USE_STack_PROTOCOL)
  /* Destination address */
  S2LP_PktStackSetDestinationAddress(address);
#elif defined(USE_BASIC_PROTOCOL)
  /* destination address */
  S2LP_PCKT_HNDL_SetRxSourceReferenceAddress(address);
#endif
}

/**
* @brief  this function enables the Tx IRQ
* @param  None
* @retval None
*/
void S2LP_EnableTxIrq(void)
{
  /* S2LP IRQs enable */
  S2LP_GPIO_IrqConfig(TX_DATA_SENT, S_ENABLE);
#if defined(USE_STack_LLP)
  S2LP_GPIO_IrqConfig(MAX_RE_TX_REACH, S_ENABLE);
#endif
}

/**
* @brief  this function enables SQI check
* @param  None
* @retval None
*/
void S2LP_EnableSQI(void)
{
  /* enable SQI check */
  S2LP_RADIO_QI_SetSQIThreshold(0x00);
  S2LP_RADIO_QI_EnableSQI(S_ENABLE);
}
/**
* @brief  this function sets the RSSI threshold
* @param  int dbmValue
* @retval None
*/
float S2LP_GetRssiTH(void)
{
  float dbmValue=0;
  dbmValue = S2LP_RADIO_QI_GetRssidBm();
  return dbmValue;
}

/**
* @brief  this function starts the TX process
* @param  None
* @retval None
*/
void S2LP_StartTx(uint8_t *buffer, uint8_t size )
{
  if(g_xStatus.MC_STATE==MC_STATE_RX)
  {
    S2LP_CMD_StrobeSabort();
  }

#ifdef CSMA_ENABLE

  /* Enable CSMA */
  S2LP_PCKT_HNDL_SetRxPersistentMode(S_DISABLE);
  S2LP_RADIO_QI_CsBlanking(S_DISABLE);
  S2LP_CSMA_Init(&xCsmaInit);
  S2LP_CSMA_Enable(S_ENABLE);
  S2LP_RADIO_QI_SetRssiThreshdBm(CSMA_RSSI_THRESHOLD);
#endif

  /* fit the TX FIFO */
  S2LP_CMD_StrobeFlushTxFifo();

//  S2LPRefreshStatus();
//  S2LP_GPIO_IrqGetStatus(&xIrqStatus);
//  platformLog("IRQ status after S2LP_CMD_StrobeFlushTxFifo: 0x%08X\r\n", *(uint32_t*)&xIrqStatus);
//  platformLog("Radio status after S2LP_CMD_StrobeFlushTxFifo: 0x%08X\r\n", *(uint32_t*)&g_xStatus);

  S2LP_WriteFIFO(size, buffer);

//  S2LPRefreshStatus();
//  S2LP_GPIO_IrqGetStatus(&xIrqStatus);
//  platformLog("IRQ status after write fifo: 0x%08X\r\n", *(uint32_t*)&xIrqStatus);
//  platformLog("Radio status after write fifo: 0x%08X\r\n", *(uint32_t*)&g_xStatus);

  /* send the TX command */
//  extern osMutexId_t radioMutexHandle;

  S2LPCmdStrobeTx();
//  HAL_Delay(1);
}

#ifdef __cplusplus
}
#endif
