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
      Color i_diffuse
    ) {
      loc = i_loc;
      ambient = i_ambient;
      diffuse = i_diffuse;
    }

    Point loc;
    Color diffuse, ambient;
};

#endif
