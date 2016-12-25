#include "texture.h"

Texture::~Texture() {
  for (int y = 0; y < height; y += 1) {
    delete[] data[y];
  }
  delete[] data;
}

void Texture::load_image(std::string fn) {
  // std::ifstream in_file(fn.c_str());
  // std::string line;
  // double limit;

  // getline(in_file, line);
  // getline(in_file, line);
  // std::stringstream ss(line);
  // ss >> width;
  // ss >> height;
  // getline(in_file, line);
  // ss >> limit;

  // data = new Color*[height];
  // for (int y = 0; y < height; y += 1) {
  //   data[y] = new Color[width];

  //   for (int x = 0; x < width; x += 1) {
  //     if (!ss) {
  //       getline(in_file, line);
  //       ss.str(line);
  //       std::cout << "  " << line << '\n';
  //     }

  //     int r, g, b;
  //     ss >> r;
  //     ss >> g;
  //     ss >> b;
  //     std::cout << '(' << r << ", " << g << ", " << b << ")\n";
  //     // data[y][x] = Color(r / limit, g / limit, b / limit);
  //   }
  // }

  // in_file.close();

  width = 20;
  height = width;

  data = new Color*[height];
  for (int y = 0; y < height; y += 1) {
    data[y] = new Color[width];

    for (int x = 0; x < width; x += 1) {
      data[y][x] = Color((double)x / (double)width, 0, (double)y / (double)height);
    }
  }
}

Color Texture::texel(double s, double t) {
  int col = std::min(s * width, (double)(width - 1));
  int row = std::min(t * height, (double)(height - 1));
  if (width > 0 && height > 0) {
    return data[row][col];
  } else {
    return Color(0, 0, 1);
  }
}
