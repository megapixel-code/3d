#include "matrix.h"

#include <math.h>
#include <raylib.h>
#include <stddef.h>

float_t **Mat_init(size_t size)
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

void Mat_free(float_t **matrix)
{
   for ( size_t i = 0; i < L_len(matrix); i++ ) {
      L_free(matrix[i]);
   }
   L_free(matrix);
}

void Mat_print(float_t **matrix)
{
   for ( size_t y = 0; y < L_len(matrix); y++ ) {
      for ( size_t x = 0; x < L_len(matrix[y]); x++ ) {
         printf("%0.2f ", matrix[x][y]);
      }
      printf("\n");
   }
}

Vector3 Mat3_vect_mult(float_t **matrix, Vector3 vect)
{
   assert(L_len(matrix) == 3);

   float_t temp[3];
   for ( size_t y = 0; y < 3; y++ ) {
      temp[y] =
         vect.x * matrix[0][y] + vect.y * matrix[1][y] + vect.z * matrix[2][y];
   }

   return (Vector3){ .x = temp[0], .y = temp[1], .z = temp[2] };
}

float_t **Mat4_mult_scalar(float_t **matrix, float_t k)
{
   float_t **out = Mat_init(4);

   for ( size_t y = 0; y < 4; y++ ) {
      for ( size_t x = 0; x < 4; x++ ) {
         out[x][y] = matrix[x][y] * k;
      }
   }

   return out;
}

float_t **Mat4_mult_mat(float_t **matrix, float_t **other)
{
   float_t **out = Mat_init(4);

   float_t res;
   for ( size_t y = 0; y < 4; y++ ) {
      for ( size_t x = 0; x < 4; x++ ) {
         res = 0;

         for ( size_t i = 0; i < 4; i++ ) {
            res += matrix[i][y] * other[x][i];
         }

         out[x][y] = res;
      }
   }

   return out;
}

Vector4 Mat4_mult_vect(float_t **matrix, Vector4 vector)
{
   return (Vector4){ .x = matrix[0][0] * vector.x +
                          matrix[1][0] * vector.y +
                          matrix[2][0] * vector.z +
                          matrix[3][0] * vector.w,
                     .y = matrix[0][1] * vector.x +
                          matrix[1][1] * vector.y +
                          matrix[2][1] * vector.z +
                          matrix[3][1] * vector.w,
                     .z = matrix[0][2] * vector.x +
                          matrix[1][2] * vector.y +
                          matrix[2][2] * vector.z +
                          matrix[3][2] * vector.w,
                     .w = matrix[0][3] * vector.x +
                          matrix[1][3] * vector.y +
                          matrix[2][3] * vector.z +
                          matrix[3][3] * vector.w };
}
