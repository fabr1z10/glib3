#pragma once

#include <unordered_map>
#include <list>
#include "gfx/collider.h"
#include "gfx/hashpair.h"

struct CollisionEngineCell {
    bool dirty;
    std::list<Collider*> colliders;
};

class CollisionEngine {
public:
    CollisionEngine (float cellWidth, float cellHeight) : m_width{cellWidth}, m_height{cellHeight} {}
    void Add (Collider*);
private:
    std::unordered_map<std::pair<int, int>, CollisionEngineCell> m_cells;
    float m_width;
    float m_height;

};