#pragma once

#include <gfx/entity.h>
#include <gfx/lua/luawrapper.h>

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
    static int AddEntity(luabridge::LuaRef ref, EntityWrapper* parent);
    static void RemoveEntityFromTag (const std::string& tag);
    static void RemoveEntityFromId (int id);
    void Clear();
    void ClearText();
    void Remove();
    bool IsNil() const;
    float GetX() const;
    float GetY() const;
    float GetZ() const;
    float GetVy() const;
    void SetVy(float);
    std::string GetTag() const;
    std::string GetState() const;
    luabridge::LuaRef GetProperty(const std::string&) const;
    void SetProperty (const std::string&, luabridge::LuaRef value);
    void SendMessage (luabridge::LuaRef ref);
    luabridge::LuaRef GetAnim() const;
    void SetAnim(const std::string&);
    void SetModel (const std::string&, const std::string&);
    bool GetFlipX() const;
    void SetFlipX(bool);
    void SetColor(int, int, int, int);
    void SetText(const std::string&);
    void SetActive (bool);
    void EnableDepth(bool);
    void EnableUpdate(bool);
    void SetEnableControls (bool);
    void EnableCollisions (bool);
    luabridge::LuaRef GetTextInfo();
    //static void EnableGroup(int);
    //static void DisableGroup(int);
    std::string GetText() const;
    int GetLines() const;
    void SetPosition(float x, float y, float z);
    void Move (float x, float y, float z);
    EntityWrapper GetParent() ;
    static EntityWrapper GetEntity(const std::string&);
    Entity* m_underlying;
    void AppendText (luabridge::LuaRef);
    void AppendButton (luabridge::LuaRef ref);
    void ChangeState(const std::string& name);
    void ChangeStateParam(const std::string& name, luabridge::LuaRef ref);
    void ResetState();
    luabridge::LuaRef GetInfo();
    void EnableStateMachine(bool);
    static void KillScript(const std::string& scriptName);
};


inline bool EntityWrapper::IsNil() const {
    return m_underlying == nullptr;
}
