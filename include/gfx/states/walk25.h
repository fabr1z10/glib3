#pragma once

#include <gfx/components/statemachine.h>
#include <glm/glm.hpp>

class InputMethod;
class Entity;
class IAnimator;
class ICollisionEngine;

class Walk25 : public State {
public:
    Walk25(float speed, float acceleration, bool fliph);
    Walk25(const Walk25&);
    std::shared_ptr<State> clone() const override;
    void Run(double) override;
    void Init () override;
    void End () override;
    void AttachStateMachine(StateMachine*) override;
    //void AddKey (int, std::shared_ptr<StateAction>);
    //bool KeyListener (int) override;
    //virtual void ModifyAnimation() = 0;
    // virtual void ResetAnimation() = 0;
protected:
    StateMachine* m_sm;
    InputMethod * m_input;
    IAnimator* m_animator;

    Entity * m_entity;
    bool m_flipHorizontal;
    float m_speed;
    glm::vec2 m_velocity;
    float m_velocitySmoothingX;
    float m_velocitySmoothingY;
    float m_acceleration;
    ICollisionEngine * m_collision;

};