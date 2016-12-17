#ifndef LIGHT_H
#define LIGHT_H

#include "point.h"
#include "color.h"

class Light {
  public:
    Light() {}
    Light(
      Point i_loc,
      Color i_ambient,
      Color i_diffuse,
      Color i_specular
    ) {
      loc = i_loc;
      ambient = i_ambient;
      diffuse = i_diffuse;
      specular = i_specular;
    }

    Point loc;
    Color diffuse, ambient, specular;
};

#endif
