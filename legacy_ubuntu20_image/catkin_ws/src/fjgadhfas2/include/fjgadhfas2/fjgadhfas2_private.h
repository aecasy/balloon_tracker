//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: fjgadhfas2_private.h
//
// Code generated for Simulink model 'fjgadhfas2'.
//
// Model version                  : 1.2
// Simulink Coder version         : 9.8 (R2022b) 13-May-2022
// C/C++ source code generated on : Thu Jan 15 18:30:43 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_fjgadhfas2_private_h_
#define RTW_HEADER_fjgadhfas2_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "fjgadhfas2_types.h"

// Private macros used by the generated code to access rtModel
#ifndef rtmSetTFinal
#define rtmSetTFinal(rtm, val)         ((rtm)->Timing.tFinal = (val))
#endif

extern real_T rt_atan2d_snf(real_T u0, real_T u1);
extern real_T rt_remd_snf(real_T u0, real_T u1);

#endif                                 // RTW_HEADER_fjgadhfas2_private_h_

//
// File trailer for generated code.
//
// [EOF]
//
