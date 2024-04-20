//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// string1.cpp
//
// Code generation for function 'string1'
//

// Include files
#include "string1.h"
#include "coder_array.h"

// Function Definitions
namespace coder {
void rtString::init(const ::coder::array<char, 2U> &b_Value)
{
  int loop_ub;
  Value.set_size(1, b_Value.size(1));
  loop_ub = b_Value.size(1);
  for (int i{0}; i < loop_ub; i++) {
    Value[i] = b_Value[i];
  }
}

rtString::rtString() = default;

rtString::~rtString() = default;

} // namespace coder

// End of code generation (string1.cpp)
