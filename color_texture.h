#ifndef COLOR_TEXTURE_H
#define COLOR_TEXTURE_H

#include "color.h"
#include "texture.h"

class ColorTexture : public Texture {
  public:
    ColorTexture() {}
    ColorTexture(Color i_color) {
      width = 1;
      height = 1;
      data = new Color*[1];
      data[0] = new Color[1];
      data[0][0] = i_color;
    }
};

#endif
