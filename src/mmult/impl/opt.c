
/* opt.c
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

/* Alternative Implementation */
#pragma GCC push_options
#pragma GCC optimize ("O1")
__attribute__((optimize(1)))
void* impl_scalar_opt(void* args)
{
  /* Get the argument struct */
  args_t* parsed_args = (args_t*)args;

  /* Get all arguments */
  register       float*       dest         = (      float*)(parsed_args->output);
  register const float*       matrix_A     = (const float*)(parsed_args->inputA);
  register const float*       matrix_B     = (const float*)(parsed_args->inputB);
  register const int          A_rows       =                parsed_args->A_rows;
  register const int          A_cols       =                parsed_args->A_cols;
  register const int          B_cols       =                parsed_args->B_cols;
  register const int          dim_blocking =                parsed_args->dim_blocking;

  for (int i = 0; i < A_rows; i++) {
    for (int j = 0; j < B_cols; j++) {
      dest[i * B_cols + j] = 0;
    }
  }

  for (int ii = 0; ii < A_rows; ii += dim_blocking) {
    for (int jj = 0; jj < B_cols; jj += dim_blocking) {
      for (int kk = 0; kk < A_cols; kk += dim_blocking) {
        for (int i = ii; i < ((ii + dim_blocking) < A_rows ? (ii + dim_blocking) : A_rows); i++) {
          for (int j = jj; j < ((jj + dim_blocking) < B_cols ? (jj + dim_blocking) : B_cols); j++) {
            int temp = dest[i * B_cols + j];
            for (int k = kk; k < ((kk + dim_blocking) < A_cols ? (kk + dim_blocking) : A_cols); k++) {
              temp += matrix_A[i * A_cols + k] * matrix_B[k * B_cols + j];
            }
            dest[i * B_cols + j] = temp;
          }
        }
      }
    }
  }

  return NULL;
}
#pragma GCC pop_options
