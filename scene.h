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

    Color color_at(int x, int y, int aa);
    void add_sphere(double x, double y, double z, double r, Color i_ambient, Color i_diffuse);
    void add_light(double x, double y, double z, Color i_ambient, Color i_diffuse);

    void test();

  private:
    int width, height;
    std::vector<Sphere> spheres;
    std::vector<Light> lights;
};

#endif
