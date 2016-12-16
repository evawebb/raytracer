#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <sstream>
#include <string>

#define TOLERANCE 0.0000001

class Vector {
  public:
    Vector() {}
    Vector(double ix, double iy, double iz) {
      x = ix; y = iy; z = iz;
    }

    double x, y, z;

    Vector operator+(Vector o) {
      return Vector(x + o.x, y + o.y, z + o.z);
    }
    Vector operator-(Vector o) {
      return Vector(x - o.x, y - o.y, z - o.z);
    }
    Vector operator*(double f) {
      return Vector(x * f, y * f, z * f);
    }
    bool operator==(Vector o) {
      double dx = x - o.x;
      double dy = y - o.y;
      double dz = z - o.z;
      double dist = sqrt(dx * dx + dy * dy + dz * dz);
      return dist < TOLERANCE;
    }
    double dot(Vector o) {
      return x * o.x + y * o.y + z * o.z;
    }
    Vector cross(Vector o) {
      return Vector(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
    }
    double mag() {
      return sqrt(x * x + y * y + z * z);
    }
    Vector normalized() {
      double m = mag();
      return Vector(x / m, y / m, z / m);
    }

    std::string to_s() {
      std::stringstream ss;
      ss << '<' << x << ", " << y << ", " << z << '>';
      return ss.str();
    }
};

#endif
