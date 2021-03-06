/*
 * File: LPF.h
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

#ifndef RTW_HEADER_LPF_h_
#define RTW_HEADER_LPF_h_
#include "rtwtypes.h"
#ifndef LPF_COMMON_INCLUDES_
# define LPF_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* LPF_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef SS_INT64
#define SS_INT64                       17
#endif

#ifndef SS_UINT64
#define SS_UINT64                      18
#endif

/* Block signals and states (auto storage) for system '<Root>' */
typedef struct {
  int16_T Filter_states[9];            /* '<Root>/Filter' */
} DW;

/* Constant parameters (auto storage) */
typedef struct {
  /* Computed Parameter: Filter_Coefficients
   * Referenced by: '<Root>/Filter'
   */
  int16_T Filter_Coefficients[10];
} ConstP;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  int16_T In1;                         /* '<Root>/In1' */
} ExtU;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  int16_T Out1;                        /* '<Root>/Out1' */
} ExtY;

/* Block signals and states (auto storage) */
extern DW rtDW;

/* External inputs (root inport signals with auto storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY rtY;

/* Constant parameters (auto storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void LPF_initialize(void);
extern void LPF_step(void);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'LPF'
 */
#endif                                 /* RTW_HEADER_LPF_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
