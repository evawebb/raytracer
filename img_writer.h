#ifndef IMG_WRITER_H
#define IMG_WRITER_H

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include "color.h"

class ImgWriter {
  public:
    ImgWriter() {
      width = 0; height = 0;
    }
    ImgWriter(int w, int h) {
      width = w; height = h; init();
    }
    ~ImgWriter();

    void write();
    void set(int x, int y, int r, int g, int b);
    void set(int x, int y, Color c);

  private:
    Color** img;
    int width, height;

    void init();
};

#endif
