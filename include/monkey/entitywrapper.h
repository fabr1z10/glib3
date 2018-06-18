#pragma once

#include <gfx/entity.h>
#include <monkey/luawrapper.h>

namespace luaFunctions {
    
    void PlayScript (luabridge::LuaRef);
    
}

struct EntityWrapper {
    EntityWrapper(Entity* entity) : m_underlying{entity}{}
    static void AddEntity(luabridge::LuaRef ref, EntityWrapper* parent);
    void Clear();
    float GetX() const;
    void SetColor(int, int, int, int);
    void SetText(const std::string&);
    void SetActive (bool);
    std::string GetText() const;
    EntityWrapper GetParent() ;
    static EntityWrapper GetEntity(const std::string&);
    Entity* m_underlying;
};
