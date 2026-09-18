#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdio.h>
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

#define L_ensure_init(list)                                         \
   do {                                                             \
      if ( (list) == NULL ) {                                       \
         Header *header = malloc(sizeof(Header) + sizeof(*(list))); \
                                                                    \
         header->cur_len    = 0;                                    \
         header->max_size   = 1;                                    \
         header->block_size = sizeof(*(list));                      \
                                                                    \
         (list) = (void *)(header + 1);                             \
      }                                                             \
   } while ( 0 )

#define L_ensure_index(list, max_index)                                     \
   do {                                                                     \
      L_ensure_init(list);                                                  \
                                                                            \
      Header *header = L_get_header(list);                                  \
                                                                            \
      if ( header->max_size <= max_index ) {                                \
         header->max_size *= 2;                                             \
      }                                                                     \
                                                                            \
      header =                                                              \
         realloc(header,                                                    \
                 sizeof(Header) + (header->block_size * header->max_size)); \
                                                                            \
      list = (void *)(header + 1);                                          \
   } while ( 0 )

#define L_append(list, data)                        \
   do {                                             \
      L_ensure_init(list);                          \
                                                    \
      Header *header = L_get_header(list);          \
      L_ensure_index((list), header->cur_len);      \
      header                  = L_get_header(list); \
      (list)[header->cur_len] = (data);             \
      header->cur_len++;                            \
   } while ( 0 )

void L_free(void *list);

#endif
