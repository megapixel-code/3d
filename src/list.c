#include "list.h"

#include <math.h>
#include <stdio.h>

void L_free(void *list)
{
   L_ensure_init(list);
   Header *header = L_get_header(list);
   free(header);
}

void L_set_len(void *list, size_t len)
{
   L_ensure_init(list);
   Header *header  = L_get_header(list);
   header->cur_len = len;
}

void L_print_f(void *list)
{
   float_t *l = (float_t *)list;

   for ( size_t i = 0; i < L_len(list); i++ ) {
      if ( i == 0 ) {
         printf("%f", l[i]);
      } else {
         printf(", %f", l[i]);
      }
   }
   printf("\n");
}
