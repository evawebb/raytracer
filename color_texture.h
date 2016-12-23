#ifndef COLOR_TEXTURE_H
#define COLOR_TEXTURE_H

#include "color.h"

class ColorTexture {
  public:
    ColorTexture() {}
    ColorTexture(Color i_color) {
      // width = 1;
      // height = 1;
      // data = new Color*[1];
      // data[0] = new Color[1];
      // data[0][0] = i_color;
      color = i_color;
    }

    Color texel(double u, double v) {
      return color;
    }

  private:
    Color color;
};

#endif
