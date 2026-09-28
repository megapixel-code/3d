#include "object.h"
#include "scene.h"

#include <math.h>
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
   SetTraceLogLevel(LOG_WARNING);
   InitWindow(500, 500, "test");
   SetTargetFPS(24);

   Scene scene;
   Scene_init(&scene);

   float_t i = 0;
   while ( !WindowShouldClose() ) {
      if ( IsKeyPressed(KEY_Q) ) {
         CloseWindow();
         exit(0);
      }

      Object_set_rotation_matrix(
         &scene.objects[0],
         (Rotation){ .rx = i * 0.02, .ry = i * 0.01, .rz = i * 0.01 });

      {
         float_t remainder = fmod(i * 0.01, 2);
         Object_set_rotation_euler(&scene.objects[1],
                                   i * 0.01,
                                   i * 0.01,
                                   remainder > 1 ? (2 - remainder) : remainder);
      }
      i++;

      Scene_apply_matrix(&scene);
      Scene_draw(&scene);
   }

   CloseWindow();
}
