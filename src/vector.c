#include "vector.h"

Vector3 Vect3_normalize(Vector3 vector)
{
   return Vect3_div(vector, Vect3_length(vector));
}

void Vect3_display(Vector3 vector)
{
   printf("vect3 = {.x = %.5f, .y = %.5f, .z = %.5f}\n",
          vector.x,
          vector.y,
          vector.z);
}
