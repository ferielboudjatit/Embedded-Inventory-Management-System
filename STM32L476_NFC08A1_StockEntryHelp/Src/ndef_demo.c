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
 *  \brief Demo application - Modified for Board and Badge Tags Only
 *
 *  This demo shows how to poll for NFCV (board tags) and NFCB (badge tags)
 *  and handle stock management with board tags.
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

/*
******************************************************************************
* GLOBAL DEFINES
******************************************************************************
*/

/* Definition of possible states the demo state machine could have */
#define DEMO_ST_NOTINIT               0  /*!< Demo State:  Not initialized */
#define DEMO_ST_START_DISCOVERY       1  /*!< Demo State:  Start Discovery */
#define DEMO_ST_DISCOVERY             2  /*!< Demo State:  Discovery       */

#define BOARD_MODE_READ               0U   /*!< Board mode: read stock status */
#define BOARD_MODE_WRITE_ENTER        1U   /*!< Board mode: write stock status */
#define BOARD_MODE_WRITE_GETOUT		  2U
#define BADGE_MODE_READ 			  3U
#define BOARD_MODE_MAX                4U   /*!< Number of board modes */

#define STOCK_OUT                     0x02 /*!< Stock status: out of stock */
#define STOCK_IN                      0x01 /*!< Stock status: in stock */
#define STOCK_UNKNOWN                 0x00 /*!< Stock status: unknown */

#define DEMO_RAW_MESSAGE_BUF_LEN      8192 /*!< Raw message buffer len */


#define NDEF_WRITE_FORMAT_TIMEOUT   10000U /*!< When write or format mode is selected, demo returns back to read mode after a timeout */
#define NDEF_LED_BLINK_DURATION       250U /*!< Led blink duration         */

/*
 ******************************************************************************
 * LOCAL VARIABLES
 ******************************************************************************
 */

static const uint8_t *demoModeDescription[BOARD_MODE_MAX] =
{
    (uint8_t *)"1. Tap a board's tag to read its content\r\n",
    (uint8_t *)"2. Tap a board's tag to write an entry to stock (01)\r\n",
	(uint8_t *)"3. Tap a board's tag to write an exit from stock (02)\r\n",
	(uint8_t *)"4. Tap a badge to read the ID\r\n"
};

static rfalNfcDiscoverParam discParam;
static uint8_t              state = DEMO_ST_NOTINIT;

static ndefContext          ndefCtx;
static uint8_t              boardMode = BOARD_MODE_READ;
static uint8_t              prevBoardMode = 0xFF;
static bool                 verbose = false;

static uint8_t              rawMessageBuf[DEMO_RAW_MESSAGE_BUF_LEN];

static uint32_t             timer;
static uint32_t             timerLed;
/*
******************************************************************************
* LOCAL FUNCTION PROTOTYPES
******************************************************************************
*/

static void demoNfc(rfalNfcDevice *nfcDevice);
static void checkUserButton(void);
static void ndefShowDemoUsage(void);

static void ledsOn(void);
static void ledsOff(void);

/*!
 *****************************************************************************
 * \brief Check user button
 *
 *  This function checks whether the user button has been pressed
 *****************************************************************************
 */
static void checkUserButton(void)
{
    /* Check if USER button is pressed */
    if( platformGpioIsLow(PLATFORM_USER_BUTTON_PORT, PLATFORM_USER_BUTTON_PIN))
    {
        boardMode++;
        boardMode %= BOARD_MODE_MAX;

        ledsOff();
        prevBoardMode = boardMode; /* Force display update */
        platformLog("%s\r\n", demoModeDescription[boardMode]);

        /* Debounce button */
        while( platformGpioIsLow(PLATFORM_USER_BUTTON_PORT, PLATFORM_USER_BUTTON_PIN) );
        if( boardMode != BOARD_MODE_READ )
        {
            timer = platformTimerCreate(NDEF_WRITE_FORMAT_TIMEOUT);
            timerLed = platformTimerCreate(NDEF_LED_BLINK_DURATION);
        }
    }
}

/*!
 *****************************************************************************
 * \brief Show board mode usage
 *
 *  This function displays current mode information
 *****************************************************************************
 */



/*!
 *****************************************************************************
 * \brief Show usage
 *
 *  This function displays usage information
 *****************************************************************************
 */


/*!
 *****************************************************************************
 * \brief Show usage
 *
 *  This function displays usage information
 *****************************************************************************
 */
static void ndefShowDemoUsage()
{
    uint32_t i;

    platformLog("Use the User button to cycle among the different modes:\r\n");
    for (i = 0; i < SIZEOF_ARRAY(demoModeDescription); i++)
    {
        platformLog("%s\r\n", demoModeDescription[i]);
    }
}

/*!
 *****************************************************************************
 * \brief Read stock status from board tag
 *
 *  This function reads the stock status from the NDEF content
 *****************************************************************************
 */



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
    if( (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk) != 0)
    {
        verbose = true;
    }
    ndefShowDemoUsage();

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

#if RFAL_FEATURE_NFCB
    rfalNfcbSensbRes      sensbRes;
    uint8_t               sensbResLen;
