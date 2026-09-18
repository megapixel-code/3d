#ifndef VECTOR_H
#define VECTOR_H

#include <assert.h>
#include <math.h>
#include <raylib.h>
#include <stdio.h>

//
// =========== { Vector3 }
//
//
// ============= { OPERATION OVERLOADING }
//

inline Vector3 Vect3_add(Vector3 vector, Vector3 other)
{
   return (Vector3){ .x = vector.x + other.x,
                     .y = vector.y + other.y,
                     .z = vector.z + other.z };
}

inline Vector3 Vect3_sub(Vector3 vector, Vector3 other)
{
   return (Vector3){ .x = vector.x - other.x,
                     .y = vector.y - other.y,
                     .z = vector.z - other.z };
}

inline Vector3 Vect3_div(Vector3 vector, float_t value)
{
   return (Vector3){ .x = vector.x / value,
                     .y = vector.y / value,
                     .z = vector.z / value };
}

inline Vector3 Vect3_mult(Vector3 vector, float_t value)
{
   return (Vector3){ .x = vector.x * value,
                     .y = vector.y * value,
                     .z = vector.z * value };
}

inline Vector3 Vect3_cross(Vector3 vector, Vector3 other)
{
   return (Vector3){ .x = vector.y * other.z - vector.z * other.y,
                     .y = vector.z * other.x - vector.x * other.z,
                     .z = vector.x * other.y - vector.y * other.x };
}

inline float_t Vect3_dot(Vector3 V1, Vector3 V2)
{
   return V1.x * V2.x + V1.y * V2.y + V1.z * V2.z;
}

//
// =========== { END OPERATION OVERLOADING }
//

inline float_t Vect3_length_squared(Vector3 vector)
{
   return pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2);
}

inline float_t Vect3_length(Vector3 vector)
{
   return sqrt(Vect3_length_squared(vector));
}

inline Vector3 Vect3_reverse(Vector3 vector)
{
   return Vect3_mult(vector, -1);
}

inline Vector4 Vect3_homogenous(Vector3 vector)
{
   return (Vector4){ .x = vector.x, .y = vector.y, .z = vector.z, .w = 1 };
}

Vector3 Vect3_normalize(Vector3 vector);

void Vect3_print(Vector3 vector);

//
// =========== { Vector4 }
//

inline Vector3 Vect4_cartesian(Vector4 vector)
{
   return (Vector3){ .x = vector.x / vector.w,
                     .y = vector.y / vector.w,
                     .z = vector.z / vector.w };
}

void Vect4_print(Vector4 vector);

#endif
