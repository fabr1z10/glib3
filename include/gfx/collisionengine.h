#pragma once

#include <unordered_map>
#include <unordered_set>
#include "gfx/collider.h"
#include "gfx/hashpair.h"

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

class CollisionEngine : public Ref {
public:
    CollisionEngine (float cellWidth, float cellHeight) : Ref(), m_width{cellWidth}, m_height{cellHeight} {}
    void Add (Collider*);
    void Remove(Collider*);
    void Move(Collider*);
    void PopCollider(Collider*);
    void PushCollider(Collider*, Location);
    Location GetLocation(Collider* c);

private:
    std::unordered_map<std::pair<int, int>, CollisionEngineCell> m_cells;
    std::unordered_map<Collider*, Location> m_colliderLocations;
    float m_width;
    float m_height;

};