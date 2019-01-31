/*
 * File: LPF.c
 *
 * Code generated for Simulink model 'LPF'.
 *
 * Model version                  : 1.69
 * Simulink Coder version         : 8.13 (R2017b) 24-Jul-2017
 * C/C++ source code generated on : Mon Jan 28 20:13:19 2019
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

/* Model step function */
void LPF_step(void)
{
  int64_T acc1;
  int32_T j;
  int64_T q1;

  /* DiscreteFir: '<Root>/Filter' incorporates:
   *  Inport: '<Root>/In1'
   */
  /* Consume delay line and beginning of input samples */
  acc1 = 0LL;
  j = 0;
  while (j < 1) {
    q1 = rtU.In1 * rtConstP.Filter_Coefficients[0];
    if ((acc1 < 0LL) && (q1 < MIN_int64_T - acc1)) {
      acc1 = MIN_int64_T;
    } else if ((acc1 > 0LL) && (q1 > MAX_int64_T - acc1)) {
      acc1 = MAX_int64_T;
    } else {
      acc1 += q1;
    }

    j = 1;
  }

  for (j = 0; j < 9; j++) {
    q1 = rtConstP.Filter_Coefficients[1 + j] * rtDW.Filter_states[j];
    if ((acc1 < 0LL) && (q1 < MIN_int64_T - acc1)) {
      acc1 = MIN_int64_T;
    } else if ((acc1 > 0LL) && (q1 > MAX_int64_T - acc1)) {
      acc1 = MAX_int64_T;
    } else {
      acc1 += q1;
    }
  }

  acc1 >>= 16;
  if (acc1 > 32767LL) {
    acc1 = 32767LL;
  } else {
    if (acc1 < -32768LL) {
      acc1 = -32768LL;
    }
  }

  /* Update delay line for next frame */
  for (j = 7; j >= 0; j--) {
    rtDW.Filter_states[1 + j] = rtDW.Filter_states[j];
  }

  rtDW.Filter_states[0] = rtU.In1;

  /* Outport: '<Root>/Out1' incorporates:
   *  DiscreteFir: '<Root>/Filter'
   */
  rtY.Out1 = (int16_T)acc1;
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
