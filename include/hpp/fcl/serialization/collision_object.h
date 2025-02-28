//
// Copyright (c) 2021 INRIA
//

#ifndef HPP_FCL_SERIALIZATION_COLLISION_OBJECT_H
#define HPP_FCL_SERIALIZATION_COLLISION_OBJECT_H

#include "hpp/fcl/collision_object.h"

#include "hpp/fcl/serialization/fwd.h"
#include "hpp/fcl/serialization/AABB.h"
#include "hpp/fcl/serialization/transform.h"

#include "hpp/fcl/BV/AABB.h"
#include "hpp/fcl/math/transform.h"

namespace boost {
namespace serialization {

template <class Archive>
void save(Archive& ar, const hpp::fcl::CollisionGeometry& collision_geometry,
          const unsigned int /*version*/) {
  ar& make_nvp("aabb_center", collision_geometry.aabb_center);
  ar& make_nvp("aabb_radius", collision_geometry.aabb_radius);
  ar& make_nvp("aabb_local", collision_geometry.aabb_local);
  ar& make_nvp("cost_density", collision_geometry.cost_density);
  ar& make_nvp("threshold_occupied", collision_geometry.threshold_occupied);
  ar& make_nvp("threshold_free", collision_geometry.threshold_free);
}

template <class Archive>
void load(Archive& ar, hpp::fcl::CollisionGeometry& collision_geometry,
          const unsigned int /*version*/) {
  ar >> make_nvp("aabb_center", collision_geometry.aabb_center);
  ar >> make_nvp("aabb_radius", collision_geometry.aabb_radius);
  ar >> make_nvp("aabb_local", collision_geometry.aabb_local);
  ar >> make_nvp("cost_density", collision_geometry.cost_density);
  ar >> make_nvp("threshold_occupied", collision_geometry.threshold_occupied);
  ar >> make_nvp("threshold_free", collision_geometry.threshold_free);
  collision_geometry.user_data = NULL;  // no way to recover this
}

HPP_FCL_SERIALIZATION_SPLIT(hpp::fcl::CollisionGeometry)


template <class Archive>
void save(Archive& ar, const hpp::fcl::CollisionObject& collision_object,
          const unsigned int /*version*/) {
  ar& make_nvp("cgeom", collision_object.collisionGeometry());
  ar& make_nvp("t", collision_object.getTransform());
  ar& make_nvp("aabb", collision_object.getAABB());
}

template <class Archive>
void load(Archive& ar, hpp::fcl::CollisionObject& collision_object,
          const unsigned int /*version*/) {

  std::shared_ptr<hpp::fcl::CollisionGeometry> cgeom;
  hpp::fcl::Transform3f t;
  hpp::fcl::AABB aabb;
  ar >> make_nvp("cgeom", cgeom);
  ar >> make_nvp("t", t);
  ar >> make_nvp("aabb", aabb);

  collision_object.setCollisionGeometry(cgeom, false);
  collision_object.setTransform(t);
  collision_object.setAABB(aabb);
  collision_object.setUserData(NULL);
}

HPP_FCL_SERIALIZATION_SPLIT(hpp::fcl::CollisionObject)

// template <class Archive>
// void serialize(Archive& ar, hpp::fcl::CollisionObject& collision_object,
//                const unsigned int /*version*/) {
//   ar& make_nvp("cgeom", collision_object.collisionGeometry());
//   ar& make_nvp("t", collision_object.getTransform());
//   ar& make_nvp("aabb", collision_object.getAABB());
// }

}  // namespace serialization
}  // namespace boost

namespace hpp {
namespace fcl {

// fwd declaration
template <typename BV>
class HeightField;

template <typename PolygonT>
class Convex;

struct OBB;
struct OBBRSS;
class AABB;

class OcTree;
class Box;
class Sphere;
class Ellipsoid;
class Capsule;
class Cone;
class TriangleP;
class Cylinder;
class Halfspace;
class Plane;

namespace serialization {
template <>
struct register_type<CollisionGeometry> {
  template <class Archive>
  static void on(Archive& ar) {
    ar.template register_type<Box>();
    ar.template register_type<Sphere>();
    ar.template register_type<Ellipsoid>();
    ar.template register_type<TriangleP>();
    ar.template register_type<Capsule>();
    ar.template register_type<Cone>();
    ar.template register_type<Cylinder>();
    ar.template register_type<Halfspace>();
    ar.template register_type<Plane>();
    ar.template register_type<OcTree>();
    ar.template register_type<HeightField<OBB>>();
    ar.template register_type<HeightField<OBBRSS>>();
    ar.template register_type<HeightField<AABB>>();
    ar.template register_type<Convex<Triangle>>();
    ;
  }
};
}  // namespace serialization
}  // namespace fcl
}  // namespace hpp


#endif  // ifndef HPP_FCL_SERIALIZATION_COLLISION_OBJECT_H
