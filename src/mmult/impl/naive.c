/* naive.c
 *
 * Author:
 * Date  :
 *
 *  Description
 */

/* Standard C includes */
#include <stdlib.h>

/* Include common headers */
#include "common/macros.h"
#include "common/types.h"

/* Include application-specific headers */
#include "include/types.h"

/* Naive Implementation */
#pragma GCC push_options
#pragma GCC optimize ("O1")
__attribute__ ((optimize(1)))
void* impl_scalar_naive(void* args)
{
  /* Get the argument struct*/
  args_t* parsed_args = (args_t*)args;

  /* Get all the arguments */
  register       float*       dest     = (      float*)(parsed_args->output);
  register const float*       matrix_A = (const float*)(parsed_args->inputA);
  register const float*       matrix_B = (const float*)(parsed_args->inputB);
  register const int          A_rows   =                parsed_args->A_rows;
  register const int          A_cols   =                parsed_args->A_cols;
  register const int          B_cols   =                parsed_args->B_cols;
  // register       size_t       size     =                parsed_args->size / 4;

  for(int i = 0; i < A_rows; i++) {
    for(int j = 0; j < B_cols; j++) {
      dest[i * B_cols + j] = 0;
      for(int k = 0; k < A_cols; k++) {
        dest[i * B_cols + j] += matrix_A[i * A_cols + k] * matrix_B[k * B_cols + j];
      }
    }
  }

  return NULL;
}
#pragma GCC pop_options
