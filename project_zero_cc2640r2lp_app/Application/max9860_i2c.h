/*
 * max9860_i2c.h
 *
 *  Created on: 28 мар. 2018 г.
 *      Author: CIT_007
 */

#ifndef APPLICATION_MAX9860_I2C_H_
#define APPLICATION_MAX9860_I2C_H_

#include <ti/drivers/I2C.h>
#include "Board.h"

#define INIT_GAIN 0x2e

void max9860_I2C_Init(void);
void max9860_I2C_Read_Status(void);
void max9860_I2C_Volume_update(uint8_t vol);
void max9860_I2C_Shutdown_state(uint8_t state); //1 - shutdown on, 0 - shutdown off

#endif /* APPLICATION_MAX9860_I2C_H_ */
