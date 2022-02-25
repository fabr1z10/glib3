#pragma once

#include <unordered_map>
#include <unordered_set>
#include "monkey/components/collider.h"
#include "monkey/hashpair.h"
#include <monkey/collisionresponse.h>
#include "monkey/math/intersect.h"
#include <monkey/math/raycast2d.h>
#include "monkey/icollisionengine.h"




// you might want to have other type of collision engine,
// using other methods (brute force, octree etc)

// 2D spatial collision engine
class SpatialHashingCollisionEngine : public ICollisionEngine {
public:
    ~SpatialHashingCollisionEngine() override;
    explicit SpatialHashingCollisionEngine (const ITab&);
    void Add (ICollider*) override ;
    void Remove(ICollider*) override ;
    void Clear() override ;
    void Move(ICollider*) override;
    void Update(double) override;

    std::pair<glm::ivec2, glm::ivec2> getLocation(const Bounds& b);
    void PushCollider(ICollider*, glm::ivec2 m, glm::ivec2 M);
    void PopCollider(ICollider*, bool rmvPairs);
    std::type_index GetType() override;
//    // Casts a ray against colliders in the scene.
//    // A raycast is conceptually like a laser beam that is fired from a point in space along a particular direction.
//    // Any object making contact with the beam can be detected and reported.
//    // This function returns a RaycastHit object with a reference to the collider that is hit by the ray
//    // (the collider property of the result will be NULL if nothing was hit). The layerMask can be used to detect objects selectively only on certain layers (this allows you to apply the detection only to enemy characters, for example).
	RayCastHit Raycast (glm::vec3 rayOrigin, glm::vec3 rayDir, float length, int mask, bool use_z = false) override ;
    std::vector<ShapeCastHit> ShapeCast (IShape*, const glm::mat4& transform, int mask, bool onlyFirst = false) override ;
private:
	struct CollisionInfo {
		CollisionReport report;
		glm::ivec2 pos;
	};
    glm::vec2 m_size;
    std::unique_ptr<IIntersector> m_intersector;
    std::unique_ptr<IRayCast> m_raycast;
    std::unordered_map<glm::ivec2, CollisionEngineCell> m_cells;
    std::unordered_map<ICollider*, std::pair<glm::ivec2, glm::ivec2>> m_colliderLocations;
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


