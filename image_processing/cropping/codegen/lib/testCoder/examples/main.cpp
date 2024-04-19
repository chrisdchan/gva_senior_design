//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// main.cpp
//
// Code generation for function 'main'
//

/*************************************************************************/
/* This automatically generated example C++ main file shows how to call  */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

// Include files
#include "main.h"
#include "string1.h"
#include "testCoder.h"
#include "testCoder_terminate.h"
#include "coder_array.h"

// Function Declarations
static coder::array<char, 2U> argInit_1xUnbounded_char_T();

static char argInit_char_T();

static coder::rtString argInit_rtString();

static void main_testCoder();

// Function Definitions
static coder::array<char, 2U> argInit_1xUnbounded_char_T()
{
  coder::array<char, 2U> result;
  // Set the size of the array.
  // Change this size to the value that the application requires.
  result.set_size(1, 2);
  // Loop over the array to initialize each element.
  for (int idx0{0}; idx0 < 1; idx0++) {
    for (int idx1{0}; idx1 < result.size(1); idx1++) {
      // Set the value of the array element.
      // Change this value to the value that the application requires.
      result[idx1] = argInit_char_T();
    }
  }
  return result;
}

static char argInit_char_T()
{
  return '?';
}

static coder::rtString argInit_rtString()
{
  coder::rtString result;
  coder::array<char, 2U> r;
  // Set the value of each structure field.
  // Change this value to the value that the application requires.
  r = argInit_1xUnbounded_char_T();
  result.init(r);
  return result;
}

static void main_testCoder()
{
  coder::rtString inputImage;
  coder::array<unsigned char, 2U> newImg;
  // Initialize function 'testCoder' input arguments.
  // Initialize function input argument 'inputImage'.
  inputImage = argInit_rtString();
  // Call the entry-point 'testCoder'.
  testCoder(&inputImage, newImg);
}

int main(int, char **)
{
  // The initialize function is being called automatically from your entry-point
  // function. So, a call to initialize is not included here. Invoke the
  // entry-point functions.
  // You can call entry-point functions multiple times.
  main_testCoder();
  // Terminate the application.
  // You do not need to do this more than one time.
  testCoder_terminate();
  return 0;
}

// End of code generation (main.cpp)
