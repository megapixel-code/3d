#include "list.h"
#include "matrix.h"

#include <raylib.h>
#include <stddef.h>
#include <stdio.h>

int main()
{
   SetTraceLogLevel(LOG_WARNING);
   InitWindow(100, 100, "test");
   printf("\n");

   float **m = Mat_init(4);

   m[1][0] = -2;
   m[1][2] = 5;
   m[2][2] = 5;
   m[2][3] = -8;
   Mat_print(m);
   printf("\n");

   Vector4 temp   = (Vector4){ .x = 4, .y = 31, .z = 1, .w = 3 };
   Vector4 result = Mat4_mult(m, temp);
   Vect4_print(result);

   Mat_free(m);

   CloseWindow();
}
