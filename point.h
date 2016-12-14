#ifndef POINT_H
#define POINT_H

#include "vector.h"

class Point {
  public:
    Point() {}
    Point(float ix, float iy, float iz) {
      x = ix; y = iy; z = iz;
    }

    float x, y, z;

    Point operator+(Point o) {
      return Point(x + o.x, y + o.y, z + o.z);
    }
    Point operator+(Vector v) {
      return Point(x + v.x, y + v.y, z + v.z);
    }
    Vector operator-(Point o) {
      return Vector(x - o.x, y - o.y, z - o.z);
    }
    Point operator*(float f) {
      return Point(x * f, y * f, z * f);
    }
};

#endif
