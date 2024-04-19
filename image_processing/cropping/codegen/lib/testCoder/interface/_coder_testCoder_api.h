//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_testCoder_api.h
//
// Code generation for function 'testCoder'
//

#ifndef _CODER_TESTCODER_API_H
#define _CODER_TESTCODER_API_H

// Include files
#include "coder_array_mex.h"
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Type Definitions
struct rtString_tag_0 {
  coder::array<char_T, 2U> Value;
};
using rtString = rtString_tag_0;

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void testCoder(rtString *inputImage, coder::array<uint8_T, 2U> *newImg);

void testCoder_api(const mxArray *prhs, const mxArray **plhs);

void testCoder_atexit();

void testCoder_initialize();

void testCoder_terminate();

void testCoder_xil_shutdown();

void testCoder_xil_terminate();

#endif
// End of code generation (_coder_testCoder_api.h)
