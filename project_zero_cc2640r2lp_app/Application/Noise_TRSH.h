/*
 * Power_calc.h
 *
 *  Created on: 25 сент. 2018 г.
 *      Author: CIT_007
 */

#ifndef APPLICATION_NOISE_TRSH_H_
#define APPLICATION_NOISE_TRSH_H_


struct power_struct {
    float power;
    float power_log;
};



struct power_struct power_calculation (int16_t *in, uint16_t samp_number);

void amplify (int16_t *in, uint16_t samp_number, int16_t power);

#define START_POWER_REDUCE -50




#endif /* APPLICATION_NOISE_TRSH_H_ */
