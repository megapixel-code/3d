#include "list.h"
#include "matrix.h"
#include "raylib.h"

#include <stddef.h>
#include <stdio.h>

int main()
{
   SetTraceLogLevel(LOG_WARNING);
   InitWindow(100, 100, "test");
   printf("\n");

   float **m = Mat_init(3);

   m[1][2] = 5;

   for ( size_t y = 0; y < L_len(m); y++ ) {
      for ( size_t x = 0; x < L_len(m); x++ ) {
         printf("%f ", m[x][y]);
      }
      printf("\n");
   }

   Mat_free(m);

   CloseWindow();
}
