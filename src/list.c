#include "list.h"

#include <stddef.h>
#include <stdlib.h>

void *L_init(size_t size)
{
   Header *header = malloc(sizeof(Header) + size);

   header->cur_len    = 0;
   header->max_size   = 1;
   header->block_size = size;

   return (void *)(header + 1);
}

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
