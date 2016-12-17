#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

class Material {
  public:
    Material() {}
    Material(
      Color i_ambient,
      Color i_diffuse,
      Color i_specular,
      double i_shininess,
      double i_reflectivity,
      double i_ambient_intensity,
      double i_diffuse_intensity,
      double i_specular_intensity
    ) {
      ambient = i_ambient;
      diffuse = i_diffuse;
      specular = i_specular;
      shininess = i_shininess;
      reflectivity = i_reflectivity;
      ambient_intensity = i_ambient_intensity;
      diffuse_intensity = i_diffuse_intensity;
      specular_intensity = i_specular_intensity;
    }
    
    double shininess, reflectivity, ambient_intensity, diffuse_intensity, specular_intensity;
    Color ambient, diffuse, specular;
};

#endif
