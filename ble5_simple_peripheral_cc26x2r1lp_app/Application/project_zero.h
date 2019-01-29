/******************************************************************************

   @file  project_zero.h

   @brief This file contains the Project Zero sample application
        definitions and prototypes.

   Group: CMCU, LPRF
   Target Device: CC2652

 ******************************************************************************
   
 Copyright (c) 2015-2018, Texas Instruments Incorporated
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 *  Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

 *  Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

 *  Neither the name of Texas Instruments Incorporated nor the names of
    its contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 ******************************************************************************
   Release Name: simplelink_cc26x2_sdk_2_30_00_34
   Release Date: 2018-10-04 14:27:27
 *****************************************************************************/

#ifndef APP_H
#define APP_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
#include <stdint.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/drivers/PIN.h>

#include <bcomdef.h>
#include <string.h>

#if !(defined __TI_COMPILER_VERSION__)
#include <intrinsics.h>
#endif

#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/drivers/utils/List.h>

//#include <xdc/runtime/Log.h> // Comment this in to use xdc.runtime.Log
#include <ti/common/cc26xx/uartlog/UartLog.h>  // Comment out if using xdc Log

#include <ti/display/AnsiColor.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/sys_ctrl.h)

#include <icall.h>
#include <bcomdef.h>
/* This Header file contains all BLE API and icall structure definition */
#include <icall_ble_api.h>

/* Bluetooth Profiles */
#include <devinfoservice.h>
#include "./services/data_service.h"

/* Application specific includes */
#include <Board.h>
/*********************************************************************
 *  EXTERNAL VARIABLES
 */

/*********************************************************************
 * CONSTANTS
 */
// Task configuration
#define PZ_TASK_PRIORITY                     1

#ifndef PZ_TASK_STACK_SIZE
#define PZ_TASK_STACK_SIZE                   2048
#endif

// Internal Events for RTOS application
#define PZ_ICALL_EVT                         ICALL_MSG_EVENT_ID  // Event_Id_31
#define PZ_APP_MSG_EVT                       Event_Id_30

// Bitwise OR of all RTOS events to pend on
#define PZ_ALL_EVENTS                        (PZ_ICALL_EVT | \
                                              PZ_APP_MSG_EVT)

// Types of messages that can be sent to the user application task from other
// tasks or interrupts. Note: Messages from BLE Stack are sent differently.
#define PZ_SERVICE_WRITE_EVT     0  /* A characteristic value has been written     */
#define PZ_SERVICE_CFG_EVT       1  /* A characteristic configuration has changed  */
#define PZ_UPDATE_CHARVAL_EVT    2  /* Request from ourselves to update a value    */
#define PZ_BUTTON_DEBOUNCED_EVT  3  /* A button has been debounced with new value  */
#define PZ_PAIRSTATE_EVT         4  /* The pairing state is updated                */
#define PZ_PASSCODE_EVT          5  /* A pass-code/PIN is requested during pairing */
#define PZ_ADV_EVT               6  /* A subscribed advertisement activity         */
#define PZ_START_ADV_EVT         7  /* Request advertisement start from task ctx   */
#define PZ_SEND_PARAM_UPD_EVT    8  /* Request parameter update req be sent        */
#define PZ_CONN_EVT              9  /* Connection Event End notice                 */
#define PZ_SEND_PACKET           10  /* Connection Event End notice                 */
#define PZ_I2C_Read_status       11  /* Connection Event End notice                 */

// General discoverable mode: advertise indefinitely
#define DEFAULT_DISCOVERABLE_MODE             GAP_ADTYPE_FLAGS_GENERAL

// Minimum connection interval (units of 1.25ms, 80=100ms) for parameter update request
#define DEFAULT_DESIRED_MIN_CONN_INTERVAL     8

// Maximum connection interval (units of 1.25ms, 800=1000ms) for  parameter update request
#define DEFAULT_DESIRED_MAX_CONN_INTERVAL     8

