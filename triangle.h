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
      Point i_a, Point i_a_texel,
      Point i_b, Point i_b_texel,
      Point i_c, Point i_c_texel,
      Material* i_material
    ) : Object(i_id, i_a, i_material) {
      a = i_a; a_texel = i_a_texel;
      b = i_b; b_texel = i_b_texel;
      c = i_c; c_texel = i_c_texel;

      a_to_b = b - a;
      a_to_c = c - a;
      normal = a_to_b.cross(a_to_c).normalized();
      a_normal = normal;
      b_normal = normal;
      c_normal = normal;
    }
    Triangle(
      int i_id,
      Point i_a, Vector i_a_normal, Point i_a_texel,
      Point i_b, Vector i_b_normal, Point i_b_texel,
      Point i_c, Vector i_c_normal, Point i_c_texel,
      Material* i_material
    ) : Object(i_id, i_a, i_material) {
      a = i_a; 
      a_texel = i_a_texel;
      a_normal = i_a_normal;
      b = i_b; 
      b_texel = i_b_texel;
      b_normal = i_b_normal;
      c = i_c; 
      c_texel = i_c_texel;
      c_normal = i_c_normal;

      a_to_b = b - a;
      a_to_c = c - a;
      normal = a_to_b.cross(a_to_c).normalized();
    }

    Point a, b, c, a_texel, b_texel, c_texel;
    Vector a_to_b, a_to_c, normal, a_normal, b_normal, c_normal;
    double u, v;

    IntersectionEvent intersect(Point origin, Vector direction);
    std::string to_s() {
      std::stringstream ss;
      ss << "A: " <<   a.to_s() << a_normal.to_s() << a_texel.to_s();
      ss << ", B: " << b.to_s() << b_normal.to_s() << b_texel.to_s();
      ss << ", C: " << c.to_s() << c_normal.to_s() << c_texel.to_s();
      return ss.str();
    }
};

#endif
