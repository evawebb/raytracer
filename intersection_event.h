#ifndef INTERSECTION_EVENT_H
#define INTERSECTION_EVENT_H

#include "point.h"

class IntersectionEvent {
  public:
    IntersectionEvent() {}
    IntersectionEvent(
      Point i_origin,
      Vector i_direction,
      bool i_intersected,
      Point i_intersection,
      double i_distance,
      Vector i_normal,
      int i_sphere_id
    ) {
      origin = i_origin;
      direction = i_direction;
      intersected = i_intersected;
      intersection = i_intersection;
      distance = i_distance;
      normal = i_normal;
      sphere_id = i_sphere_id;
    }

    Point origin, intersection;
    Vector direction, normal;
    bool intersected;
    double distance;
    int sphere_id;
};

#endif
