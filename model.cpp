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
  add_triangle(i_a, Point(0, 0), i_b, Point(0, 0), i_c, Point(0, 0), NULL);
}

void Model::add_triangle(
  Point i_a, Point i_a_texel,
  Point i_b, Point i_b_texel,
  Point i_c, Point i_c_texel
) {
  add_triangle(
    i_a, i_a_texel,
    i_b, i_b_texel,
    i_c, i_c_texel,
    NULL
  );
}

void Model::add_triangle(Point i_a, Point i_b, Point i_c, Material* i_material) {
  add_triangle(
    i_a, Point(0, 0),
    i_b, Point(0, 0),
    i_c, Point(0, 0),
    i_material
  );
}

void Model::add_triangle(
  Point i_a, Point i_a_texel,
  Point i_b, Point i_b_texel,
  Point i_c, Point i_c_texel,
  Material* i_material
) {
  objects.push_back(new Triangle(
    objects.size(),
    transform * i_a, i_a_texel,
    transform * i_b, i_b_texel,
    transform * i_c, i_c_texel,
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
    i_a, i_a_normal, Point(0, 0),
    i_b, i_b_normal, Point(0, 0),
    i_c, i_c_normal, Point(0, 0),
    i_material
  );
}

void Model::add_triangle(
  Point i_a, Vector i_a_normal, Point i_a_texel,
  Point i_b, Vector i_b_normal, Point i_b_texel,
  Point i_c, Vector i_c_normal, Point i_c_texel,
  Material* i_material
) {
  Matrix normal_transform(transform);
  normal_transform.m[0][3] = 0;
  normal_transform.m[1][3] = 0;
  normal_transform.m[2][3] = 0;
  normal_transform.m[3][3] = 1;

  objects.push_back(new Triangle(
    objects.size(),
    transform * i_a, (normal_transform * i_a_normal).normalized(), i_a_texel,
    transform * i_b, (normal_transform * i_b_normal).normalized(), i_b_texel,
    transform * i_c, (normal_transform * i_c_normal).normalized(), i_c_texel,
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
