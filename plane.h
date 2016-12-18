#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include "object.h"
#include "point.h"
#include "vector.h"
#include "intersection_event.h"
#include "material.h"

class Plane : public Object {
  public:
    Plane() {}
    Plane(
      int i_id,
      Point i_loc,
      Vector i_normal,
      Material i_material
    ) : Object(i_id, i_loc, i_material) {
      normal = i_normal.normalized();
    }

    Vector normal;

    IntersectionEvent intersect(Point origin, Vector direction);
};

#endif
