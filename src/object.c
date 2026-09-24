#include "object.h"

#include "list.h"
#include "string.h"

#include <stddef.h>
#include <stdio.h>
#include <strings.h>

Object Object_init(char *object_name)
{
   char *pre_path  = "assets/";
   char *post_path = ".obj";
   char *path =
      malloc(strlen(pre_path) + strlen(object_name) + strlen(post_path) + 1);
   strcpy(path, pre_path);
   strcat(path, object_name);
   strcat(path, post_path);

   Object result = {
      .verticies        = NULL,
      .verticies_scaled = NULL,
      .verticies_screen = NULL,
      .triangles        = NULL,
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

void Object_update_scaling(Object *o)
{
   Vector4 temp;

   L_set_len(o->verticies_scaled, 0);
   for ( size_t i = 0; i < L_len(o->verticies); i++ ) {
      temp = Mat4_mult(o->model, Vect3_homogenous(o->verticies[i]));
      L_append(o->verticies_scaled, Vect4_cartesian(temp));
   }
}
