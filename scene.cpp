#include "scene.h"

Scene::Scene() {
  width = 50;
  height = 50;
}

Scene::Scene(int w, int h) {
  width = w;
  height = h;
}

int* Scene::color_at(int x, int y) {
  float scale = (width < height) ? (width / 2.0) : (height / 2.0);
  float adj_x = (x - scale) / scale;
  float adj_y = (y - scale) / scale;
  Point origin(adj_x, adj_y, 0);
  Vector direction(0, 0, 1);

  int* color = new int[3];
  float t = spheres[0].intersect(origin, direction);
  if (t > 0) {
    float red_p = (0.5 - t) / 0.2;
    color[0] = red_p * 255;
  } else {
    color[0] = 0;
  }
  color[1] = 0;
  color[2] = 0;
  return color;
}

void Scene::add_sphere(float x, float y, float z, float r) {
  spheres.push_back(Sphere(Point(x, y, z), r));
}

void Scene::test() {
  std::cout << "The scene has " << spheres.size() << " spheres.\n";
  for (int i = 0; i < spheres.size(); i += 1) {
    std::cout << "Sphere " << i << ": (" << spheres[i].loc.x << ", " << spheres[i].loc.y << ", " << spheres[i].loc.z << "), with radius " << spheres[i].radius << "\n";
  }
}
