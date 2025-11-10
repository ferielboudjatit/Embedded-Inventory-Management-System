/******************************************************************************
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

/*! \file
 *
 *  \author
 *
 *  \brief Demo application
 *
 *  This demo shows how to poll for several types of NFC cards/devices and how
 *  to exchange data with these devices, using the RFAL library.
 *
 *  This demo does not fully implement the activities according to the standards,
 *  it performs the required to communicate with a card/device and retrieve
 *  its UID. Also blocking methods are used for data exchange which may lead to
 *  long periods of blocking CPU/MCU.
 *  For standard compliant example please refer to the Examples provided
 *  with the RFAL library.
 *
 */

/*
 ******************************************************************************
 * INCLUDES
 ******************************************************************************
 */
#include "demo.h"
#include "utils.h"
#include "rfal_nfc.h"
#include "ndef_poller.h"
#include "ndef_t2t.h"
#include "ndef_t4t.h"
#include "ndef_t5t.h"
#include "ndef_message.h"
#include "ndef_types.h"
#include "ndef_dump.h"
#include "rfal_defConfig.h"

#include "app_x-cube-subg2.h"
#include "app_x-cube-nfcx.h"
#include "s2868A1.h"
#include "rfal_rf.h"

#include "s2lp_management.h"


#include "task.h"
#include "cmsis_os2.h"

/*
******************************************************************************
* GLOBAL DEFINES
******************************************************************************
*/

/* Definition of possible states the demo state machine could have */
#define DEMO_ST_NOTINIT               	0  /*!< Demo State:  Not initialized */
#define DEMO_ST_START_DISCOVERY       	1  /*!< Demo State:  Start Discovery */
#define DEMO_ST_DISCOVERY             	2  /*!< Demo State:  Discovery       */
#define DEMO_ST_SUBG_TRANSMIT		  	3
#define DEMO_ST_SUBG_CHECK_TRANSMITION	4


#define NDEF_WRITE_FORMAT_TIMEOUT   10000U /*!< When write or format mode is selected, demo returns back to read mode after a timeout */
#define NDEF_LED_BLINK_DURATION       250U /*!< Led blink duration         */

#define DEMO_RAW_MESSAGE_BUF_LEN      8192 /*!< Raw message buffer len     */

#define DEMO_ST_MANUFACTURER_ID      0x02U /*!< ST Manufacturer ID         */
#define RFAL_NFCB_UID_LEN                 16U              /*!< NFC-V UID length   */

#define IN_STOCK					01
#define OO_STOCK					02
#define MAX_MESSAGE_LENGTH 			96
/*
 ******************************************************************************
 * LOCAL VARIABLES
 ******************************************************************************
 */


#if RFAL_SUPPORT_CE && RFAL_FEATURE_LISTEN_MODE
#if RFAL_SUPPORT_MODE_LISTEN_NFCA
/* NFC-A CE config */
/* 4-byte UIDs with first byte 0x08 would need random number for the subsequent 3 bytes.
 * 4-byte UIDs with first byte 0x*F are Fixed number, not unique, use for this demo
 * 7-byte UIDs need a manufacturer ID and need to assure uniqueness of the rest.*/
static uint8_t ceNFCA_NFCID[]     = {0x5F, 'S', 'T', 'M'};    /* =_STM, 5F 53 54 4D NFCID1 / UID (4 bytes) */
static uint8_t ceNFCA_SENS_RES[]  = {0x02, 0x00};             /* SENS_RES / ATQA for 4-byte UID            */
static uint8_t ceNFCA_SEL_RES     = 0x20;                     /* SEL_RES / SAK                             */
#endif /*RFAL_SUPPORT_MODE_LISTEN_NFCA */

