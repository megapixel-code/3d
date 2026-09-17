#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdlib.h>

#define WARN_UNUSED __attribute__((warn_unused_result))

typedef struct {
   size_t cur_len;
   size_t max_size;
   size_t block_size;
} Header;

inline Header WARN_UNUSED *L_get_header(void *list)
{
   return ((Header *)list) - 1;
}

inline size_t WARN_UNUSED L_len(void *list)
{
   Header *header = L_get_header(list);
   return header->cur_len;
}

void *WARN_UNUSED L_init(size_t size);
void *WARN_UNUSED L_ensure_index(void *list, size_t max_index);

#define L_append(list, data)                                         \
   do {                                                              \
      if ( list == NULL ) {                                          \
         list = L_init(sizeof(*list));                               \
      }                                                              \
      Header *header        = L_get_header(list);                    \
      list                  = L_ensure_index(list, header->cur_len); \
      list[header->cur_len] = data;                                  \
      header->cur_len++;                                             \
   } while ( 0 )

#endif
