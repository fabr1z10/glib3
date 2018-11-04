#pragma once

#include <unordered_map>
#include <unordered_set>
#include "gfx/components/collider.h"
#include "gfx/hashpair.h"
#include <gfx/collisionresponse.h>
#include "gfx/math/intersect.h"
#include "gfx/runner.h"

struct CollisionEngineCell {
    bool dirty;
    std::unordered_set<Collider*> colliders;
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

class CollisionEngine : public Runner {
public:
    CollisionEngine (float cellWidth, float cellHeight);
    void Add (Collider*);
    void Remove(Collider*);
    void Clear();
    void Move(Collider*);
    void PopCollider(Collider*);
    void PushCollider(Collider*, Location);
    Location GetLocation(const Bounds& b);
    // runner implementation
    void Update(double) override;
    void SetResponseManager(std::unique_ptr<CollisionResponseManager>);
    using ParentClass = CollisionEngine;
    // Casts a ray against colliders in the scene.
    // A raycast is conceptually like a laser beam that is fired from a point in space along a particular direction.
    // Any object making contact with the beam can be detected and reported.
    // This function returns a RaycastHit object with a reference to the collider that is hit by the ray
    // (the collider property of the result will be NULL if nothing was hit). The layerMask can be used to detect objects selectively only on certain layers (this allows you to apply the detection only to enemy characters, for example).
    RayCastHit2D Raycast (glm::vec3 rayOrigin, glm::vec2 rayDir, float length, int mask);
    Entity* ShapeCast (std::shared_ptr<Shape>, const glm::mat4& transform, int mask);
    void Enable25DCollision(float);
private:
    std::unordered_map<std::pair<int, int>, CollisionEngineCell> m_cells;
    std::unordered_map<Collider*, Location> m_colliderLocations;
    float m_width;
    float m_height;
    std::unique_ptr<Intersector> m_intersector;
    std::unique_ptr<CollisionResponseManager> m_responseManager;
    std::unordered_map<std::pair<Collider*, Collider*>, CollisionInfo> m_previouslyCollidingPairs;
    bool m_coll25d;
    float m_eps;

};


inline void CollisionEngine::SetResponseManager(std::unique_ptr<CollisionResponseManager> r){
    m_responseManager = std::move(r);
}

