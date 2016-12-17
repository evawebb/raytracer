#include "img_writer.h"

ImgWriter::~ImgWriter() {
  for (int y = 0; y < height; y += 1) {
    delete[] img[y];
  }
  delete[] img;
}

void ImgWriter::init() {
  img = new Color*[height];
  for (int y = 0; y < height; y += 1) {
    img[y] = new Color[width];
    for (int x = 0; x < width; x += 1) {
      img[y][x] = Color(0, 0, 0);
    }
  }
}

void ImgWriter::write() {
  std::stringstream ss;
  ss << "P3\n";
  ss << width << ' ' << height << '\n';
  ss << "255\n";

  for (int y = 0; y < height; y += 1) {
    for (int x = 0; x < width; x += 1) {
      ss << (int)(255 * img[y][x].r) << ' ';
      ss << (int)(255 * img[y][x].g) << ' ';
      ss << (int)(255 * img[y][x].b) << ' ';
    }
    ss << '\n';
  }

  std::ofstream out_file("img.ppm");
  out_file << ss.str();
  out_file.close();
}

void ImgWriter::set(int x, int y, int r, int g, int b) {
  set(x, y, Color(r, g, b));
}

void ImgWriter::set(int x, int y, Color c) {
  if (
    0 <= x && x < width
    && 0 <= y && y < height
  ) {
    img[y][x] = c;
  }
}
