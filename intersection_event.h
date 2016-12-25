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
      int i_object_id,
      double i_u,
      double i_v,
      double i_texel_s,
      double i_texel_t
    ) {
      origin = i_origin;
      direction = i_direction;
      intersected = i_intersected;
      intersection = i_intersection;
      distance = i_distance;
      normal = i_normal;
      object_id = i_object_id;
      u = i_u;
      v = i_v;
      texel_s = i_texel_s;
      texel_t = i_texel_t;
    }

    Point origin, intersection;
    Vector direction, normal;
    bool intersected;
    double distance, u, v, texel_s, texel_t;
    int object_id;
};

#endif
