/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_testCoder_api.c
 *
 * Code generation for function '_coder_testCoder_api'
 *
 */

/* Include files */
#include "_coder_testCoder_api.h"
#include "rt_nonfinite.h"
#include "testCoder.h"
#include "testCoder_data.h"
#include "testCoder_emxutil.h"
#include "testCoder_types.h"

/* Variable Definitions */
static emlrtRTEInfo p_emlrtRTEI = {
    1,                      /* lineNo */
    1,                      /* colNo */
    "_coder_testCoder_api", /* fName */
    ""                      /* pName */
};

/* Function Declarations */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, rtString *y);

static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               emxArray_char_T *y);

static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               emxArray_char_T *ret);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *inputImage,
                             const char_T *identifier, rtString *y);

static const mxArray *emlrt_marshallOut(const emxArray_uint8_T *u);

/* Function Definitions */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, rtString *y)
{
  emlrtMsgIdentifier thisId;
  const mxArray *propValues;
  const char_T *propClasses = "coder.internal.string";
  const char_T *propNames = "Value";
  propValues = NULL;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckMcosClass2017a((emlrtCTX)sp, parentId, u, (const char_T *)"string");
  emlrtAssign(&u,
              emlrtConvertInstanceToRedirectTarget(
                  (emlrtCTX)sp, u, 0, (const char_T *)"coder.internal.string"));
  emlrtCheckMcosClass2017a((emlrtCTX)sp, parentId, u,
                           (const char_T *)"coder.internal.string");
  emlrtGetAllProperties((emlrtCTX)sp, u, 0, 1, (const char_T **)&propNames,
                        (const char_T **)&propClasses, &propValues);
  thisId.fIdentifier = "Value";
  c_emlrt_marshallIn(sp, emlrtAlias(propValues), &thisId, y->Value);
  emlrtDestroyArrays(1, &propValues);
  emlrtDestroyArray(&u);
}

static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               emxArray_char_T *y)
{
  d_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               emxArray_char_T *ret)
{
  static const int32_T dims[2] = {1, -1};
  int32_T iv[2];
  int32_T i;
  char_T *ret_data;
  const boolean_T bv[2] = {false, true};
  emlrtCheckVsBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"char",
                            false, 2U, (void *)&dims[0], &bv[0], &iv[0]);
  i = ret->size[0] * ret->size[1];
  ret->size[0] = iv[0];
  ret->size[1] = iv[1];
  emxEnsureCapacity_char_T(sp, ret, i, (emlrtRTEInfo *)NULL);
  ret_data = ret->data;
  emlrtImportArrayR2015b((emlrtCTX)sp, src, &ret_data[0], 1, false);
  emlrtDestroyArray(&src);
}

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *inputImage,
                             const char_T *identifier, rtString *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(sp, emlrtAlias(inputImage), &thisId, y);
  emlrtDestroyArray(&inputImage);
}

static const mxArray *emlrt_marshallOut(const emxArray_uint8_T *u)
{
  static const int32_T iv[2] = {0, 0};
  const mxArray *m;
  const mxArray *y;
  const uint8_T *u_data;
  u_data = u->data;
  y = NULL;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxUINT8_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u_data[0]);
  emlrtSetDimensions((mxArray *)m, &u->size[0], 2);
  emlrtAssign(&y, m);
  return y;
}

void testCoder_api(const mxArray *prhs, const mxArray **plhs)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  emxArray_uint8_T *newImg;
  rtString inputImage;
  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInitStruct_rtString(&st, &inputImage, &p_emlrtRTEI);
  emxInit_uint8_T(&st, &newImg, 2, &p_emlrtRTEI);
  /* Marshall function inputs */
  emlrt_marshallIn(&st, emlrtAliasP(prhs), "inputImage", &inputImage);
  /* Invoke the target function */
  testCoder(&st, &inputImage, newImg);
  /* Marshall function outputs */
  newImg->canFreeData = false;
  *plhs = emlrt_marshallOut(newImg);
  emxFree_uint8_T(&st, &newImg);
  emxFreeStruct_rtString(&st, &inputImage);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/* End of code generation (_coder_testCoder_api.c) */
