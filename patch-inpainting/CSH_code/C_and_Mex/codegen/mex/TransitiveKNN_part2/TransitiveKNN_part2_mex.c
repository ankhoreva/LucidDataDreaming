/*
 * TransitiveKNN_part2_mex.c
 *
 * Code generation for function 'TransitiveKNN_part2'
 *
 * C source code generated on: Mon Jan 05 13:12:27 2015
 *
 */

/* Include files */
#include "mex.h"
#include "TransitiveKNN_part2.h"

/* Function Declarations */
static void TransitiveKNN_part2_mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);

/* Variable Definitions */
emlrtContext emlrtContextGlobal = { true, false, EMLRT_VERSION_INFO, NULL, "TransitiveKNN_part2", NULL, false, {2045744189U,2170104910U,2743257031U,4284093946U}, NULL };
void *emlrtRootTLSGlobal = NULL;

/* Function Definitions */
static void TransitiveKNN_part2_mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  mxArray *outputs[3];
  mxArray *inputs[6];
  int n = 0;
  int nOutputs = (nlhs < 1 ? 1 : nlhs);
  int nInputs = nrhs;
  emlrtStack stack={0,0,0}; /* Root of the run-time stack. */
  /* Module initialization. */
  TransitiveKNN_part2_initialize(&stack, &emlrtContextGlobal);
  /* Check for proper number of arguments. */
  if (nrhs != 6) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs", 5, mxINT32_CLASS, 6, mxCHAR_CLASS, 19, "TransitiveKNN_part2");
  } else if (nlhs > 3) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:TooManyOutputArguments", 3, mxCHAR_CLASS, 19, "TransitiveKNN_part2");
  }
  /* Temporary copy for mex inputs. */
  for (n = 0; n < nInputs; ++n) {
    inputs[n] = (mxArray *)prhs[n];
  }
  /* Call the function. */
  TransitiveKNN_part2_api(&stack, (const mxArray**)inputs, (const mxArray**)outputs);
  /* Copy over outputs to the caller. */
  for (n = 0; n < nOutputs; ++n) {
    plhs[n] = emlrtReturnArrayR2009a(outputs[n]);
  }
  /* Module finalization. */
  TransitiveKNN_part2_terminate(&stack);
}

void TransitiveKNN_part2_atexit_wrapper(void)
{
  emlrtStack stack={0,0,0}; /* Root of the run-time stack. */
   TransitiveKNN_part2_atexit(&stack);
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  /* Initialize the memory manager. */
  mexAtExit(TransitiveKNN_part2_atexit_wrapper);
  /* Dispatch the entry-point. */
  TransitiveKNN_part2_mexFunction(nlhs, plhs, nrhs, prhs);
}
/* End of code generation (TransitiveKNN_part2_mex.c) */
