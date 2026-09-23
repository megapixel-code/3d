#include "list.h"
#include "matrix.h"
#include "scene.h"

#include <math.h>
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
   SetTraceLogLevel(LOG_WARNING);
   InitWindow(500, 500, "test");
   printf("\n");

   Scene scene;
   Scene_init(&scene);

   Scene_draw(&scene);
   sleep(1);

   CloseWindow();
}
