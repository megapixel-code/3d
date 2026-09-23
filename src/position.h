#ifndef POSITION_H
#define POSITION_H

#include <math.h>
#include <stdio.h>

typedef struct {
   float_t x;
   float_t y;
   float_t z;
} Position;

void Position_print(Position p);

#endif
