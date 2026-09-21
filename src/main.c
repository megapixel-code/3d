#include "list.h"
#include "matrix.h"

#include <math.h>
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>

int main()
{
   SetTraceLogLevel(LOG_WARNING);
   InitWindow(100, 100, "test");
   printf("\n");

   float **m = Mat_init(4);

   for ( size_t y = 0; y < L_len(m); y++ ) {
      for ( size_t x = 0; x < L_len(m[y]); x++ ) {
         m[x][y] = (y * L_len(m)) + x;
      }
   }
   m[0][0] = 12;
   m[1][1] = 12;

   Mat_print(m);
   printf("\n");
   // float_t **result = Mat_adjugate(m);
   // Mat_print(result);
   // Mat_free(result);

   float_t **result = Mat_inverse(m);
   Mat_print(result);
   Mat_free(result);

   Mat_free(m);

   CloseWindow();
}
