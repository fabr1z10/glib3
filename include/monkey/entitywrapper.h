#pragma once

#include <monkey/entity.h>
#include <monkey/lua/luawrapper.h>

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

    /**
     * Dynamically adds an entity to the parent, described by a lua table.
     * The newly created id will be returned to LUA, so that it will be possible
     * to operate on the new entity (for instance, by attaching a script)
     * @param ref the entity specification
     * @param parent the parent node the new entity will be a child of
     * @return the id of the newly created entity
     */
    static int AddEntity(luabridge::LuaRef ref, EntityWrapper* parent);
    static bool isKeyDown(int);

    /** get all files in folder, return as array
     *
     * @param dir this is the name of the folder relative to HOME
     *        recursive whether the search is recursive
     * @return a list of lua files in the folder
     */
    static luabridge::LuaRef getFiles (const std::string& dir, bool recursive, const std::string& pattern);

    static EntityWrapper GetEntityFromTag(const std::string&);
    static EntityWrapper GetEntityFromId(int id);

    /**
     * Removes the entity with the specified tag from the scene.
     * @param tag the tag of the entity that will be removed
     */
    static void RemoveEntityFromTag (const std::string& tag);

    /**
     * Removes the entity with the specified id from the scene.
     * @param tag the tag of the entity that will be removed
     */
    static void RemoveEntityFromId (int id);



    void Clear();
    void ClearText();
    void Remove();
    bool IsNil() const;
    int GetId() const;
    float GetX() const;
    float GetY() const;
    float GetZ() const;
    float GetVx() const;
    float GetVx25() const;
    float GetVy() const;
    void SetVx(float);
    void SetVx25(float);
    void SetVy(float);
    float GetScale() const;
    void SetScale(float);
    std::string GetTag() const;
    std::string GetState() const;
    void SetState (const std::string&) ;
    void EnableStateMachine(bool);
    void DropCharacters();
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
    // simulate a hotspot click
    void ForceClick (float x, float y);
    luabridge::LuaRef GetTextInfo();
    luabridge::LuaRef GetAttackRect();
    //static void EnableGroup(int);
    //static void DisableGroup(int);
    std::string GetText() const;
    int GetLines() const;
    void SetPosition(float x, float y, float z);
    void Move (float x, float y, float z);
    EntityWrapper GetParent() ;
    Entity* m_underlying;
    void AppendText (luabridge::LuaRef);
    void AppendButton (luabridge::LuaRef ref);
    void ChangeState(const std::string& name);
    void ChangeStateParam(const std::string& name, luabridge::LuaRef ref);
    void ResetState();
    void SetFollow(bool);
    void Call(const std::string& id, luabridge::LuaRef args);
    luabridge::LuaRef GetInfo();
    static void KillScript(const std::string& scriptName);
};


inline bool EntityWrapper::IsNil() const {
    return m_underlying == nullptr;
}
