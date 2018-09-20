/*
 * Interpolation.h
 *
 *  Created on: 19 сент. 2018 г.
 *      Author: CIT_007
 */

#ifndef APPLICATION_INTERPOLATION_H_
#define APPLICATION_INTERPOLATION_H_

#include <stdint.h>

uint16_t InterpolateLagrangePolynomial (uint16_t x, uint16_t* x_values, uint16_t* y_values, uint16_t size);


double InterpolateLagrangePolynomialD (double x, double* x_values, double* y_values, int size);


#endif /* APPLICATION_INTERPOLATION_H_ */
