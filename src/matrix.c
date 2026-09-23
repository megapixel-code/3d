#include "matrix.h"

#include "list.h"

#include <math.h>
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>

float_t **Mat_init(size_t size)
{
   float_t **matrix = NULL;
   L_ensure_index(matrix, size - 1);

   for ( size_t y = 0; y < size; y++ ) {
      float_t *temp = NULL;
      L_ensure_index(temp, size - 1);

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
         if ( matrix[x][y] >= 0 ) {
            printf(" ");
         }
         printf("%0.2f ", matrix[x][y]);
      }
      printf("\n");
   }
}

/* 0 1 2 |       |       |     |
 * 3 4 5 | x = 0 | y = 0 | ==> | 4 5
 * 6 7 8 |       |       |     | 7 8
 * */
float **Mat_sub_mat(float **matrix, size_t x, size_t y)
{
   float **out = NULL;
   L_ensure_index(out, L_len(matrix) - 1);

   for ( size_t cur_x = 0; cur_x < L_len(matrix); cur_x++ ) {
      if ( cur_x == x ) {
         continue;
      }
      float *col = NULL;
      L_ensure_index(col, L_len(matrix[cur_x]) - 1);
      L_append(out, col);
      for ( size_t cur_y = 0; cur_y < L_len(matrix[cur_x]); cur_y++ ) {
         if ( cur_y == y ) {
            continue;
         }
         L_append(col, matrix[cur_x][cur_y]);
      }
   }

   return out;
}

float_t Mat_det(float_t **matrix)
{
   size_t len = L_len(matrix);

   switch ( len ) {
      case 1: {
         return matrix[0][0];
      } break;
      case 2: {
         return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
      } break;
      case 3: {
         float_t result = 0;
         float_t temp_pos;
         float_t temp_neg;

         for ( size_t x = 0; x < len; x++ ) {
            temp_pos = 1;
            temp_neg = 1;
            for ( size_t y = 0; y < len; y++ ) {
               temp_pos *= matrix[(x + y) % len][y];
               temp_neg *= matrix[(len + x - y) % len][y];
            }
            result += temp_pos - temp_neg;
         }

         return result;
      } break;
      case 4: {
         float_t result = 0;

         float_t **sub_mat;

         int sign = 1;
         for ( size_t y = 0; y < L_len(matrix); y++ ) {
            //
            sub_mat = Mat_sub_mat(matrix, 0, y);
            result += sign * matrix[0][y] * Mat_det(sub_mat);
            Mat_free(sub_mat);
            sign *= -1;
         }

         return result;
      } break;
      default: {
         fprintf(stderr,
                 "Error: %s: cannot compute det of matrix size %zu\n",
                 __func__,
                 len);
      } break;
   }
   return 0;
}

float_t **Mat_adjugate(float_t **matrix)
{
   float_t **result = Mat_init(L_len(matrix));

   float_t **temp;
   for ( size_t y = 0; y < L_len(matrix); y++ ) {
      for ( size_t x = 0; x < L_len(matrix[y]); x++ ) {
         temp         = Mat_sub_mat(matrix, y, x);
         result[x][y] = pow(-1, x + y) * Mat_det(temp);
         Mat_free(temp);
      }
   }

   return result;
}

float_t **Mat_inverse(float_t **matrix)
{
   float_t **adjugate = Mat_adjugate(matrix);
   float_t   det      = Mat_det(matrix);
   float_t **result   = Mat4_mult(adjugate, 1 / det);
   Mat_free(adjugate);

   return result;
}

Vector3 Mat3_mult_vect(float_t **matrix, Vector3 vect)
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

float_t **
Mat_get_model(Vector3 translation, double_t rx, double_t ry, double_t rz)
{
   float_t **result = Mat_init(4);
   for ( size_t i = 0; i < L_len(result); i++ ) {
      result[i][i] = 1;
   }
   result[3][0] = translation.x;
   result[3][1] = translation.y;
   result[3][2] = translation.z;

   float_t **temp;
   if ( rx != 0 ) {
      result[0][0] = 1;
      result[1][1] = cos(rx);
      result[2][2] = cos(rx);
      result[1][2] = sin(rx);
      result[2][1] = -sin(rx);

      temp = Mat4_mult(
         result,
         Mat_get_model((Vector3){ .x = 0, .y = 0, .z = 0 }, 0, ry, rz));

      Mat_free(result);
      result = temp;
   } else if ( ry != 0 ) {
      result[0][0] = cos(ry);
      result[2][2] = cos(ry);
      result[1][1] = 1;
      result[2][0] = sin(ry);
      result[0][2] = -sin(ry);

      temp = Mat4_mult(
         result,
         Mat_get_model((Vector3){ .x = 0, .y = 0, .z = 0 }, rx, 0, rz));

      Mat_free(result);
      result = temp;
   } else if ( rz != 0 ) {
      result[0][0] = cos(rz);
      result[1][0] = -sin(rz);
      result[0][1] = sin(rz);
      result[1][1] = cos(rz);
      result[2][2] = 1;

      temp = Mat4_mult(
         result,
         Mat_get_model((Vector3){ .x = 0, .y = 0, .z = 0 }, rx, ry, 0));

      Mat_free(result);
      result = temp;
   }

   return result;
}

float_t **Mat_get_projection(float_t l,
                             float_t r,
                             float_t t,
                             float_t b,
                             float_t n,
                             float_t f)
{
   float_t **result = Mat_init(4);

   result[0][0] = 2 / (r - l);
   result[3][0] = -(r + l) / (r - l);

   result[1][1] = 2 / (t - b);
   result[3][1] = -(t + b) / (t - b);

   result[2][2] = -2 / (f - n);
   result[3][2] = -(f + n) / (f - n);

   result[3][3] = 1;

   return result;
}

float_t **Mat_get_viewport(float_t sx,
                           float_t sy,
                           float_t ws,
                           float_t hs,
                           float_t ns,
                           float_t fs)
{
   float_t **result = Mat_init(4);

   result[0][0] = ws / 2;
   result[3][0] = sx + (ws / 2);

   result[1][1] = hs / 2;
   result[3][1] = sy + (hs / 2);

   result[2][2] = (fs - ns) / 2;
   result[3][2] = (ns + fs) / 2;

   result[3][3] = 1;

   return result;
}
