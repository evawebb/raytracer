#ifndef SCENE_H
#define SCENE_H

#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>
#include "sphere.h"
#include "intersection_event.h"
#include "color.h"
#include "light.h"

class Scene {
  public:
    Scene();
    Scene(int w, int h);

    Color color_at(int x, int y);
    void add_sphere(double x, double y, double z, double r);
    void add_light(double x, double y, double z, Color i_diffuse, Color i_ambient);

    void test();

  private:
    int width, height;
    std::vector<Sphere> spheres;
    std::vector<Light> lights;
};

#endif
