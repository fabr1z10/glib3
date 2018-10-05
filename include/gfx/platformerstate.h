#pragma once

#include <gfx/statemachine.h>
#include <glm/glm.hpp>

class Controller2D;
class Renderer;

class PlatformerState : public State {
public:
    PlatformerState(const std::string& anim);
    void End () override {}
    void Start () override ;
    void Init(Entity* e) override;
protected:
    Controller2D* m_controller;
    Renderer* m_renderer;
    std::string m_anim;
};