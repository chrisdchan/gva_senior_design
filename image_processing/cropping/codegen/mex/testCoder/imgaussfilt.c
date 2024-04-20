/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * imgaussfilt.c
 *
 * Code generation for function 'imgaussfilt'
 *
 */

/* Include files */
#include "imgaussfilt.h"
#include "rt_nonfinite.h"
#include "testCoder_data.h"
#include "testCoder_emxutil.h"
#include "testCoder_types.h"
#include "libmwimfilter.h"
#include "libmwippfilter.h"

/* Variable Definitions */
static emlrtRSInfo i_emlrtRSI = {
    14,            /* lineNo */
    "imgaussfilt", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\imgaussfilt.m" /* pathName
                                                                          */
};

static emlrtRSInfo j_emlrtRSI = {
    23,                      /* lineNo */
    "spatialGaussianFilter", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\imgaussfilt.m" /* pathName
                                                                          */
};

static emlrtRSInfo k_emlrtRSI = {
    24,                      /* lineNo */
    "spatialGaussianFilter", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\imgaussfilt.m" /* pathName
                                                                          */
};

static emlrtRSInfo l_emlrtRSI = {
    106,        /* lineNo */
    "imfilter", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\imfilter.m" /* pathName
                                                                       */
};

static emlrtRSInfo m_emlrtRSI = {
    110,        /* lineNo */
    "imfilter", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\imfilter.m" /* pathName
                                                                       */
};

static emlrtRSInfo n_emlrtRSI = {
    854,        /* lineNo */
    "padImage", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\imfilter.m" /* pathName
                                                                       */
};

static emlrtRSInfo o_emlrtRSI = {
    20,         /* lineNo */
    "padarray", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\padarray.m" /* pathName
                                                                       */
};

static emlrtRSInfo p_emlrtRSI = {
    66,         /* lineNo */
    "padarray", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\padarray.m" /* pathName
                                                                       */
};

static emlrtRSInfo q_emlrtRSI = {
    80,         /* lineNo */
    "padarray", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\padarray.m" /* pathName
                                                                       */
};

static emlrtRSInfo s_emlrtRSI = {
    28,       /* lineNo */
    "repmat", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\eml\\lib\\matlab\\elmat\\repmat.m" /* pathName
                                                                         */
};

static emlrtRSInfo t_emlrtRSI = {
    733,                 /* lineNo */
    "getPaddingIndices", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\padarray.m" /* pathName
                                                                       */
};

static emlrtRSInfo u_emlrtRSI = {
    928,                 /* lineNo */
    "filterPartOrWhole", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\imfilter.m" /* pathName
                                                                       */
};

static emlrtRSInfo v_emlrtRSI = {
    1002,           /* lineNo */
    "imfiltercore", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\imfilter.m" /* pathName
                                                                       */
};

static emlrtECInfo emlrtECI = {
    -1,             /* nDims */
    843,            /* lineNo */
    9,              /* colNo */
    "ReplicatePad", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\padarray.m" /* pName
                                                                       */
};

static emlrtBCInfo emlrtBCI = {
    -1,             /* iFirst */
    -1,             /* iLast */
    843,            /* lineNo */
    16,             /* colNo */
    "",             /* aName */
    "ReplicatePad", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\padarray.m", /* pName
                                                                        */
    0 /* checkKind */
};

static emlrtRTEInfo i_emlrtRTEI = {
    49,                   /* lineNo */
    19,                   /* colNo */
    "assertValidSizeArg", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\assertValidSizeArg.m" /* pName */
};

static emlrtRTEInfo j_emlrtRTEI = {
    64,                   /* lineNo */
    15,                   /* colNo */
    "assertValidSizeArg", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\assertValidSizeArg.m" /* pName */
};

static emlrtDCInfo c_emlrtDCI = {
    827,            /* lineNo */
    33,             /* colNo */
    "ReplicatePad", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\padarray.m", /* pName
                                                                        */
    1 /* checkKind */
};

static emlrtBCInfo b_emlrtBCI = {
    -1,         /* iFirst */
    -1,         /* iLast */
    100,        /* lineNo */
    32,         /* colNo */
    "",         /* aName */
    "padarray", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\padarray.m", /* pName
                                                                        */
    0 /* checkKind */
};

