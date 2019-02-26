#pragma once

#include <platformer/characterstatemachine.h>

class Controller2D;
class Animator;
class Entity;

// this include walk and idle which is a special
// case of walk with target speed = 0
// goes to jump state if it does not touch below.
class Walk : public State2 {
public:
    Walk(float speed);
    // when the state changes to idle,
    // we need to update the animation and the
    // collider shape. These might depend also on other
    // factors (for instance, is supermario? can fire?)
    void Init () override;
    void Run (double) override;
    void End () override {}
    void AttachStateMachine(StateMachine2*) override;
private:
    CharacterStateMachine* m_stateMachine;
    Animator* m_animator;
    Controller2D* m_controller;
    Entity* m_entity;
    float m_velocitySmoothing;
    float m_speed;
};
