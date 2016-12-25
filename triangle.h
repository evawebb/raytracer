#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <sstream>
#include <string>
#include "object.h"
#include "point.h"
#include "vector.h"
#include "intersection_event.h"
#include "material.h"

class Triangle : public Object {
  public:
    Triangle() {}
    Triangle(
      int i_id,
      Point i_a, double i_a_texel_s, double i_a_texel_t,
      Point i_b, double i_b_texel_s, double i_b_texel_t,
      Point i_c, double i_c_texel_s, double i_c_texel_t,
      Material* i_material
    ) : Object(i_id, i_a, i_material) {
      a = i_a; a_texel_s = i_a_texel_s; a_texel_t = i_a_texel_t;
      b = i_b; b_texel_s = i_b_texel_s; b_texel_t = i_b_texel_t;
      c = i_c; c_texel_s = i_c_texel_s; c_texel_t = i_c_texel_t;
      a_to_b = b - a;
      a_to_c = c - a;
      normal = a_to_b.cross(a_to_c).normalized();
    }

    Point a, b, c;
    Vector a_to_b, a_to_c, normal;
    double a_texel_s, a_texel_t, b_texel_s, b_texel_t, c_texel_s, c_texel_t;
    double u, v;

    IntersectionEvent intersect(Point origin, Vector direction);
    std::string to_s() {
      std::stringstream ss;
      ss << "A: " << a.to_s() << '(' << a_texel_s << ", " << a_texel_t << ')';
      ss << ", B: " << b.to_s() << '(' << b_texel_s << ", " << b_texel_t << ')';
      ss << ", C: " << c.to_s() << '(' << c_texel_s << ", " << c_texel_t << ')';
      return ss.str();
    }
};

#endif
