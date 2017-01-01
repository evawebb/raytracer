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

      Point origin = 
        transform *
        Point(adj_x + adj_x_aa, adj_y + adj_y_aa, 0);
      Point focal_point =
        transform *
        Point(0, 0, -focal_length);
      Vector direction = (origin - focal_point).normalized();

      Color c = cast_ray(
        origin, 
        direction,
        10,
        false // 500 <= x && x <= 502 && y == 400
      );
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

Color Scene::cast_ray(Point origin, Vector direction, int limit, bool print) {
  if (limit > 0) {
    if (print) {
      std::cout << "\nRay casting results summary:\n";
    }
    IntersectionEvent n_ie;
    for (int m = 0; m < models.size(); m += 1) {
      IntersectionEvent ie = models[m].intersect(origin, direction);

      if (ie.intersected && ie.distance < n_ie.distance) {
        n_ie = ie;
      }
    }

    if (print) {
      std::cout << "The intersection distance was: " << n_ie.distance << '\n';
    }

    if (n_ie.intersected) {
      Color diffuse_comp(0, 0, 0);
      Color ambient_comp(0, 0, 0);
      Color specular_comp(0, 0, 0);
      Color reflective_comp(0, 0, 0);

      if (print) {
        std::cout << "The intersection was at " << n_ie.intersection.to_s() << " on object " << n_ie.object_id << " of model " << n_ie.model_id << ".\n";
        std::cout << "Barycentric u: " << n_ie.u << '\n';
        std::cout << "Barycentric v: " << n_ie.v << '\n';
        std::cout << "Texel: " << n_ie.texel.to_s() << '\n';
        std::cout << "Object material summary:\n";
        std::cout << "  Shininess: " << n_ie.material->shininess << '\n';
        std::cout << "  Reflectivity: " << n_ie.material->reflectivity << '\n';
        std::cout << "  Ambient intensity: " << n_ie.material->ambient_intensity << '\n';
        std::cout << "  Diffuse intensity: " << n_ie.material->diffuse_intensity << '\n';
        std::cout << "  Specular intensity: " << n_ie.material->specular_intensity << '\n';
      }

      for (int l = 0; l < lights.size(); l += 1) {
        Vector l_vector = lights[l].loc - n_ie.intersection;
        double l_distance = l_vector.mag();
        l_vector = l_vector.normalized();

        if (print) {
          std::cout << "Light " << (l + 1) << ":\n";
        }

        bool blocked = false;
        for (int m = 0; m < models.size(); m += 1) {
          IntersectionEvent b_ie = models[m].intersect(
            n_ie.intersection + l_vector * 0.01,
            l_vector
          );
          blocked = blocked || (b_ie.intersected && b_ie.distance < l_distance);
        }

        Color this_ac =
          lights[l].ambient *
          n_ie.material->ambient_texture->texel(n_ie.texel);
        ambient_comp.r += this_ac.r;
        ambient_comp.g += this_ac.g;
        ambient_comp.b += this_ac.b;

        if (print) {
          std::cout << "  Light ambient color: " << lights[l].ambient.to_s() << '\n';
          std::cout << "  Material ambient color: " << n_ie.material->ambient_texture->texel(n_ie.texel).to_s() << '\n';
          std::cout << "  Ambient component: " << this_ac.to_s() << '\n';
        }

        if (!blocked) {
          Vector r_vector = 
            (
              n_ie.normal * 
              n_ie.normal.dot(l_vector) 
              * 2
            ) - l_vector;

          Color this_dc =
            lights[l].diffuse *
            n_ie.material->diffuse_texture->texel(n_ie.texel) *
            std::max(0.0, l_vector.dot(n_ie.normal));
          diffuse_comp.r += this_dc.r;
          diffuse_comp.g += this_dc.g;
          diffuse_comp.b += this_dc.b;

          if (print) {
            std::cout << "  Light diffuse color: " << lights[l].diffuse.to_s() << '\n';
            std::cout << "  Material diffuse color: " << n_ie.material->diffuse_texture->texel(n_ie.texel).to_s() << '\n';
            std::cout << "  Diffuse dot product multiplier: " << std::max(0.0, l_vector.dot(n_ie.normal)) << '\n';
            std::cout << "  Diffuse component: " << this_dc.to_s() << '\n';
          }

          Color this_sc =
            lights[l].specular *
            n_ie.material->specular *
            std::pow(
              std::max(0.0, r_vector.dot(direction * -1)),
              n_ie.material->shininess
            );
          specular_comp.r += this_sc.r;
          specular_comp.g += this_sc.g;
          specular_comp.b += this_sc.b;

          if (print) {
            std::cout << "  Light specular color: " << lights[l].specular.to_s() << '\n';
            std::cout << "  Material specular color: " << n_ie.material->specular.to_s() << '\n';
            std::cout << "  Specular dot product multiplier: " << std::pow(std::max(0.0, r_vector.dot(direction * -1)), n_ie.material->shininess) << '\n';
            std::cout << "  Specular component: " << this_sc.to_s() << '\n';
          }
        } else {
          if (print) {
            std::cout << "  This light is blocked.\n";
          }
        }
      }

      ambient_comp = ambient_comp * (1.0 / lights.size());
      diffuse_comp = diffuse_comp * (1.0 / lights.size());
      specular_comp = specular_comp * (1.0 / lights.size());

      if (n_ie.material->reflectivity > 0) {
        Vector ref_dir = (n_ie.normal * n_ie.normal.dot(direction * -1) * 2) + direction;
        reflective_comp = cast_ray(
          n_ie.intersection + ref_dir * 0.1,
          ref_dir,
          limit - 1,
          false
        );
      }

      Color final_color = reflective_comp.blend(
        ambient_comp.blend(
          diffuse_comp.blend(
            specular_comp,
            n_ie.material->diffuse_intensity,
            n_ie.material->specular_intensity
          ),
          n_ie.material->ambient_intensity,
          1
        ),
        n_ie.material->reflectivity
      );

      if (print) {
        std::cout << "Final color: " << final_color.to_s() << "\n\n";
      }

      return final_color;
    } else {
      return Color(0, 0, 0);
    }
  }
}

void Scene::add_model(Model m) {
  models.push_back(m);
}

void Scene::add_light(double x, double y, double z, Color i_ambient, Color i_diffuse, Color i_specular) {
  lights.push_back(Light(
    Point(x, y, z),
    i_ambient,
    i_diffuse,
    i_specular
  ));
}

void Scene::add_transformation(Matrix next_matrix) {
  transform = next_matrix * transform;
}

void Scene::translate_cam(Vector trans) {
  add_transformation(Matrix(
    1, 0, 0, trans.x,
    0, 1, 0, trans.y,
    0, 0, 1, trans.z,
    0, 0, 0,       1
  ));
}

void Scene::rotate_cam(double radians, Vector axis) {
  axis = axis.normalized();
  double c = cos(radians);
  double s = sin(radians);
  double xx = axis.x * axis.x * (1 - c);
  double xy = axis.x * axis.y * (1 - c);
  double xz = axis.x * axis.z * (1 - c);
  double yy = axis.y * axis.y * (1 - c);
  double yz = axis.y * axis.z * (1 - c);
  double zz = axis.z * axis.z * (1 - c);

  add_transformation(Matrix(
             xx + c, xy - axis.z * s, xz + axis.y * s, 0,
    xy + axis.z * s,          yy + c, yz - axis.x * s, 0,
    xz - axis.y * s, yz + axis.x * s,          zz + c, 0,
                  0,               0,               0, 1
  ));
}
