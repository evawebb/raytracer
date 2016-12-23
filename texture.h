#ifndef TEXTURE_H
#define TEXTURE_H

#include <fstream>
#include <string>
#include <iostream>
#include "color.h"

class Texture {
  public:
    Texture() {}
    Texture(std::string fn) {
      load_image(fn);
    }
    ~Texture();

    Color texel(double u, double v);

  public:
    Color** data;
    int width, height;

  private:
    void load_image(std::string fn);
};

#endif
