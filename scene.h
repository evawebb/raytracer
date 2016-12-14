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
    void add_sphere(float x, float y, float z, float r);
    void add_light(float x, float y, float z, Color i_diffuse, Color i_ambient);

    void test();

  private:
    int width, height;
    std::vector<Sphere> spheres;
    std::vector<Light> lights;
};

#endif
