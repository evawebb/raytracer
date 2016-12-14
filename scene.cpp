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
  int* color = new int[3];
  if (sqrt(x * x + y * y) < 100) {
    color[0] = 255;
  } else {
    color[0] = 0;
  }
  color[1] = 0;
  color[2] = 0;
  return color;
}

void Scene::add_sphere(int x, int y, int z, float r) {
  spheres.push_back(Sphere(Point(x, y, z), r));
}

void Scene::test() {
  std::cout << "The scene has " << spheres.size() << " spheres.\n";
  for (int i = 0; i < spheres.size(); i += 1) {
    std::cout << "Sphere " << i << ": (" << spheres[i].loc.x << ", " << spheres[i].loc.y << ", " << spheres[i].loc.z << "), with radius " << spheres[i].radius << "\n";
  }
}
