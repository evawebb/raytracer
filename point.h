#ifndef POINT_H
#define POINT_H

#include <sstream>
#include <string>
#include "vector.h"

class Point {
  public:
    Point() {}
    Point(double ix, double iy) {
      x = ix; y = iy; z = 0; w = 1;
    }
    Point(double ix, double iy, double iz) {
      x = ix; y = iy; z = iz; w = 1;
    }

    double x, y, z, w;

    Point operator+(Point o) {
      return Point(x + o.x, y + o.y, z + o.z);
    }
    Point operator+(Vector v) {
      return Point(x + v.x, y + v.y, z + v.z);
    }
    Vector operator-(Point o) {
      return Vector(x - o.x, y - o.y, z - o.z);
    }
    Point operator*(double f) {
      return Point(x * f, y * f, z * f);
    }

    std::string to_s() {
      std::stringstream ss;
      ss << '(' << x << ", " << y << ", " << z << ')';
      return ss.str();
    }
};

#endif
