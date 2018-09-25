#pragma once

#include <gfx/statemachine.h>

class CollisionEngine;
class Renderer;

class Hit : public State {
public:
    Hit (const std::string&);
    void Init(Entity*) override;
    void Start() override;
    bool Run(double) override { return false;}
    void End() override {}
private:
    CollisionEngine* m_engine;
    Renderer* m_renderer;
    std::string m_anim;
};