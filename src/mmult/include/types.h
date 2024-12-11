/* types.h
 *
 * Author: Khalid Al-Hawaj
 * Date  : 13 Nov. 2023
 * 
 * This file contains all required types decalartions.
*/

#ifndef __INCLUDE_TYPES_H_
#define __INCLUDE_TYPES_H_

typedef struct {
  float*   inputA;
  float*   inputB;
  float*   output;

  size_t   size;

  int      A_rows;
  int	   A_cols;
  int	   B_cols;

  int      dim_blocking;    // new block variable

  int      cpu;
  int      nthreads;
} args_t;

#endif //__INCLUDE_TYPES_H_
