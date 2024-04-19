//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_testCoder_mex.cpp
//
// Code generation for function 'testCoder'
//

// Include files
#include "_coder_testCoder_mex.h"
#include "_coder_testCoder_api.h"

// Function Definitions
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
                 const mxArray *prhs[])
{
  mexAtExit(&testCoder_atexit);
  // Module initialization.
  testCoder_initialize();
  // Dispatch the entry-point.
  unsafe_testCoder_mexFunction(nlhs, plhs, nrhs, prhs);
  // Module termination.
  testCoder_terminate();
}

emlrtCTX mexFunctionCreateRootTLS()
{
  emlrtCreateRootTLSR2022a(&emlrtRootTLSGlobal, &emlrtContextGlobal, nullptr, 1,
                           nullptr, (const char_T *)"windows-1252", true);
  return emlrtRootTLSGlobal;
}

void unsafe_testCoder_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                  const mxArray *prhs[1])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  const mxArray *outputs;
  st.tls = emlrtRootTLSGlobal;
  // Check for proper number of arguments.
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4,
                        9, "testCoder");
  }
  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 9,
                        "testCoder");
  }
  // Call the function.
  testCoder_api(prhs[0], &outputs);
  // Copy over outputs to the caller.
  emlrtReturnArrays(1, &plhs[0], &outputs);
}

// End of code generation (_coder_testCoder_mex.cpp)
