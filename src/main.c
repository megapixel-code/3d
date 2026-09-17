#include "list.h"
#include "vector.h"

#include <stddef.h>
#include <stdio.h>

int main()
{
   int *list = L_init(sizeof(int));

   L_append(list, 4);
   L_append(list, 4);
   L_append(list, 4);
   L_append(list, 4);
   L_append(list, 4);
   L_append(list, 4);
   L_append(list, 4);
   L_append(list, 8);
   L_append(list, 4);

   for ( size_t i = 0; i < L_len(list); i++ ) {
      printf("%d, ", list[i]);
   }
}
