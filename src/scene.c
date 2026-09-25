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

   Object plane = Object_init(
      "plane",
      Mat_get_model((Vector3){ .x = -4, .y = 0, .z = -9 }, 0, 0, 0));
   Object_update_scaling(&plane);
   L_append(scene->objects, plane);

   Object cube =
      Object_init("cube",
                  Mat_get_model((Vector3){ .x = 0, .y = 0, .z = 0 }, 1, 1, 0));
   Object_update_scaling(&cube);
   L_append(scene->objects, cube);
   Object cube2 =
      Object_init("cube",
                  Mat_get_model((Vector3){ .x = 4, .y = 0, .z = 50 }, 1, 1, 0));
   Object_update_scaling(&cube2);
   L_append(scene->objects, cube2);
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

void Triangle_filter(Scene *scene)
{
   float_t **inverse_viewport = Mat_inverse(scene->viewport);
   size_t   *verticies_outside_render;

   Position pos_pre_viewport;
   for ( size_t object_n = 0; object_n < L_len(scene->objects); object_n++ ) {
      verticies_outside_render = NULL;

      for ( size_t i = 0; i < L_len(scene->objects[object_n].verticies_screen);
            i++ ) {
         pos_pre_viewport = Vect4_cartesian(Mat4_mult(
            inverse_viewport,
            Vect3_homogenous(scene->objects[object_n].verticies_screen[i])));
         if ( (pos_pre_viewport.x < -1 || pos_pre_viewport.x > 1) ||
              (pos_pre_viewport.y < -1 || pos_pre_viewport.y > 1) ||
              (pos_pre_viewport.z < -1 || pos_pre_viewport.z > 1) ) {
            L_append(verticies_outside_render, i);
         }
      }

      for ( size_t triangle_n = 0;
            triangle_n < L_len(scene->objects[object_n].triangles);
            triangle_n++ ) {
         scene->objects[object_n].triangles[triangle_n].should_render = true;
      }

      for ( size_t i = 0; i < L_len(verticies_outside_render); i++ ) {
         for ( size_t triangle_n = 0;
               triangle_n < L_len(scene->objects[object_n].triangles);
               triangle_n++ ) {
            for ( size_t face_n = 0; face_n < 3; face_n++ ) {
               if ( scene->objects[object_n]
                       .triangles[triangle_n]
                       .faces[face_n] == verticies_outside_render[i] ) {
                  scene->objects[object_n].triangles[triangle_n].should_render =
                     false;
                  break;
               }
            }
         }
      }
      L_free(verticies_outside_render);
   }

   Mat_free(inverse_viewport);
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
