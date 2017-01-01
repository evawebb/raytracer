#ifndef INTERSECTION_EVENT_H
#define INTERSECTION_EVENT_H

#include "point.h"
#include "vector.h"
#include "material.h"

class IntersectionEvent {
  public:
    IntersectionEvent() {
      origin = Point(0, 0, 0);
      direction = Vector(0, 0, 0);
      intersected = false;
      intersection = Point(0, 0, 0);
      distance = 1000000;
      normal = Vector(0, 0, 0);
      object_id = -1;
      u = -1;
      v = -1;
      texel_s = -1;
      texel_t = -1;
      material = NULL;
    }
    IntersectionEvent(Point i_origin, Vector i_direction) {
      origin = i_origin;
      direction = i_direction;
      intersected = false;
      intersection = Point(0, 0, 0);
      distance = 1000000;
      normal = Vector(0, 0, 0);
      object_id = -1;
      u = -1;
      v = -1;
      texel_s = -1;
      texel_t = -1;
      material = NULL;
    }
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
      double i_texel_t,
      Material* i_material
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
      material = i_material;
    }

    Point origin, intersection;
    Vector direction, normal;
    bool intersected;
    double distance, u, v, texel_s, texel_t;
    int model_id, object_id;
    Material* material;
};

#endif
