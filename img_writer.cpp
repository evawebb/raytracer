#include "img_writer.h"

ImgWriter::~ImgWriter() {
  for (int y = 0; y < height; y += 1) {
    for (int x = 0; x < width; x += 1) {
      delete img[y][x];
    }
    delete img[y];
  }
  delete img;
}

void ImgWriter::init() {
  img = new int**[height];
  for (int y = 0; y < height; y += 1) {
    img[y] = new int*[width];
    for (int x = 0; x < width; x += 1) {
      img[y][x] = new int[3];
      img[y][x][0] = 0;
      img[y][x][1] = 0;
      img[y][x][2] = 0;
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
      ss << img[y][x][0] << ' ';
      ss << img[y][x][1] << ' ';
      ss << img[y][x][2] << ' ';
    }
    ss << '\n';
  }

  std::ofstream out_file("img.ppm");
  out_file << ss.str();
  out_file.close();
}

void ImgWriter::set(int x, int y, int r, int g, int b) {
  if (
    0 <= x && x < width
    && 0 <= y && y < height
  ) {
    img[y][x][0] = r;
    img[y][x][1] = g;
    img[y][x][2] = b;
  }
}
