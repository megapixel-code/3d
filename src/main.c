#include "list.h"
#include "matrix.h"
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
   printf("\n");

   Scene scene;
   Scene_init(&scene);

   float_t i = 0;
   while ( !WindowShouldClose() ) {
      if ( IsKeyPressed(KEY_Q) ) {
         CloseWindow();
         exit(0);
      }

      Mat_free(scene.objects[0].model);
      scene.objects[0].model =
         Mat_get_model((Vector3){ .x = -4, .y = 0, .z = 100 },
                       i * (PI / (24 * 1)),
                       i * (PI / (24 * 2)),
                       i * (PI / (24 * 4)));
      i++;
      Object_update_scaling(&scene.objects[0]);

      Scene_apply_matrix(&scene);
      Scene_draw(&scene);
   }

   CloseWindow();
}
