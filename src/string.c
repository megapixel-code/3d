#include "string.h"

/**
 * Get the next string that end with char c in the buffer. We remove the
 * trailing spaces in front of the buffer. We also increase the index to put it
 * at the end.
 *
 * @param char* buffer, the buffer we containing the contents
 * @param int* index, the index we are currently in said buffer
 * @param char c, the char we want the string to end with
 *
 * @return char*, a string that ends with char c without spaces in front or NULL
 * in case the char c was not found
 */
char *lib_get_next_str_char(char *buffer, size_t *index, char c)
{
   while ( buffer[*index] == ' ' && buffer[*index] != '\0' ) {
      (*index)++;
   }
   if ( buffer[*index] == '\0' ) {
      return NULL;
   }
   char *output = buffer + *index;

   while ( buffer[*index] != c &&
           buffer[*index] != '\n' &&
           buffer[*index] != '\0' ) {
      (*index)++;
   }
   if ( buffer[*index] == '\0' ) {
      return NULL;
   }

   buffer[*index] = '\0';
   (*index)++;

   return output;
}