static emlrtBCInfo c_emlrtBCI = {
    -1,         /* iFirst */
    -1,         /* iLast */
    100,        /* lineNo */
    37,         /* colNo */
    "",         /* aName */
    "padarray", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\padarray.m", /* pName
                                                                        */
    0 /* checkKind */
};

static emlrtBCInfo d_emlrtBCI = {
    -1,         /* iFirst */
    -1,         /* iLast */
    100,        /* lineNo */
    42,         /* colNo */
    "",         /* aName */
    "padarray", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\padarray.m", /* pName
                                                                        */
    0 /* checkKind */
};

static emlrtBCInfo e_emlrtBCI = {
    -1,         /* iFirst */
    -1,         /* iLast */
    100,        /* lineNo */
    47,         /* colNo */
    "",         /* aName */
    "padarray", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\padarray.m", /* pName
                                                                        */
    0 /* checkKind */
};

static emlrtBCInfo f_emlrtBCI = {
    -1,         /* iFirst */
    -1,         /* iLast */
    100,        /* lineNo */
    23,         /* colNo */
    "",         /* aName */
    "padarray", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\padarray.m", /* pName
                                                                        */
    0 /* checkKind */
};

static emlrtBCInfo g_emlrtBCI = {
    -1,         /* iFirst */
    -1,         /* iLast */
    100,        /* lineNo */
    25,         /* colNo */
    "",         /* aName */
    "padarray", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\padarray.m", /* pName
                                                                        */
    0 /* checkKind */
};

static emlrtDCInfo d_emlrtDCI = {
    83,         /* lineNo */
    56,         /* colNo */
    "padarray", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\padarray.m", /* pName
                                                                        */
    1 /* checkKind */
};

static emlrtRTEInfo q_emlrtRTEI = {
    827,        /* lineNo */
    27,         /* colNo */
    "padarray", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\padarray.m" /* pName
                                                                       */
};

static emlrtRTEInfo r_emlrtRTEI = {
    106,        /* lineNo */
    9,          /* colNo */
    "imfilter", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\imfilter.m" /* pName
                                                                       */
};

static emlrtRTEInfo s_emlrtRTEI =
    {
        28,      /* lineNo */
        9,       /* colNo */
        "colon", /* fName */
        "C:\\Program "
        "Files\\MATLAB\\R2022a\\toolbox\\eml\\lib\\matlab\\ops\\colon.m" /* pName
                                                                          */
};

static emlrtRTEInfo t_emlrtRTEI = {
    842,        /* lineNo */
    9,          /* colNo */
    "padarray", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\padarray.m" /* pName
                                                                       */
};

static emlrtRTEInfo u_emlrtRTEI = {
    1024,       /* lineNo */
    26,         /* colNo */
    "imfilter", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\imfilter.m" /* pName
                                                                       */
};

static emlrtRTEInfo v_emlrtRTEI = {
    83,         /* lineNo */
    28,         /* colNo */
    "padarray", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\padarray.m" /* pName
                                                                       */
};

static emlrtRTEInfo w_emlrtRTEI = {
    59,         /* lineNo */
    9,          /* colNo */
    "imfilter", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\imfilter.m" /* pName
                                                                       */
};

static emlrtRTEInfo x_emlrtRTEI = {
    80,         /* lineNo */
    5,          /* colNo */
    "padarray", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\padarray.m" /* pName
                                                                       */
};

static emlrtRTEInfo y_emlrtRTEI = {
    836,        /* lineNo */
    9,          /* colNo */
    "padarray", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\padarray.m" /* pName
                                                                       */
};

static emlrtRTEInfo ab_emlrtRTEI = {
    842,        /* lineNo */
    30,         /* colNo */
    "padarray", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\images\\images\\eml\\padarray.m" /* pName
                                                                       */
};

