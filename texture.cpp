#include "texture.h"

Texture::~Texture() {
  for (int y = 0; y < height; y += 1) {
    delete[] data[y];
  }
  delete[] data;
}

void Texture::load_image(std::string fn) {
  std::ifstream in_file(fn.c_str());
  std::string line;
  double limit;
  std::vector<double> rs, gs, bs;
  int color_index = 0;

  getline(in_file, line);
  getline(in_file, line);
  std::stringstream ss(line);
  ss >> width;
  ss >> height;
  getline(in_file, line);
  limit = atof(line.c_str());

  while(getline(in_file, line)) {
    while (line.find_first_of(' ') != std::string::npos) {
      std::string s_n = line.substr(0, line.find_first_of(' '));
      line.erase(0, line.find_first_of(' ') + 1);
      double c = atof(s_n.c_str()) / limit;
      if (color_index == 0) {
        rs.push_back(c);
      } else if (color_index == 1) {
        gs.push_back(c);
      } else {
        bs.push_back(c);
      }
      color_index = (color_index + 1) % 3;
    }
  }

  in_file.close();

  int index = 0;
  data = new Color*[height];
  for (int y = 0; y < height; y += 1) {
    data[y] = new Color[width];

    for (int x = 0; x < width; x += 1) {
      data[y][x] = Color(rs[index], gs[index], bs[index]);
      index += 1;
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
