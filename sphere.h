#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>
#include <iostream>
#include "point.h"
#include "intersection_event.h"

class Sphere {
  public:
    Sphere() {}
    Sphere(int i_id, Point i_loc, double i_radius) {
      id = i_id;
      loc = i_loc;
      radius = i_radius;
    }

    int id;
    Point loc;
    double radius;

    IntersectionEvent intersect(Point origin, Vector direction);
};

#endif
