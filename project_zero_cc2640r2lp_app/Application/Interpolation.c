/*
 * Interpolation.c
 *
 *  Created on: 19 сент. 2018 г.
 *      Author: CIT_007
 */


#include "Interpolation.h"



uint16_t InterpolateLagrangePolynomial (uint16_t x, uint16_t* x_values, uint16_t* y_values, uint16_t size)
{
    uint16_t lagrange_pol = 0;
    uint16_t basics_pol;

    for (uint16_t i = 0; i < size; i++)
    {
        basics_pol = 1;
        for (uint16_t j = 0; j < size; j++)
        {
            if (j == i) continue;
            basics_pol *= (x - x_values[j])/(x_values[i] - x_values[j]);
        }
        lagrange_pol += basics_pol*y_values[i];
    }
    return lagrange_pol;
}

double InterpolateLagrangePolynomialD (double x, double* x_values, double* y_values, int size)
{
    double lagrange_pol = 0;
    double basics_pol;

    for (int i = 0; i < size; i++)
    {
        basics_pol = 1;
        for (int j = 0; j < size; j++)
        {
            if (j == i) continue;
            basics_pol *= (x - x_values[j])/(x_values[i] - x_values[j]);
        }
        lagrange_pol += basics_pol*y_values[i];
    }
    return lagrange_pol;
}
