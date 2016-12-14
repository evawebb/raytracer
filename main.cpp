#include <cstdlib>
#include <iostream>
#include "img_writer.h"
#include "scene.h"

int main(int argc, char** argv) {
  ImgWriter iw(256, 256);
  Scene sc(256, 256);
  sc.add_sphere(1, 1, 1, 3.5);
  sc.test();

  for (int y = 0; y < 256; y += 1) {
    for (int x = 0; x < 256; x += 1) {
      int* c = sc.color_at(x, y);
      iw.set(x, y, c[0], c[1], c[2]);
    }
  }

  iw.write();

  Sphere s(Point(1, 2, 3), 4);

  return 0;
}
