#pragma once

#include <array>
#include <platformer/characterstatemachine.h>

class Dynamics2D;
class Controller2D;
class Animator;
class Entity;
class InputMethod;

// this include walk and idle which is a special
// case of walk with target speed = 0
// goes to jump state if it does not touch below.
class Jump : public State2 {
public:
    Jump(float speed, float acceleration, const std::string& jumpUp, const std::string& jumpDown, bool flip);
    Jump(const Jump&);
    // when the state changes to idle,
    // we need to update the animation and the
    // collider shape. These might depend also on other
    // factors (for instance, is supermario? can fire?)
    void Init () override;
    void Run (double) override;
    void End () override {}
    void AttachStateMachine(StateMachine2*) override;
    std::shared_ptr<State2> clone() const override;
    void UpdateAnimation();
private:
    CharacterStateMachine* m_stateMachine;
    Animator* m_animator;
    Dynamics2D* m_dynamics;
    Controller2D* m_controller;
    InputMethod* m_input;
    Entity* m_entity;
    float m_velocitySmoothing;
    float m_speed;
    float m_acceleration;
    int m_animFlag;
    int m_prevAnimFlag;
    std::array<std::string, 2> m_anims;
    std::string m_colliderId;
    bool m_horizontalFlip;

};
