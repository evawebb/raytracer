#ifndef IMG_WRITER_H
#define IMG_WRITER_H

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "color.h"

class ImgWriter {
  public:
    ImgWriter() {
      fn = "img.ppm";
      width = 0; height = 0;
    }
    ImgWriter(std::string i_fn, int w, int h) {
      fn = i_fn;
      width = w; height = h; init();
    }
    ~ImgWriter();

    void write();
    void set(int x, int y, int r, int g, int b);
    void set(int x, int y, Color c);

  private:
    Color** img;
    std::string fn;
    int width, height;

    void init();
};

#endif
