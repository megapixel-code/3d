#include "scene.h"

#include "list.h"
#include "matrix.h"
#include "object.h"
#include "position.h"
#include "vector.h"

#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void Scene_init(Scene *scene)
{
   scene->projection = Mat_get_projection(-7, 7, -7, 7, -10, 10);
   scene->viewport   = Mat_get_viewport(0, 0, 500, 500, 0.1, 500);
   scene->objects    = NULL;

   Object plane = Object_init("plane",
                              (Position){ .x = -4, .y = 0, .z = 0 },
                              (Rotation){ 0, 0, 0 });
   L_append(scene->objects, plane);

   Object cube = Object_init("cube",
                             (Position){ .x = 0, .y = 0, .z = 8.7 },
                             (Rotation){ 1, 1, 0 });
   L_append(scene->objects, cube);

   cube = Object_init("cube",
                      (Position){ .x = 4, .y = 0, .z = 0 },
                      (Rotation){ 1, 1, 0 });
   L_append(scene->objects, cube);
}

void Scene_apply_matrix(Scene *scene)
{
   Vector4 temp;

   for ( size_t object_n = 0; object_n < L_len(scene->objects); object_n++ ) {
      L_set_len(scene->objects[object_n].verticies_screen, 0);
      L_set_len(scene->objects[object_n].index_verticies_outside_render, 0);

      for ( size_t vertice_n = 0;
            vertice_n < L_len(scene->objects[object_n].verticies_scaled);
            vertice_n++ ) {
         temp = Vect3_homogenous(
            scene->objects[object_n].verticies_scaled[vertice_n]);

         temp = Mat4_mult(scene->projection, temp);
         if ( (temp.x < -1 || temp.x > 1) ||
              (temp.y < -1 || temp.y > 1) ||
              (temp.z < -1 || temp.z > 1) ) {
            L_append(scene->objects[object_n].index_verticies_outside_render,
                     vertice_n);
         }
         temp = Mat4_mult(scene->viewport, temp);

         L_append(scene->objects[object_n].verticies_screen,
                  Vect4_cartesian(temp));
      }
   }
}

/* this will set the should_render boolean on every triangle
 * */
void Triangle_filter(Scene *scene)
{
   Object cur_object;

   for ( size_t object_n = 0; object_n < L_len(scene->objects); object_n++ ) {
      for ( size_t triangle_n = 0;
            triangle_n < L_len(scene->objects[object_n].triangles);
            triangle_n++ ) {
         scene->objects[object_n].triangles[triangle_n].should_render = true;
      }

      for ( size_t i = 0;
            i < L_len(scene->objects[object_n].index_verticies_outside_render);
            i++ ) {
         cur_object = scene->objects[object_n];
         for ( size_t triangle_n = 0; triangle_n < L_len(cur_object.triangles);
               triangle_n++ ) {
            for ( size_t face_n = 0; face_n < 3; face_n++ ) {
               if ( cur_object.triangles[triangle_n].faces[face_n] !=
                    cur_object.index_verticies_outside_render[i] ) {
                  continue;
               }
               cur_object.triangles[triangle_n].should_render = false;
               break;
            }
         }
      }
   }
}

void Scene_draw(Scene *scene)
{
   Triangle_filter(scene);

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
         if ( !cur_triangle.should_render ) {
            continue;
         }

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
