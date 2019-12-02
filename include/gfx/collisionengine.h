#pragma once

#include <unordered_map>
#include <unordered_set>
#include "gfx/components/collider.h"
#include "gfx/hashpair.h"
#include <gfx/collisionresponse.h>
#include "gfx/math/intersect.h"
#include "gfx/icollisionengine.h"

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
    int i, j;
};


class CollisionEngine : public ICollisionEngine {
public:
    CollisionEngine (float cellWidth, float cellHeight);
    ~CollisionEngine() override;
    void Add (ICollider*) override ;
    void Remove(ICollider*) override ;
    void Clear() override ;
    void Move(ICollider*) override;
    void PopCollider(ICollider*, bool rmvPairs);
    void PushCollider(ICollider*, Location);
    Location GetLocation(const Bounds& b);
    // runner implementation
    void Update(double) override;

    using ParentClass = CollisionEngine;
    // Casts a ray against colliders in the scene.
    // A raycast is conceptually like a laser beam that is fired from a point in space along a particular direction.
    // Any object making contact with the beam can be detected and reported.
    // This function returns a RaycastHit object with a reference to the collider that is hit by the ray
    // (the collider property of the result will be NULL if nothing was hit). The layerMask can be used to detect objects selectively only on certain layers (this allows you to apply the detection only to enemy characters, for example).
    RayCastHit Raycast (glm::vec3 rayOrigin, glm::vec3 rayDir, float length, int mask, bool use_z = false) override ;
    ShapeCastHit ShapeCast (std::shared_ptr<Shape>, const glm::mat4& transform, int mask) override ;
    void Enable25DCollision(float);
    std::string toString() override;
    std::type_index GetType() override;

private:
    std::unordered_map<std::pair<int, int>, CollisionEngineCell> m_cells;
    std::unordered_map<ICollider*, Location> m_colliderLocations;
    float m_width;
    float m_height;
    std::unique_ptr<Intersector> m_intersector;

    std::unordered_map<std::pair<ICollider*, ICollider*>, CollisionInfo> m_previouslyCollidingPairs;
    bool m_coll25d;
    float m_eps;

};


