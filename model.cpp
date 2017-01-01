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

void Model::load_obj_file(std::string fn) {
  std::ifstream in_file(fn.c_str());
  std::string line;
  std::vector<Point> vertices;

  while (getline(in_file, line)) {
    std::cout << line << '\n';
  }

  in_file.close();
}

void Model::add_triangle(Point i_a, Point i_b, Point i_c) {
  add_triangle(i_a, 0, 0, i_b, 0, 0, i_c, 0, 0, NULL);
}

void Model::add_triangle(
  Point i_a, double i_a_texel_s, double i_a_texel_t,
  Point i_b, double i_b_texel_s, double i_b_texel_t,
  Point i_c, double i_c_texel_s, double i_c_texel_t
) {
  add_triangle(
    i_a, i_a_texel_s, i_a_texel_t,
    i_b, i_b_texel_s, i_b_texel_t,
    i_c, i_c_texel_s, i_c_texel_t,
    NULL
  );
}

void Model::add_triangle(Point i_a, Point i_b, Point i_c, Material* i_material) {
  add_triangle(
    i_a, 0, 0,
    i_b, 0, 0,
    i_c, 0, 0,
    i_material
  );
}

void Model::add_triangle(
  Point i_a, double i_a_texel_s, double i_a_texel_t,
  Point i_b, double i_b_texel_s, double i_b_texel_t,
  Point i_c, double i_c_texel_s, double i_c_texel_t,
  Material* i_material
) {
  objects.push_back(new Triangle(
    objects.size(),
    transform * i_a, i_a_texel_s, i_a_texel_t,
    transform * i_b, i_b_texel_s, i_b_texel_t,
    transform * i_c, i_c_texel_s, i_c_texel_t,
    i_material
  ));
}

void Model::add_triangle(
  Point i_a, Vector i_a_normal,
  Point i_b, Vector i_b_normal,
  Point i_c, Vector i_c_normal
) {
  add_triangle(
    i_a, i_a_normal,
    i_b, i_b_normal,
    i_c, i_c_normal,
    NULL
  );
}

void Model::add_triangle(
  Point i_a, Vector i_a_normal,
  Point i_b, Vector i_b_normal,
  Point i_c, Vector i_c_normal,
  Material* i_material
) {
  add_triangle(
    i_a, i_a_normal, 0, 0,
    i_b, i_b_normal, 0, 0,
    i_c, i_c_normal, 0, 0,
    i_material
  );
}

void Model::add_triangle(
  Point i_a, Vector i_a_normal, double i_a_texel_s, double i_a_texel_t,
  Point i_b, Vector i_b_normal, double i_b_texel_s, double i_b_texel_t,
  Point i_c, Vector i_c_normal, double i_c_texel_s, double i_c_texel_t,
  Material* i_material
) {
  objects.push_back(new Triangle(
    objects.size(),
    transform * i_a, i_a_normal, i_a_texel_s, i_a_texel_t,
    transform * i_b, i_b_normal, i_b_texel_s, i_b_texel_t,
    transform * i_c, i_c_normal, i_c_texel_s, i_c_texel_t,
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

void Model::add_transformation(Matrix next_matrix) {
  transform = next_matrix * transform;
}

void Model::translate(Vector trans) {
  add_transformation(Matrix(
    1, 0, 0, trans.x,
    0, 1, 0, trans.y,
    0, 0, 1, trans.z,
    0, 0, 0,       1
  ));
}

void Model::scale(double x_mult, double y_mult, double z_mult) {
  add_transformation(Matrix(
    x_mult,      0,      0, 0,
         0, y_mult,      0, 0,
         0,      0, z_mult, 0,
         0,      0,      0, 1
  ));
}

void Model::rotate(double radians, Vector axis) {
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