#endif /* RFAL_FEATURE_NFCB */

#if RFAL_FEATURE_NFCV
    rfalNfcvInventoryRes  invRes;
    uint16_t              rcvdLen;
#endif /* RFAL_FEATURE_NFCV */

    rfalNfcWorker(); /* Run RFAL worker periodically */

    if( (boardMode != BOARD_MODE_READ) && (platformTimerIsExpired(timer)) )
    {
        platformLog("Timer expired, back to Read mode...\r\n");
        boardMode = BOARD_MODE_READ;
        ledsOff();
    }

    if( boardMode != prevBoardMode )
    {
    	prevBoardMode = boardMode;
        platformLog("%s\r\n", demoModeDescription[boardMode]);
    }


    checkUserButton();

    switch( state )
    {
        /*******************************************************************************/
        case DEMO_ST_START_DISCOVERY:
            ledsOff();

            rfalNfcDeactivate( RFAL_NFC_DEACTIVATE_IDLE );
            rfalNfcDiscover( &discParam );

            state = DEMO_ST_DISCOVERY;
            break;

        /*******************************************************************************/
        case DEMO_ST_DISCOVERY:
            if( rfalNfcIsDevActivated( rfalNfcGetState() ) )
            {
                rfalNfcGetActiveDevice( &nfcDevice );

                ledsOff();
                platformDelay(50);

                prevBoardMode = 0xFF; /* Force the display of the prompt */

                switch( nfcDevice->type )
                {
                    /*******************************************************************************/
                    #if RFAL_FEATURE_NFCV
                    case RFAL_NFC_LISTEN_TYPE_NFCV:
                        {
                            uint8_t devUID[RFAL_NFCV_UID_LEN];

                            ST_MEMCPY( devUID, nfcDevice->nfcid, nfcDevice->nfcidLen );
                            REVERSE_BYTES( devUID, RFAL_NFCV_UID_LEN );
                            platformLog("Board tag found. UID: %s\r\n", hex2Str(devUID, RFAL_NFCV_UID_LEN));
                            platformLedOn(PLATFORM_LED_V_PORT, PLATFORM_LED_V_PIN);

                            demoNfc(nfcDevice);

                            /* Loop until tag is removed from the field */
                            platformLog("Operation completed\r\nTag can be removed from the field\r\n");
                            rfalNfcvPollerInitialize();
                            while (rfalNfcvPollerInventory( RFAL_NFCV_NUM_SLOTS_1, RFAL_NFCV_UID_LEN * 8U, nfcDevice->dev.nfcv.InvRes.UID, &invRes, &rcvdLen) == ERR_NONE)
                            {
                                platformDelay(130);
                            }
                        }
                        break;
                    #endif /* RFAL_FEATURE_NFCV */

                    /*******************************************************************************/
                    #if RFAL_FEATURE_NFCB
                    case RFAL_NFC_LISTEN_TYPE_NFCB:

                        platformLog("Badge tag found. UID: %s\r\n", hex2Str( nfcDevice->nfcid, nfcDevice->nfcidLen ) );
                        platformLedOn(PLATFORM_LED_B_PORT, PLATFORM_LED_B_PIN);

                        demoNfc(nfcDevice);

                        /* Loop until tag is removed from the field */
                        platformLog("Operation completed\r\nTag can be removed from the field\r\n");
                        rfalNfcbPollerInitialize();
                        while( rfalNfcbPollerCheckPresence(RFAL_NFCB_SENS_CMD_ALLB_REQ, RFAL_NFCB_SLOT_NUM_1, &sensbRes, &sensbResLen) == ERR_NONE )
                        {
                            if( ST_BYTECMP(sensbRes.nfcid0, nfcDevice->dev.nfcb.sensbRes.nfcid0, RFAL_NFCB_NFCID0_LEN) != 0 )
                            {
                                break;
                            }
                            rfalNfcbPollerSleep(nfcDevice->dev.nfcb.sensbRes.nfcid0);
                            platformDelay(130);
                        }
                        break;
                    #endif /* RFAL_FEATURE_NFCB */

                    /*******************************************************************************/
                    default:
                        break;
                }

                rfalNfcDeactivate( RFAL_NFC_DEACTIVATE_IDLE );
                platformDelay(500);
                state = DEMO_ST_START_DISCOVERY;
            }
            break;

        /*******************************************************************************/
        case DEMO_ST_NOTINIT:
        default:
            break;
    }
}

/*!
 *****************************************************************************
 * \brief Demo NFC Handler
 *
 *  This function handles both board and badge tag operations
 *****************************************************************************
 */
