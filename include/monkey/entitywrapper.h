#pragma once

#include <gfx/entity.h>
#include <monkey/luawrapper.h>

namespace luaFunctions {
    
    void PlayScript (luabridge::LuaRef);
    void EnableScriptEngine (bool);
    void EndRoom();
    void EnableMouse(bool);
    void EnableKeyboard(bool);
    void EnableKey(int, bool);
    //void EnableUpdate(bool);
}

struct EntityWrapper {
    EntityWrapper() : m_underlying(nullptr) {}
    EntityWrapper(Entity* entity) : m_underlying{entity}{}
    static EntityWrapper AddEntity(luabridge::LuaRef ref, EntityWrapper* parent);
    static EntityWrapper RemoveEntity(const std::string& tag);
    void Clear();
    void ClearText();

    bool IsNil() const;
    float GetX() const;
    float GetY() const;
    float GetZ() const;
    std::string GetAnim() const;
    bool GetFlipX() const;
    void SetColor(int, int, int, int);
    void SetText(const std::string&);
    void SetActive (bool);
    void EnableUpdate(bool);
    void SetEnableControls (bool);
    luabridge::LuaRef GetTextInfo();
    //static void EnableGroup(int);
    //static void DisableGroup(int);
    std::string GetText() const;
    int GetLines() const;
    void SetPosition(float x, float y, float z);
    EntityWrapper GetParent() ;
    static EntityWrapper GetEntity(const std::string&);
    Entity* m_underlying;
    void AppendText (const std::string&);
    void AppendButton (luabridge::LuaRef ref);
    void ChangeState(const std::string& name);
};


inline bool EntityWrapper::IsNil() const {
    return m_underlying == nullptr;
}