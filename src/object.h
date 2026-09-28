#ifndef OBJECT_H
#define OBJECT_H

#include "list.h"
#include "matrix.h"
#include "string.h"
#include "triangle.h"

#include <stdio.h>
#include <string.h>

typedef struct {
   Position  position;
   Rotation  rotation;
   Position *verticies;
   Position *verticies_scaled;
   Position *verticies_screen;
   size_t   *index_verticies_outside_render;
   float_t **model;
   Triangle *triangles;
} Object;

Object Object_init(char *object_name, Position p, Rotation r);
void   Object_reset_model(Object *o);
void   Object_set_rotation_matrix(Object *o, Rotation r);
void   Object_set_rotation_euler(Object *o,
                                 float_t yaw,
                                 float_t pitch,
                                 float_t roll);

#endif
