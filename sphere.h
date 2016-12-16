#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>
#include <iostream>
#include "point.h"
#include "color.h"
#include "intersection_event.h"

class Sphere {
  public:
    Sphere() {}
    Sphere(
      int i_id, 
      Point i_loc, 
      double i_radius,
      Color i_ambient,
      Color i_diffuse
    ) {
      id = i_id;
      loc = i_loc;
      radius = i_radius;
      ambient = i_ambient;
      diffuse = i_diffuse;
    }

    int id;
    Point loc;
    double radius;
    Color ambient, diffuse;

    IntersectionEvent intersect(Point origin, Vector direction);
};

#endif
