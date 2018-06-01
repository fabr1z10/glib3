#pragma once

#include <gfx/entity.h>

struct EntityWrapper {
    EntityWrapper(Entity* entity) : m_underlying{entity}{}
    float GetX() const;
    void SetColor(int, int, int, int);
    EntityWrapper GetParent() ;

    Entity* m_underlying;
};