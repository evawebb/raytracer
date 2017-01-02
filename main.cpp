#include <cstdlib>
#include <cmath>
#include <iostream>
#include "img_writer.h"
#include "scene.h"
#include "color.h"
#include "color_material.h"
#include "texture.h"
#include "matrix.h"

#define S_L 1080
#define ANTIALIASING 1

double rand_double() {
  int precision = 10000;
  return (float)(rand() % precision) / precision;
}

int main(int argc, char** argv) {
  int scene = 0;
  if (argc >= 2) {
    scene = atoi(argv[1]);
  }

  srand(time(NULL));
  int img_height = S_L;
  // int img_width = 16 * S_L / 9;
  int img_width = S_L;
  std::stringstream ss;
  ss << "scene_" << time(NULL) << '_' << scene << ".ppm";

  ImgWriter iw(ss.str(), img_width, img_height);
  Scene sc(img_width, img_height);

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

  if (scene == 0) {
    Model s1(0);
    s1.add_sphere(Point(0.4, -0.4, 0.1), 0.1, red);

    Model s2(1);
    s2.add_sphere(Point(0.5, -0.5, 0.5), 0.3, green);

    Model s3(2);
    s3.add_sphere(Point(-0.5, -0.2, 1), 0.4, blue);

    sc.add_model(s1);
    sc.add_model(s2);
    sc.add_model(s3);

    sc.add_light(2, 0, 0, Color(0.3, 0.3, 0.3), white, white);
    sc.add_light(0, 0.2, -1, Color(0.3, 0.3, 0.3), white, white);
  } else if (scene == 1) {
    Model s1(0);
    s1.add_sphere(Point(0, 0.5, 0.5), 0.5, blue);

    Model s2(1);
    s2.add_sphere(Point(0, -0.3, 0.3), 0.1, red);

    sc.add_model(s1);
    sc.add_model(s2);

    sc.add_light(0, -1, 0.1, Color(0.3, 0.3, 0.3), white, white);
    sc.add_light(0, 1, -0.2, Color(0.3, 0.3, 0.3), white, white);
  } else if (scene == 2) {
    Model m(0);
    for (int x = 1; x < 10; x += 1) {
      for (int y = 1; y < 10; y += 1) {
        ColorMaterial* mat = new ColorMaterial(white, white, white, x * 2, 0, 0.1, 0.2, y * 0.05);
        m.add_sphere(Point(x * 0.2 - 1, y * 0.2 - 1, 1), 0.1, mat);
      }
    }

    sc.add_model(m);

    sc.add_light(0, 0, 0, Color(0.3, 0.3, 0.3), white, white);
  } else if (scene == 3) {
    Model m(0);
    for (int i = 0; i < 100; i += 1) {
      Color c(rand_double(), rand_double(), rand_double());
      ColorMaterial* mat = new ColorMaterial(c, c, white, rand_double() * 20, rand_double(), 0.4, 0.4, 0.4);
      m.add_sphere(
        Point(
          rand_double() * 2 - 1, 
          rand_double() * 2 - 1,
          rand_double() * 2 + 1
        ),
        rand_double() * 0.2,
        mat
      );
    }

    sc.add_model(m);

    sc.add_light(0, 0, 0, white, white, white);
  } else if (scene == 4) {
    Model m(0);
    m.add_sphere(Point(0, 0, 1), 0.5, new ColorMaterial(
      Color(0, 1, 0), Color(0, 1, 0), white,
      2, 0, 0.5, 0.5, 0.5
    ));

    sc.add_model(m);

    sc.add_light(0, -1, 0, white, white, white);
  } else if (scene == 5) {
    double box_size = 1;

    Model spheres(0);
    spheres.add_sphere(Point(0.5, 0.4, 1.2), 0.5,  mirror);
    spheres.add_sphere(Point(-0.4, 0.3, 0.6), 0.4, mirror);
    spheres.add_sphere(Point(0.1, -0.5, 1.5), 0.2, mirror);

    Model planes(1);
    planes.add_plane(Point(box_size, 0, 0), Vector(-1, 0, 0), red);
    planes.add_plane(Point(-box_size, 0, 0), Vector(1, 0, 0), red);
    planes.add_plane(Point(0, box_size, 0), Vector(0, 1, 0), blue);
    planes.add_plane(Point(0, -box_size, 0), Vector(0, -1, 0), blue);
    planes.add_plane(Point(0, 0, 2 * box_size), Vector(0, 0, 1), green);
    planes.add_plane(Point(0, 0, 0), Vector(0, 0, -1), green);

    sc.add_model(spheres);
    sc.add_model(planes);

    sc.add_light(0, -0.8, 1, white, white, white);
    sc.add_light(-0.5, -0.5, 0.5, white, white, white);
  } else if (scene == 6) {
    double box_size = 1;

    Model spheres(0);
    spheres.add_sphere(Point(0.5, 0.4, 1.2), 0.5,  red);
    spheres.add_sphere(Point(-0.4, 0.3, 0.6), 0.4, blue);
    spheres.add_sphere(Point(0.1, -0.6, 1.5), 0.2, mirror);

    Model planes(1);
    planes.add_plane(Point(box_size, 0, 0), Vector(-1, 0, 0), red);
    planes.add_plane(Point(-box_size, 0, 0), Vector(1, 0, 0), red);
    planes.add_plane(Point(0, box_size, 0), Vector(0, 1, 0), mirror);
    planes.add_plane(Point(0, -box_size, 0), Vector(0, -1, 0), blue);
    planes.add_plane(Point(0, 0, 2 * box_size + 0.2), Vector(0, 0, 1), green);
    planes.add_plane(Point(0, 0, 0), Vector(0, 0, -1), green);

    sc.add_model(spheres);
    sc.add_model(planes);

    sc.add_light(0, -0.8, 1, white, white, white);
    sc.add_light(-0.5, -0.5, 0.5, white, white, white);
  } else if (scene == 7) {
    Model m(0);
    m.add_plane(Point(0, 0, 1), Vector(0, 0, 1), blue);
    // m.add_plane(Point(0, 0, 1), Vector(0, 0, -1), blue);

    sc.add_model(m);

    sc.add_light(0, 0, 0, white, white, white);
  } else if (scene == 8) {
    Model bg(0);
    bg.add_plane(Point(0, 0, 3), Vector(0, 0, -1), red);

    Model hemisphere(1);
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

        hemisphere.add_triangle(
          Point(
            rad * sin(left) * sin(top), 
            rad * cos(left) + y_offset, 
            rad * sin(left) * cos(top) + z_offset
          ),
          Point(
            rad * sin(left) * sin(bottom), 
            rad * cos(left) + y_offset, 
            rad * sin(left) * cos(bottom) + z_offset
          ),
          Point(
            rad * sin(right) * sin(top), 
            rad * cos(right) + y_offset, 
            rad * sin(right) * cos(top) + z_offset
          ),
          blue
        );
        hemisphere.add_triangle(
          Point(
            rad * sin(left) * sin(bottom), 
            rad * cos(left) + y_offset, 
            rad * sin(left) * cos(bottom) + z_offset
          ),
          Point(
            rad * sin(right) * sin(top), 
            rad * cos(right) + y_offset, 
            rad * sin(right) * cos(top) + z_offset
          ),
          Point(
            rad * sin(right) * sin(bottom), 
            rad * cos(right) + y_offset, 
            rad * sin(right) * cos(bottom) + z_offset
          ),
          blue
        );
      }
    }

    Model triangle(2);
    triangle.add_triangle(
      Point(rand_double(), -rand_double(), 2),
      Point(rand_double(), -rand_double(), 2),
      Point(rand_double(), -rand_double(), 2),
      green
    );

    sc.add_model(bg);
    sc.add_model(hemisphere);
    sc.add_model(triangle);

    sc.add_light(0, -1, 0, white, white, white);
  } else if (scene == 9) {
    Texture* elsa = new Texture("elsa.ppm");
    Material* txed = new Material(
      elsa,
      elsa,
      white,
      3,
      0,
      ai, di, si
    );

    Model m(0);
    m.add_triangle(
      Point(-1, -1,    2), Point(0, 0),
      Point(-1,  1,    1), Point(0, 1),
      Point( 1, -1,  1.5), Point(1, 0),
      txed
    );
    m.add_triangle(
      Point( 1, -1,  1.5), Point(1, 0),
      Point(-1,  1,    1), Point(0, 1),
      Point( 1,  1,  0.5), Point(1, 1),
      txed
    );

    sc.add_model(m);

    sc.add_light(0, -0.5, 0, white, white, white);
  } else if (scene == 10) {
    Texture* sakura = new Texture("sakura.ppm");
    Material* m = new Material(
      sakura,
      sakura,
      white,
      3, 0,
      ai, di, si
    ); 

    Model box(0);
    box.add_triangle(
      Point(-1, -1,  1.9), Point(0, 0),
      Point( 1, -1,  1.9), Point(1, 0),
      Point(-1,  1,  1.9), Point(0, 1),
      m
    );
    box.add_triangle(
      Point( 1, -1,  1.9), Point(1, 0),
      Point( 1,  1,  1.9), Point(1, 1),
      Point(-1,  1,  1.9), Point(0, 1),
      m
    );

    box.add_triangle(
      Point( 1, -1,  1.9), Point(0, 0),
      Point( 1, -1, -0.1), Point(1, 0),
      Point( 1,  1,  1.9), Point(0, 1),
      m
    );
    box.add_triangle(
      Point( 1, -1, -0.1), Point(1, 0),
      Point( 1,  1, -0.1), Point(1, 1),
      Point( 1,  1,  1.9), Point(0, 1),
      m
    );

    box.add_triangle(
      Point( 1, -1, -0.1), Point(0, 0),
      Point(-1, -1, -0.1), Point(1, 0),
      Point( 1,  1, -0.1), Point(0, 1),
      m
    );
    box.add_triangle(
      Point(-1, -1, -0.1), Point(1, 0),
      Point(-1,  1, -0.1), Point(1, 1),
      Point( 1,  1, -0.1), Point(0, 1),
      m
    );

    box.add_triangle(
      Point(-1, -1, -0.1), Point(0, 0),
      Point(-1, -1,  1.9), Point(1, 0),
      Point(-1,  1, -0.1), Point(0, 1),
      m
    );
    box.add_triangle(
      Point(-1, -1,  1.9), Point(1, 0),
      Point(-1,  1,  1.9), Point(1, 1),
      Point(-1,  1, -0.1), Point(0, 1),
      m
    );

    box.add_triangle(
      Point(-1, -1, -0.1), Point(0, 0),
      Point( 1, -1, -0.1), Point(1, 0),
      Point(-1, -1,  1.9), Point(0, 1),
      m
    );
    box.add_triangle(
      Point( 1, -1, -0.1), Point(1, 0),
      Point( 1, -1,  1.9), Point(1, 1),
      Point(-1, -1,  1.9), Point(0, 1),
      m
    );

    box.add_triangle(
      Point(-1,  1,  1.9), Point(0, 0),
      Point( 1,  1,  1.9), Point(1, 0),
      Point(-1,  1, -0.1), Point(0, 1),
      m
    );
    box.add_triangle(
      Point( 1,  1,  1.9), Point(1, 0),
      Point( 1,  1, -0.1), Point(1, 1), 
      Point(-1,  1, -0.1), Point(0, 1),
      m
    );

    Model sphere(1);
    sphere.add_sphere(Point(0, 0.2, 1.1), 0.4, mirror);

    sc.add_model(box);
    sc.add_model(sphere);

    sc.add_light(0, -0.2, 0, white, white, white);
    sc.add_light(0, -0.8, 1.1, white, white, white);
  } else if (scene == 11) {
    Texture* koboli = new Texture("koboli.ppm");
    Material* txed = new Material(
      koboli,
      koboli,
      white,
      3,
      0,
      ai, di, si
    );
    Model model(0);
    model.scale(2, 1, 1);
    model.translate(Vector(0.3, -0.2, 3));
    model.add_triangle(
      Point(-1, -1,   2), Point(0, 0),
      Point(-1,  1,   1), Point(0, 1),
      Point( 1, -1, 1.5), Point(1, 0),
      txed
    );
    model.add_triangle(
      Point( 1, -1, 1.5), Point(1, 0),
      Point(-1,  1,   1), Point(0, 1),
      Point( 1,  1, 0.5), Point(1, 1),
      txed
    );

    sc.add_model(model);
    sc.add_light(0, -0.5, 0, white, white, white);
  } else if (scene == 12) {
    Texture* sakura = new Texture("sakura.ppm");
    Material* m = new Material(
      sakura,
      sakura,
      white,
      3, 0,
      ai, di, si
    ); 

    Model box(0);
    box.scale(3, 3, 3);
    box.rotate(0.5, Vector(1, -1, 1));
    box.add_triangle(
      Point(-1, -1,  1), Point(0, 0),
      Point( 1, -1,  1), Point(1, 0),
      Point(-1,  1,  1), Point(0, 1),
      m
    );
    box.add_triangle(
      Point( 1, -1,  1), Point(1, 0),
      Point( 1,  1,  1), Point(1, 1),
      Point(-1,  1,  1), Point(0, 1),
      m
    );

    box.add_triangle(
      Point( 1, -1,  1), Point(0, 0),
      Point( 1, -1, -1), Point(1, 0),
      Point( 1,  1,  1), Point(0, 1),
      m
    );
    box.add_triangle(
      Point( 1, -1, -1), Point(1, 0),
      Point( 1,  1, -1), Point(1, 1),
      Point( 1,  1,  1), Point(0, 1),
      m
    );

    box.add_triangle(
      Point( 1, -1, -1), Point(0, 0),
      Point(-1, -1, -1), Point(1, 0),
      Point( 1,  1, -1), Point(0, 1),
      m
    );
    box.add_triangle(
      Point(-1, -1, -1), Point(1, 0),
      Point(-1,  1, -1), Point(1, 1),
      Point( 1,  1, -1), Point(0, 1),
      m
    );

    box.add_triangle(
      Point(-1, -1, -1), Point(0, 0),
      Point(-1, -1,  1), Point(1, 0),
      Point(-1,  1, -1), Point(0, 1),
      m
    );
    box.add_triangle(
      Point(-1, -1,  1), Point(1, 0),
      Point(-1,  1,  1), Point(1, 1),
      Point(-1,  1, -1), Point(0, 1),
      m
    );

    box.add_triangle(
      Point(-1, -1, -1), Point(0, 0),
      Point( 1, -1, -1), Point(1, 0),
      Point(-1, -1,  1), Point(0, 1),
      m
    );
    box.add_triangle(
      Point( 1, -1, -1), Point(1, 0),
      Point( 1, -1,  1), Point(1, 1),
      Point(-1, -1,  1), Point(0, 1),
      m
    );

    box.add_triangle(
      Point(-1,  1,  1), Point(0, 0),
      Point( 1,  1,  1), Point(1, 0),
      Point(-1,  1, -1), Point(0, 1),
      m
    );
    box.add_triangle(
      Point( 1,  1,  1), Point(1, 0),
      Point( 1,  1, -1), Point(1, 1), 
      Point(-1,  1, -1), Point(0, 1),
      m
    );

    Model sphere(1);
    sphere.add_sphere(Point(0, 0.2, 1.1), 0.4, mirror);

    sc.add_model(box);
    sc.add_model(sphere);

    sc.add_light(0, -0.2, 0, white, white, white);
    sc.add_light(0, -0.8, 1.1, white, white, white);
  } else if (scene == 13) {
    Texture* elsa = new Texture("elsa.ppm");
    Material* m_tex = new Material(
      elsa, elsa, white,
      3, 0, ai, di, si
    );

    Model box(0);
    box.translate(Vector(0, 0, 2));
    double w = 0.5;
    box.add_triangle(
      Point(-w, -w,  1), Point(0, 0),
      Point( w, -w,  1), Point(1, 0),
      Point(-w,  w,  1), Point(0, 1), 
      m_tex
    );
    box.add_triangle(
      Point( w, -w,  1), Point(1, 0),
      Point( w,  w,  1), Point(1, 1),
      Point(-w,  w,  1), Point(0, 1),
      m_tex
    );

    box.add_triangle(
      Point( 1, -w,  w), Point(0, 0),
      Point( 1, -w, -w), Point(1, 0),
      Point( 1,  w,  w), Point(0, 1),
      m_tex
    );
    box.add_triangle(
      Point( 1, -w, -w), Point(1, 0),
      Point( 1,  w, -w), Point(1, 1),
      Point( 1,  w,  w), Point(0, 1),
      m_tex
    );

    box.add_triangle(
      Point( w, -w, -1), Point(0, 0),
      Point(-w, -w, -1), Point(1, 0),
      Point( w,  w, -1), Point(0, 1),
      m_tex
    );
    box.add_triangle(
      Point(-w, -w, -1), Point(1, 0),
      Point(-w,  w, -1), Point(1, 1),
      Point( w,  w, -1), Point(0, 1),
      m_tex
    );

    box.add_triangle(
      Point(-1, -w, -w), Point(0, 0),
      Point(-1, -w,  w), Point(1, 0),
      Point(-1,  w, -w), Point(0, 1),
      m_tex
    );
    box.add_triangle(
      Point(-1, -w,  w), Point(1, 0),
      Point(-1,  w,  w), Point(1, 1),
      Point(-1,  w, -w), Point(0, 1),
      m_tex
    );

    box.add_triangle(
      Point(-w, -1, -w), Point(0, 0),
      Point( w, -1, -w), Point(1, 0),
      Point(-w, -1,  w), Point(0, 1),
      m_tex
    );
    box.add_triangle(
      Point( w, -1, -w), Point(1, 0),
      Point( w, -1,  w), Point(1, 1),
      Point(-w, -1,  w), Point(0, 1),
      m_tex
    );

    box.add_triangle(
      Point(-w,  1,  w), Point(0, 0),
      Point( w,  1,  w), Point(1, 0),
      Point(-w,  1, -w), Point(0, 1),
      m_tex
    );
    box.add_triangle(
      Point( w,  1,  w), Point(1, 0),
      Point( w,  1, -w), Point(1, 1), 
      Point(-w,  1, -w), Point(0, 1),
      m_tex
    );

    Model bg(1);
    double dist = 5;
    bg.add_triangle(
      Point(-100, -100, dist),
      Point( 100, -100, dist),
      Point(-100,  100, dist),
      green
    );
    bg.add_triangle(
      Point(-100,  100, dist),
      Point( 100, -100, dist),
      Point( 100,  100, dist),
      green
    );

    sc.add_model(box);
    sc.add_model(bg);

    sc.rotate_cam(-1, Vector(1, -1, 1));
    sc.translate_cam(Vector(-1.5, -1, 0.5));

    sc.add_light(0, 0, 0, white, white, white);
    sc.add_light(0, 0, 2, white, white, white);
  } else if (scene == 14) {
    Model bg(0);
    double dist = 5;
    bg.add_triangle(
      Point(-100, -100, dist),
      Point( 100, -100, dist),
      Point(-100,  100, dist),
      green
    );
    bg.add_triangle(
      Point(-100,  100, dist),
      Point( 100, -100, dist),
      Point( 100,  100, dist),
      green
    );

    Model sphere(1);
    sphere.translate(Vector(0, 0, 2));
    double step = 0.05 * 3.14159;
    for (double i = 0; i < 2 * 3.14159; i += step) {
      for (double j = 0; j < 3.14159; j += step) {
        double top = j;
        double bottom = j + step;
        double left = i;
        double right = i + step;

        Point o(0, 0, 0);
        Point a(
          sin(top) * cos(left),
          cos(top),
          sin(top) * sin(left)
        );
        Point b(
          sin(top) * cos(right),
          cos(top),
          sin(top) * sin(right)
        );
        Point c(
          sin(bottom) * cos(left),
          cos(bottom),
          sin(bottom) * sin(left)
        );
        Point d(
          sin(bottom) * cos(right),
          cos(bottom),
          sin(bottom) * sin(right)
        );

        sphere.add_triangle(
          a, a - o,
          b, b - o,
          c, c - o,
          blue
        );
        sphere.add_triangle(
          c, c - o,
          b, b - o,
          d, d - o,
          blue
        );
      }
    }

    sc.add_model(bg);
    sc.add_model(sphere);

    sc.add_light(-0.5, -0.9, 0, white, white, white);
  } else if (scene == 15) {
    Model pikachu(0);
    pikachu.scale(0.008, 0.008, 0.008);
    pikachu.rotate(3.5, Vector(1, 0, 0));
    pikachu.rotate(-0.4, Vector(0, 1, 0));
    pikachu.translate(Vector(0, 1, 1.2));
    pikachu.load_obj_file("models/Pikachu/singletex/pikachu.obj", blue);

    Model bg(1);
    bg.add_plane(Point( 0,  0,     2), Vector( 0,  0, -1), green);

    sc.add_model(pikachu);
    sc.add_model(bg);

    sc.add_light(0, -0.99, 1, white, white, white);
    sc.add_light(0, -0.5, 0, white, white, white);
  }

  std::cout << '\n';
  std::cout << "Rendering scene " << scene << "...\n";
  Color most_intense(0, 0, 0);
  for (int y = 0; y < img_height; y += 1) {
    for (int x = 0; x < img_width; x += 1) {
      Color c = sc.color_at(x, y, 3, ANTIALIASING);
      iw.set(x, y, c);

      if (c.r + c.g + c.b > most_intense.r + most_intense.g + most_intense.b) {
        most_intense = c;
      }
    }

    if ((y + 1) % (img_height / 100) == 0) {
      std::cout << (y + 1) << " of " << img_height << " rows rendered.\n";
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
