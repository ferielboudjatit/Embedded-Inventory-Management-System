/********************************************************************************
  * @file           : nfc_messages.h
  * @brief          : This file contains definitions for message types which are going to be used to notify TouchGFX task
  ******************************************************************************
  */

#ifndef __NFC_MESSAGES_H__
#define __NFC_MESSAGES_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "../../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"
#include "../../Middlewares/Third_Party/FreeRTOS/Source/include/queue.h"
#include "../../Middlewares/Third_Party/FreeRTOS/Source/include/task.h"


extern QueueHandle_t nfcMessageQueue;

typedef enum
{
//  WELCOME_MESSAGE = 0,
  SCAN_BADGE_MESSAGE = 0,
  BOARD_SCANNED_MESSAGE = 1,
  BADGE_SCANNED_MESSAGE = 2,
  BOARD_ENTERED_MESSAGE = 3,
  BOARD_GOTOUT_MESSAGE = 4,
  SCAN_BOARD_BEFORE_MESSAGE = 5,
  SCAN_BADGE_BEFORE_MESSAGE = 6,
  RESCAN_BOARD_SLOWLY = 7,
  TRANSMISSION_ERROR = 8
} NFCtask_messages_t;

void SendToTouchGFX(NFCtask_messages_t message_tag);

#ifdef __cplusplus
}
#endif

#endif /* __NFC_MESSAGES_H__*/
