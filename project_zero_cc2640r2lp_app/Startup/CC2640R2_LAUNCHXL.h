/*
 * Copyright (c) 2015-2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/** ============================================================================
 *  @file       CC2640R2_LAUNCHXL.h
 *
 *  @brief      CC2640R2 LaunchPad Board Specific header file.
 *
 *  The CC2640R2_LAUNCHXL header file should be included in an application as
 *  follows:
 *  @code
 *  #include "CC2640R2_LAUNCHXL.h"
 *  @endcode
 *
 *  This board file is made for the 7x7 mm QFN package, to convert this board
 *  file to use for other smaller device packages please refer to the table
 *  below which lists the max IOID values supported by each package. All other
 *  unused pins should be set to IOID_UNUSED.
 *
 *  Furthermore the board file is also used
 *  to define a symbol that configures the RF front end and bias.
 *  See the comments below for more information.
 *  For an in depth tutorial on how to create a custom board file, please refer
 *  to the section "Running the SDK on Custom Boards" with in the Software
 *  Developer's Guide.
 *
 *  Refer to the datasheet for all the package options and IO descriptions:
 *  http://www.ti.com/lit/ds/symlink/cc2640r2f.pdf
 *
 *  +-----------------------+------------------+-----------------------+
 *  |     Package Option    |  Total GPIO Pins |   MAX IOID            |
 *  +=======================+==================+=======================+
 *  |     7x7 mm QFN        |     31           |   IOID_30             |
 *  +-----------------------+------------------+-----------------------+
 *  |     5x5 mm QFN        |     15           |   IOID_14             |
 *  +-----------------------+------------------+-----------------------+
 *  |     4x4 mm QFN        |     10           |   IOID_9              |
 *  +-----------------------+------------------+-----------------------+
 *  |     2.7 x 2.7 mm WCSP |     14           |   IOID_13             |
 *  +-----------------------+------------------+-----------------------+
 *  ============================================================================
 */
#ifndef __CC2640R2_LAUNCHXL_BOARD_H__
#define __CC2640R2_LAUNCHXL_BOARD_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include <ti/drivers/PIN.h>
#include <ti/devices/cc26x0r2/driverlib/ioc.h>
#include "GeneralDef.h"

/* Externs */
extern const PIN_Config BoardGpioInitTable[];

/* Defines */
#ifndef CC2640R2_LAUNCHXL
  #define CC2640R2_LAUNCHXL
#endif /* CC2640R2_LAUNCHXL */

/*
 *  ============================================================================
 *  RF Front End and Bias configuration symbols for TI reference designs and
 *  kits. This symbol sets the RF Front End configuration in ble_user_config.h
 *  and selects the appropriate PA table in ble_user_config.c.
 *  Other configurations can be used by editing these files.
 *
 *  Define only one symbol:
 *  CC2650EM_7ID    - Differential RF and internal biasing
                      (default for CC2640R2 LaunchPad)
 *  CC2650EM_5XD    – Differential RF and external biasing
 *  CC2650EM_4XS    – Single-ended RF on RF-P and external biasing
 *  CC2640R2DK_CXS  - WCSP: Single-ended RF on RF-N and external biasing
 *                    (Note that the WCSP is only tested and characterized for
 *                     single ended configuration, and it has a WCSP-specific
 *                     PA table)
 *
 *  Note: CC2650EM_xxx reference designs apply to all CC26xx devices.
 *  ==========================================================================
 */
#define CC2650EM_7ID


/* Mapping of pins to board signals using general board aliases
 *      <board signal alias>                  <pin mapping>
 */

/* Analog Capable DIOs */
#define CC2640R2_LAUNCHXL_DIO23_ANALOG          IOID_23
#define CC2640R2_LAUNCHXL_DIO24_ANALOG          IOID_24
#define CC2640R2_LAUNCHXL_DIO25_ANALOG          IOID_25
#define CC2640R2_LAUNCHXL_DIO26_ANALOG          IOID_26
#define CC2640R2_LAUNCHXL_DIO27_ANALOG          IOID_27
#define CC2640R2_LAUNCHXL_DIO28_ANALOG          IOID_28
#define CC2640R2_LAUNCHXL_DIO29_ANALOG          IOID_29
#define CC2640R2_LAUNCHXL_DIO30_ANALOG          IOID_30

