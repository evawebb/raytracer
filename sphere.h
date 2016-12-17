#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>
#include <iostream>
#include "point.h"
#include "intersection_event.h"
#include "material.h"

class Sphere {
  public:
    Sphere() {}
    Sphere(
      int i_id, 
      Point i_loc, 
      double i_radius,
      Material i_material
    ) {
      id = i_id;
      loc = i_loc;
      radius = i_radius;
      material = i_material;
    }

    int id;
    Point loc;
    double radius;
    Material material;

    IntersectionEvent intersect(Point origin, Vector direction);
};

#endif
