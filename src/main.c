#include "position.h"
#include "vector.h"

#include <stdio.h>

int main()
{
   Vector3 v = { .x = 0, .y = 2, .z = 2 };

   Vector3 out = Vect3_mult(v, 4);
   Vect3_display(v);
   Vect3_display(out);
}