/* Digital IOs */
#define CC2640R2_LAUNCHXL_DIO0                  PIN_UNASSIGNED
#define CC2640R2_LAUNCHXL_DIO1_RFSW             PIN_UNASSIGNED
#define CC2640R2_LAUNCHXL_DIO12                 IOID_12
#define CC2640R2_LAUNCHXL_DIO15                 PIN_UNASSIGNED
#define CC2640R2_LAUNCHXL_DIO16_TDO             IOID_16
#define CC2640R2_LAUNCHXL_DIO17_TDI             IOID_17
#define CC2640R2_LAUNCHXL_DIO21                 IOID_21
#define CC2640R2_LAUNCHXL_DIO22                 IOID_22

/* Discrete Inputs */
#ifdef HANDS_FREE_NOT_BOARD
    #define CC2640R2_LAUNCHXL_PIN_BTN1              IOID_29 //PIN_UNASSIGNED
    #define CC2640R2_LAUNCHXL_PIN_BTN2              IOID_30 //PIN_UNASSIGNED
#else
#ifdef HANDS_FREE_NOT_BOARD_NEW_VERSION
    #define CC2640R2_LAUNCHXL_PIN_BTN1              IOID_29 //PIN_UNASSIGNED
    #define CC2640R2_LAUNCHXL_PIN_BTN2              IOID_30 //PIN_UNASSIGNED
#else
#ifdef HANDS_FREE_BOARD_VERSION3
    #define CC2640R2_LAUNCHXL_PIN_BTN1              IOID_11 //PIN_UNASSIGNED
    #define CC2640R2_LAUNCHXL_PIN_BTN2              IOID_12 //PIN_UNASSIGNED
    #define CC2640R2_LAUNCHXL_PIN_POWER              IOID_15 //PIN_UNASSIGNED
#else
    #define CC2640R2_LAUNCHXL_PIN_BTN1              IOID_13 //PIN_UNASSIGNED
    #define CC2640R2_LAUNCHXL_PIN_BTN2              IOID_14 //PIN_UNASSIGNED
#endif
#endif
#endif
/* GPIO */
#define CC2640R2_LAUNCHXL_GPIO_LED_ON           1
#define CC2640R2_LAUNCHXL_GPIO_LED_OFF          0

/* I2C */
#ifdef HANDS_FREE_NOT_BOARD
    #define CC2640R2_LAUNCHXL_I2C0_SCL0             IOID_10//IOID_4
    #define CC2640R2_LAUNCHXL_I2C0_SDA0             IOID_8//IOID_5
#else
#ifdef HANDS_FREE_NOT_BOARD_NEW_VERSION
    #define CC2640R2_LAUNCHXL_I2C0_SCL0             IOID_19//IOID_4
    #define CC2640R2_LAUNCHXL_I2C0_SDA0             IOID_18//IOID_5
#else
#ifdef HANDS_FREE_BOARD_VERSION3
    #define CC2640R2_LAUNCHXL_I2C0_SCL0             IOID_25//IOID_4
    #define CC2640R2_LAUNCHXL_I2C0_SDA0             IOID_26//IOID_5
#else
    #define CC2640R2_LAUNCHXL_I2C0_SCL0             IOID_2//IOID_4
    #define CC2640R2_LAUNCHXL_I2C0_SDA0             IOID_27//IOID_5
#endif
#endif
#endif

/* LEDs */
#define CC2640R2_LAUNCHXL_PIN_LED_ON            1
#define CC2640R2_LAUNCHXL_PIN_LED_OFF           0

#ifdef HANDS_FREE_NOT_BOARD
    #define CC2640R2_LAUNCHXL_PIN_RLED              IOID_0
    #define CC2640R2_LAUNCHXL_PIN_GLED              IOID_1
