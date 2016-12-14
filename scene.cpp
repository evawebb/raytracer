#include "scene.h"

Scene::Scene() {
  width = 50;
  height = 50;
}

Scene::Scene(int w, int h) {
  width = w;
  height = h;
}

Color Scene::color_at(int x, int y) {
  float scale = (width < height) ? (width / 2.0) : (height / 2.0);
  float adj_x = (x - scale) / scale;
  float adj_y = (y - scale) / scale;
  Point origin(adj_x, adj_y, 0);
  Vector direction(0, 0, 1);
  Color c(0, 0, 0);

  // Obviously replace these at some point.
  Color diffuse_material(1, 0.3, 0.3);
  Color ambient_material(1, 1, 1);

  for (int s = 0; s < spheres.size(); s += 1) {
    IntersectionEvent ie = spheres[s].intersect(origin, direction);

    if (ie.intersected) {
      Color diffuse_comp(0, 0, 0), ambient_comp(0, 0, 0);

      for (int l = 0; l < lights.size(); l += 1) {
        Vector l_vector = lights[l].loc - ie.intersection;

        Color diffuse_add = 
          lights[l].diffuse *
          diffuse_material * 
          std::max(0.0f, l_vector.dot(ie.normal));
        diffuse_comp = diffuse_comp + diffuse_add;
        ambient_comp = ambient_comp +
          lights[l].ambient * 
          ambient_material;
      }

      c = diffuse_comp + ambient_comp;
    }
  }

  return c;
}

void Scene::add_sphere(float x, float y, float z, float r) {
  spheres.push_back(Sphere(Point(x, y, z), r));
}

void Scene::add_light(float x, float y, float z, Color i_diffuse, Color i_ambient) {
  lights.push_back(Light(
    Point(x, y, z),
    i_diffuse,
    i_ambient
  ));
}

void Scene::test() {
  std::cout << "The scene has " << spheres.size() << " spheres.\n";
  for (int i = 0; i < spheres.size(); i += 1) {
    std::cout << "Sphere " << i << ": (" << spheres[i].loc.x << ", " << spheres[i].loc.y << ", " << spheres[i].loc.z << "), with radius " << spheres[i].radius << "\n";
  }

  std::cout << "The scene has " << lights.size() << " lights.\n";
  for (int i = 0; i < lights.size(); i += 1) {
    std::cout << "Light " << i << ": (" << lights[i].loc.x << ", " << lights[i].loc.y << ", " << lights[i].loc.z << ")\n";
  }
}
