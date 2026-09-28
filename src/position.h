#ifndef POSITION_H
#define POSITION_H

#include <math.h>
#include <stdio.h>

typedef struct {
   float_t x;
   float_t y;
   float_t z;
} Position;

typedef struct {
   float_t rx;
   float_t ry;
   float_t rz;
} Rotation;

void Position_print(Position p);

#endif
