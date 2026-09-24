#ifndef OBJECT_H
#define OBJECT_H

#include "list.h"
#include "matrix.h"
#include "string.h"
#include "triangle.h"

#include <stdio.h>
#include <string.h>

typedef struct {
   Position *verticies;
   Position *verticies_scaled;
   Position *verticies_screen;
   float_t **model;
   Triangle *triangles;
} Object;

Object Object_init(char *object_name, float_t **model);
void   Object_update_scaling(Object *o);

#endif
