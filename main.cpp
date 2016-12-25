#include <cstdlib>
#include <cmath>
#include <iostream>
#include "img_writer.h"
#include "scene.h"
#include "color.h"
#include "color_material.h"
#include "texture.h"

#define SCENE 10
#define S_L 1000
#define ANTIALIASING 2

double rand_double() {
  int precision = 10000;
  return (float)(rand() % precision) / precision;
}

int main(int argc, char** argv) {
  srand(time(NULL));
  int s_l = S_L;
  std::stringstream ss;
  ss << "scene_" << SCENE << ".ppm";

  ImgWriter iw(ss.str(), s_l, s_l);
  Scene sc(s_l, s_l);

  Color white(1, 1, 1);
  double ai = 0.5;
  double di = 0.5;
  double si = 0.5;
  ColorMaterial* red = new ColorMaterial(
    Color(1, 0, 0),
    Color(1, 0, 0),
    white,
    2,
    0,
    ai, di, si
  );
  ColorMaterial* green = new ColorMaterial(
    Color(0, 1, 0),
    Color(0, 1, 0),
    white,
    2,
    0,
    ai, di, si
  );
  ColorMaterial* blue = new ColorMaterial(
    Color(0, 0, 1),
    Color(0, 0, 1),
    white,
    1.5,
    0,
    ai, di, si
  );
  ColorMaterial* mirror = new ColorMaterial(
    white,
    white,
    white,
    3,
    0.9,
    0, 0, si
  );

  if (SCENE == 0) {
    sc.add_sphere(0.4, -0.4, 0.1, 0.1, red);
    sc.add_sphere(0.5, -0.5, 0.5, 0.3, green);
    sc.add_sphere(-0.5, -0.2, 1, 0.4, blue);
    sc.add_light(2, 0, 0, Color(0.3, 0.3, 0.3), white, white);
    sc.add_light(0, 0.2, -1, Color(0.3, 0.3, 0.3), white, white);
  } else if (SCENE == 1) {
    sc.add_sphere(0, 0.5, 0.5, 0.5, blue);
    sc.add_sphere(0, -0.3, 0.3, 0.1, red);
    sc.add_light(0, -1, 0.1, Color(0.3, 0.3, 0.3), white, white);
    sc.add_light(0, 1, -0.2, Color(0.3, 0.3, 0.3), white, white);
  } else if (SCENE == 2) {
    for (int x = 1; x < 10; x += 1) {
      for (int y = 1; y < 10; y += 1) {
        ColorMaterial* m = new ColorMaterial(white, white, white, x * 2, 0, 0.1, 0.2, y * 0.05);
        sc.add_sphere(x * 0.2 - 1, y * 0.2 - 1, 1, 0.1, m);
      }
    }
    sc.add_light(0, 0, 0, Color(0.3, 0.3, 0.3), white, white);
  } else if (SCENE == 3) {
    for (int i = 0; i < 100; i += 1) {
      Color c(rand_double(), rand_double(), rand_double());
      ColorMaterial* m = new ColorMaterial(c, c, white, rand_double() * 20, rand_double(), 0.4, 0.4, 0.4);
      sc.add_sphere(
        rand_double() * 2 - 1, 
        rand_double() * 2 - 1,
        rand_double() * 2 + 1,
        rand_double() * 0.2,
        m
      );
    }
    sc.add_light(0, 0, 0, white, white, white);
  } else if (SCENE == 4) {
    sc.add_sphere(0, 0, 1, 0.5, new ColorMaterial(
      Color(0, 1, 0), Color(0, 1, 0), white,
      2, 0, 0.5, 0.5, 0.5
    ));
    sc.add_light(0, -1, 0, white, white, white);
  } else if (SCENE == 5) {
    double box_size = 1;
    sc.add_sphere(0.5, 0.4, 1.2, 0.5,  mirror);
    sc.add_sphere(-0.4, 0.3, 0.6, 0.4, mirror);
    sc.add_sphere(0.1, -0.5, 1.5, 0.2, mirror);
    sc.add_plane(Point(box_size, 0, 0), Vector(-1, 0, 0), red);
    sc.add_plane(Point(-box_size, 0, 0), Vector(1, 0, 0), red);
    sc.add_plane(Point(0, box_size, 0), Vector(0, 1, 0), blue);
    sc.add_plane(Point(0, -box_size, 0), Vector(0, -1, 0), blue);
    sc.add_plane(Point(0, 0, 2 * box_size), Vector(0, 0, 1), green);
    sc.add_plane(Point(0, 0, 0), Vector(0, 0, -1), green);
    sc.add_light(0, -0.8, 1, white, white, white);
    sc.add_light(-0.5, -0.5, 0.5, white, white, white);
  } else if (SCENE == 6) {
    double box_size = 1;
    sc.add_sphere(0.5, 0.4, 1.2, 0.5,  red);
    sc.add_sphere(-0.4, 0.3, 0.6, 0.4, blue);
    sc.add_sphere(0.1, -0.6, 1.5, 0.2, mirror);
    sc.add_plane(Point(box_size, 0, 0), Vector(-1, 0, 0), red);
    sc.add_plane(Point(-box_size, 0, 0), Vector(1, 0, 0), red);
    sc.add_plane(Point(0, box_size, 0), Vector(0, 1, 0), mirror);
    sc.add_plane(Point(0, -box_size, 0), Vector(0, -1, 0), blue);
    sc.add_plane(Point(0, 0, 2 * box_size + 0.2), Vector(0, 0, 1), green);
    sc.add_plane(Point(0, 0, 0), Vector(0, 0, -1), green);
    sc.add_light(0, -0.8, 1, white, white, white);
    sc.add_light(-0.5, -0.5, 0.5, white, white, white);
  } else if (SCENE == 7) {
    sc.add_plane(Point(0, 0, 1), Vector(0, 0, 1), blue);
    // sc.add_plane(Point(0, 0, 1), Vector(0, 0, -1), blue);
    sc.add_light(0, 0, 0, white, white, white);
  } else if (SCENE == 8) {
    sc.add_plane(Point(0, 0, 3), Vector(0, 0, -1), red);
    double rad = 0.5;
    double y_offset = 0.7;
    double z_offset = 1;
    double step = 3.14159 / 20;
    for (double i = 0; i < 2 * 3.14159; i += step) {
      for (double j = 0; j < 0.5 * 3.14159; j += step) {
        double top = i;
        double bottom = i + step;
        double left = j;
        double right = j + step;

        sc.add_triangle(
          Point(
            rad * sin(left) * sin(top), 
            rad * cos(left) + y_offset, 
            rad * sin(left) * cos(top) + z_offset
          ), 0, 0,
          Point(
            rad * sin(left) * sin(bottom), 
            rad * cos(left) + y_offset, 
            rad * sin(left) * cos(bottom) + z_offset
          ), 0, 0,
          Point(
            rad * sin(right) * sin(top), 
            rad * cos(right) + y_offset, 
            rad * sin(right) * cos(top) + z_offset
          ), 0, 0,
          blue
        );
        sc.add_triangle(
          Point(
            rad * sin(left) * sin(bottom), 
            rad * cos(left) + y_offset, 
            rad * sin(left) * cos(bottom) + z_offset
          ), 0, 0,
          Point(
            rad * sin(right) * sin(top), 
            rad * cos(right) + y_offset, 
            rad * sin(right) * cos(top) + z_offset
          ), 0, 0,
          Point(
            rad * sin(right) * sin(bottom), 
            rad * cos(right) + y_offset, 
            rad * sin(right) * cos(bottom) + z_offset
          ), 0, 0,
          blue
        );
      }
    }
    sc.add_triangle(
      Point(rand_double(), -rand_double(), 2), 0, 0,
      Point(rand_double(), -rand_double(), 2), 0, 0,
      Point(rand_double(), -rand_double(), 2), 0, 0,
      green
    );
    sc.add_light(0, -1, 0, white, white, white);
  } else if (SCENE == 9) {
    Texture* elsa = new Texture("elsa.ppm");
    Material* txed = new Material(
      elsa,
      elsa,
      white,
      3,
      0,
      ai, di, si
    );
    sc.add_triangle(
      Point(-1, -1,    2), 0, 0,
      Point(-1,  1,    1), 0, 1,
      Point( 1, -1,  1.5), 1, 0,
      txed
    );
    sc.add_triangle(
      Point( 1, -1,  1.5), 1, 0,
      Point(-1,  1,    1), 0, 1,
      Point( 1,  1,  0.5), 1, 1,
      txed
    );
    sc.add_light(0, -0.5, 0, white, white, white);
  } else if (SCENE == 10) {
    Texture* sakura = new Texture("sakura.ppm");
    Material* m = new Material(
      sakura,
      sakura,
      white,
      3, 0,
      ai, di, si
    );

    sc.add_triangle(
      Point(-1, -1,  1.9), 0, 0,
      Point( 1, -1,  1.9), 1, 0,
      Point(-1,  1,  1.9), 0, 1,
      m
    );
    sc.add_triangle(
      Point( 1, -1,  1.9), 1, 0,
      Point( 1,  1,  1.9), 1, 1,
      Point(-1,  1,  1.9), 0, 1,
      m
    );

    sc.add_triangle(
      Point( 1, -1,  1.9), 0, 0,
      Point( 1, -1, -0.1), 1, 0,
      Point( 1,  1,  1.9), 0, 1,
      m
    );
    sc.add_triangle(
      Point( 1, -1, -0.1), 1, 0,
      Point( 1,  1, -0.1), 1, 1,
      Point( 1,  1,  1.9), 0, 1,
      m
    );

    sc.add_triangle(
      Point( 1, -1, -0.1), 0, 0,
      Point(-1, -1, -0.1), 1, 0,
      Point( 1,  1, -0.1), 0, 1,
      m
    );
    sc.add_triangle(
      Point(-1, -1, -0.1), 1, 0,
      Point(-1,  1, -0.1), 1, 1,
      Point( 1,  1, -0.1), 0, 1,
      m
    );

    sc.add_triangle(
      Point(-1, -1, -0.1), 0, 0,
      Point(-1, -1,  1.9), 1, 0,
      Point(-1,  1, -0.1), 0, 1,
      m
    );
    sc.add_triangle(
      Point(-1, -1,  1.9), 1, 0,
      Point(-1,  1,  1.9), 1, 1,
      Point(-1,  1, -0.1), 0, 1,
      m
    );

    sc.add_triangle(
      Point(-1, -1, -0.1), 0, 0,
      Point( 1, -1, -0.1), 1, 0,
      Point(-1, -1,  1.9), 0, 1,
      m
    );
    sc.add_triangle(
      Point( 1, -1, -0.1), 1, 0,
      Point( 1, -1,  1.9), 1, 1,
      Point(-1, -1,  1.9), 0, 1,
      m
    );

    sc.add_triangle(
      Point(-1,  1,  1.9), 0, 0,
      Point( 1,  1,  1.9), 1, 0,
      Point(-1,  1, -0.1), 0, 1,
      m
    );
    sc.add_triangle(
      Point( 1,  1,  1.9), 1, 0,
      Point( 1,  1, -0.1), 1, 1, 
      Point(-1,  1, -0.1), 0, 1,
      m
    );

    sc.add_sphere(0, 0, 1.1, 0.4, mirror);
    sc.add_light(0, -0.2, 0, white, white, white);
    sc.add_light(0, -0.8, 1.1, white, white, white);
  }

  std::cout << '\n';
  std::cout << "Rendering...\n";
  Color most_intense(0, 0, 0);
  for (int y = 0; y < s_l; y += 1) {
    for (int x = 0; x < s_l; x += 1) {
      Color c = sc.color_at(x, y, 5, ANTIALIASING);
      iw.set(x, y, c);

      if (c.r + c.g + c.b > most_intense.r + most_intense.g + most_intense.b) {
        most_intense = c;
      }
    }

    if (y % (s_l / 10) == 0) {
      std::cout << y << " of " << s_l << " rows rendered.\n";
    }
  }

  std::cout << '\n';
  std::cout << "Most intense color:\n";
  std::cout << most_intense.to_s() << '\n';

  std::cout << '\n';
  std::cout << "Writing to file...\n";
  iw.write();

  return 0;
}
