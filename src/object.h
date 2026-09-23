#ifndef OBJECT_H
#define OBJECT_H

#include "list.h"
#include "matrix.h"
#include "triangle.h"

typedef struct {
   Position *verticies;
   Position *verticies_scaled;
   Position *verticies_screen;
   float_t **model;
   Triangle *triangles;
} Object;

void Object_update_scaling(Object *o);

#endif
