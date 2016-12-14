#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include "point.h"
#include "intersection_event.h"

class Sphere {
  public:
    Sphere() {}
    Sphere(Point l, float rad) {
      loc = l;
      radius = rad;
    }

    Point loc;
    float radius;

    IntersectionEvent intersect(Point origin, Vector direction);
};

#endif
