#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "object.h"
#include "sphere.h"
#include "plane.h"
#include "triangle.h"
#include "point.h"
#include "vector.h"
#include "matrix.h"
#include "intersection_event.h"

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

    void add_triangle(Point i_a, Point i_b, Point i_c);
    void add_triangle(
      Point i_a, double i_a_texel_s, double i_a_texel_t,
      Point i_b, double i_b_texel_s, double i_b_texel_t,
      Point i_c, double i_c_texel_s, double i_c_texel_t
    );
    void add_triangle(Point i_a, Point i_b, Point i_c, Material* i_material);
    void add_triangle(
      Point i_a, double i_a_texel_s, double i_a_texel_t,
      Point i_b, double i_b_texel_s, double i_b_texel_t,
      Point i_c, double i_c_texel_s, double i_c_texel_t,
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
      Point i_a, Vector i_a_normal, double i_a_texel_s, double i_a_texel_t,
      Point i_b, Vector i_b_normal, double i_b_texel_s, double i_b_texel_t,
      Point i_c, Vector i_c_normal, double i_c_texel_s, double i_c_texel_t,
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
};

#endif
