#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include "color.h"
#include "texture.h"

class Material {
  public:
    Material() {}
    Material(
      Texture* i_ambient_texture,
      Texture* i_diffuse_texture,
      Color i_specular,
      double i_shininess,
      double i_reflectivity,
      double i_ambient_intensity,
      double i_diffuse_intensity,
      double i_specular_intensity
    ) {
      ambient_texture = i_ambient_texture,
      diffuse_texture = i_diffuse_texture,
      specular = i_specular;
      shininess = i_shininess;
      reflectivity = i_reflectivity;
      ambient_intensity = i_ambient_intensity;
      diffuse_intensity = i_diffuse_intensity;
      specular_intensity = i_specular_intensity;
    }

    Texture* ambient_texture;
    Texture* diffuse_texture;
    Color specular;
    std::string name;
    double shininess, reflectivity, ambient_intensity, diffuse_intensity, specular_intensity;
};

#endif