// Slave latency to use for parameter update request
#define DEFAULT_DESIRED_SLAVE_LATENCY         0

// Supervision timeout value (units of 10ms, 1000=10s) for parameter update request
#define DEFAULT_DESIRED_CONN_TIMEOUT          2000

// Supervision timeout conversion rate to miliseconds
#define CONN_TIMEOUT_MS_CONVERSION            10

// Connection interval conversion rate to miliseconds
#define CONN_INTERVAL_MS_CONVERSION           1.25

// Pass parameter updates to the app for it to decide.
#define DEFAULT_PARAM_UPDATE_REQ_DECISION     GAP_UPDATE_REQ_PASS_TO_APP

// Delay (in ms) after connection establishment before sending a parameter update requst
#define PZ_SEND_PARAM_UPDATE_DELAY            0



/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * TYPEDEFS
 */
// Struct for messages sent to the application task
typedef struct
{
    uint8_t event;
    void    *pData;
} pzMsg_t;

// Struct for messages about characteristic data
typedef struct
{
    uint16_t svcUUID; // UUID of the service
    uint16_t dataLen; //
    uint8_t paramID; // Index of the characteristic
    uint8_t data[]; // Flexible array member, extended to malloc - sizeof(.)
} pzCharacteristicData_t;

// Struct for message about sending/requesting passcode from peer.
typedef struct
{
    uint16_t connHandle;
    uint8_t uiInputs;
    uint8_t uiOutputs;
    uint32_t numComparison;
} pzPasscodeReq_t;

// Struct for message about a pending parameter update request.
typedef struct
{
    uint16_t connHandle;
} pzSendParamReq_t;

// Struct for message about button state
typedef struct
{
    PIN_Id pinId;
    uint8_t state;
} pzButtonState_t;

// Container to store passcode data when passing from gapbondmgr callback
// to app event. See the pfnPairStateCB_t documentation from the gapbondmgr.h
// header file for more information on each parameter.
typedef struct
{
    uint8_t state;
    uint16_t connHandle;
    uint8_t status;
} pzPairStateData_t;

// Container to store passcode data when passing from gapbondmgr callback
// to app event. See the pfnPasscodeCB_t documentation from the gapbondmgr.h
// header file for more information on each parameter.
typedef struct
{
    uint8_t deviceAddr[B_ADDR_LEN];
    uint16_t connHandle;
    uint8_t uiInputs;
    uint8_t uiOutputs;
    uint32_t numComparison;
} pzPasscodeData_t;

// Container to store advertising event data when passing from advertising
// callback to app event. See the respective event in GapAdvScan_Event_IDs
// in gap_advertiser.h for the type that pBuf should be cast to.
typedef struct
{
    uint32_t event;
    void *pBuf;
} pzGapAdvEventData_t;

// List element for parameter update and PHY command status lists
typedef struct
{
    List_Elem elem;
    uint16_t *connHandle;
} pzConnHandleEntry_t;

// Connected device information
typedef struct
{
    uint16_t connHandle;                    // Connection Handle
    Clock_Struct* pUpdateClock;             // pointer to clock struct
    bool phyCngRq;                          // Set to true if PHY change request is in progress
    uint8_t currPhy;                        // The active PHY for a connection
    uint8_t rqPhy;                          // The requested PHY for a connection
    uint8_t phyRqFailCnt;                   // PHY change request fail count
} pzConnRec_t;

/*********************************************************************
 * FUNCTIONS
 */

void ProjectZero_DataService_ValueChangeHandler(pzCharacteristicData_t *pCharData);
void ProjectZero_DataService_CfgChangeHandler( pzCharacteristicData_t *pCharData);
/* Utility functions */
status_t ProjectZero_enqueueMsg(uint8_t event,
                                   void *pData);

/*
 * Task creation function for the Project Zero.
 */
extern void ProjectZero_createTask(void);

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* APP_H */