#else
#ifdef HANDS_FREE_NOT_BOARD_NEW_VERSION
    #define CC2640R2_LAUNCHXL_PIN_RLED              IOID_11
    #define CC2640R2_LAUNCHXL_PIN_GLED              IOID_9
#else
#ifdef HANDS_FREE_BOARD_VERSION3
    #define CC2640R2_LAUNCHXL_PIN_RLED              IOID_14
    #define CC2640R2_LAUNCHXL_PIN_GLED              IOID_13
#else
    #define CC2640R2_LAUNCHXL_PIN_RLED              IOID_6
    #define CC2640R2_LAUNCHXL_PIN_GLED              IOID_7
#endif
#endif
#endif

/* UART Board */
#ifdef HANDS_FREE_NOT_BOARD_NEW_VERSION
    #define CC2640R2_LAUNCHXL_UART_RX               PIN_UNASSIGNED//IOID_8       /* RXD */
    #define CC2640R2_LAUNCHXL_UART_TX               PIN_UNASSIGNED//IOID_9      /* TXD */
#else
#ifdef HANDS_FREE_BOARD_VERSION3
    #define CC2640R2_LAUNCHXL_UART_RX               IOID_2//IOID_2          /* RXD */
    #define CC2640R2_LAUNCHXL_UART_TX               IOID_3          /* TXD */
#else
    #define CC2640R2_LAUNCHXL_UART_RX               IOID_3//IOID_2          /* RXD */
    #define CC2640R2_LAUNCHXL_UART_TX               IOID_2          /* TXD */
#endif
#endif

#define CC2640R2_LAUNCHXL_UART_CTS              PIN_UNASSIGNED         /* CTS */
#define CC2640R2_LAUNCHXL_UART_RTS              PIN_UNASSIGNED         /* RTS */

#ifdef HANDS_FREE_NOT_BOARD
    #define CC2640R2_LAUNCHXL_I2S_ADO               IOID_22//IOID_0
    #define CC2640R2_LAUNCHXL_I2S_ADI               IOID_21//IOID_1
    /* I2S */
    #define CC2640R2_LAUNCHXL_I2S_BCLK              IOID_26//IOID_30
    #define CC2640R2_LAUNCHXL_I2S_MCLK              IOID_19//(PIN_Id)IOID_UNUSED
    #define CC2640R2_LAUNCHXL_I2S_WCLK              IOID_24//IOID_29
#else
#ifdef HANDS_FREE_NOT_BOARD_NEW_VERSION
    #define CC2640R2_LAUNCHXL_I2S_ADO               IOID_13//IOID_0
    #define CC2640R2_LAUNCHXL_I2S_ADI               IOID_14//IOID_1
    /* I2S */
    #define CC2640R2_LAUNCHXL_I2S_BCLK              IOID_8//IOID_30
    #define CC2640R2_LAUNCHXL_I2S_MCLK              IOID_15//(PIN_Id)IOID_UNUSED
    #define CC2640R2_LAUNCHXL_I2S_WCLK              IOID_12//IOID_29
#else
#ifdef HANDS_FREE_BOARD_VERSION3
    #define CC2640R2_LAUNCHXL_I2S_ADO               IOID_19//IOID_0
    #define CC2640R2_LAUNCHXL_I2S_ADI               IOID_20//IOID_1
    /* I2S */
    #define CC2640R2_LAUNCHXL_I2S_BCLK              IOID_5//IOID_30
    #define CC2640R2_LAUNCHXL_I2S_MCLK              IOID_21//(PIN_Id)IOID_UNUSED
    #define CC2640R2_LAUNCHXL_I2S_WCLK              IOID_4//IOID_29
