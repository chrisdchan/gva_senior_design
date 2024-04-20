/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * testCoder.c
 *
 * Code generation for function 'testCoder'
 *
 */

/* Include files */
#include "testCoder.h"
#include "imgaussfilt.h"
#include "rt_nonfinite.h"
#include "testCoder_data.h"
#include "testCoder_emxutil.h"
#include "testCoder_types.h"
#include "warning.h"
#include "libmwjpegreader.h"
#include "libmwrgb2gray_tbb.h"

/* Variable Definitions */
static emlrtRSInfo emlrtRSI = {
    2,           /* lineNo */
    "testCoder", /* fcnName */
    "C:\\Users\\chris\\bu\\gva_senior_design\\image_"
    "processing\\cropping\\testCoder.m" /* pathName */
};

static emlrtRSInfo b_emlrtRSI = {
    3,           /* lineNo */
    "testCoder", /* fcnName */
    "C:\\Users\\chris\\bu\\gva_senior_design\\image_"
    "processing\\cropping\\testCoder.m" /* pathName */
};

static emlrtRSInfo c_emlrtRSI = {
    4,           /* lineNo */
    "testCoder", /* fcnName */
    "C:\\Users\\chris\\bu\\gva_senior_design\\image_"
    "processing\\cropping\\testCoder.m" /* pathName */
};

static emlrtRSInfo d_emlrtRSI = {
    30,       /* lineNo */
    "imread", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" /* pathName
                                                                            */
};

static emlrtRSInfo e_emlrtRSI = {
    89,       /* lineNo */
    "imread", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" /* pathName
                                                                            */
};

static emlrtRSInfo g_emlrtRSI = {
    149,      /* lineNo */
    "imread", /* fcnName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" /* pathName
                                                                            */
};

static emlrtRTEInfo emlrtRTEI = {
    57,       /* lineNo */
    17,       /* colNo */
    "imread", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" /* pName
                                                                            */
};

static emlrtRTEInfo b_emlrtRTEI = {
    59,       /* lineNo */
    13,       /* colNo */
    "imread", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" /* pName
                                                                            */
};

static emlrtRTEInfo c_emlrtRTEI = {
    62,       /* lineNo */
    13,       /* colNo */
    "imread", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" /* pName
                                                                            */
};

static emlrtRTEInfo d_emlrtRTEI = {
    65,       /* lineNo */
    13,       /* colNo */
    "imread", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" /* pName
                                                                            */
};

static emlrtRTEInfo e_emlrtRTEI = {
    118,      /* lineNo */
    13,       /* colNo */
    "imread", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" /* pName
                                                                            */
};

static emlrtRTEInfo f_emlrtRTEI = {
    120,      /* lineNo */
    9,        /* colNo */
    "imread", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" /* pName
                                                                            */
};

static emlrtRTEInfo g_emlrtRTEI = {
    125,      /* lineNo */
    9,        /* colNo */
    "imread", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" /* pName
                                                                            */
};

static emlrtRTEInfo h_emlrtRTEI = {
    16,         /* lineNo */
    5,          /* colNo */
    "rgb2gray", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\eml\\lib\\matlab\\images\\rgb2gray.m" /* pName
                                                                            */
};

static emlrtDCInfo
    emlrtDCI =
        {
            100,      /* lineNo */
            37,       /* colNo */
            "imread", /* fName */
            "C:\\Program "
            "Files\\MATLAB\\R2022a\\toolbox\\eml\\lib\\matlab\\imagesci\\imread"
            ".m", /* pName */
            4     /* checkKind */
};

static emlrtDCInfo
    b_emlrtDCI =
        {
            98,       /* lineNo */
            37,       /* colNo */
            "imread", /* fName */
            "C:\\Program "
            "Files\\MATLAB\\R2022a\\toolbox\\eml\\lib\\matlab\\imagesci\\imread"
            ".m", /* pName */
            4     /* checkKind */
};

static emlrtRTEInfo k_emlrtRTEI = {
    32,       /* lineNo */
    18,       /* colNo */
    "imread", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" /* pName
                                                                            */
};

static emlrtRTEInfo l_emlrtRTEI = {
    100,      /* lineNo */
    26,       /* colNo */
    "imread", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" /* pName
                                                                            */
};

static emlrtRTEInfo m_emlrtRTEI = {
    98,       /* lineNo */
    26,       /* colNo */
    "imread", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" /* pName
                                                                            */
};

