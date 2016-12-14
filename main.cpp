#include <cstdlib>
#include <iostream>
#include "img_writer.h"
#include "scene.h"

int main(int argc, char** argv) {
  int s_l = 1000;
  ImgWriter iw(s_l, s_l);
  Scene sc(s_l, s_l);
  sc.add_sphere(0.5, -0.5, 0.5, 0.3);
  sc.add_sphere(-0.5, -0.2, 1, 0.4);
  sc.add_light(0, -2, -1, Color(1, 1, 1), Color(0.3, 0.3, 0.3));
  sc.add_light(0, 0, -1, Color(0, 0, 1), Color(0.3, 0.3, 0.3));
  sc.test();

  for (int y = 0; y < s_l; y += 1) {
    for (int x = 0; x < s_l; x += 1) {
      Color c = sc.color_at(x, y);
      iw.set(x, y, c);
    }
  }

  iw.write();

  Sphere s(Point(1, 2, 3), 4);

  return 0;
}
