#ifndef MATRIX_H
#define MATRIX_H

#include <sstream>
#include <string>

class Matrix {
  public:
    Matrix() {
      m = new double*[4];
      for (int i = 0; i < 4; i += 1) {
        m[i] = new double[4];

        for (int j = 0; j < 4; j += 1) {
          m[i][j] = 0;
        }
      }
    }
    Matrix(
      double aa, double ab, double ac, double ad,
      double ba, double bb, double bc, double bd,
      double ca, double cb, double cc, double cd,
      double da, double db, double dc, double dd
    ) {
      m = new double*[4];
      for (int i = 0; i < 4; i += 1) {
        m[i] = new double[4];
      }

      m[0][0] = aa; m[0][1] = ab; m[0][2] = ac; m[0][3] = ad;
      m[1][0] = ba; m[1][1] = bb; m[1][2] = bc; m[1][3] = bd;
      m[2][0] = ca; m[2][1] = cb; m[2][2] = cc; m[2][3] = cd;
      m[3][0] = da; m[3][1] = db; m[3][2] = dc; m[3][3] = dd;
    }

    Matrix operator*(Matrix o) {
      Matrix result;

      for (int row = 0; row < 4; row += 1) {
        for (int col = 0; col < 4; col += 1) {
          double val = 0;

          for (int i = 0; i < 4; i += 1) {
            val += m[row][i] * o.m[i][col];
          }

          result.m[row][col] = val;
        }
      }

      return result;
    }

    Point operator*(Point o) {
      return Point(
        o.x * m[0][0] + o.y * m[0][1] + o.z * m[0][2] + o.w * m[0][3],
        o.x * m[1][0] + o.y * m[1][1] + o.z * m[1][2] + o.w * m[1][3],
        o.x * m[2][0] + o.y * m[2][1] + o.z * m[2][2] + o.w * m[2][3]
        //o.x * m[3][0] + o.y * m[3][1] + o.z * m[3][2] + o.w * m[3][3]
      );
    }

    std::string to_s() {
      std::stringstream ss;

      ss << "[ " << m[0][0] << ", " << m[0][1] << ", " << m[0][2] << ", " << m[0][3] << ",\n";
      ss << "  " << m[1][0] << ", " << m[1][1] << ", " << m[1][2] << ", " << m[1][3] << ",\n";
      ss << "  " << m[2][0] << ", " << m[2][1] << ", " << m[2][2] << ", " << m[2][3] << ",\n";
      ss << "  " << m[3][0] << ", " << m[3][1] << ", " << m[3][2] << ", " << m[3][3] << " ]\n";

      return ss.str();
    }

    double** m;
};

#endif
