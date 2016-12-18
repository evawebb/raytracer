#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include "object.h"
#include "point.h"
#include "vector.h"
#include "intersection_event.h"
#include "material.h"

class Triangle : public Object {
  public:
    Triangle() {}
    Triangle(
      int i_id,
      Point i_a,
      Point i_b,
      Point i_c,
      Material i_material
    ) : Object(i_id, i_a, i_material) {
      a = i_a;
      b = i_b;
      c = i_c;
      a_to_b = b - a;
      a_to_c = c - a;
      normal = a_to_b.cross(a_to_c).normalized();
    }

    Point a, b, c;
    Vector a_to_b, a_to_c, normal;

    IntersectionEvent intersect(Point origin, Vector direction);
};

#endif
