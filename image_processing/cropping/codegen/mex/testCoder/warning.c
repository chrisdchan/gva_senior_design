/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * warning.c
 *
 * Code generation for function 'warning'
 *
 */

/* Include files */
#include "warning.h"
#include "rt_nonfinite.h"
#include "testCoder_data.h"

/* Variable Definitions */
static emlrtMCInfo emlrtMCI = {
    14,        /* lineNo */
    25,        /* colNo */
    "warning", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\shared\\coder\\coder\\lib\\+coder\\+"
    "internal\\warning.m" /* pName */
};

static emlrtMCInfo b_emlrtMCI = {
    14,        /* lineNo */
    9,         /* colNo */
    "warning", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\shared\\coder\\coder\\lib\\+coder\\+"
    "internal\\warning.m" /* pName */
};

static emlrtRSInfo y_emlrtRSI = {
    14,        /* lineNo */
    "warning", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\shared\\coder\\coder\\lib\\+coder\\+"
    "internal\\warning.m" /* pathName */
};

/* Function Declarations */
static void b_feval(const emlrtStack *sp, const mxArray *m, const mxArray *m1,
                    emlrtMCInfo *location);

static const mxArray *feval(const emlrtStack *sp, const mxArray *m1,
                            const mxArray *m2, const mxArray *m3,
                            const mxArray *m4, emlrtMCInfo *location);

/* Function Definitions */
static void b_feval(const emlrtStack *sp, const mxArray *m, const mxArray *m1,
                    emlrtMCInfo *location)
{
  const mxArray *pArrays[2];
  pArrays[0] = m;
  pArrays[1] = m1;
  emlrtCallMATLABR2012b((emlrtCTX)sp, 0, NULL, 2, &pArrays[0],
                        (const char_T *)"feval", true, location);
}

static const mxArray *feval(const emlrtStack *sp, const mxArray *m1,
                            const mxArray *m2, const mxArray *m3,
                            const mxArray *m4, emlrtMCInfo *location)
{
  const mxArray *pArrays[4];
  const mxArray *m;
  pArrays[0] = m1;
  pArrays[1] = m2;
  pArrays[2] = m3;
  pArrays[3] = m4;
  return emlrtCallMATLABR2012b((emlrtCTX)sp, 1, &m, 4, &pArrays[0],
                               (const char_T *)"feval", true, location);
}

void warning(const emlrtStack *sp, const char_T varargin_2[200])
{
  static const int32_T iv[2] = {1, 7};
  static const int32_T iv1[2] = {1, 7};
  static const int32_T iv2[2] = {1, 41};
  static const int32_T iv3[2] = {1, 200};
  static const char_T msgID[41] = {
      'M', 'A', 'T', 'L', 'A', 'B', ':', 'i', 'm', 'a', 'g', 'e', 's', 'c',
      'i', ':', 'j', 'p', 'g', ':', 'u', 'n', 'h', 'a', 'n', 'd', 'l', 'e',
      'd', 'L', 'i', 'b', 'r', 'a', 'r', 'y', 'E', 'r', 'r', 'o', 'r'};
  static const char_T b_u[7] = {'m', 'e', 's', 's', 'a', 'g', 'e'};
  static const char_T u[7] = {'w', 'a', 'r', 'n', 'i', 'n', 'g'};
  emlrtStack st;
  const mxArray *b_y;
  const mxArray *c_y;
  const mxArray *d_y;
  const mxArray *e_y;
  const mxArray *m;
  const mxArray *y;
  st.prev = sp;
  st.tls = sp->tls;
  y = NULL;
  m = emlrtCreateCharArray(2, &iv[0]);
  emlrtInitCharArrayR2013a((emlrtCTX)sp, 7, m, &u[0]);
  emlrtAssign(&y, m);
  b_y = NULL;
  m = emlrtCreateCharArray(2, &iv1[0]);
  emlrtInitCharArrayR2013a((emlrtCTX)sp, 7, m, &b_u[0]);
  emlrtAssign(&b_y, m);
  c_y = NULL;
  m = emlrtCreateCharArray(2, &iv2[0]);
  emlrtInitCharArrayR2013a((emlrtCTX)sp, 41, m, &msgID[0]);
  emlrtAssign(&c_y, m);
  d_y = NULL;
  m = emlrtCreateDoubleScalar(8.0);
  emlrtAssign(&d_y, m);
  e_y = NULL;
  m = emlrtCreateCharArray(2, &iv3[0]);
  emlrtInitCharArrayR2013a((emlrtCTX)sp, 200, m, &varargin_2[0]);
  emlrtAssign(&e_y, m);
  st.site = &y_emlrtRSI;
  b_feval(&st, y, feval(&st, b_y, c_y, d_y, e_y, &emlrtMCI), &b_emlrtMCI);
}

/* End of code generation (warning.c) */
