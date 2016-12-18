#include "scene.h"

Scene::Scene() {
  width = 50;
  height = 50;
}

Scene::Scene(int w, int h) {
  width = w;
  height = h;
}

Color Scene::color_at(int x, int y, double focal_length, int aa) {
  double dim = (width < height) ? width : height;
  double scale = dim / 2;
  double adj_x = (x - scale) / scale;
  double adj_y = (y - scale) / scale;

  double total_r = 0;
  double total_g = 0;
  double total_b = 0;

  for (int aa_x = 0; aa_x < aa; aa_x += 1) {
    double adj_x_aa = (1 + 2 * aa_x) / (2 * aa * scale);

    for (int aa_y = 0; aa_y < aa; aa_y += 1) {
      double adj_y_aa = (1 + 2 * aa_y) / (2 * aa * scale);

      Point origin(adj_x + adj_x_aa, adj_y + adj_y_aa, 0);
      Vector direction = (origin - Point(0, 0, -focal_length)).normalized();

      Color c = cast_ray(origin, direction, 10);
      total_r += c.r;
      total_g += c.g;
      total_b += c.b;
    }
  }

  return Color(
    total_r / (aa * aa),
    total_g / (aa * aa),
    total_b / (aa * aa)
  );
}

Color Scene::cast_ray(Point origin, Vector direction, int limit) {
  if (limit > 0) {
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
    Material material;
    for (int s = 0; s < objects.size(); s += 1) {
      IntersectionEvent ie = objects[s]->intersect(origin, direction);

      if (ie.intersected && ie.distance < n_ie.distance) {
        nearest_intersect = s;
        n_ie = ie;
        material = objects[s]->material;
      }
    }

    if (nearest_intersect >= 0) {
      Color diffuse_comp(0, 0, 0);
      Color ambient_comp(0, 0, 0);
      Color specular_comp(0, 0, 0);
      Color reflective_comp(0, 0, 0);

      for (int l = 0; l < lights.size(); l += 1) {
        Vector l_vector = lights[l].loc - n_ie.intersection;
        double l_distance = l_vector.mag();
        l_vector = l_vector.normalized();

        bool blocked = false;
        for (int s = 0; s < objects.size(); s += 1) {
          IntersectionEvent b_ie = objects[s]->intersect(
            n_ie.intersection + l_vector * 0.01,
            l_vector
          );
          blocked = blocked || (b_ie.intersected && b_ie.distance < l_distance);
        }

        Color this_ac =
          lights[l].ambient *
          material.ambient;
        ambient_comp.r += this_ac.r;
        ambient_comp.g += this_ac.g;
        ambient_comp.b += this_ac.b;

        if (!blocked) {
          Vector r_vector = 
            (
              n_ie.normal * 
              n_ie.normal.dot(l_vector) 
              * 2
            ) - l_vector;

          Color this_dc =
            lights[l].diffuse *
            material.diffuse *
            std::max(0.0, l_vector.dot(n_ie.normal));
          diffuse_comp.r += this_dc.r;
          diffuse_comp.g += this_dc.g;
          diffuse_comp.b += this_dc.b;

          Color this_sc =
            lights[l].specular *
            material.specular *
            std::pow(
              std::max(0.0, r_vector.dot(direction * -1)),
              material.shininess
            );
          specular_comp.r += this_sc.r;
          specular_comp.g += this_sc.g;
          specular_comp.b += this_sc.b;
        }
      }

      ambient_comp = ambient_comp * (1.0 / lights.size());
      diffuse_comp = diffuse_comp * (1.0 / lights.size());
      specular_comp = specular_comp * (1.0 / lights.size());

      if (material.reflectivity > 0) {
        Vector ref_dir = (n_ie.normal * n_ie.normal.dot(direction * -1) * 2) + direction;
        reflective_comp = cast_ray(
          n_ie.intersection + ref_dir * 0.1,
          ref_dir,
          limit - 1
        );
      }

      return reflective_comp.blend(
        ambient_comp.blend(
          diffuse_comp.blend(
            specular_comp,
            material.diffuse_intensity,
            material.specular_intensity
          ),
          material.ambient_intensity,
          1
        ),
        material.reflectivity
      );
    } else {
      return Color(0, 0, 0);
    }
  }
}

void Scene::add_sphere(double x, double y, double z, double r, Material i_material) {
  objects.push_back(new Sphere(
    objects.size(), 
    Point(x, y, z), 
    r, 
    i_material
  ));
}

void Scene::add_plane(Point i_loc, Vector i_normal, Material i_material) {
  objects.push_back(new Plane(
    objects.size(),
    i_loc,
    i_normal,
    i_material
  ));
}

void Scene::add_light(double x, double y, double z, Color i_ambient, Color i_diffuse, Color i_specular) {
  lights.push_back(Light(
    Point(x, y, z),
    i_ambient,
    i_diffuse,
    i_specular
  ));
}
