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
         m[x][y] = (y * L_len(m)) + x - (L_len(m) * L_len(m) / 2.0);
      }
   }

   Mat_print(m);
   printf("\n");

   float_t result = Mat_det(m);
   printf("%f\n", result);

   Mat_free(m);

   CloseWindow();
}
