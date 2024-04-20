/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_testCoder_mex.c
 *
 * Code generation for function '_coder_testCoder_mex'
 *
 */

/* Include files */
#include "_coder_testCoder_mex.h"
#include "_coder_testCoder_api.h"
#include "rt_nonfinite.h"
#include "testCoder_data.h"
#include "testCoder_initialize.h"
#include "testCoder_terminate.h"

/* Function Definitions */
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
                 const mxArray *prhs[])
{
  mexAtExit(&testCoder_atexit);
  /* Module initialization. */
  testCoder_initialize();
  /* Dispatch the entry-point. */
  testCoder_mexFunction(nlhs, plhs, nrhs, prhs);
  /* Module termination. */
  testCoder_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLSR2022a(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1,
                           NULL, (const char_T *)"windows-1252", true);
  return emlrtRootTLSGlobal;
}

void testCoder_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                           const mxArray *prhs[1])
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  const mxArray *outputs;
  st.tls = emlrtRootTLSGlobal;
  /* Check for proper number of arguments. */
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4,
                        9, "testCoder");
  }
  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 9,
                        "testCoder");
  }
  /* Call the function. */
  testCoder_api(prhs[0], &outputs);
  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, &plhs[0], &outputs);
}

/* End of code generation (_coder_testCoder_mex.c) */
