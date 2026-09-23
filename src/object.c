#include "object.h"

void Object_update_scaling(Object *o)
{
   Vector4 temp;

   L_set_len(o->verticies_scaled, 0);
   for ( size_t i = 0; i < L_len(o->verticies); i++ ) {
      temp = Mat4_mult(o->model, Vect3_homogenous(o->verticies[i]));
      L_append(o->verticies_scaled, Vect4_cartesian(temp));
   }
}
