#ifndef COLOR_H
#define COLOR_H

#include <cstdlib>
#include <sstream>
#include <string>

class Color {
  public:
    Color() {}
    Color(double ir, double ig, double ib) {
      r = ir; g = ig; b = ib;
    }

    double r, g, b;

    Color blend(Color o, double t_this, double t_other) {
      return Color(
        t_this * r + t_other * o.r,
        t_this * g + t_other * o.g,
        t_this * b + t_other * o.b
      );
    }
    Color blend(Color o, double t) {
      return blend(o, t, 1 - t);
    }

    Color operator*(double f) {
      return Color(r * f, g * f, b * f);
    }
    Color operator*(Color o) {
      return Color(r * o.r, g * o.g, b * o.b);
    }

    std::string to_s() {
      std::stringstream ss;
      ss << "c(" << r << ", " << g << ", " << b << ')';
      return ss.str();
    }
};

#endif
