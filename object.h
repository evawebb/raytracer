#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include "point.h"
#include "vector.h"
#include "intersection_event.h"
#include "material.h"

class Object {
  public:
    Object() {}
    Object(
      int i_id,
      Point i_loc,
      Material* i_material
    ) {
      id = i_id;
      loc = i_loc;
      material = i_material;
    }

    int id;
    Point loc;
    Material* material;

    virtual IntersectionEvent intersect(Point origin, Vector direction) = 0;
};

#endif
