#ifndef SCENE_H
#define SCENE_H

#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>
#include "sphere.h"

class Scene {
  public:
    Scene();
    Scene(int w, int h);

    int* color_at(int x, int y);
    void add_sphere(int x, int y, int z, float r);

    void test();

  private:
    int width, height;
    std::vector<Sphere> spheres;
    // std::vector<Light> lights;
};

#endif
