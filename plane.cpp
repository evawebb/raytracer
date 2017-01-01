#include "plane.h"

IntersectionEvent Plane::intersect(Point origin, Vector direction) {
  double t = (loc - origin).dot(normal) / direction.dot(normal);

  if (t > 0) {
    Point intersection = origin + direction * t;

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
      Point(0, 0),
      material
    );
  } else {
    return IntersectionEvent(origin, direction);
  }
}
