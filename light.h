#ifndef LIGHT_H
#define LIGHT_H

#include "point.h"
#include "color.h"

class Light {
  public:
    Light() {}
    Light(
      Point i_loc,
      Color i_diffuse,
      Color i_ambient
    ) {
      loc = i_loc;
      diffuse = i_diffuse;
      ambient = i_ambient;
    }

    Point loc;
    Color diffuse, ambient;
};

#endif