static void demoNfc(rfalNfcDevice *pNfcDevice)
{
    ReturnCode err;
    ndefInfo info;
    uint32_t rawMessageLen;
    ndefBuffer bufRawMessage;

    if( pNfcDevice->type == RFAL_NFC_LISTEN_TYPE_NFCB )
    {
        /* Badge tag - just log the ID (already done in discovery) */
        return;
    }

    if( pNfcDevice->type == RFAL_NFC_LISTEN_TYPE_NFCV )
    {
        /* Board tag - handle stock management */

        /* Initialize NDEF context */
        err = ndefPollerContextInitialization(&ndefCtx, pNfcDevice);
        if( err != ERR_NONE )
        {
            platformLog("NDEF NOT DETECTED (ndefPollerContextInitialization returns %d)\r\n", err);
            return;
        }

        /* Perform NDEF Detect procedure */
        err = ndefPollerNdefDetect(&ndefCtx, &info);
        if( err != ERR_NONE )
        {
            platformLog("NDEF NOT DETECTED (ndefPollerNdefDetect returns %d)\r\n", err);
            return;
        }

        switch( boardMode )
        {
            case BOARD_MODE_READ:
                /* Read the NDEF message content */
                err = ndefPollerReadRawMessage(&ndefCtx, rawMessageBuf, sizeof(rawMessageBuf), &rawMessageLen, true);
                if( err != ERR_NONE )
                {
                    platformLog("NDEF message cannot be read (ndefPollerReadRawMessage returns %d)\r\n", err);
                    return;
                }

                if( verbose )
                {
                    bufRawMessage.buffer = rawMessageBuf;
                    bufRawMessage.length = rawMessageLen;
                    ndefBufferDump(" NDEF Content", (ndefConstBuffer*)&bufRawMessage, verbose);
                }

                /* Check stock status from first byte */
                if( rawMessageLen > 0 )
                {
                    uint8_t stockStatus = rawMessageBuf[0];
                    switch( stockStatus )
                    {
                        case STOCK_IN:
                            platformLog("State is in stock\r\n");
                            break;
                        case STOCK_OUT:
                            platformLog("State is out of stock\r\n");
                            break;
                        default:
                            platformLog("unknown stock\r\n");
                            break;
                    }
                }
                else
                {
                    platformLog("unknown stock\r\n");
                }
                break;

            case BOARD_MODE_WRITE_ENTER:
                /* Write "in stock" status */
//                rawMessageBuf[0] = STOCK_IN;
                err = appInNdefT5TPollerTagFormat(&ndefCtx, NULL, 0);
                HAL_Delay(5);	// FB ADD ROBUST for when error detected but still somehow detects error
				if( err != ERR_NONE )
				{
					platformLog("Message cannot be written (appInNdefT5TPollerTagFormat return %d)\r\n", err);
				}
                else
                {
                    platformLog("Board marked as IN STOCK\r\n");
                    /* Flash LEDs to indicate successful write */
                    for( int i = 0; i < 3; i++ )
                    {
                        ledsOn();
                        platformDelay(100);
                        ledsOff();
                        platformDelay(100);
                    }
                    /* Return to read mode after write */
                    boardMode = BOARD_MODE_READ;
                    prevBoardMode = 0xFF;
                }
                break;
            case BOARD_MODE_WRITE_GETOUT:
                /* Write "in stock" status */
//                rawMessageBuf[0] = STOCK_OUT;
                err = appOutNdefT5TPollerTagFormat(&ndefCtx, NULL, 0);
                HAL_Delay(5);	// FB ADD ROBUST for when error detected but still somehow detects error
				if( err != ERR_NONE )
				{
					platformLog("Message cannot be written (appInNdefT5TPollerTagFormat return %d)\r\n", err);
				}
                else
                {
                    platformLog("Board marked as Out of STOCK\r\n");
                    /* Flash LEDs to indicate successful write */
                    for( int i = 0; i < 3; i++ )
                    {
                        ledsOn();
                        platformDelay(100);
                        ledsOff();
                        platformDelay(100);
                    }
                    /* Return to read mode after write */
                    boardMode = BOARD_MODE_READ;
                    prevBoardMode = 0xFF;
                }
                break;


            default:
                break;
        }
    }
}

static void ledsOn(void)
{
    platformLedOn(PLATFORM_LED_A_PORT, PLATFORM_LED_A_PIN);
    platformLedOn(PLATFORM_LED_B_PORT, PLATFORM_LED_B_PIN);
    platformLedOn(PLATFORM_LED_F_PORT, PLATFORM_LED_F_PIN);
    platformLedOn(PLATFORM_LED_V_PORT, PLATFORM_LED_V_PIN);
    platformLedOn(PLATFORM_LED_AP2P_PORT, PLATFORM_LED_AP2P_PIN);
    platformLedOn(PLATFORM_LED_FIELD_PORT, PLATFORM_LED_FIELD_PIN);
}

static void ledsOff(void)
{
    platformLedOff(PLATFORM_LED_A_PORT, PLATFORM_LED_A_PIN);
    platformLedOff(PLATFORM_LED_B_PORT, PLATFORM_LED_B_PIN);
    platformLedOff(PLATFORM_LED_F_PORT, PLATFORM_LED_F_PIN);
    platformLedOff(PLATFORM_LED_V_PORT, PLATFORM_LED_V_PIN);
    platformLedOff(PLATFORM_LED_AP2P_PORT, PLATFORM_LED_AP2P_PIN);
    platformLedOff(PLATFORM_LED_FIELD_PORT, PLATFORM_LED_FIELD_PIN);
}
