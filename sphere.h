#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include "point.h"

class Sphere {
  public:
    Sphere() {}
    Sphere(Point l, float rad) {
      loc = l;
      radius = rad;
    }

    Point loc;
    float radius;

    float intersect(Point origin, Vector direction);
};

#endif
