#pragma once


#include <gfx/components/statemachine2.h>

class Controller2D;
class Dynamics2D;
class InputMethod;
class Animator;

class PlatformerState : public State2 {
public:
    PlatformerState();
    PlatformerState(const PlatformerState&);
    void AttachStateMachine(StateMachine2*) override;
protected:
    Animator* m_animator;
    StateMachine2* m_sm;
    Controller2D * m_controller;
    Dynamics2D * m_dynamics;
    InputMethod * m_input;
    Entity * m_entity;
};