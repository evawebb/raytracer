#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>
#include <iostream>
#include "object.h"
#include "point.h"
#include "vector.h"
#include "intersection_event.h"
#include "color_material.h"

class Sphere : public Object {
  public:
    Sphere() {}
    Sphere(
      int i_id, 
      Point i_loc, 
      double i_radius,
      ColorMaterial i_material
    ) : Object(i_id, i_loc, i_material) {
      radius = i_radius;
    }

    double radius;

    IntersectionEvent intersect(Point origin, Vector direction);
};

#endif
