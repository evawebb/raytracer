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
#include "material.h"
#include "model.h"

class Scene {
  public:
    Scene();
    Scene(int w, int h);

    Color color_at(int x, int y, double focal_length, int aa);
    Color cast_ray(Point origin, Vector direction, int limit, bool print);
    void add_model(Model m);
    void add_light(double x, double y, double z, Color i_ambient, Color i_diffuse, Color i_specular);

  private:
    int width, height;
    std::vector<Model> models;
    std::vector<Light> lights;
};

#endif
