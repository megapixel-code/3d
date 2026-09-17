#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdlib.h>

typedef struct {
   size_t cur_size;
   size_t max_size;
   size_t block_size;
} Header;

inline size_t L_len(void *content)
{
   Header *header = ((Header *)content) - 1;
   return header->cur_size;
}

#endif
