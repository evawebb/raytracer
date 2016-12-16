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
  double scale = (width < height) ? (width / 2.0) : (height / 2.0);
  double adj_x = (x - scale) / scale;
  double adj_y = (y - scale) / scale;
  Point origin(adj_x, adj_y, 0);
  Vector direction(0, 0, 1);
  Color c(0, 0, 0);

  // Obviously replace these at some point.
  Color diffuse_material(1, 1, 1);
  Color ambient_material(1, 1, 1);

  int nearest_intersect = -1;
  IntersectionEvent n_ie(
    Point(0, 0, 0),
    Vector(0, 0, 0),
    false,
    Point(0, 0, 0),
    1000000,
    Vector(0, 0, 0),
    -1
  );
  for (int s = 0; s < spheres.size(); s += 1) {
    IntersectionEvent ie = spheres[s].intersect(origin, direction);

    if (ie.intersected && ie.distance < n_ie.distance) {
      nearest_intersect = s;
      n_ie = ie;
    }
  }

  if (nearest_intersect >= 0) {
    Color diffuse_comp(0, 0, 0), ambient_comp(0, 0, 0);

    for (int l = 0; l < lights.size(); l += 1) {
      Vector l_vector = (lights[l].loc - n_ie.intersection).normalized();

      bool blocked = false;
      for (int s = 0; s < spheres.size(); s += 1) {
        IntersectionEvent b_ie = spheres[s].intersect(
          n_ie.intersection, 
          l_vector
        );
        blocked = blocked | b_ie.intersected;
      }

      if (!blocked) {
        diffuse_comp = diffuse_comp + 
          lights[l].diffuse *
          diffuse_material * 
          std::max(0.0, l_vector.dot(n_ie.normal));
      }

      ambient_comp = ambient_comp +
        lights[l].ambient * 
        ambient_material;
    }

    c = diffuse_comp + ambient_comp;
  }

  return c;
}

void Scene::add_sphere(double x, double y, double z, double r) {
  spheres.push_back(Sphere(spheres.size(), Point(x, y, z), r));
}

void Scene::add_light(double x, double y, double z, Color i_diffuse, Color i_ambient) {
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
