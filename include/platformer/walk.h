#pragma once

#include <platformer/characterstatemachine.h>

class Controller2D;
class Dynamics2D;
class Animator;
class Entity;
class InputMethod;

// this include walk and idle which is a special
// case of walk with target speed = 0
// goes to jump state if it does not touch below.

// walk handles the following animanitions:
// idle -- when no button is pressed, and horizontal velocity is below eps
// walk -- when button is pressed and horizontal velocity has same direction as button
// turn -- when button is pressed and horizontal velocity has opposite direction than button
class Walk : public State2 {
public:
    Walk(float speed, float acceleration, float jumpVelocity,
        const std::string& idleAnim, const std::string& walkAnim, const std::string& turnAnim) : State2(),
    m_speed(speed), m_acceleration(acceleration), m_velocitySmoothing(0.0f), m_jumpVelocity(jumpVelocity),
    m_anims{idleAnim, walkAnim, turnAnim}, m_prevAnimFlag(-1), m_colliderId("walk") {
    }
    Walk(const Walk & orig) : State2(orig) {
        m_speed = orig.m_speed;
        m_velocitySmoothing = orig.m_velocitySmoothing;
    }
    void Init () override;
    void Run(double) override;
    void AttachStateMachine(StateMachine2* sm) override;
    void End () override {}
    void KeyListener(int);
    std::shared_ptr<State2> clone() const override;
    void UpdateAnimation(bool left, bool right);

private:
    CharacterStateMachine* m_sm;
    Controller2D* m_controller;
    Dynamics2D * m_dynamics;
    InputMethod* m_input;
    Entity* m_entity;
    float m_velocitySmoothing;
    float m_acceleration;
    float m_speed;
    float m_jumpVelocity;
    int m_animFlag;
    int m_prevAnimFlag;
    std::array<std::string, 3> m_anims;
    std::string m_colliderId;
};




