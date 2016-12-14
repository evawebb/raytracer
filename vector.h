#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <sstream>
#include <string>

class Vector {
  public:
    Vector() {}
    Vector(float ix, float iy, float iz) {
      x = ix; y = iy; z = iz;
    }

    float x, y, z;

    Vector operator+(Vector o) {
      return Vector(x + o.x, y + o.y, z + o.z);
    }
    Vector operator-(Vector o) {
      return Vector(x - o.x, y - o.y, z - o.z);
    }
    Vector operator*(float f) {
      return Vector(x * f, y * f, z * f);
    }
    float dot(Vector o) {
      return x * o.x + y * o.y + z * o.z;
    }
    Vector cross(Vector o) {
      return Vector(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
    }
    float mag() {
      return sqrt(x * x + y * y + z * z);
    }
    Vector normalized() {
      float m = mag();
      return Vector(x / m, y / m, z / m);
    }

    std::string to_s() {
      std::stringstream ss;
      ss << '<' << x << ", " << y << ", " << z << '>';
      return ss.str();
    }
};

#endif
