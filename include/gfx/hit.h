#pragma once

#include <gfx/components/statemachine.h>
#include <graph/shape.h>
#include <gfx/lua/luawrapper.h>


class CollisionEngine;
class Renderer;

class Hit : public State {
public:
    Hit (const std::string&);
    void Init(Entity*) override;
    void Start() override;
    bool Run(double) override;
    void End() override {}
protected:
    Renderer* m_renderer;
    std::string m_anim;
};

class HitCollision : public Hit {
public:
    HitCollision (const std::string&, int frame, std::shared_ptr<Shape> collisionShape, glm::vec2 offset, int mask, luabridge::LuaRef callback);
    void Init(Entity*) override;
    void Start() override;
    bool Run(double) override;
    void End() override {}
private:
    luabridge::LuaRef m_callback;
    int m_frame;
    int m_mask;
    glm::vec2 m_offset;
    std::shared_ptr<Shape> m_shape;
    CollisionEngine* m_engine;
    bool m_hitDone;
};