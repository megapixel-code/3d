#include "list.h"

void L_free(void *list)
{
   Header *header = L_get_header(list);
   free(header);
}

void L_set_len(void *list, size_t len)
{
   L_ensure_init(list);
   Header *header  = L_get_header(list);
   header->cur_len = len;
}
