#ifndef TEXTURE_H
#define TEXTURE_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include "color.h"
#include "point.h"

class Texture {
  public:
    Texture() {}
    Texture(std::string fn) {
      load_image(fn);
    }
    ~Texture();

    Color texel(Point t);

    Color** data;
    int width, height;

  private:
    void load_image(std::string fn);
};

#endif
