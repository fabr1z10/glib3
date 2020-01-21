#pragma once

#include <monkey/activities/targetactivity.h>
#include <monkey/math/shape.h>
#include <monkey/lua/luawrapper.h>

class CollisionEngine;
class Entity;
class Renderer;

class CollisionCheck : public TargetActivity {

public:
    CollisionCheck(std::shared_ptr<Shape> shape, const std::string& actorId, glm::vec2 offset, int mask, luabridge::LuaRef callback);
    void Start() override;
    void Run (float dt) override {};

private:
    std::shared_ptr<Shape> m_shape;
    std::string m_actorId;
    Entity* m_actor;
    glm::vec2 m_offset;
    int m_mask;
    luabridge::LuaRef m_callback;
    CollisionEngine* m_engine;
    //Renderer* m_renderer;
};
