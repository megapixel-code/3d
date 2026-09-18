#include "list.h"

void L_free(void *list)
{
   Header *header = L_get_header(list);
   free(header);
}
