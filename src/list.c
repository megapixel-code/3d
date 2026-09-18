#include "list.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void *L_ensure_index(void *list, size_t max_index)
{
   Header *header = L_get_header(list);

   if ( header->max_size <= max_index ) {
      header->max_size *= 2;
   }

   header =
      realloc(header, sizeof(Header) + (header->block_size * header->max_size));

   return (void *)(header + 1);
}

void L_free(void *list)
{
   Header *header = L_get_header(list);
   free(header);
}
