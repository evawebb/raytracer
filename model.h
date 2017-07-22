#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "object.h"
#include "sphere.h"
#include "plane.h"
#include "triangle.h"
#include "point.h"
#include "vector.h"
#include "matrix.h"
#include "intersection_event.h"
#include "color_material.h"

class Model {
  public:
    Model() {
      model_id = -1;
    }
    Model(int i_model_id) {
      model_id = i_model_id;
    }
    
    int model_id;

    IntersectionEvent intersect(Point origin, Vector direction);

    void load_obj_file(std::string fn, Material* mat);
    std::vector<Material*> load_mtl_file(std::string fn, std::string directory);

    void add_triangle(Point i_a, Point i_b, Point i_c);
    void add_triangle(
      Point i_a, Point i_a_texel,
      Point i_b, Point i_b_texel,
      Point i_c, Point i_c_texel
    );
    void add_triangle(Point i_a, Point i_b, Point i_c, Material* i_material);
    void add_triangle(
      Point i_a, Point i_a_texel,
      Point i_b, Point i_b_texel,
      Point i_c, Point i_c_texel,
      Material* i_material
    );
    void add_triangle(
      Point i_a, Vector i_a_normal,
      Point i_b, Vector i_b_normal,
      Point i_c, Vector i_c_normal
    );
    void add_triangle(
      Point i_a, Vector i_a_normal,
      Point i_b, Vector i_b_normal,
      Point i_c, Vector i_c_normal,
      Material* i_material
    );
    void add_triangle(
      Point i_a, Vector i_a_normal, Point i_a_texel,
      Point i_b, Vector i_b_normal, Point i_b_texel,
      Point i_c, Vector i_c_normal, Point i_c_texel,
      Material* i_material
    );
    void add_sphere(Point i_loc, double i_radius);
    void add_sphere(Point i_loc, double i_radius, Material* i_material);
    void add_plane(Point i_loc, Vector i_normal);
    void add_plane(Point i_loc, Vector i_normal, Material* i_material);

    void add_transformation(Matrix next_matrix);
    void translate(Vector trans);
    void scale(double x_mult, double y_mult, double z_mult);
    void rotate(double radians, Vector axis);

  private:
    std::vector<Object*> objects;
    Matrix transform;

    std::vector<std::string> split(std::string raw, char delim, bool cluster);
};

#endif
