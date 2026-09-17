#include "list.h"

void *L_init(size_t size)
{
   Header *header  = malloc(sizeof(Header) + size);
   void   *content = (void *)(header + 1);

   header->cur_size   = 0;
   header->max_size   = 1;
   header->block_size = size;

   return content;
}

void L_append(void *list, )
{
}
