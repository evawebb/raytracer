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
    double dot_b_b = a_to_b.dot(a_to_b);
    double dot_b_c = a_to_b.dot(a_to_c);
    double dot_c_c = a_to_c.dot(a_to_c);
    double dot_i_b = a_to_i.dot(a_to_b);
    double dot_i_c = a_to_i.dot(a_to_c);
    double denom = 1.0 / (dot_b_b * dot_c_c - dot_b_c * dot_b_c);
    double u = (dot_c_c * dot_i_b - dot_b_c * dot_i_c) * denom;
    double v = (dot_b_b * dot_i_c - dot_b_c * dot_i_b) * denom;

    // If the point is inside the triangle, then neither u nor v will
    // be negative and their sum should be less than 1.
    if (u >= 0 && v >= 0 && (u + v) <= 1) {
      // Using the texel coordinates of the triangle's vertices, calculate
      // the texel coordinates of this point.
      double r = 1 - u - v;
      double texel_s = r * a_texel_s + u * b_texel_s + v * c_texel_s;
      double texel_t = r * a_texel_t + u * b_texel_t + v * c_texel_t;

      return IntersectionEvent(
        origin,
        direction,
        true,
        intersection,
        t,
        normal,
        id,
        u,
        v,
        texel_s,
        texel_t,
        *material
      );
    } else {
      return IntersectionEvent(origin, direction);
    }
  } else {
    return IntersectionEvent(origin, direction);
  }
}
