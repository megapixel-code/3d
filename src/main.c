#include "list.h"
#include "vector.h"

#include <stddef.h>
#include <stdio.h>

int main()
{
   SetTraceLogLevel(LOG_WARNING);
   InitWindow(100, 100, "test");

   int *list = NULL;

   for ( int i = 0; i < 100; i++ ) {
      L_append(list, i);
   }

   for ( size_t i = 0; i < L_len(list); i++ ) {
      printf("%d, ", list[i]);
   }

   CloseWindow();
}
