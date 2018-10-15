/*
 * Power_calc.c
 *
 *  Created on: 25 сент. 2018 г.
 *      Author: CIT_007
 */

#include <math.h>
#include <stdint.h>
#include "Noise_TRSH.h"


struct power_struct power_calculation (int16_t *in, uint16_t samp_number){

    struct power_struct out;
    float channel_power_1 = 0;

    for(uint8_t i = 0 ; i < samp_number ; i++)
    {
        channel_power_1 += sqrtf((int32_t)in[i] * (int32_t)in[i]);
    }
    out.power = (float)channel_power_1 * 0.000018768310546875 / (float)samp_number;
    out.power_log = 10*logf( out.power / 1.23 );

    return out;
}



void amplify (int16_t *in, uint16_t samp_number, int16_t power)
{
    float power_dif;
    float amplify_gain;

    float power_average;

    power_dif = START_POWER_REDUCE-power;
    power_average = power_dif;//power_average*0.9 + power_dif * 0.1;

    if(power_average < 0 )
    {
        power_average = 0;
    }
    amplify_gain = 1/(1.23* pow(100, power_average / 20));

    for(uint8_t i = 0 ; i < samp_number ; i++)
    {
        in[i] = (int16_t) ((float)in[i] * amplify_gain);
    }


}

