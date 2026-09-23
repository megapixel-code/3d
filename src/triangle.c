#include "triangle.h"

Triangle Triangle_init(Position *verticies, int faces[3])
{
   return (Triangle){
      .vertices = verticies,
      .faces    = { faces[0], faces[1], faces[2] },
   };
}