static emlrtRTEInfo n_emlrtRTEI = {
    43,         /* lineNo */
    24,         /* colNo */
    "rgb2gray", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\eml\\lib\\matlab\\images\\rgb2gray.m" /* pName
                                                                            */
};

static emlrtRTEInfo o_emlrtRTEI = {
    98,       /* lineNo */
    5,        /* colNo */
    "imread", /* fName */
    "C:\\Program "
    "Files\\MATLAB\\R2022a\\toolbox\\eml\\lib\\matlab\\imagesci\\imread.m" /* pName
                                                                            */
};

/* Function Definitions */
void testCoder(const emlrtStack *sp, const rtString *inputImage,
               emxArray_uint8_T *newImg)
{
  emlrtStack b_st;
  emlrtStack st;
  emxArray_char_T *fname_tmp;
  emxArray_uint8_T *out;
  real_T outDimsInit[3];
  real_T outDims_data[3];
  real_T libjpegMsgCode;
  int32_T i;
  int32_T outNumDims;
  char_T libjpegWarnBuffer[200];
  char_T *fname_tmp_data;
  int8_T colorSpaceStatus;
  int8_T errWarnType;
  int8_T fileStatus;
  int8_T libjpegReadDone;
  uint8_T *newImg_data;
  uint8_T *out_data;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b((emlrtCTX)sp);
  emxInit_char_T(sp, &fname_tmp, &k_emlrtRTEI);
  covrtLogFcn(&emlrtCoverageInstance, 0U, 0U);
  covrtLogBasicBlock(&emlrtCoverageInstance, 0U, 0U);
  st.site = &emlrtRSI;
  b_st.site = &d_emlrtRSI;
  i = fname_tmp->size[0] * fname_tmp->size[1];
  fname_tmp->size[0] = 1;
  fname_tmp->size[1] = inputImage->Value->size[1] + 1;
  emxEnsureCapacity_char_T(&b_st, fname_tmp, i, &k_emlrtRTEI);
  fname_tmp_data = fname_tmp->data;
  outNumDims = inputImage->Value->size[1];
  for (i = 0; i < outNumDims; i++) {
    fname_tmp_data[i] = inputImage->Value->data[i];
  }
  fname_tmp_data[inputImage->Value->size[1]] = '\x00';
  for (i = 0; i < 200; i++) {
    libjpegWarnBuffer[i] = ' ';
  }
  jpegreader_getimagesize(&fname_tmp_data[0], &outDimsInit[0], &fileStatus,
                          &colorSpaceStatus, &libjpegMsgCode,
                          &libjpegWarnBuffer[0], &errWarnType);
  if (outDimsInit[2] == 3.0) {
    outDims_data[0] = outDimsInit[0];
    outDims_data[1] = outDimsInit[1];
    outDims_data[2] = 3.0;
    outNumDims = 3;
  } else {
    outDims_data[0] = outDimsInit[0];
    outDims_data[1] = outDimsInit[1];
    outNumDims = 2;
  }
  if ((fileStatus == -1) || (colorSpaceStatus == -2) ||
      (colorSpaceStatus == -1) || (errWarnType == -1)) {
    if (fileStatus == -1) {
      emlrtErrorWithMessageIdR2018a(
          &st, &emlrtRTEI, "MATLAB:imagesci:imread:codegenFileOpenError",
          "MATLAB:imagesci:imread:codegenFileOpenError", 3, 4,
          inputImage->Value->size[1], &inputImage->Value->data[0]);
    }
    if (colorSpaceStatus == -2) {
      emlrtErrorWithMessageIdR2018a(&st, &b_emlrtRTEI,
                                    "MATLAB:imagesci:jpg:cmykColorSpace",
                                    "MATLAB:imagesci:jpg:cmykColorSpace", 0);
    }
    if (colorSpaceStatus == -1) {
      emlrtErrorWithMessageIdR2018a(
          &st, &c_emlrtRTEI, "MATLAB:imagesci:jpg:unsupportedJpegColorSpace",
          "MATLAB:imagesci:jpg:unsupportedJpegColorSpace", 0);
    }
    if (errWarnType == -1) {
      emlrtErrorWithMessageIdR2018a(&st, &d_emlrtRTEI,
                                    "MATLAB:imagesci:jpg:unhandledLibraryError",
                                    "MATLAB:imagesci:jpg:unhandledLibraryError",
                                    5, 6, 8.0, 4, 200, &libjpegWarnBuffer[0]);
    }
  }
  if (errWarnType == -2) {
    b_st.site = &e_emlrtRSI;
    warning(&b_st, libjpegWarnBuffer);
  }
  emxInit_uint8_T(&st, &out, 3, &o_emlrtRTEI);
  if (outNumDims == 3) {
    if (!(outDims_data[0] >= 0.0)) {
      emlrtNonNegativeCheckR2012b(outDims_data[0], &b_emlrtDCI, &st);
    }
    if (!(outDims_data[1] >= 0.0)) {
      emlrtNonNegativeCheckR2012b(outDims_data[1], &b_emlrtDCI, &st);
    }
    i = out->size[0] * out->size[1] * out->size[2];
    out->size[0] = (int32_T)outDims_data[0];
    out->size[1] = (int32_T)outDims_data[1];
    out->size[2] = 3;
    emxEnsureCapacity_uint8_T(&st, out, i, &m_emlrtRTEI);
    out_data = out->data;
  } else {
    if (!(outDims_data[0] >= 0.0)) {
      emlrtNonNegativeCheckR2012b(outDims_data[0], &emlrtDCI, &st);
    }
    if (!(outDims_data[1] >= 0.0)) {
      emlrtNonNegativeCheckR2012b(outDims_data[1], &emlrtDCI, &st);
    }
    i = out->size[0] * out->size[1] * out->size[2];
    out->size[0] = (int32_T)outDims_data[0];
    out->size[1] = (int32_T)outDims_data[1];
    out->size[2] = 1;
    emxEnsureCapacity_uint8_T(&st, out, i, &l_emlrtRTEI);
    out_data = out->data;
  }
  jpegreader_uint8(&fname_tmp_data[0], &out_data[0], &outDims_data[0],
                   (real_T)outNumDims, &fileStatus, &libjpegReadDone,
                   &libjpegMsgCode, &libjpegWarnBuffer[0], &errWarnType);
  emxFree_char_T(&st, &fname_tmp);
  if ((fileStatus == -1) || (libjpegReadDone == 0) || (errWarnType == -1)) {
    if (fileStatus == -1) {
      emlrtErrorWithMessageIdR2018a(
          &st, &e_emlrtRTEI, "MATLAB:imagesci:imread:codegenFileOpenError",
          "MATLAB:imagesci:imread:codegenFileOpenError", 3, 4,
          inputImage->Value->size[1], &inputImage->Value->data[0]);
    }
    if (errWarnType == -1) {
      emlrtErrorWithMessageIdR2018a(&st, &f_emlrtRTEI,
                                    "MATLAB:imagesci:jpg:unhandledLibraryError",
                                    "MATLAB:imagesci:jpg:unhandledLibraryError",
                                    5, 6, 8.0, 4, 200, &libjpegWarnBuffer[0]);
    }
    if (libjpegReadDone != 1) {
      emlrtErrorWithMessageIdR2018a(&st, &g_emlrtRTEI,
                                    "MATLAB:imagesci:jpg:unhandledLibraryError",
                                    "MATLAB:imagesci:jpg:unhandledLibraryError",
                                    5, 6, 8.0, 4, 200, &libjpegWarnBuffer[0]);
    }
  }
  if (errWarnType == -2) {
    b_st.site = &g_emlrtRSI;
    warning(&b_st, libjpegWarnBuffer);
  }
  st.site = &b_emlrtRSI;
  if (out->size[2] != 3) {
    emlrtErrorWithMessageIdR2018a(
        &st, &h_emlrtRTEI, "MATLAB:images:rgb2gray:invalidInputSizeRGB",
        "MATLAB:images:rgb2gray:invalidInputSizeRGB", 0);
  }
  i = newImg->size[0] * newImg->size[1];
  newImg->size[0] = out->size[0];
  newImg->size[1] = out->size[1];
  emxEnsureCapacity_uint8_T(&st, newImg, i, &n_emlrtRTEI);
  newImg_data = newImg->data;
  rgb2gray_tbb_uint8(&out_data[0], (real_T)out->size[0] * (real_T)out->size[1],
                     &newImg_data[0], true);
  st.site = &c_emlrtRSI;
  imgaussfilt(&st, newImg);
  emxFree_uint8_T(sp, &out);
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtCTX)sp);
}

/* End of code generation (testCoder.c) */
