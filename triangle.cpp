#include "triangle.h"

IntersectionEvent Triangle::intersect(Point origin, Vector direction) {
  // This is the distance along the ray to where it intersects
  // with the plane.
  double t = (loc - origin).dot(normal) / direction.dot(normal);

  // If the distance is nonpositive, then the plane is actually behind
  // the ray, so there's not really an intersection.
  if (t > 0) {
    // This is where the ray intersects with the plane.
    Point intersection = origin + direction * t;

    // This is the vector pointing from the main vertex of the
    // triangle to the intersection point.
    Vector a_to_i = intersection - a;

    // These are the barycentric coordinates of the intersection point
    // within the triangle. u is the influence along the a_to_b vector,
    // and v is the influence along the a_to_c vector.
    double dot_c_c = a_to_c.dot(a_to_c);
    double dot_c_b = a_to_c.dot(a_to_b);
    double dot_c_i = a_to_c.dot(a_to_i);
    double dot_b_b = a_to_b.dot(a_to_b);
    double dot_b_i = a_to_b.dot(a_to_i);
    double denom = 1.0 / (dot_c_c * dot_b_b - dot_c_b * dot_c_b);
    double u = (dot_b_b * dot_c_i - dot_c_b * dot_b_i) * denom;
    double v = (dot_c_c * dot_b_i - dot_c_b * dot_c_i) * denom;

    // If the point is inside the triangle, then neither u nor v will
    // be negative and their sum should be less than 1.
    if (u >= 0 && v >= 0 && (u + v) <= 1) {
      return IntersectionEvent(
        origin,
        direction,
        true,
        intersection,
        t,
        normal,
        id
      );
    } else {
      return IntersectionEvent(
        origin,
        direction,
        false,
        Point(0, 0, 0),
        t,
        Vector(0, 0, 0),
        -1
      );
    }
  } else {
    return IntersectionEvent(
      origin,
      direction,
      false,
      Point(0, 0, 0),
      -1,
      Vector(0, 0, 0),
      -1
    );
  }
}
