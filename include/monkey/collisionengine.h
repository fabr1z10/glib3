#pragma once

#include <unordered_map>
#include <unordered_set>
#include "monkey/components/collider.h"
#include "monkey/hashpair.h"
#include <monkey/collisionresponse.h>
#include "monkey/math/intersect.h"
#include <monkey/math/raycast2d.h>
#include "monkey/icollisionengine.h"

struct CollisionEngineCell {
    bool dirty;
    std::unordered_set<ICollider*> colliders;
};

struct Location {
    int x0, x1, y0, y1;
    bool operator == (const Location& l) const {
        return (x0 == l.x0 && x1 == l.x1 && y0 == l.y0 && y1 == l.y1);
    }
    bool operator!= (const Location& l) const {
        return !(this->operator==(l));
    }
};

struct CollisionInfo {
    CollisionReport report;
    glm::ivec3 pos;
};

// you might want to have other type of collision engine,
// using other methods (brute force, octree etc)
class SpatialHashingCollisionEngine : public ICollisionEngine {
public:
    ~SpatialHashingCollisionEngine() override;
    // can be 2d or 3d
    explicit SpatialHashingCollisionEngine (const ITable&);
    void Add (ICollider*) override ;
    void Remove(ICollider*) override ;
    void Clear() override ;
    void Move(ICollider*) override;
    void Update(double) override;

    std::pair<glm::ivec3, glm::ivec3> getLocation(const Bounds& b);
    void PushCollider(ICollider*, glm::ivec3 m, glm::ivec3 M);
    void PopCollider(ICollider*, bool rmvPairs);
    std::type_index GetType() override;
//    // Casts a ray against colliders in the scene.
//    // A raycast is conceptually like a laser beam that is fired from a point in space along a particular direction.
//    // Any object making contact with the beam can be detected and reported.
//    // This function returns a RaycastHit object with a reference to the collider that is hit by the ray
//    // (the collider property of the result will be NULL if nothing was hit). The layerMask can be used to detect objects selectively only on certain layers (this allows you to apply the detection only to enemy characters, for example).
    RayCastHit Raycast (glm::vec3 rayOrigin, glm::vec3 rayDir, float length, int mask, bool use_z = false) override ;
    ShapeCastHit ShapeCast (IShape*, const glm::mat4& transform, int mask) override ;
private:
    bool m_3d;
    glm::vec3 m_size;
    std::unique_ptr<IIntersector> m_intersector;
    std::unique_ptr<IRayCast> m_raycast;
    std::unordered_map<glm::ivec3, CollisionEngineCell> m_cells;
    std::unordered_map<ICollider*, std::pair<glm::ivec3, glm::ivec3>> m_colliderLocations;
    std::unordered_map<std::pair<ICollider*, ICollider*>, CollisionInfo> m_previouslyCollidingPairs;

};

//class CollisionEngine : public ICollisionEngine {
//public:
//    CollisionEngine (float cellWidth, float cellHeight);
//    CollisionEngine (const ITable&);
//    ~CollisionEngine() override;
//    void Add (ICollider*) override ;
//    void Remove(ICollider*) override ;
//    void Clear() override ;
//    void Move(ICollider*) override;
//    void PopCollider(ICollider*, bool rmvPairs);
//    void PushCollider(ICollider*, Location);
//    Location GetLocation(const Bounds& b);
//    // runner implementation
//    void Update(double) override;
//
//    using ParentClass = CollisionEngine;

//    void Enable25DCollision(float);
//    std::string toString() override;
//    std::type_index GetType() override;
//
//private:
//    std::unordered_map<std::pair<int, int>, CollisionEngineCell> m_cells;
//    std::unordered_map<ICollider*, Location> m_colliderLocations;
//    float m_width;
//    float m_height;
//    std::unique_ptr<Intersector> m_intersector;
//
//    std::unordered_map<std::pair<ICollider*, ICollider*>, CollisionInfo> m_previouslyCollidingPairs;
//    bool m_coll25d;
//    float m_eps;
//
//};


