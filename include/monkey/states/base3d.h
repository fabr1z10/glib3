#pragma once

#include <monkey/components/statemachine.h>
#include <monkey/components/animrenderer.h>

class Controller3D;
class Dynamics3D;

// this is the walk state for moving in 3d world (x, z horizontal)
class Base3D : public State {
public:
    explicit Base3D(const ITab&);
    void AttachStateMachine(StateMachine*) override;

protected:
    Controller3D* m_controller;
    Dynamics3D * m_dynamics;
    AnimationRenderer* m_renderer;
    Entity * m_entity;

    float m_acceleration;
    float m_maxSpeed;
    float m_gravity;

};