#if RFAL_SUPPORT_MODE_LISTEN_NFCF
/* NFC-F CE config */
static uint8_t ceNFCF_nfcid2[]     = {0x02, 0xFE, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
static uint8_t ceNFCF_SC[]         = {0x12, 0xFC};
static uint8_t ceNFCF_SENSF_RES[]  = {0x01,                                                       /* SENSF_RES                                */
                                      0x02, 0xFE, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66,             /* NFCID2                                   */
                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x00,             /* PAD0, PAD01, MRTIcheck, MRTIupdate, PAD2 */
                                      0x00, 0x00 };                                               /* RD                                       */
#endif /*RFAL_SUPPORT_MODE_LISTEN_NFCF */
#endif /*  RFAL_SUPPORT_CE && RFAL_FEATURE_LISTEN_MODE */

/*
 ******************************************************************************
 * LOCAL VARIABLES
 ******************************************************************************
 */

static rfalNfcDiscoverParam discParam;
static uint8_t              state = DEMO_ST_NOTINIT;

static ndefContext          ndefCtx;

static bool                 verbose             = false;

static uint8_t              rawMessageBuf[DEMO_RAW_MESSAGE_BUF_LEN];

static bool 				OOmsgReady		= false;
static bool 				INmsgReady		= false;

uint8_t stateStock = 0;

uint32_t         rawMessageLen;
ndefBuffer       bufRawMessage;


char OOmsg[MAX_MESSAGE_LENGTH];
char INmsg[MAX_MESSAGE_LENGTH];

//extern osMutexId_t radioMutexHandle;

extern RadioIrqs xIrqStatus;

/*
******************************************************************************
* LOCAL FUNCTION PROTOTYPES
******************************************************************************
*/

static ReturnCode demoNdef(rfalNfcDevice *nfcDevice);

#if NDEF_FEATURE_FULL_API
static bool ndefIsSTTag(ndefContext *ctx);
#endif /* NDEF_FEATURE_FULL_API */

ReturnCode  demoTransceiveBlocking( uint8_t *txBuf, uint16_t txBufSize, uint8_t **rxBuf, uint16_t **rcvLen, uint32_t fwt );

//static void formatTag(const uint8_t *content, uint32_t contentLen);
static ReturnCode formatStock(uint8_t stock);
static void handleUnknownStock(void);
void MX_SUBG2_P2P_NFC_Comm(uint8_t *pTxBuff, uint8_t cTxlen);
static void Stock_message(uint8_t *msg, uint8_t msgLen, bool flag);
/*!
 *****************************************************************************
 * \brief Demo Ini
 *
 *  This function Initializes the required layers for the demo
 *
 * \return true  : Initialization ok
 * \return false : Initialization failed
 *****************************************************************************
 */
bool demoIni( void )
{
    ReturnCode err;

    err = rfalNfcInitialize();
    if( err == ERR_NONE )
    {
        rfalNfcDefaultDiscParams( &discParam );

        discParam.devLimit      = 1U;
        discParam.notifyCb             = NULL;
        discParam.totalDuration        = 1000U;
        discParam.techs2Find           = RFAL_NFC_TECH_NONE;          /* For the demo, enable the NFC Technlogies based on RFAL Feature switches */

#if RFAL_FEATURE_NFCA
        discParam.techs2Find          |= RFAL_NFC_POLL_TECH_A;
#endif /* RFAL_FEATURE_NFCA */

#if RFAL_FEATURE_NFCB
        discParam.techs2Find          |= RFAL_NFC_POLL_TECH_B;
#endif /* RFAL_FEATURE_NFCB */

#if RFAL_FEATURE_NFCF
        discParam.techs2Find          |= RFAL_NFC_POLL_TECH_F;
#endif /* RFAL_FEATURE_NFCF */

#if RFAL_FEATURE_NFCV
        discParam.techs2Find          |= RFAL_NFC_POLL_TECH_V;
#endif /* RFAL_FEATURE_NFCV */

#if RFAL_FEATURE_ST25TB
        discParam.techs2Find          |= RFAL_NFC_POLL_TECH_ST25TB;
#endif /* RFAL_FEATURE_ST25TB */

#if ST25R95
        discParam.isoDepFS           = RFAL_ISODEP_FSXI_128;          /* ST25R95 cannot support 256 bytes of data block */
#endif /* ST25R95 */

#if RFAL_SUPPORT_MODE_POLL_ACTIVE_P2P && RFAL_FEATURE_NFC_DEP
        discParam.techs2Find |= RFAL_NFC_POLL_TECH_AP2P;
#endif /* RFAL_SUPPORT_MODE_POLL_ACTIVE_P2P && RFAL_FEATURE_NFC_DEP */

#if RFAL_SUPPORT_MODE_LISTEN_ACTIVE_P2P && RFAL_FEATURE_NFC_DEP && RFAL_FEATURE_LISTEN_MODE
        discParam.techs2Find |= RFAL_NFC_LISTEN_TECH_AP2P;
#endif /* RFAL_SUPPORT_MODE_LISTEN_ACTIVE_P2P && RFAL_FEATURE_NFC_DEP && RFAL_FEATURE_LISTEN_MODE */

#if DEMO_CARD_EMULATION_ONLY
        discParam.totalDuration        = 60000U;              /* 60 seconds */
        discParam.techs2Find           = RFAL_NFC_TECH_NONE;  /* Overwrite any previous poller modes */
#endif /* DEMO_CARD_EMULATION_ONLY */

#if RFAL_SUPPORT_CE && RFAL_FEATURE_LISTEN_MODE

#if RFAL_SUPPORT_MODE_LISTEN_NFCA
        /* Set configuration for NFC-A CE */
        ST_MEMCPY( discParam.lmConfigPA.SENS_RES, ceNFCA_SENS_RES, RFAL_LM_SENS_RES_LEN );     /* Set SENS_RES / ATQA */
        ST_MEMCPY( discParam.lmConfigPA.nfcid, ceNFCA_NFCID, RFAL_LM_NFCID_LEN_04 );           /* Set NFCID / UID */
        discParam.lmConfigPA.nfcidLen = RFAL_LM_NFCID_LEN_04;                                  /* Set NFCID length to 7 bytes */
        discParam.lmConfigPA.SEL_RES  = ceNFCA_SEL_RES;                                        /* Set SEL_RES / SAK */

        discParam.techs2Find |= RFAL_NFC_LISTEN_TECH_A;
#endif /* RFAL_SUPPORT_MODE_LISTEN_NFCA */

#if RFAL_SUPPORT_MODE_LISTEN_NFCF
        /* Set configuration for NFC-F CE */
        ST_MEMCPY( discParam.lmConfigPF.SC, ceNFCF_SC, RFAL_LM_SENSF_SC_LEN );                 /* Set System Code */
        ST_MEMCPY( &ceNFCF_SENSF_RES[RFAL_NFCF_CMD_LEN], ceNFCF_nfcid2, RFAL_NFCID2_LEN );     /* Load NFCID2 on SENSF_RES */
        ST_MEMCPY( discParam.lmConfigPF.SENSF_RES, ceNFCF_SENSF_RES, RFAL_LM_SENSF_RES_LEN );  /* Set SENSF_RES / Poll Response */

        discParam.techs2Find |= RFAL_NFC_LISTEN_TECH_F;
#endif /* RFAL_SUPPORT_MODE_LISTEN_NFCF */
#endif /* RFAL_SUPPORT_CE && RFAL_FEATURE_LISTEN_MODE */

        /* Check for valid configuration by calling Discover once */
        err = rfalNfcDiscover( &discParam );
        rfalNfcDeactivate( RFAL_NFC_DEACTIVATE_IDLE );

        if( err != ERR_NONE )
        {
            return false;
        }

        state = DEMO_ST_START_DISCOVERY;
        return true;
    }
    return false;
}

/*!
 *****************************************************************************
 * \brief Demo Cycle
 *
 *  This function executes the demo state machine.
 *  It must be called periodically
 *****************************************************************************
 */
void demoCycle( void )
{
    static rfalNfcDevice *nfcDevice;
    static bool boardScanned = false;	// Track if board has been scanned
    static bool userScanned = false;	// Track if user badge has been scanned
    static uint8_t boardUID[RFAL_NFCV_UID_LEN];		// Store board UID
    static uint8_t userUID[RFAL_NFCB_UID_LEN];		// Store badge UID

#if RFAL_FEATURE_NFCB
    rfalNfcbSensbRes      sensbRes;		// NFC-B response structure
    uint8_t               sensbResLen;		// Response length
#endif /* RFAL_FEATURE_NFCB */

#if RFAL_FEATURE_NFCV
    rfalNfcvInventoryRes  invRes;		// NFC-V response structure
    uint16_t              rcvdLen;		// Response length
#endif /* RFAL_FEATURE_NFCV */

    rfalNfcWorker();             // RFAL worker, runs periodically to process NFC operations

    // Main state maching
    switch( state )
    {
        /*******************************************************************************/
        case DEMO_ST_START_DISCOVERY:
        	// Initialize NFC discovery process
            rfalNfcDeactivate( RFAL_NFC_DEACTIVATE_IDLE );		// Reset NFC state
            rfalNfcDiscover( &discParam );						// Start device discovery
            state = DEMO_ST_DISCOVERY;							// Move to discovery state
            break;

        /*******************************************************************************/
        case DEMO_ST_DISCOVERY:
        	// Check if an NFC device has been detected and activated
            if( rfalNfcIsDevActivated( rfalNfcGetState() ) )
            {
            	// Get the detected device information
            	rfalNfcGetActiveDevice( &nfcDevice );
                platformDelay(50);		// brief delay for stability
                switch( nfcDevice->type )
                {
					/*******************************************************************************/
					#if RFAL_FEATURE_NFCV
						case RFAL_NFC_LISTEN_TYPE_NFCV: // Board tag (NFC-V type)
							{
								// Check if board can be scanned (first scan, after user scan, or returning board)
								if ((!boardScanned || userScanned) || *rawMessageBuf == OO_STOCK)
								{
									// Extract and store board UID
									ST_MEMCPY(boardUID, nfcDevice->nfcid, nfcDevice->nfcidLen);
									REVERSE_BYTES( boardUID, RFAL_NFCV_UID_LEN );                 // Reverse the UID for display purposes
									platformLog("Board UID: %s\r\n", hex2Str(boardUID, RFAL_NFCV_UID_LEN));

									// Update scan flags
									boardScanned = true;
									userScanned = false;

									// Read NDEF data from tag to determine stock status
									ReturnCode err = demoNdef(nfcDevice);
									if(err != ERR_NONE)
									{
										// Reset flags and restart on NDEF read error
										boardScanned = false;
										userScanned = false;
										SendToTouchGFX(RESCAN_BOARD_SLOWLY);
										rfalNfcDeactivate(RFAL_NFC_DEACTIVATE_IDLE);
										state = DEMO_ST_START_DISCOVERY;
										return;
									}
								}
								else if (!userScanned && *rawMessageBuf == IN_STOCK)
								{
									// Prevent scanning board before badge when loaning out
									platformLog("You must scan a badge before scanning another board.\r\n");
									SendToTouchGFX(SCAN_BADGE_BEFORE_MESSAGE);
								}
								// Prepare return message if board is being returned
								if(*rawMessageBuf == OO_STOCK){
								    sprintf(OOmsg, "Message board got into stock : %s_%u\r\n",
								            hex2Str(boardUID, RFAL_NFCV_UID_LEN),
								            stateStock);
									platformLog(OOmsg);
									platformLog("Remove board.\r\n");
									SendToTouchGFX(BOARD_SCANNED_MESSAGE);
								}

								// Loop until tag is removed from the field
								rfalNfcvPollerInitialize();
								while (rfalNfcvPollerInventory( RFAL_NFCV_NUM_SLOTS_1, RFAL_NFCV_UID_LEN * 8U, nfcDevice->dev.nfcv.InvRes.UID, &invRes, &rcvdLen) == ERR_NONE)
								{
									platformDelay(130);
								}
								// Mark return message ready for transmission
								if(*rawMessageBuf == OO_STOCK)
								{
									OOmsgReady = true;
								}

							}
							break;
						#endif
						/*******************************************************************************/

						#if RFAL_FEATURE_NFCB
						case RFAL_NFC_LISTEN_TYPE_NFCB: // User tag (NFC-B type)
							platformLog("Badge is being scanned...\r\n");
							// Ensure board was scanned first
							if(!boardScanned)
							{
								platformLog("Scan a board first.\r\n");
								SendToTouchGFX(SCAN_BOARD_BEFORE_MESSAGE);
							}

							// Process user badge only if board was scanned and is being loaned out
							if (boardScanned && *rawMessageBuf == IN_STOCK)
							{
								// Extract and store user UID
								ST_MEMCPY(userUID, nfcDevice->nfcid, nfcDevice->nfcidLen);
								platformLog("User UID: %s\r\n", hex2Str(userUID, nfcDevice->nfcidLen));

								// Update scan flags
								userScanned = true;
//								boardScanned = false;

								// Create loan message with user and board information
							    sprintf(INmsg, "Message board got out of stock : %s_%s_%u\r\n",
							            hex2Str(userUID, RFAL_NFCB_NFCID0_LEN),
							            hex2Str(boardUID, RFAL_NFCV_UID_LEN),
							            stateStock);
								platformLog(INmsg);

								// Handle NFC-B deactivation based on ISO-DEP support
								if( rfalNfcbIsIsoDepSupported( &nfcDevice->dev.nfcb ) )
								{
									rfalIsoDepDeselect();	// Proper ISO-DEP deselection
								}
								else
								{
									rfalNfcbPollerSleep(nfcDevice->dev.nfcb.sensbRes.nfcid0);	// Put tag to sleep
								}
								/* Loop until tag is removed from the field */
								platformLog("Operation completed.\r\n");
								platformLog("Remove badge.\r\n");
								SendToTouchGFX(BADGE_SCANNED_MESSAGE);
								rfalNfcbPollerInitialize();

								while( rfalNfcbPollerCheckPresence(RFAL_NFCB_SENS_CMD_ALLB_REQ, RFAL_NFCB_SLOT_NUM_1, &sensbRes, &sensbResLen) == ERR_NONE )
								{
									// Break if different tag detected
									if( ST_BYTECMP(sensbRes.nfcid0, nfcDevice->dev.nfcb.sensbRes.nfcid0, RFAL_NFCB_NFCID0_LEN) != 0 )
									{
										break;
									}
									rfalNfcbPollerSleep(nfcDevice->dev.nfcb.sensbRes.nfcid0);
									platformDelay(130);
								}
								INmsgReady = true;
							}
							break;
						#endif /* RFAL_FEATURE_NFCB */

                    /*******************************************************************************/
                    default:
                        break;	// device type unknown to system
                }

                // Deactivate NFC after processing
                rfalNfcDeactivate( RFAL_NFC_DEACTIVATE_IDLE );
                state = DEMO_ST_SUBG_TRANSMIT;
            break;

        /*******************************************************************************/
        case DEMO_ST_SUBG_TRANSMIT:
            // Handle Sub-GHz message transmission
            if (OOmsgReady)
            {
            	// Transmit return message
                Stock_message((uint8_t *)OOmsg, MAX_MESSAGE_LENGTH, OOmsgReady);
            }
            else if (INmsgReady)
            {
            	// Transmit loan message
                Stock_message((uint8_t *)INmsg,MAX_MESSAGE_LENGTH, INmsgReady);
            }
            state = DEMO_ST_SUBG_CHECK_TRANSMITION;

            break;

        case DEMO_ST_SUBG_CHECK_TRANSMITION:
            if (OOmsgReady)
            {
                // Check transmission status
            	S2LP_GPIO_IrqGetStatus(&xIrqStatus);
            	if(xIrqStatus.IRQ_TX_DATA_SENT == S_RESET)
            	{
            		// Transmission failed
            		platformLog("TX Error!\r\n");
            		SendToTouchGFX(TRANSMISSION_ERROR);

            	}
            	else if(OOmsgReady)
            	{
            		// Transmission successful
            		platformLog("Message transmitted\r\n");
            		SendToTouchGFX(BOARD_ENTERED_MESSAGE);

            	}
            	// Reset message flag
                OOmsgReady = false;
                boardScanned = false;
                userScanned = false;
            	// prompt for next scan
                platformLog("Tap a board tag to scan it.\r\n");
            }
            else if (INmsgReady)
            {
                // Check transmission status
            	S2LP_GPIO_IrqGetStatus(&xIrqStatus);
            	if(xIrqStatus.IRQ_TX_DATA_SENT == S_RESET)
            	{
            		platformLog("TX Error!\r\n");
            		SendToTouchGFX(TRANSMISSION_ERROR);
            	}
            	else if(INmsgReady)
            	{
            		platformLog("Message transmitted\r\n");
            		SendToTouchGFX(BOARD_GOTOUT_MESSAGE);
            	}
            	INmsgReady = false;
                boardScanned = false;
                userScanned = false;
                platformLog("Tap a board tag to scan it.\r\n");
            }

            // Return to discovery state for next scan
            state = DEMO_ST_START_DISCOVERY;

        	break;
        /*******************************************************************************/
        case DEMO_ST_NOTINIT:
        default:
            break;		// Uninitialized or unknown state
      }
     }
}

static ReturnCode demoNdef(rfalNfcDevice *pNfcDevice)
{
    /*
     * Perform NDEF Context Initialization
     */

    ReturnCode       err;
    uint32_t         rawMessageLen;
    ndefInfo         info;

    err = ndefPollerContextInitialization(&ndefCtx, pNfcDevice);
    if( err != ERR_NONE )
    {
        platformLog("NDEF NOT DETECTED (ndefPollerContextInitialization returns %d)\r\n", err);
        return err;
    }

    /*
     * Perform NDEF Detect procedure
     */
    err = ndefPollerNdefDetect(&ndefCtx, &info);
    if( err != ERR_NONE )
    {
        platformLog("NDEF NOT DETECTED (ndefPollerNdefDetect returns %d)\r\n", err);
        return err;
    }

	err = ndefPollerReadRawMessage(&ndefCtx, rawMessageBuf, sizeof(rawMessageBuf), &rawMessageLen, true);
	if( err != ERR_NONE )
	{
		platformLog("NDEF message cannot be read (ndefPollerReadRawMessage returns %d)\r\n", err);
		return err;
	}

	if( verbose )
	{
		bufRawMessage.buffer = rawMessageBuf;
		bufRawMessage.length = rawMessageLen;
	}
	switch (*rawMessageBuf)
	{
	case IN_STOCK:
        return formatStock(IN_STOCK);

	case OO_STOCK:
		return formatStock(OO_STOCK);
	default:
		platformLog("Unknown stock\r\n");
		handleUnknownStock();
		break;
	}
	return err;
}

#if NDEF_FEATURE_FULL_API
static bool ndefIsSTTag(ndefContext *ctx)
{
    bool ret = false;

#if defined(STM32L476xx) /* Enable to format any manufacturer tag while debugging */
    if( (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk) != 0)
    {
        ret = true;
    }
#endif
    if( ctx == NULL )
    {
        return ret;
    }
    switch (ctx->device.type)
    {
        case RFAL_NFC_LISTEN_TYPE_NFCA:
            if( (ctx->device.dev.nfca.nfcId1Len != 4) && (ctx->device.dev.nfca.nfcId1[0] == 0x02 ) )
            {
                ret = true;
            }
            break;
        case RFAL_NFC_LISTEN_TYPE_NFCF:
            break;
        case RFAL_NFC_LISTEN_TYPE_NFCB:
            break;
        case RFAL_NFC_LISTEN_TYPE_NFCV:
            if( ctx->device.dev.nfcv.InvRes.UID[6] == 0x02 )
            {
                ret = true;
            }
            break;
        default:
            break;
    }
    return (ret);
}
#endif /* NDEF_FEATURE_FULL_API */


static ReturnCode formatStock(uint8_t stock)
{
	ReturnCode err = ERR_NONE;

	if( !ndefIsSTTag(&ndefCtx) )
	{
		platformLog("Manufacturer ID not found or not an ST tag. Format aborted \r\n");
		return err;
	}
	if (stock == OO_STOCK)
	{
		err = appInNdefT5TPollerTagFormat(&ndefCtx, NULL, 0);
		HAL_Delay(5);	
		if( err != ERR_NONE )
		{
			platformLog("Message cannot be written (appInNdefT5TPollerTagFormat return %d)\r\n", err);
			return err;
		}
		platformLog("Board entered to stock.\r\n");
		stateStock = IN_STOCK;
	}
	else if (stock == IN_STOCK)
	{
		err = appOutNdefT5TPollerTagFormat(&ndefCtx, NULL, 0);
		HAL_Delay(5);	
		if( err != ERR_NONE )
		{
			platformLog("Message cannot be written (appOutNdefT5TPollerTagFormat return %d)\r\n", err);
			return err;
		}
		platformLog("Remove board and scan badge.\r\n");
		SendToTouchGFX(SCAN_BADGE_MESSAGE);
		stateStock = OO_STOCK;
	}
	return err;
}

static void handleUnknownStock(void)
{
	ReturnCode err;
	platformLog("Unknown stock status.\r\n");
    err = appInNdefT5TPollerTagFormat(&ndefCtx, NULL, 0);
	if( err != ERR_NONE )
	{
		platformLog("Message cannot be written (appInNdefT5TPollerTagFormat return %d)\r\n", err);
		return;
	}
    platformLog("Scan again.\r\n");
	stateStock = 01;

	return;
}

static void Stock_message(uint8_t *msg, uint8_t msgLen, bool flag) //Became static, maybe this can solve issue
{
	rfalDeinitialize();
	MX_SPI1_Init();
	MX_X_CUBE_SUBG2_Init();
	HAL_Delay(10);		// Settling delay
	if(flag == OOmsgReady)
	{
		platformLog("Transmitting stock entry message....");
	}
	else if(flag == INmsgReady)
	{
		platformLog("Transmitting stock exit message....");
	}
	MX_SUBG2_P2P_NFC_Comm(msg, msgLen);
	rfalInitialize();
}


void SendToTouchGFX(NFCtask_messages_t message_tag)
{
    xQueueSend(nfcMessageQueue, &message_tag, 0);
}


