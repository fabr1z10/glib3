#pragma once

#include <gfx/components/statemachine.h>
#include <glm/glm.hpp>
#include <gfx/keyboard.h>

class Controller2D;
class Renderer;
class Dynamics2D;

class PlatformerState : public StateBehaviour {
public:
    PlatformerState();
    void Init(Entity* e) override;
protected:
    Keyboard& m_keyboard;
    Entity* m_entity;
    Controller2D* m_controller;
    Dynamics2D* m_dynamics;
    Renderer* m_renderer;
};
