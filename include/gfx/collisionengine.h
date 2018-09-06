#pragma once

#include <unordered_map>
#include <unordered_set>
#include "gfx/collider.h"
#include "gfx/hashpair.h"
#include <gfx/collisionresponse.h>
#include "graph/intersect.h"

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

class CollisionEngine : public Ref {
public:
    CollisionEngine (float cellWidth, float cellHeight);
    void Add (Collider*);
    void Remove(Collider*);
    void Move(Collider*);
    void PopCollider(Collider*);
    void PushCollider(Collider*, Location);
    Location GetLocation(Collider* c);
    void Update(double);
    void SetResponseManager(std::unique_ptr<CollisionResponseManager>);
private:
    std::unordered_map<std::pair<int, int>, CollisionEngineCell> m_cells;
    std::unordered_map<Collider*, Location> m_colliderLocations;
    float m_width;
    float m_height;
    std::unique_ptr<Intersector> m_intersector;
    std::unique_ptr<CollisionResponseManager> m_responseManager;
    std::unordered_map<std::pair<Collider*, Collider*>, CollisionInfo> m_previouslyCollidingPairs;

};


inline void CollisionEngine::SetResponseManager(std::unique_ptr<CollisionResponseManager> r){
    m_responseManager = std::move(r);
}