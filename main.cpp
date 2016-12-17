#include <cstdlib>
#include <iostream>
#include "img_writer.h"
#include "scene.h"
#include "color.h"
#include "material.h"

int main(int argc, char** argv) {
  int s_l = 1000;
  ImgWriter iw(s_l, s_l);
  Scene sc(s_l, s_l);

  Color white(1, 1, 1);
  double ai = 1;
  double di = 1;
  double si = 1;
  Material red(
    Color(1, 0, 0),
    Color(1, 0, 0),
    white,
    15,
    0.5,
    ai, di, si
  );
  Material green(
    Color(0, 1, 0),
    Color(0, 1, 0),
    white,
    15,
    0.5,
    ai, di, si
  );
  Material blue(
    Color(0, 0, 1),
    Color(0, 0, 1),
    white,
    1.5,
    0.5,
    ai, di, si
  );
  Material mirror(
    white,
    white,
    white,
    3,
    0.9,
    0, 0, si
  );

  int scene = 0;
  if (scene == 0) {
    sc.add_sphere(0.4, -0.4, 0.1, 0.1, red);
    sc.add_sphere(0.5, -0.5, 0.5, 0.3, green);
    sc.add_sphere(-0.5, -0.2, 1, 0.4, blue);
    sc.add_light(2, 0, 0, Color(0.3, 0.3, 0.3), white, white);
    sc.add_light(0, 0.2, -1, Color(0.3, 0.3, 0.3), white, white);
  } else if (scene == 1) {
    sc.add_sphere(0, 0.5, 0.5, 0.5, blue);
    sc.add_sphere(0, -0.3, 0.3, 0.1, red);
    sc.add_light(0, -1, 0.1, Color(0.3, 0.3, 0.3), white, white);
    sc.add_light(0, 1, -0.2, Color(0.3, 0.3, 0.3), white, white);
  } else if (scene == 2) {
    for (int x = 1; x < 10; x += 1) {
      for (int y = 1; y < 10; y += 1) {
        Material m(white, white, white, x * 2, 0, 0.1, 0.2, y * 0.05);
        sc.add_sphere(x * 0.2 - 1, y * 0.2 - 1, 1, 0.1, m);
      }
    }
    sc.add_light(0, 0, 0, Color(0.3, 0.3, 0.3), white, white);
  }

  std::cout << '\n';
  sc.test();

  std::cout << '\n';
  std::cout << "Rendering...\n";
  int num_buckets = 10;
  int* hist = new int[num_buckets];
  for (int i = 0; i < num_buckets; i += 1) {
    hist[i] = 0;
  }
  Color most_intense(0, 0, 0);
  for (int y = 0; y < s_l; y += 1) {
    for (int x = 0; x < s_l; x += 1) {
      Color c = sc.color_at(x, y, 5, 2);
      iw.set(x, y, c);

      int b = (c.r + c.g + c.b) / 3.0 * num_buckets;
      hist[b] += 1;
      if (c.r + c.g + c.b > most_intense.r + most_intense.g + most_intense.b) {
        most_intense = c;
      }
    }

    if (y % (s_l / 10) == 0) {
      std::cout << y << " of " << s_l << " rows rendered.\n";
    }
  }

  std::cout << '\n';
  std::cout << "Intensity values:\n";
  for (int i = 0; i < num_buckets; i += 1) {
    std::cout << hist[i] << '\n';
  }
  std::cout << "Most intense color:\n";
  std::cout << '(' << most_intense.r << ", " << most_intense.g << ", " << most_intense.b << ")\n";

  std::cout << '\n';
  std::cout << "Writing to file...\n";
  iw.write();

  return 0;
}
