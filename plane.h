#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include "point.h"
#include "vector.h"
#include "intersection_event.h"
#include "material.h"

class Plane {
  public:
    Plane() {}
    Plane(
      int i_id,
      Point i_loc,
      Vector i_normal,
      Material i_material
    ) {
      id = i_id;
      loc = i_loc;
      normal = i_normal.normalized();
      material = i_material;
    }

    int id;
    Point loc;
    Vector normal;
    Material material;

    IntersectionEvent intersect(Point origin, Vector direction);
};

#endif
