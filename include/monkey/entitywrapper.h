#pragma once

#include <gfx/entity.h>
#include <monkey/luawrapper.h>

namespace luaFunctions {
    
    void PlayScript (luabridge::LuaRef);
    
}

struct EntityWrapper {
    EntityWrapper() : m_underlying(nullptr) {}
    EntityWrapper(Entity* entity) : m_underlying{entity}{}
    static EntityWrapper AddEntity(luabridge::LuaRef ref, EntityWrapper* parent);
    static EntityWrapper RemoveEntity(const std::string& tag);
    void Clear();
    bool IsNil() const;
    float GetX() const;
    std::string GetAnim() const;
    bool GetFlipX() const;
    void SetColor(int, int, int, int);
    void SetText(const std::string&);
    void SetActive (bool);
    //static void EnableGroup(int);
    //static void DisableGroup(int);
    std::string GetText() const;
    int GetLines() const;
    void SetPosition(float x, float y, float z);
    EntityWrapper GetParent() ;
    static EntityWrapper GetEntity(const std::string&);
    Entity* m_underlying;
    void AppendText (const std::string&);
};


inline bool EntityWrapper::IsNil() const {
    return m_underlying == nullptr;
}