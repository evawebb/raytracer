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

std::vector<std::string> Model::split(std::string raw, char delim, bool cluster) {
  std::vector<std::string> out;

  if (cluster) {
    std::string group_string = std::string() + delim + delim;
    size_t ind = raw.find(group_string);
    while (ind != std::string::npos) {
      raw.erase(ind + 1, 1);
      ind = raw.find(group_string);
    }
  }

  while (raw.find_first_of(delim) != std::string::npos) {
    out.push_back(raw.substr(0, raw.find_first_of(delim)));
    raw.erase(0, raw.find_first_of(delim) + 1);
  }

  if (raw.size() > 0) {
    out.push_back(raw);
  }
  
  return out;
}

void Model::load_obj_file(std::string fn, Material* mat) {
  std::ifstream in_file(fn.c_str());
  std::string line;
  std::vector<Point> vertices;
  std::vector<Point> texel_coordinates;
  std::vector<Vector> normals;
  std::vector<Material*> materials;
  Material* curr_mat = mat;
  bool smooth = true;

  std::vector<std::string> fn_parts = split(fn, '/', true);
  std::string directory("./");
  fn = directory + fn;
  for (size_t i = 0; i < fn_parts.size() - 1; i += 1) {
    directory += fn_parts[i];
    directory += '/';
  }

  vertices.push_back(Point(0, 0, 0));
  texel_coordinates.push_back(Point(0, 0));
  normals.push_back(Vector(0, 0, 0));

  while (getline(in_file, line)) {
    if (line[0] != '#' && line.size() > 0) {
      std::vector<std::string> split_line = split(line, ' ', true);

      if (split_line[0].compare("v") == 0) {
        vertices.push_back(Point(
          atof(split_line[1].c_str()),
          atof(split_line[2].c_str()),
          atof(split_line[3].c_str())
        ));
      } else if (split_line[0].compare("vt") == 0) {
        texel_coordinates.push_back(Point(
          atof(split_line[1].c_str()),
          atof(split_line[2].c_str())
        ));
      } else if (split_line[0].compare("vn") == 0) {
        normals.push_back(Vector(
          atof(split_line[1].c_str()),
          atof(split_line[2].c_str()),
          atof(split_line[3].c_str())
        ));
      } else if (split_line[0].compare("f") == 0) {
        std::vector<std::string> v1 = split(split_line[1], '/', false);
        std::vector<std::string> v2 = split(split_line[2], '/', false);
        std::vector<std::string> v3 = split(split_line[3], '/', false);

        add_triangle(
          vertices[         atof(v1[0].c_str())],
          normals[          atof(v1[2].c_str())],
          texel_coordinates[atof(v1[1].c_str())],
          vertices[         atof(v2[0].c_str())],
          normals[          atof(v2[2].c_str())],
          texel_coordinates[atof(v2[1].c_str())],
          vertices[         atof(v3[0].c_str())],
          normals[          atof(v3[2].c_str())],
          texel_coordinates[atof(v3[1].c_str())],
          curr_mat
        );
      } else if (split_line[0].compare("mtllib") == 0) {
        materials = load_mtl_file(directory + split_line[1], directory);
        curr_mat = materials.back();
      } else if (split_line[0].compare("usemtl") == 0) {
        for (size_t i = 0; i < materials.size(); i += 1) {
          if (materials[i]->name.compare(split_line[1]) == 0) {
            curr_mat = materials[i];
            break;
          }
        }
      }
    }
  }

  in_file.close();
}

std::vector<Material*> Model::load_mtl_file(std::string fn, std::string directory) {
  std::ifstream in_file(fn.c_str());
  std::string line;
  std::vector<Material*> materials;

  materials.push_back(new ColorMaterial(
    Color(0.2, 0.2, 0.2),
    Color(0.8, 0.8, 0.8),
    Color(1, 1, 1),
    1, 0,
    1, 1, 0
  ));
  materials[0]->name = "(null)";

  while (getline(in_file, line)) {
    if (line[0] != '#' && line.size() > 0) {
      while (std::isspace(line[0])) {
        line.erase(line.begin());
      }

      std::vector<std::string> split_line = split(line, ' ', true);

      if (split_line[0].compare("newmtl") == 0) {
        materials.insert(materials.begin(), new Material());
        materials[0]->name = split_line[1];
        materials[0]->ambient_intensity = 0.5;
        materials[0]->diffuse_intensity = 1.0;
        materials[0]->specular_intensity = 0.5;
      } else if (split_line[0].compare("Ns") == 0) {
        materials[0]->shininess = atof(split_line[1].c_str());
      } else if (split_line[0].compare("Kd") == 0) {
        materials[0]->diffuse_texture = new ColorTexture(Color(
          atof(split_line[1].c_str()),
          atof(split_line[2].c_str()),
          atof(split_line[3].c_str())
        ));
      } else if (split_line[0].compare("Ks") == 0) {
        materials[0]->specular = Color(
          atof(split_line[1].c_str()),
          atof(split_line[2].c_str()),
          atof(split_line[3].c_str())
        );
      } else if (split_line[0].compare("Ka") == 0) {
        materials[0]->ambient_texture = new ColorTexture(Color(
          atof(split_line[1].c_str()),
          atof(split_line[2].c_str()),
          atof(split_line[3].c_str())
        ));
      } else if (split_line[0].compare("map_Kd") == 0) {
        materials[0]->diffuse_texture = new Texture(directory + split_line[1]);
      }
    }
  }

  in_file.close();

  return materials;
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
