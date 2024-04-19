/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * testCoder_initialize.c
 *
 * Code generation for function 'testCoder_initialize'
 *
 */

/* Include files */
#include "testCoder_initialize.h"
#include "_coder_testCoder_mex.h"
#include "rt_nonfinite.h"
#include "testCoder_data.h"

/* Function Declarations */
static void testCoder_once(void);

/* Function Definitions */
static void testCoder_once(void)
{
  mex_InitInfAndNan();
  /* Allocate instance data */
  covrtAllocateInstanceData(&emlrtCoverageInstance);
  /* Initialize Coverage Information */
  covrtScriptInit(&emlrtCoverageInstance,
                  "C:\\Users\\chris\\bu\\gva_senior_design\\image_"
                  "processing\\cropping\\testCoder.m",
                  0U, 1U, 1U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U);
  /* Initialize Function Information */
  covrtFcnInit(&emlrtCoverageInstance, 0U, 0U, "testCoder", 0, -1, 147);
  /* Initialize Basic Block Information */
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 0U, 44, -1, 143);
  /* Initialize If Information */
  /* Initialize MCDC Information */
  /* Initialize For Information */
  /* Initialize While Information */
  /* Initialize Switch Information */
  /* Start callback for coverage engine */
  covrtScriptStart(&emlrtCoverageInstance, 0U);
}

void testCoder_initialize(void)
{
  static const volatile char_T *emlrtBreakCheckR2012bFlagVar = NULL;
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  emlrtBreakCheckR2012bFlagVar = emlrtGetBreakCheckFlagAddressR2012b();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, NULL);
  emlrtEnterRtStackR2012b(&st);
  emlrtLicenseCheckR2022a(
      &st, (const char_T *)"EMLRT:runTime:MexFunctionNeedsLicense",
      (const char_T *)"image_toolbox", 2);
  if (emlrtFirstTimeR2012b(emlrtRootTLSGlobal)) {
    testCoder_once();
  }
}

/* End of code generation (testCoder_initialize.c) */
