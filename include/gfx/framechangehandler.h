#pragma once

#include <string>
#include <memory>
#include <gfx/lua/luawrapper.h>

class Entity;
class IMesh;

class IFrameChangeHandler {

public:
    virtual void Handle (const std::string& anim, int frame) = 0;
    void SetEntity(Entity* entity) {
        m_entity = entity;
    }
    void SetMesh (std::shared_ptr<IMesh>);
    virtual void Init(luabridge::LuaRef ref, const std::string& anim, int frame) = 0;
protected:
    Entity* m_entity;
};