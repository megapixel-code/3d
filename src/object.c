#include "object.h"

#include "list.h"
#include "matrix.h"
#include "string.h"

#include <math.h>
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

Object Object_parse_file(char *name)
{
   char *pre_path  = "assets/";
   char *post_path = ".obj";
   char *path = malloc(strlen(pre_path) + strlen(name) + strlen(post_path) + 1);
   strcpy(path, pre_path);
   strcat(path, name);
   strcat(path, post_path);

   Object result = {
      .verticies                      = NULL,
      .verticies_scaled               = NULL,
      .verticies_screen               = NULL,
      .index_verticies_outside_render = NULL,
      .model                          = NULL,
      .triangles                      = NULL,
   };

   FILE *f = fopen(path, "r");
   if ( f == NULL ) {
      fprintf(stderr,
              "ERROR: %s: cannot open path: \"%s\"\n",
              __FUNCTION__,
              path);
      return result;
   }

   char  *buffer   = NULL;
   size_t capacity = 0;
   while ( getline(&buffer, &capacity, f) >= 0 ) {
      if ( !memcmp(buffer, "f ", 2) ) {
         size_t i            = 1;
         char **char_indexes = NULL;
         char  *temp;
         while ( 1 ) {
            temp = lib_get_next_str_char(buffer, &i, ' ');
            if ( temp == NULL ) {
               break;
            }
            fflush(stdout);

            L_append(char_indexes, temp);
         }

         size_t *val_indexes = NULL;
         size_t  val_temp;
         for ( size_t index_n = 0; index_n < L_len(char_indexes); index_n++ ) {
            i = 0;
            lib_get_next_str_char(char_indexes[index_n], &i, '/');
            sscanf(char_indexes[index_n], "%zu", &val_temp);
            L_append(val_indexes, --val_temp);
         }
         L_free(char_indexes);

         for ( size_t i = 1; i < L_len(val_indexes) - 1; i++ ) {
            L_append(result.triangles,
                     Triangle_init(result.verticies,
                                   (int[3]){ val_indexes[0],
                                             val_indexes[i],
                                             val_indexes[i + 1] }));
         }

         L_free(val_indexes);
      } else if ( !memcmp(buffer, "v ", 2) ) {
         size_t index      = 2;
         char  *char_x     = lib_get_next_str_char(buffer, &index, ' ');
         buffer[index - 1] = '\0';
         char *char_y      = lib_get_next_str_char(buffer, &index, ' ');
         buffer[index - 1] = '\0';
         char *char_z      = lib_get_next_str_char(buffer, &index, ' ');
         buffer[index - 1] = '\0';

         float_t val_x, val_y, val_z;
         sscanf(char_x, "%f", &val_x);
         sscanf(char_y, "%f", &val_y);
         sscanf(char_z, "%f", &val_z);
         L_append(result.verticies,
                  PROTECT((Position){ .x = val_x, .y = val_y, .z = val_z }));
      }
   }
   fclose(f);

   printf("INFO: %s: loaded file \"%s\"\n", __FUNCTION__, path);
   return result;
}

Object Object_init(char *object_name, Position p, Rotation r)
{
   Object result = Object_parse_file(object_name);

   result.position = p;
   result.rotation = r;
   result.model    = NULL;
   Object_reset_model(&result);

   return result;
}

void Object_apply_model(Object *o)
{
   L_free(o->verticies_scaled);
   o->verticies_scaled = Mat4_mult(o->model, o->verticies);
}

void Object_reset_model(Object *o)
{
   Mat_free(o->model);
   o->model = Mat_get_model(
      (Vector3){ .x = o->position.x, .y = o->position.y, .z = o->position.z },
      o->rotation);
   Object_apply_model(o);
}

void Object_set_rotation_matrix(Object *o, Rotation r)
{
   float_t **temp_model = Mat_get_model(
      (Vector3){ .x = o->position.x, .y = o->position.y, .z = o->position.z },
      r);

   L_free(o->verticies_scaled);
   o->verticies_scaled = Mat4_mult(temp_model, o->verticies);

   Mat_free(temp_model);
}

void Object_set_rotation_euler(Object *o,
                               float_t yaw,
                               float_t pitch,
                               float_t roll)
{
   float_t **model_yaw =
      Mat_get_model((Vector3){ 0, 0, 0 },
                    (Rotation){ .rx = 0, .ry = 0, .rz = yaw });
   Position *pos_yaw = Mat4_mult(model_yaw, o->verticies);
   Mat_free(model_yaw);

   L_free(o->verticies_scaled);
   float_t **model_translation = Mat_get_model(
      (Vector3){ .x = o->position.x, .y = o->position.y, .z = o->position.z },
      (Rotation){ 0, 0, 0 });
   o->verticies_scaled = Mat4_mult(model_translation, pos_yaw);

   Mat_free(model_translation);
   L_free(pos_yaw);
}
