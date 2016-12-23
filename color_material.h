#ifndef COLOR_MATERIAL_H
#define COLOR_MATERIAL_H

#include "color.h"
#include "color_texture.h"

class ColorMaterial {
  public:
    ColorMaterial() {}
    ColorMaterial(
      Color i_ambient,
      Color i_diffuse,
      Color i_specular,
      double i_shininess,
      double i_reflectivity,
      double i_ambient_intensity,
      double i_diffuse_intensity,
      double i_specular_intensity
    // ) : Material(
    //   NULL,
    //   NULL,
    //   i_specular,
    //   i_shininess,
    //   i_reflectivity,
    //   i_ambient_intensity,
    //   i_diffuse_intensity,
    //   i_specular_intensity
    ) {
      ambient_texture = new ColorTexture(i_ambient);
      diffuse_texture = new ColorTexture(i_diffuse);
      specular = i_specular;
      shininess = i_shininess;
      reflectivity = i_reflectivity;
      ambient_intensity = i_ambient_intensity;
      diffuse_intensity = i_diffuse_intensity;
      specular_intensity = i_specular_intensity;
    }

    ColorTexture* ambient_texture;
    ColorTexture* diffuse_texture;
    Color specular;
    double shininess, reflectivity, ambient_intensity, diffuse_intensity, specular_intensity;
};

#endif
