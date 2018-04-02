/*
 * File: LPF.h
 *
 * Code generated for Simulink model 'LPF'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 8.13 (R2017b) 24-Jul-2017
 * C/C++ source code generated on : Mon Apr  2 20:36:57 2018
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
  int32_T Filter1_circBuf;             /* '<S1>/Filter1' */
  int16_T Filter1_states[19];          /* '<S1>/Filter1' */
} DW;

/* Constant parameters (auto storage) */
typedef struct {
  /* Computed Parameter: Filter1_Coefficients
   * Referenced by: '<S1>/Filter1'
   */
  int16_T Filter1_Coefficients[20];
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
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('filterC/LPF')    - opens subsystem filterC/LPF
 * hilite_system('filterC/LPF/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'filterC'
 * '<S1>'   : 'filterC/LPF'
 */
#endif                                 /* RTW_HEADER_LPF_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
