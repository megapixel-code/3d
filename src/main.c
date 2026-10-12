#include "list.h"
#include "matrix.h"
#include "object.h"
#include "position.h"
#include "scene.h"

#include <math.h>
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

void base_animations(Scene *scene, float_t i)
{
   {
      Object_set_rotation_matrix(
         &scene->objects[0],
         (Rotation){ .rx = i * 0.02, .ry = i * 0.01, .rz = i * 0.01 });
   }
   {
      float_t remainder = fmod(i * 0.01, PI * 2);
      Object_set_rotation_euler(&scene->objects[1],
                                i * 0.01,
                                remainder > PI ? ((PI * 2) - remainder)
                                               : remainder,
                                i * 0.1);
   }
   Object_set_rotation_axis_angle(&scene->objects[2],
                                  (Vector3){ .x = 1, .y = 1, .z = 1 },
                                  i / 10);

   Scene_apply_matrix(scene);
   Scene_draw(scene);
}

void euler_animation(Scene *scene, float_t i)
{
   float_t yaw_start   = PI;
   float_t pitch_start = PI / 2;
   float_t roll_start  = PI;

   float_t yaw_end   = 0;
   float_t pitch_end = 0;
   float_t roll_end  = 0;

   float_t pause_duration     = 100;
   float_t animation_duration = 100;
   float_t remainder          = fmod(i, animation_duration + pause_duration);

   if ( remainder < pause_duration / 2 ) {
      Object_set_rotation_euler(&scene->objects[1],
                                yaw_start,
                                pitch_start,
                                roll_start);
   } else if ( remainder < (pause_duration / 2) + animation_duration ) {
      float_t annimation_progress =
         (remainder - (pause_duration / 2)) / animation_duration;
      Object_set_rotation_euler(
         &scene->objects[1],
         yaw_start + annimation_progress * (yaw_end - yaw_start),
         pitch_start + annimation_progress * (pitch_end - pitch_start),
         roll_start + annimation_progress * (roll_end - roll_start));
   } else {
      Object_set_rotation_euler(&scene->objects[1],
                                yaw_end,
                                pitch_end,
                                roll_end);
   }

   Scene_apply_matrix(scene);
   Scene_draw(scene);
}

void exp_animation(Scene *scene, float_t i)
{
   float_t x_start = 0;
   float_t y_start = 1;
   float_t z_start = 0;

   float_t x_end = 10;
   float_t y_end = 0;
   float_t z_end = 0;

   float_t pause_duration     = 100;
   float_t animation_duration = 100;
   float_t remainder          = fmod(i, animation_duration + pause_duration);

   if ( remainder < pause_duration / 2 ) {
      Object_set_rotation_exponential_map(
         &scene->objects[2],
         (Vector3){ .x = x_start, .y = y_start, .z = z_start });
   } else if ( remainder < (pause_duration / 2) + animation_duration ) {
      float_t annimation_progress =
         (remainder - (pause_duration / 2)) / animation_duration;
      Object_set_rotation_exponential_map(
         &scene->objects[2],
         (Vector3){ .x = x_start + annimation_progress * (x_end - x_start),
                    .y = y_start + annimation_progress * (y_end - y_start),
                    .z = z_start + annimation_progress * (z_end - z_start) });
   } else {
      Object_set_rotation_exponential_map(
         &scene->objects[2],
         (Vector3){ .x = x_end, .y = y_end, .z = z_end });
   }

   Scene_apply_matrix(scene);
   Scene_draw(scene);
}

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
      if ( IsKeyPressed(KEY_E) ) {
         if ( scene.display_mode == DISPLAY_MODE_ANIMATION_EULER ) {
            scene.display_mode = DISPLAY_MODE_NONE;
            printf("INFO: %s: Set display_mode to DISPLAY_MODE_NONE\n",
                   __FUNCTION__);
         } else {
            scene.display_mode = DISPLAY_MODE_ANIMATION_EULER;
            printf(
               "INFO: %s: Set display_mode to DISPLAY_MODE_ANIMATION_EULER\n",
               __FUNCTION__);
         }
      }
      if ( IsKeyPressed(KEY_X) ) {
         if ( scene.display_mode == DISPLAY_MODE_ANIMATION_EXP ) {
            scene.display_mode = DISPLAY_MODE_NONE;
            printf("INFO: %s: Set display_mode to DISPLAY_MODE_NONE\n",
                   __FUNCTION__);
         } else {
            scene.display_mode = DISPLAY_MODE_ANIMATION_EXP;
            printf("INFO: %s: Set display_mode to DISPLAY_MODE_ANIMATION_EXP\n",
                   __FUNCTION__);
         }
      }

      i++;

      switch ( scene.display_mode ) {
         case (DISPLAY_MODE_NONE): {
            base_animations(&scene, i);
         } break;
         case (DISPLAY_MODE_ANIMATION_EULER): {
            euler_animation(&scene, i);
         } break;
         case (DISPLAY_MODE_ANIMATION_EXP): {
            exp_animation(&scene, i);
         } break;
      }
   }

   CloseWindow();
}
