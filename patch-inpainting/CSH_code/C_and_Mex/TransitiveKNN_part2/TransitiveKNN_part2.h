/*
 * TransitiveKNN_part2.h
 *
 * Code generation for function 'TransitiveKNN_part2'
 *
 * C source code generated on: Wed Nov 19 10:38:03 2014
 *
 */

#ifndef __TRANSITIVEKNN_PART2_H__
#define __TRANSITIVEKNN_PART2_H__
/* Include files */
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "mwmathutil.h"

#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include "blas.h"
#include "rtwtypes.h"
#include "TransitiveKNN_part2_types.h"

/* Variable Declarations */
extern emlrtRSInfo ab_emlrtRSI;
extern emlrtRSInfo bb_emlrtRSI;
extern emlrtRSInfo cb_emlrtRSI;
extern emlrtRSInfo db_emlrtRSI;
extern emlrtRSInfo cc_emlrtRSI;
extern emlrtRSInfo dc_emlrtRSI;
extern emlrtRSInfo jc_emlrtRSI;
extern emlrtRSInfo kc_emlrtRSI;
extern emlrtRSInfo lc_emlrtRSI;
extern emlrtRSInfo bd_emlrtRSI;
extern emlrtRSInfo ld_emlrtRSI;
extern emlrtRSInfo md_emlrtRSI;
extern emlrtRSInfo nd_emlrtRSI;
extern emlrtRSInfo od_emlrtRSI;
extern emlrtMCInfo c_emlrtMCI;
extern emlrtMCInfo d_emlrtMCI;
extern emlrtMCInfo g_emlrtMCI;
extern emlrtMCInfo h_emlrtMCI;
extern emlrtMCInfo i_emlrtMCI;
extern emlrtRTEInfo u_emlrtRTEI;

/* Function Declarations */
extern void TransitiveKNN_part2(const emlrtStack *sp, const emxArray_uint8_T *A, const emxArray_uint8_T *B, real_T k, real_T width, const emxArray_real_T *overSafeResults, const emxArray_real_T *errorMat, emxArray_real_T *CSH_ann, emxArray_real_T *numUniqueResultsPerPixel, emxArray_real_T *sortedErrors);
extern void TransitiveKNN_part2_api(emlrtStack *sp, const mxArray * const prhs[6], const mxArray *plhs[3]);
extern void TransitiveKNN_part2_atexit(emlrtStack *sp);
extern void TransitiveKNN_part2_initialize(emlrtStack *sp, emlrtContext *aContext);
extern void TransitiveKNN_part2_terminate(emlrtStack *sp);
#endif
/* End of code generation (TransitiveKNN_part2.h) */
