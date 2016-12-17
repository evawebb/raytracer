#include <cstdlib>
#include <iostream>
#include "img_writer.h"
#include "scene.h"

int main(int argc, char** argv) {
  int s_l = 1000;
  ImgWriter iw(s_l, s_l);
  Scene sc(s_l, s_l);
  Color ambient(1, 1, 1);

  if (true) {
    sc.add_sphere(
      0.4, -0.4, 0.1, 
      0.1,
      Color(1, 0, 0),
      ambient,
      0.5
    );
    sc.add_sphere(
      0.5, -0.5, 0.5, 
      0.3,
      Color(0, 0, 1),
      ambient,
      0.5
    );
    sc.add_sphere(
      -0.5, -0.2, 1, 
      0.4,
      Color(0, 1, 0),
      ambient,
      0.5
    );
    sc.add_light(2, 0, 0, Color(0.3, 0.3, 0.3), Color(1, 1, 1));
    sc.add_light(0, 0.2, -1, Color(0.3, 0.3, 0.3), Color(1, 1, 1));
  } else {
    sc.add_sphere(
      0, 0.5, 0.5, 
      0.5,
      Color(0, 0, 1),
      ambient,
      0.5
    );
    sc.add_sphere(
      0, -0.3, 0.3, 
      0.1,
      Color(1, 0, 0),
      ambient,
      0
    );
    sc.add_light(0, -1, 0.1, Color(0.3, 0.3, 0.3), Color(1, 1, 1));
    sc.add_light(0, 1, -0.2, Color(0.3, 0.3, 0.3), Color(1, 1, 1));
  }

  std::cout << '\n';
  sc.test();

  std::cout << '\n';
  std::cout << "Rendering...\n";
  for (int y = 0; y < s_l; y += 1) {
    for (int x = 0; x < s_l; x += 1) {
      Color c = sc.color_at(x, y, 2);
      iw.set(x, y, c);
    }

    if (y % (s_l / 10) == 0) {
      std::cout << y << " of " << s_l << " rows rendered.\n";
    }
  }

  std::cout << '\n';
  std::cout << "Writing to file...\n";
  iw.write();

  return 0;
}
