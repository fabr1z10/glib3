#pragma once

#include <array>
#include <platformer/characterstatemachine.h>

class Controller2D;
class Dynamics2D;
class Animator;
class Entity;
class InputMethod;

class Duck : public State2 {
public:
    Duck(float acceleration, const std::string &duckAnim) :
        State2(), m_acceleration(acceleration), m_velocitySmoothing(0.0f), m_duckAnim(duckAnim), m_colliderId("duck") {}

    Duck(const Duck &orig) : State2(orig) {
        m_duckAnim = orig.m_duckAnim;
        m_velocitySmoothing = orig.m_velocitySmoothing;
    }

    void Init() override;

    void Run(double) override;

    void AttachStateMachine(StateMachine2 *sm) override;

    void End() override {}

    std::shared_ptr<State2> clone() const override;

private:
    CharacterStateMachine* m_sm;
    Controller2D* m_controller;
    InputMethod* m_input;
    Dynamics2D * m_dynamics;

    float m_acceleration;
    float m_velocitySmoothing;
    std::string m_duckAnim;
    std::string m_colliderId;

};




