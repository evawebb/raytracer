#ifndef COLOR_H
#define COLOR_H

#include <cstdlib>

class Color {
  public:
    Color() {}
    Color(double ir, double ig, double ib) {
      r = ir; g = ig; b = ib;
    }

    double r, g, b;

    int* to_arr() {
      int* arr = new int[3];
      arr[0] = r; arr[1] = g; arr[2] = b;
      return arr;
    }

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
};

#endif
