#pragma once

#include <monkey/components/statemachine.h>
#include <monkey/components/depth25.h>
#include <glm/glm.hpp>

class InputMethod;
class Entity;
class IAnimator;
class ICollisionEngine;

class Jump25 : public State {
public:
    Jump25(float speed, float acceleration);
    void AttachStateMachine(StateMachine*) override;

    void Run(double) override;
    void Init (const ITab&) override;
    void End () override;
protected:
    float m_speed;
    Entity * m_entity;
    float m_velocitySmoothingX;
    float m_velocitySmoothingY;
    glm::vec2 m_velocity;
    float m_acceleration;
    ICollisionEngine * m_coll;
    InputMethod * m_input;
    IAnimator* m_animator;
    ICollisionEngine * m_collision;
    Depth25* m_depth;

};

