#ifndef MATRIX_H
#define MATRIX_H

#include "list.h"

#include <math.h>
#include <stddef.h>

float **WARN_UNUSED Mat_init(size_t size);
void                Mat_free(float **matrix);

#endif
