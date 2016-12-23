#include "texture.h"

Texture::~Texture() {
  for (int y = 0; y < height; y += 1) {
    delete[] data[y];
  }
  delete[] data;
}

void Texture::load_image(std::string fn) {
  width = 100;
  height = 100;

  data = new Color*[height];
  for (int y = 0; y < height; y += 1) {
    data[y] = new Color[width];

    for (int x = 0; x < width; x += 1) {
      data[y][x] = Color(1, 1, 0);
    }
  }
}

Color Texture::texel(double u, double v) {
  if (width > 0 && height > 0) {
    return data[0][0];
  } else {
    return Color(0, 0, 1);
  }
}