/* Function Definitions */
void imgaussfilt(const emlrtStack *sp, emxArray_uint8_T *A)
{
  static const real_T kernel[169] = {
      0.00034388074002273089, 0.00063359251209252722, 0.0010446174516432778,
      0.0015411665540596389,  0.0020346369704453988,  0.0024036395714370842,
      0.0025409540793697454,  0.0024036395714370842,  0.0020346369704453988,
      0.0015411665540596389,  0.0010446174516432778,  0.00063359251209252722,
      0.00034388074002273089, 0.00063359251209252722, 0.0011673799217518947,
      0.0019246841079806,     0.0028395646364931175,  0.0037487727553907673,
      0.0044286517300479228,  0.00468165061571408,    0.0044286517300479228,
      0.0037487727553907673,  0.0028395646364931175,  0.0019246841079806,
      0.0011673799217518947,  0.00063359251209252722, 0.0010446174516432778,
      0.0019246841079806,     0.0031732676282061173,  0.00468165061571408,
      0.0061806813808338865,  0.0073016123078529322,  0.0077187369521141552,
      0.0073016123078529322,  0.0061806813808338865,  0.00468165061571408,
      0.0031732676282061173,  0.0019246841079806,     0.0010446174516432778,
      0.0015411665540596389,  0.0028395646364931175,  0.00468165061571408,
      0.0069070293008996614,  0.009118610272550896,   0.010772365196341647,
      0.011387766125742308,   0.010772365196341647,   0.009118610272550896,
      0.0069070293008996614,  0.00468165061571408,    0.0028395646364931175,
      0.0015411665540596389,  0.0020346369704453988,  0.0037487727553907673,
      0.0061806813808338865,  0.009118610272550896,   0.012038323522362981,
      0.01422159884658895,    0.015034046715579355,   0.01422159884658895,
      0.012038323522362981,   0.009118610272550896,   0.0061806813808338865,
      0.0037487727553907673,  0.0020346369704453988,  0.0024036395714370842,
      0.0044286517300479228,  0.0073016123078529322,  0.010772365196341647,
      0.01422159884658895,    0.016800833885015916,   0.017760627634958236,
      0.016800833885015916,   0.01422159884658895,    0.010772365196341647,
      0.0073016123078529322,  0.0044286517300479228,  0.0024036395714370842,
      0.0025409540793697454,  0.00468165061571408,    0.0077187369521141552,
      0.011387766125742308,   0.015034046715579355,   0.017760627634958236,
      0.018775252237269731,   0.017760627634958236,   0.015034046715579355,
      0.011387766125742308,   0.0077187369521141552,  0.00468165061571408,
      0.0025409540793697454,  0.0024036395714370842,  0.0044286517300479228,
      0.0073016123078529322,  0.010772365196341647,   0.01422159884658895,
      0.016800833885015916,   0.017760627634958236,   0.016800833885015916,
      0.01422159884658895,    0.010772365196341647,   0.0073016123078529322,
      0.0044286517300479228,  0.0024036395714370842,  0.0020346369704453988,
      0.0037487727553907673,  0.0061806813808338865,  0.009118610272550896,
      0.012038323522362981,   0.01422159884658895,    0.015034046715579355,
      0.01422159884658895,    0.012038323522362981,   0.009118610272550896,
      0.0061806813808338865,  0.0037487727553907673,  0.0020346369704453988,
      0.0015411665540596389,  0.0028395646364931175,  0.00468165061571408,
      0.0069070293008996614,  0.009118610272550896,   0.010772365196341647,
      0.011387766125742308,   0.010772365196341647,   0.009118610272550896,
      0.0069070293008996614,  0.00468165061571408,    0.0028395646364931175,
      0.0015411665540596389,  0.0010446174516432778,  0.0019246841079806,
      0.0031732676282061173,  0.00468165061571408,    0.0061806813808338865,
      0.0073016123078529322,  0.0077187369521141552,  0.0073016123078529322,
      0.0061806813808338865,  0.00468165061571408,    0.0031732676282061173,
      0.0019246841079806,     0.0010446174516432778,  0.00063359251209252722,
      0.0011673799217518947,  0.0019246841079806,     0.0028395646364931175,
      0.0037487727553907673,  0.0044286517300479228,  0.00468165061571408,
      0.0044286517300479228,  0.0037487727553907673,  0.0028395646364931175,
      0.0019246841079806,     0.0011673799217518947,  0.00063359251209252722,
      0.00034388074002273089, 0.00063359251209252722, 0.0010446174516432778,
      0.0015411665540596389,  0.0020346369704453988,  0.0024036395714370842,
      0.0025409540793697454,  0.0024036395714370842,  0.0020346369704453988,
      0.0015411665540596389,  0.0010446174516432778,  0.00063359251209252722,
      0.00034388074002273089};
  static const real_T nonZeroKernel[169] = {
      0.00034388074002273089, 0.00063359251209252722, 0.0010446174516432778,
      0.0015411665540596389,  0.0020346369704453988,  0.0024036395714370842,
      0.0025409540793697454,  0.0024036395714370842,  0.0020346369704453988,
      0.0015411665540596389,  0.0010446174516432778,  0.00063359251209252722,
      0.00034388074002273089, 0.00063359251209252722, 0.0011673799217518947,
      0.0019246841079806,     0.0028395646364931175,  0.0037487727553907673,
      0.0044286517300479228,  0.00468165061571408,    0.0044286517300479228,
      0.0037487727553907673,  0.0028395646364931175,  0.0019246841079806,
      0.0011673799217518947,  0.00063359251209252722, 0.0010446174516432778,
      0.0019246841079806,     0.0031732676282061173,  0.00468165061571408,
      0.0061806813808338865,  0.0073016123078529322,  0.0077187369521141552,
      0.0073016123078529322,  0.0061806813808338865,  0.00468165061571408,
      0.0031732676282061173,  0.0019246841079806,     0.0010446174516432778,
      0.0015411665540596389,  0.0028395646364931175,  0.00468165061571408,
      0.0069070293008996614,  0.009118610272550896,   0.010772365196341647,
      0.011387766125742308,   0.010772365196341647,   0.009118610272550896,
      0.0069070293008996614,  0.00468165061571408,    0.0028395646364931175,
      0.0015411665540596389,  0.0020346369704453988,  0.0037487727553907673,
      0.0061806813808338865,  0.009118610272550896,   0.012038323522362981,
      0.01422159884658895,    0.015034046715579355,   0.01422159884658895,
      0.012038323522362981,   0.009118610272550896,   0.0061806813808338865,
      0.0037487727553907673,  0.0020346369704453988,  0.0024036395714370842,
      0.0044286517300479228,  0.0073016123078529322,  0.010772365196341647,
      0.01422159884658895,    0.016800833885015916,   0.017760627634958236,
      0.016800833885015916,   0.01422159884658895,    0.010772365196341647,
      0.0073016123078529322,  0.0044286517300479228,  0.0024036395714370842,
      0.0025409540793697454,  0.00468165061571408,    0.0077187369521141552,
      0.011387766125742308,   0.015034046715579355,   0.017760627634958236,
      0.018775252237269731,   0.017760627634958236,   0.015034046715579355,
      0.011387766125742308,   0.0077187369521141552,  0.00468165061571408,
      0.0025409540793697454,  0.0024036395714370842,  0.0044286517300479228,
      0.0073016123078529322,  0.010772365196341647,   0.01422159884658895,
      0.016800833885015916,   0.017760627634958236,   0.016800833885015916,
      0.01422159884658895,    0.010772365196341647,   0.0073016123078529322,
      0.0044286517300479228,  0.0024036395714370842,  0.0020346369704453988,
      0.0037487727553907673,  0.0061806813808338865,  0.009118610272550896,
      0.012038323522362981,   0.01422159884658895,    0.015034046715579355,
      0.01422159884658895,    0.012038323522362981,   0.009118610272550896,
      0.0061806813808338865,  0.0037487727553907673,  0.0020346369704453988,
      0.0015411665540596389,  0.0028395646364931175,  0.00468165061571408,
      0.0069070293008996614,  0.009118610272550896,   0.010772365196341647,
      0.011387766125742308,   0.010772365196341647,   0.009118610272550896,
      0.0069070293008996614,  0.00468165061571408,    0.0028395646364931175,
      0.0015411665540596389,  0.0010446174516432778,  0.0019246841079806,
      0.0031732676282061173,  0.00468165061571408,    0.0061806813808338865,
      0.0073016123078529322,  0.0077187369521141552,  0.0073016123078529322,
      0.0061806813808338865,  0.00468165061571408,    0.0031732676282061173,
      0.0019246841079806,     0.0010446174516432778,  0.00063359251209252722,
      0.0011673799217518947,  0.0019246841079806,     0.0028395646364931175,
      0.0037487727553907673,  0.0044286517300479228,  0.00468165061571408,
      0.0044286517300479228,  0.0037487727553907673,  0.0028395646364931175,
      0.0019246841079806,     0.0011673799217518947,  0.00063359251209252722,
      0.00034388074002273089, 0.00063359251209252722, 0.0010446174516432778,
      0.0015411665540596389,  0.0020346369704453988,  0.0024036395714370842,
      0.0025409540793697454,  0.0024036395714370842,  0.0020346369704453988,
      0.0015411665540596389,  0.0010446174516432778,  0.00063359251209252722,
      0.00034388074002273089};
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack st;
  emxArray_int32_T *idxA;
  emxArray_uint32_T *idxDir;
  emxArray_uint32_T *y;
  emxArray_uint8_T *a;
  real_T outSizeT[2];
  real_T padSize[2];
  int32_T b_i;
  int32_T i;
  int32_T j;
  int32_T *idxA_data;
  uint32_T *idxDir_data;
  uint32_T *y_data;
  uint8_T *A_data;
  uint8_T *a_data;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  e_st.prev = &d_st;
  e_st.tls = d_st.tls;
  f_st.prev = &e_st;
  f_st.tls = e_st.tls;
  A_data = A->data;
  emlrtHeapReferenceStackEnterFcnR2012b((emlrtCTX)sp);
  st.site = &i_emlrtRSI;
  b_st.site = &j_emlrtRSI;
  b_st.site = &k_emlrtRSI;
  outSizeT[0] = A->size[0];
  padSize[0] = 6.0;
  outSizeT[1] = A->size[1];
  padSize[1] = 6.0;
  if ((A->size[0] != 0) && (A->size[1] != 0)) {
    real_T padSizeT[2];
    real_T sizeA[2];
    boolean_T tooBig;
    c_st.site = &l_emlrtRSI;
    d_st.site = &n_emlrtRSI;
    e_st.site = &o_emlrtRSI;
    emxInit_uint8_T(&d_st, &a, 2, &w_emlrtRTEI);
    if ((A->size[0] == 0) || (A->size[1] == 0)) {
      int32_T loop_ub;
      boolean_T exitg1;
      sizeA[0] = (real_T)A->size[0] + 12.0;
      sizeA[1] = (real_T)A->size[1] + 12.0;
      e_st.site = &p_emlrtRSI;
      padSizeT[0] = sizeA[0];
      padSizeT[1] = sizeA[1];
      f_st.site = &s_emlrtRSI;
      loop_ub = 0;
      exitg1 = false;
      while ((!exitg1) && (loop_ub < 2)) {
        if ((uint32_T)padSizeT[loop_ub] > 2147483647U) {
          emlrtErrorWithMessageIdR2018a(
              &f_st, &i_emlrtRTEI,
              "Coder:toolbox:eml_assert_valid_size_arg_invalidSizeVector",
              "Coder:toolbox:eml_assert_valid_size_arg_invalidSizeVector", 4,
              12, MIN_int32_T, 12, MAX_int32_T);
        } else {
          loop_ub++;
        }
      }
      if (!(sizeA[0] * sizeA[1] <= 2.147483647E+9)) {
        emlrtErrorWithMessageIdR2018a(&f_st, &j_emlrtRTEI,
                                      "Coder:MATLAB:pmaxsize",
                                      "Coder:MATLAB:pmaxsize", 0);
      }
      i = a->size[0] * a->size[1];
      a->size[0] = (int32_T)sizeA[0];
      a->size[1] = (int32_T)sizeA[1];
      emxEnsureCapacity_uint8_T(&e_st, a, i, &r_emlrtRTEI);
      a_data = a->data;
      loop_ub = (int32_T)sizeA[0] * (int32_T)sizeA[1];
      for (i = 0; i < loop_ub; i++) {
        a_data[i] = 0U;
      }
    } else {
      real_T d;
      real_T d1;
      int32_T loop_ub;
      uint32_T maxval;
      sizeA[0] = A->size[0];
      sizeA[1] = A->size[1];
      e_st.site = &q_emlrtRSI;
      f_st.site = &t_emlrtRSI;
      if ((uint32_T)sizeA[0] + 12U < (uint32_T)sizeA[1] + 12U) {
        maxval = (uint32_T)sizeA[1] + 12U;
      } else {
        maxval = (uint32_T)sizeA[0] + 12U;
      }
      if ((real_T)maxval != (int32_T)maxval) {
        emlrtIntegerCheckR2012b(maxval, &c_emlrtDCI, &f_st);
      }
      emxInit_int32_T(&f_st, &idxA, &x_emlrtRTEI);
      emxInit_uint32_T(&f_st, &y, &ab_emlrtRTEI);
      y_data = y->data;
      i = idxA->size[0] * idxA->size[1];
      idxA->size[0] = (int32_T)maxval;
      idxA->size[1] = 2;
      emxEnsureCapacity_int32_T(&f_st, idxA, i, &q_emlrtRTEI);
      idxA_data = idxA->data;
      if (sizeA[0] < 1.0) {
        y->size[0] = 1;
        y->size[1] = 0;
      } else {
        i = y->size[0] * y->size[1];
        y->size[0] = 1;
        loop_ub = (int32_T)sizeA[0];
        y->size[1] = loop_ub;
        emxEnsureCapacity_uint32_T(&f_st, y, i, &s_emlrtRTEI);
        y_data = y->data;
        loop_ub--;
        for (i = 0; i <= loop_ub; i++) {
          y_data[i] = i + 1U;
        }
      }
      emxInit_uint32_T(&f_st, &idxDir, &y_emlrtRTEI);
      i = idxDir->size[0] * idxDir->size[1];
      idxDir->size[0] = 1;
      idxDir->size[1] = y->size[1] + 12;
      emxEnsureCapacity_uint32_T(&f_st, idxDir, i, &t_emlrtRTEI);
      idxDir_data = idxDir->data;
      for (i = 0; i < 6; i++) {
        idxDir_data[i] = 1U;
      }
      loop_ub = y->size[1];
      for (i = 0; i < loop_ub; i++) {
        idxDir_data[i + 6] = y_data[i];
      }
      for (i = 0; i < 6; i++) {
        idxDir_data[(i + y->size[1]) + 6] = (uint32_T)sizeA[0];
      }
      if ((idxDir->size[1] < 1) || (idxDir->size[1] > (int32_T)maxval)) {
        emlrtDynamicBoundsCheckR2012b(idxDir->size[1], 1, (int32_T)maxval,
                                      &emlrtBCI, &f_st);
      }
      emlrtSubAssignSizeCheckR2012b(&idxDir->size[1], 1, &idxDir->size[0], 2,
                                    &emlrtECI, &f_st);
      loop_ub = idxDir->size[1];
      for (i = 0; i < loop_ub; i++) {
        idxA_data[i] = (int32_T)idxDir_data[i];
      }
      if (sizeA[1] < 1.0) {
        y->size[0] = 1;
        y->size[1] = 0;
      } else {
        i = y->size[0] * y->size[1];
        y->size[0] = 1;
        loop_ub = (int32_T)sizeA[1];
        y->size[1] = loop_ub;
        emxEnsureCapacity_uint32_T(&f_st, y, i, &s_emlrtRTEI);
        y_data = y->data;
        loop_ub--;
        for (i = 0; i <= loop_ub; i++) {
          y_data[i] = i + 1U;
        }
      }
      i = idxDir->size[0] * idxDir->size[1];
      idxDir->size[0] = 1;
      idxDir->size[1] = y->size[1] + 12;
      emxEnsureCapacity_uint32_T(&f_st, idxDir, i, &t_emlrtRTEI);
      idxDir_data = idxDir->data;
      for (i = 0; i < 6; i++) {
        idxDir_data[i] = 1U;
      }
      loop_ub = y->size[1];
      for (i = 0; i < loop_ub; i++) {
        idxDir_data[i + 6] = y_data[i];
      }
      for (i = 0; i < 6; i++) {
        idxDir_data[(i + y->size[1]) + 6] = (uint32_T)sizeA[1];
      }
      emxFree_uint32_T(&f_st, &y);
      if ((idxDir->size[1] < 1) || (idxDir->size[1] > idxA->size[0])) {
        emlrtDynamicBoundsCheckR2012b(idxDir->size[1], 1, idxA->size[0],
                                      &emlrtBCI, &f_st);
      }
      emlrtSubAssignSizeCheckR2012b(&idxDir->size[1], 1, &idxDir->size[0], 2,
                                    &emlrtECI, &f_st);
      loop_ub = idxDir->size[1];
      for (i = 0; i < loop_ub; i++) {
        idxA_data[i + idxA->size[0]] = (int32_T)idxDir_data[i];
      }
      emxFree_uint32_T(&f_st, &idxDir);
      d = (real_T)A->size[0] + 12.0;
      if (d != (int32_T)d) {
        emlrtIntegerCheckR2012b(d, &d_emlrtDCI, &d_st);
      }
      d1 = (real_T)A->size[1] + 12.0;
      if (d1 != (int32_T)d1) {
        emlrtIntegerCheckR2012b(d1, &d_emlrtDCI, &d_st);
      }
      i = a->size[0] * a->size[1];
      a->size[0] = (int32_T)d;
      loop_ub = (int32_T)d1;
      a->size[1] = (int32_T)d1;
      emxEnsureCapacity_uint8_T(&d_st, a, i, &v_emlrtRTEI);
      a_data = a->data;
      for (j = 0; j < loop_ub; j++) {
        i = a->size[0];
        for (b_i = 0; b_i < i; b_i++) {
          int32_T i1;
          int32_T i2;
          int32_T i3;
          i1 = A->size[0];
          if (b_i + 1 > idxA->size[0]) {
            emlrtDynamicBoundsCheckR2012b(b_i + 1, 1, idxA->size[0],
                                          &c_emlrtBCI, &d_st);
          }
          i2 = idxA_data[b_i];
          if ((i2 < 1) || (i2 > i1)) {
            emlrtDynamicBoundsCheckR2012b(i2, 1, i1, &b_emlrtBCI, &d_st);
          }
          i1 = A->size[1];
          if ((j + 1 < 1) || (j + 1 > idxA->size[0])) {
            emlrtDynamicBoundsCheckR2012b(j + 1, 1, idxA->size[0], &e_emlrtBCI,
                                          &d_st);
          }
          i3 = idxA_data[j + idxA->size[0]];
          if ((i3 < 1) || (i3 > i1)) {
            emlrtDynamicBoundsCheckR2012b(i3, 1, i1, &d_emlrtBCI, &d_st);
          }
          if (b_i + 1 > a->size[0]) {
            emlrtDynamicBoundsCheckR2012b(b_i + 1, 1, a->size[0], &f_emlrtBCI,
                                          &d_st);
          }
          if ((j + 1 < 1) || (j + 1 > a->size[1])) {
            emlrtDynamicBoundsCheckR2012b(j + 1, 1, a->size[1], &g_emlrtBCI,
                                          &d_st);
          }
          a_data[b_i + a->size[0] * j] =
              A_data[(i2 + A->size[0] * (i3 - 1)) - 1];
        }
      }
      emxFree_int32_T(&d_st, &idxA);
    }
    c_st.site = &m_emlrtRSI;
    d_st.site = &u_emlrtRSI;
    tooBig = true;
    if ((outSizeT[0] <= 65500.0) || (!(outSizeT[1] > 65500.0))) {
      tooBig = false;
    }
    tooBig = !tooBig;
    e_st.site = &v_emlrtRSI;
    i = A->size[0] * A->size[1];
    A->size[0] = (int32_T)outSizeT[0];
    A->size[1] = (int32_T)outSizeT[1];
    emxEnsureCapacity_uint8_T(&e_st, A, i, &u_emlrtRTEI);
    A_data = A->data;
    if (tooBig) {
      padSizeT[0] = a->size[0];
      sizeA[0] = 13.0;
      padSizeT[1] = a->size[1];
      sizeA[1] = 13.0;
      ippfilter_uint8(&a_data[0], &A_data[0], &outSizeT[0], 2.0, &padSizeT[0],
                      &kernel[0], &sizeA[0], false);
    } else {
      boolean_T conn[169];
      padSizeT[0] = a->size[0];
      padSizeT[1] = a->size[1];
      for (i = 0; i < 169; i++) {
        conn[i] = true;
      }
      sizeA[0] = 13.0;
      sizeA[1] = 13.0;
      imfilter_uint8(&a_data[0], &A_data[0], 2.0, &outSizeT[0], 2.0,
                     &padSizeT[0], &nonZeroKernel[0], 169.0, &conn[0], 2.0,
                     &sizeA[0], &padSize[0], 2.0, true, false);
    }
    emxFree_uint8_T(&e_st, &a);
  }
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtCTX)sp);
}

/* End of code generation (imgaussfilt.c) */
