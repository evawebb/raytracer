#include "sphere.h"

IntersectionEvent Sphere::intersect(Point origin, Vector direction) {
  // This is the direct vector from the ray origin to the sphere center.
  Vector direct(loc.x - origin.x, loc.y - origin.y, loc.z - origin.z);

  // This is the direct vector projected onto the ray's direction.
  // In other words, this vector points along the ray's direction and 
  // stops when it is abreast of the sphere's center.
  Vector past = direction * direction.dot(direct);

  // If the past vector is pointing opposite the direction vector, 
  // then it's not really an intersection.
  Vector p_n = past.normalized();
  if (past.normalized() == direction) {
    // This is the distance from the sphere's center to the past vector.
    // This forms one of the legs of a right triangle with three vertices:
    // * The sphere's center
    // * The tip of the past vector
    // * The intersection point of the ray on the sphere's surfae
    double clearance = (past - direct).mag();

    // If the clearance is greater than the sphere's radius, then the
    // ray didn't intersect with the sphere.
    if (clearance <= radius) {
      // This is the distance backwards from the tip of the past vector to
      // the intersection point.
      double inside_dist = sqrt(radius * radius - clearance * clearance);

      // This is the distance from the ray origin to the intersection point.
      // If the origin is inside the sphere it intersects with, then this
      // should be calculated differently.
      double t;
      if (direct.mag() > radius) {
        t = past.mag() - inside_dist;
      } else {
        t = past.mag() + inside_dist;
      }

      // If the distance to the intersection is zero, then you just
      // intersected with yourself!
      if (t != 0) {
        // This is the point of intersection.
        Point intersection = origin + direction * t;

        // Finally, this is the surface normal at the intersection point.
        Vector normal = (intersection - loc).normalized();

        return IntersectionEvent(
          origin,
          direction,
          true,
          intersection,
          t,
          normal,
          id,
          0,
          0,
          0,
          0
        );
      } else {
        return IntersectionEvent(origin, direction);
      }
    } else {
      return IntersectionEvent(origin, direction);
    }
  } else {
    return IntersectionEvent(origin, direction);
  }
}