#else
    #define CC2640R2_LAUNCHXL_I2S_ADO               IOID_3//IOID_0
    #define CC2640R2_LAUNCHXL_I2S_ADI               IOID_26//IOID_1 IOID_26
    /* I2S */
    #define CC2640R2_LAUNCHXL_I2S_BCLK              IOID_23//IOID_30
    #define CC2640R2_LAUNCHXL_I2S_MCLK              IOID_22//(PIN_Id)IOID_UNUSED
    #define CC2640R2_LAUNCHXL_I2S_WCLK              IOID_25//IOID_29
#endif
#endif
#endif
/*!
 *  @brief  Initialize the general board specific settings
 *
 *  This function initializes the general board specific settings.
 */
void CC2640R2_LAUNCHXL_initGeneral(void);

/*!
 *  @def    CC2640R2_LAUNCHXL_ADCBufName
 *  @brief  Enum of ADCs
 */
typedef enum CC2640R2_LAUNCHXL_ADCBufName {
    CC2640R2_LAUNCHXL_ADCBUF0 = 0,

    CC2640R2_LAUNCHXL_ADCBUFCOUNT
} CC2640R2_LAUNCHXL_ADCBufName;

/*!
 *  @def    CC2640R2_LAUNCHXL_ADCBuf0SourceName
 *  @brief  Enum of ADCBuf channels
 */
typedef enum CC2640R2_LAUNCHXL_ADCBuf0ChannelName {
    CC2640R2_LAUNCHXL_ADCBUF0CHANNEL0 = 0,
    CC2640R2_LAUNCHXL_ADCBUF0CHANNEL1,
    CC2640R2_LAUNCHXL_ADCBUF0CHANNEL2,
    CC2640R2_LAUNCHXL_ADCBUF0CHANNEL3,
    CC2640R2_LAUNCHXL_ADCBUF0CHANNEL4,
    CC2640R2_LAUNCHXL_ADCBUF0CHANNEL5,
    CC2640R2_LAUNCHXL_ADCBUF0CHANNEL6,
    CC2640R2_LAUNCHXL_ADCBUF0CHANNEL7,
    CC2640R2_LAUNCHXL_ADCBUF0CHANNELVDDS,
    CC2640R2_LAUNCHXL_ADCBUF0CHANNELDCOUPL,
    CC2640R2_LAUNCHXL_ADCBUF0CHANNELVSS,

    CC2640R2_LAUNCHXL_ADCBUF0CHANNELCOUNT
} CC2640R2_LAUNCHXL_ADCBuf0ChannelName;

/*!
 *  @def    CC2640R2_LAUNCHXL_ADCName
 *  @brief  Enum of ADCs
 */
typedef enum CC2640R2_LAUNCHXL_ADCName {
    CC2640R2_LAUNCHXL_ADC0 = 0,
    CC2640R2_LAUNCHXL_ADC1,
    CC2640R2_LAUNCHXL_ADC2,
    CC2640R2_LAUNCHXL_ADC3,
    CC2640R2_LAUNCHXL_ADC4,
    CC2640R2_LAUNCHXL_ADC5,
    CC2640R2_LAUNCHXL_ADC6,
    CC2640R2_LAUNCHXL_ADC7,
    CC2640R2_LAUNCHXL_ADCDCOUPL,
    CC2640R2_LAUNCHXL_ADCVSS,
    CC2640R2_LAUNCHXL_ADCVDDS,

    CC2640R2_LAUNCHXL_ADCCOUNT
} CC2640R2_LAUNCHXL_ADCName;

/*!
 *  @def    CC2640R2_LAUNCHXL_CryptoName
 *  @brief  Enum of Crypto names
 */
typedef enum CC2640R2_LAUNCHXL_CryptoName {
    CC2640R2_LAUNCHXL_CRYPTO0 = 0,

    CC2640R2_LAUNCHXL_CRYPTOCOUNT
} CC2640R2_LAUNCHXL_CryptoName;

/*!
 *  @def    CC2640R2_LAUNCHXL_GPIOName
 *  @brief  Enum of GPIO names
 */
