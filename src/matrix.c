#include "matrix.h"

#include "list.h"

#include <stdio.h>

float **Mat_init(size_t size)
{
   float_t **matrix = NULL;
   L_ensure_index(matrix, size);

   for ( size_t y = 0; y < size; y++ ) {
      float_t *temp = NULL;
      L_ensure_index(temp, size);

      for ( size_t x = 0; x < size; x++ ) {
         L_append(temp, 0);
      }

      L_append(matrix, temp);
   }

   return matrix;
}

void Mat_free(float **matrix)
{
   for ( size_t i = 0; i < L_len(matrix); i++ ) {
      L_free(matrix[i]);
   }
   L_free(matrix);
}
