#pragma once

#include <gfx/component.h>
#include <glm/glm.hpp>


class Dynamics2D : public Component {
public:
    Dynamics2D (float jumpHeight, float timeToJumpApex) : m_velocity(glm::vec2(0.0f)) {
        m_gravity = -(2.0f * jumpHeight) / (timeToJumpApex * timeToJumpApex);
        m_jumpVelocity = fabs(m_gravity) * timeToJumpApex;
    }
    void Start() override {}
    void Update(double) override {}

    glm::vec2 m_velocity;
    float m_gravity;
    float m_jumpVelocity;
    using ParentClass = Dynamics2D;
};