#ifndef SPHERE_H
#define SPHERE_H

#include "point.h"

class Sphere {
  public:
    Sphere() {}
    Sphere(Point l, float r) {
      loc = l;
      radius = r;
    }

    Point loc;
    float radius;
};

#endif
