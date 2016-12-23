#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include "point.h"
#include "vector.h"
#include "intersection_event.h"
#include "color_material.h"

class Object {
  public:
    Object() {}
    Object(
      int i_id,
      Point i_loc,
      ColorMaterial i_material
    ) {
      id = i_id;
      loc = i_loc;
      material = i_material;
    }

    int id;
    Point loc;
    ColorMaterial material;

    virtual IntersectionEvent intersect(Point origin, Vector direction) = 0;
};

#endif
