#pragma once

#include <gfx/entity.h>
#include <monkey/luawrapper.h>

namespace luaFunctions {
    
    void PlayScript (luabridge::LuaRef);
    
}

struct EntityWrapper {
    EntityWrapper(Entity* entity) : m_underlying{entity}{}
    float GetX() const;
    void SetColor(int, int, int, int);
    void SetText(const std::string&);
    std::string GetText() const;
    EntityWrapper GetParent() ;
    static EntityWrapper GetEntity(const std::string&);
    Entity* m_underlying;
};
