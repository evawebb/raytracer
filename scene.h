#ifndef SCENE_H
#define SCENE_H

#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>
#include "sphere.h"
#include "plane.h"
#include "triangle.h"
#include "intersection_event.h"
#include "color.h"
#include "light.h"
#include "color_material.h"

class Scene {
  public:
    Scene();
    Scene(int w, int h);

    Color color_at(int x, int y, double focal_length, int aa);
    Color cast_ray(Point origin, Vector direction, int limit, bool print);
    void add_sphere(double x, double y, double z, double r, Material* i_material);
    void add_plane(Point i_loc, Vector i_normal, Material* i_material);
    void add_triangle(Point i_a, Point i_b, Point i_c, Material* i_material);
    void add_light(double x, double y, double z, Color i_ambient, Color i_diffuse, Color i_specular);

  private:
    int width, height;
    std::vector<Object*> objects;
    std::vector<Light> lights;
};

#endif
