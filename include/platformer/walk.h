#pragma once

#include <platformer/characterstatemachine.h>

class Controller2D;
class Animator;
class Entity;
class InputMethod;

// this include walk and idle which is a special
// case of walk with target speed = 0
// goes to jump state if it does not touch below.
class Walk : public State2 {
public:
    Walk(float speed) : State2(), m_speed(speed), m_velocitySmoothing(0.0f) {}
    Walk(const Walk & orig) : State2(orig) {
        m_speed = orig.m_speed;
        m_velocitySmoothing = orig.m_velocitySmoothing;
    }
    void Init () override {}
    void Run(double) override;
    void AttachStateMachine(StateMachine2* sm) override;
    void End () override {}
    std::shared_ptr<State2> clone() const override;

private:
    CharacterStateMachine* m_stateMachine;
    //Animator* m_animator;
    Controller2D* m_controller;
    InputMethod* m_input;
    Entity* m_entity;
    float m_velocitySmoothing;
    float m_speed;
};




