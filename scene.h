#ifndef SCENE_H
#define SCENE_H

#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>
#include "sphere.h"
#include "plane.h"
#include "intersection_event.h"
#include "color.h"
#include "light.h"
#include "material.h"

class Scene {
  public:
    Scene();
    Scene(int w, int h);

    Color color_at(int x, int y, double focal_length, int aa);
    Color cast_ray(Point origin, Vector direction, int limit);
    void add_sphere(double x, double y, double z, double r, Material i_material);
    void add_plane(Point i_loc, Vector i_normal, Material i_material);
    void add_light(double x, double y, double z, Color i_ambient, Color i_diffuse, Color i_specular);

    void test();

  private:
    int width, height;
    std::vector<Sphere> spheres;
    std::vector<Plane> planes;
    std::vector<Light> lights;
};

#endif
