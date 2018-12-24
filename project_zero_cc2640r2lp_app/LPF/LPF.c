/*
 * File: LPF.c
 *
 * Code generated for Simulink model 'LPF'.
 *
 * Model version                  : 1.66
 * Simulink Coder version         : 8.13 (R2017b) 24-Jul-2017
 * C/C++ source code generated on : Thu Dec 13 20:28:47 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. RAM efficiency
 *    2. Execution efficiency
 * Validation result: Not run
 */

#include "LPF.h"
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if 0

/* Skip this size verification because of preprocessor limitation */
#if ( ULLONG_MAX != (0xFFFFFFFFFFFFFFFFULL) ) || ( LLONG_MAX != (0x7FFFFFFFFFFFFFFFLL) )
#error Code was generated for compiler with different sized ulong_long/long_long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif
#endif

/* Block signals and states (auto storage) */
DW rtDW;

/* External inputs (root inport signals with auto storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with auto storage) */
ExtY rtY;

/* Real-time model */
RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

/* Model step function */
void LPF_step(void)
{
  int32_T tmp;
  int32_T tmp_0;
  int32_T tmp_1;
  int16_T tmp_2;

  /* S-Function (sdspbiquad): '<Root>/Filter' incorporates:
   *  Inport: '<Root>/In1'
   */
  tmp = 343 * rtU.In1;
  tmp_0 = -18253 * rtDW.Filter_FILT_STATES[0];
  tmp_1 = 7437 * rtDW.Filter_FILT_STATES[1];
  tmp = ((((((tmp & 2047) != 0) + (tmp >> 11)) - ((tmp_0 & 32767) != 0)) -
          (tmp_0 >> 15)) - (tmp_1 >> 15)) - ((tmp_1 & 32767) != 0);
  if (rtDW.Filter_FILT_STATES[0] > 16383) {
    tmp_2 = MAX_int16_T;
  } else if (rtDW.Filter_FILT_STATES[0] <= -16384) {
    tmp_2 = MIN_int16_T;
  } else {
    tmp_2 = (int16_T)(rtDW.Filter_FILT_STATES[0] << 1);
  }

  tmp_0 = (int16_T)tmp + tmp_2;
  if (tmp_0 > 32767) {
    tmp_0 = 32767;
  } else {
    if (tmp_0 < -32768) {
      tmp_0 = -32768;
    }
  }

  tmp_0 += rtDW.Filter_FILT_STATES[1];
  if (tmp_0 > 32767) {
    tmp_0 = 32767;
  } else {
    if (tmp_0 < -32768) {
      tmp_0 = -32768;
    }
  }

  rtDW.Filter_FILT_STATES[1] = rtDW.Filter_FILT_STATES[0];
  rtDW.Filter_FILT_STATES[0] = (int16_T)tmp;

  /* Outport: '<Root>/Out1' incorporates:
   *  S-Function (sdspbiquad): '<Root>/Filter'
   */
  rtY.Out1 = (int16_T)tmp_0;
}

/* Model initialize function */
void LPF_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
