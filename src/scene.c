#include "scene.h"

#include "list.h"
#include "matrix.h"
#include "object.h"
#include "position.h"
#include "vector.h"

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void Scene_init(Scene *scene)
{
   scene->projection = Mat_get_projection(-1, 1, 1, -1, 1, 100);
   scene->viewport   = Mat_get_viewport(0, 0, 400, 400, 0, 1);
   scene->objects    = NULL;

   Object cube;
   cube.verticies        = NULL;
   cube.verticies_scaled = NULL;
   cube.verticies_screen = NULL;
   cube.triangles        = NULL;

   L_append(cube.verticies, PROTECT((Position){ .x = 0, .y = 0, .z = 0 }));
   L_append(cube.verticies, PROTECT((Position){ .x = 1, .y = 0, .z = 0 }));
   L_append(cube.verticies, PROTECT((Position){ .x = 1, .y = 1, .z = 0 }));
   L_append(cube.verticies, PROTECT((Position){ .x = 0, .y = 1, .z = 0 }));
   L_append(cube.verticies, PROTECT((Position){ .x = 0, .y = 0, .z = 1 }));
   L_append(cube.verticies, PROTECT((Position){ .x = 1, .y = 0, .z = 1 }));
   L_append(cube.verticies, PROTECT((Position){ .x = 1, .y = 1, .z = 1 }));
   L_append(cube.verticies, PROTECT((Position){ .x = 0, .y = 1, .z = 1 }));

   L_append(cube.triangles, Triangle_init(cube.verticies, (int[3]){ 0, 4, 5 }));
   L_append(cube.triangles, Triangle_init(cube.verticies, (int[3]){ 0, 5, 1 }));
   L_append(cube.triangles, Triangle_init(cube.verticies, (int[3]){ 1, 5, 6 }));
   L_append(cube.triangles, Triangle_init(cube.verticies, (int[3]){ 1, 6, 2 }));
   L_append(cube.triangles, Triangle_init(cube.verticies, (int[3]){ 2, 6, 7 }));
   L_append(cube.triangles, Triangle_init(cube.verticies, (int[3]){ 2, 7, 3 }));
   L_append(cube.triangles, Triangle_init(cube.verticies, (int[3]){ 3, 7, 4 }));
   L_append(cube.triangles, Triangle_init(cube.verticies, (int[3]){ 3, 4, 0 }));
   L_append(cube.triangles, Triangle_init(cube.verticies, (int[3]){ 1, 2, 3 }));
   L_append(cube.triangles, Triangle_init(cube.verticies, (int[3]){ 1, 3, 0 }));
   L_append(cube.triangles, Triangle_init(cube.verticies, (int[3]){ 4, 6, 5 }));
   L_append(cube.triangles, Triangle_init(cube.verticies, (int[3]){ 4, 7, 6 }));

   cube.model = Mat_get_model((Vector3){ .x = 0, .y = 0, .z = 10 }, 0);
   Object_update_scaling(&cube);

   L_append(scene->objects, cube);
}

void Scene_apply_matrix(Scene *scene)
{
   Vector4 temp;

   for ( size_t object_n = 0; object_n < L_len(scene->objects); object_n++ ) {
      L_set_len(scene->objects[object_n].verticies_screen, 0);
      for ( size_t vertice_n = 0;
            vertice_n < L_len(scene->objects[object_n].verticies_scaled);
            vertice_n++ ) {
         temp = Vect3_homogenous(
            scene->objects[object_n].verticies_scaled[vertice_n]);

         temp = Mat4_mult(scene->projection, temp);
         temp = Mat4_mult(scene->viewport, temp);

         L_append(scene->objects[object_n].verticies_screen,
                  Vect4_cartesian(temp));
      }
   }
}

void Scene_draw(Scene *scene)
{
   BeginDrawing();
   ClearBackground(WHITE);
   Scene_apply_matrix(scene);

   Object   cur_object;
   Triangle cur_triangle;
   for ( size_t object_n = 0; object_n < L_len(scene->objects); object_n++ ) {
      cur_object = scene->objects[object_n];

      for ( size_t triangle_n = 0; triangle_n < L_len(cur_object.triangles);
            triangle_n++ ) {
         cur_triangle = cur_object.triangles[triangle_n];

         DrawLine(cur_object.verticies_screen[cur_triangle.faces[0]].x,
                  cur_object.verticies_screen[cur_triangle.faces[0]].y,
                  cur_object.verticies_screen[cur_triangle.faces[1]].x,
                  cur_object.verticies_screen[cur_triangle.faces[1]].y,
                  BLACK);
         DrawLine(cur_object.verticies_screen[cur_triangle.faces[1]].x,
                  cur_object.verticies_screen[cur_triangle.faces[1]].y,
                  cur_object.verticies_screen[cur_triangle.faces[2]].x,
                  cur_object.verticies_screen[cur_triangle.faces[2]].y,
                  BLACK);
         DrawLine(cur_object.verticies_screen[cur_triangle.faces[2]].x,
                  cur_object.verticies_screen[cur_triangle.faces[2]].y,
                  cur_object.verticies_screen[cur_triangle.faces[0]].x,
                  cur_object.verticies_screen[cur_triangle.faces[0]].y,
                  BLACK);
      }
   }

   EndDrawing();
}
