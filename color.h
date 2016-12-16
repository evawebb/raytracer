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

    Color operator*(double f) {
      return Color(r * f, g * f, b * f);
    }
    Color operator*(Color o) {
      return Color(r * o.r, g * o.g, b * o.b);
    }
    Color operator+(Color o) {
      return Color(r + o.r / 2.0, g + o.g / 2.0, b + o.b / 2.0);
      // return Color(r + o.r, g + o.g, b + o.b);
    }
};

#endif
