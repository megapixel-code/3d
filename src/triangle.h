#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "list.h"
#include "matrix.h"
#include "position.h"

#include <math.h>
#include <raylib.h>

typedef struct {
   Position *vertices; // array of all vertex coordinates
   int faces[3]; // array of indexes of vertices in counter-clockwise order
} Triangle;

Triangle WARN_UNUSED Triangle_init(Position *verticies, int faces[3]);
#endif
