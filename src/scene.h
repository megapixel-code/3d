#ifndef SCENE_H
#define SCENE_H

#include "list.h"
#include "matrix.h"
#include "object.h"
#include "position.h"
#include "triangle.h"
#include "vector.h"

#include <math.h>
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
   float_t **projection;
   float_t **viewport;
   Object   *objects;
} Scene;

void Scene_init(Scene *scene);
void Scene_draw(Scene *scene);
void Scene_apply_matrix(Scene *scene);

#endif