typedef enum CC2640R2_LAUNCHXL_GPIOName {
    CC2640R2_LAUNCHXL_GPIO_S1 = 0,
    CC2640R2_LAUNCHXL_GPIO_S2,
    CC2640R2_LAUNCHXL_GPIO_LED_GREEN,
    CC2640R2_LAUNCHXL_GPIO_LED_RED,

    CC2640R2_LAUNCHXL_GPIOCOUNT
} CC2640R2_LAUNCHXL_GPIOName;

/*!
 *  @def    CC2640R2_LAUNCHXL_GPTimerName
 *  @brief  Enum of GPTimer parts
 */
typedef enum CC2640R2_LAUNCHXL_GPTimerName {
    CC2640R2_LAUNCHXL_GPTIMER0A = 0,
    CC2640R2_LAUNCHXL_GPTIMER0B,
    CC2640R2_LAUNCHXL_GPTIMER1A,
    CC2640R2_LAUNCHXL_GPTIMER1B,
    CC2640R2_LAUNCHXL_GPTIMER2A,
    CC2640R2_LAUNCHXL_GPTIMER2B,
    CC2640R2_LAUNCHXL_GPTIMER3A,
    CC2640R2_LAUNCHXL_GPTIMER3B,

    CC2640R2_LAUNCHXL_GPTIMERPARTSCOUNT
} CC2640R2_LAUNCHXL_GPTimerName;

/*!
 *  @def    CC2640R2_LAUNCHXL_GPTimers
 *  @brief  Enum of GPTimers
 */
typedef enum CC2640R2_LAUNCHXL_GPTimers {
    CC2640R2_LAUNCHXL_GPTIMER0 = 0,
    CC2640R2_LAUNCHXL_GPTIMER1,
    CC2640R2_LAUNCHXL_GPTIMER2,
    CC2640R2_LAUNCHXL_GPTIMER3,

    CC2640R2_LAUNCHXL_GPTIMERCOUNT
} CC2640R2_LAUNCHXL_GPTimers;

/*!
 *  @def    CC2640R2_LAUNCHXL_I2CName
 *  @brief  Enum of I2C names
 */
typedef enum CC2640R2_LAUNCHXL_I2CName {
    CC2640R2_LAUNCHXL_I2C0 = 0,

    CC2640R2_LAUNCHXL_I2CCOUNT
} CC2640R2_LAUNCHXL_I2CName;

/*!
 *  @def    CC2640R2_LAUNCHXL_UARTName
 *  @brief  Enum of UARTs
 */
typedef enum CC2640R2_LAUNCHXL_UARTName {
    CC2640R2_LAUNCHXL_UART0 = 0,

    CC2640R2_LAUNCHXL_UARTCOUNT
} CC2640R2_LAUNCHXL_UARTName;

/*!
 *  @def    CC2640R2_LAUNCHXL_UDMAName
 *  @brief  Enum of DMA buffers
 */
typedef enum CC2640R2_LAUNCHXL_UDMAName {
    CC2640R2_LAUNCHXL_UDMA0 = 0,

    CC2640R2_LAUNCHXL_UDMACOUNT
} CC2640R2_LAUNCHXL_UDMAName;

/*!
 *  @def    CC2640R2_LAUNCHXL_WatchdogName
 *  @brief  Enum of Watchdogs
 */
typedef enum CC2640R2_LAUNCHXL_WatchdogName {
    CC2640R2_LAUNCHXL_WATCHDOG0 = 0,

    CC2640R2_LAUNCHXL_WATCHDOGCOUNT
} CC2640R2_LAUNCHXL_WatchdogName;

/*!
 *  @def    CC2650_LAUNCHXL_TRNGName
 *  @brief  Enum of TRNG names on the board
 */
typedef enum CC2640R2_LAUNCHXL_TRNGName {
    CC2640R2_LAUNCHXL_TRNG0 = 0,
    CC2640R2_LAUNCHXL_TRNGCOUNT
} CC2640R2_LAUNCHXL_TRNGName;

#ifdef __cplusplus
}
#endif

#endif /* __CC2640R2_LAUNCHXL_BOARD_H__ */
