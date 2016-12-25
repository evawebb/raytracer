#include "model.h"

IntersectionEvent Model::intersect(Point origin, Vector direction) {
  IntersectionEvent n_ie;
  for (int o = 0; o < objects.size(); o += 1) {
    IntersectionEvent ie = objects[o]->intersect(origin, direction);

    if (ie.intersected && ie.distance < n_ie.distance) {
      n_ie = ie;
    }
  }

  n_ie.model_id = model_id;
  return n_ie;
}

void Model::add_triangle(Point i_a, Point i_b, Point i_c) {
  objects.push_back(new Triangle(
    objects.size(),
    i_a, 0, 0,
    i_b, 0, 0,
    i_c, 0, 0,
    NULL
  ));
}

void Model::add_triangle(
  Point i_a, double i_a_texel_s, double i_a_texel_t,
  Point i_b, double i_b_texel_s, double i_b_texel_t,
  Point i_c, double i_c_texel_s, double i_c_texel_t
) {
  objects.push_back(new Triangle(
    objects.size(),
    i_a, i_a_texel_s, i_a_texel_t,
    i_b, i_b_texel_s, i_b_texel_t,
    i_c, i_c_texel_s, i_c_texel_t,
    NULL
  ));
}

void Model::add_triangle(
  Point i_a, double i_a_texel_s, double i_a_texel_t,
  Point i_b, double i_b_texel_s, double i_b_texel_t,
  Point i_c, double i_c_texel_s, double i_c_texel_t,
  Material* i_material
) {
  objects.push_back(new Triangle(
    objects.size(),
    i_a, i_a_texel_s, i_a_texel_t,
    i_b, i_b_texel_s, i_b_texel_t,
    i_c, i_c_texel_s, i_c_texel_t,
    i_material
  ));
}

void Model::add_sphere(Point i_loc, double i_radius) {
  objects.push_back(new Sphere(
    objects.size(),
    i_loc,
    i_radius,
    NULL
  ));
}

void Model::add_sphere(Point i_loc, double i_radius, Material* i_material) {
  objects.push_back(new Sphere(
    objects.size(),
    i_loc,
    i_radius,
    i_material
  ));
}

void Model::add_plane(Point i_loc, Vector i_normal) {
  objects.push_back(new Plane(
    objects.size(),
    i_loc,
    i_normal,
    NULL
  ));
}

void Model::add_plane(Point i_loc, Vector i_normal, Material* i_material) {
  objects.push_back(new Plane(
    objects.size(),
    i_loc,
    i_normal,
    i_material
  ));
}
