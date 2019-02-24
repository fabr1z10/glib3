#pragma once

#include <gfx/component.h>
#include <glm/glm.hpp>


class Dynamics2D : public Component {
public:
    Dynamics2D (float jumpHeight, float timeToJumpApex) :
        m_velocity(glm::vec2(0.0f)), m_jumpHeight(jumpHeight), m_timeToJumpApex(timeToJumpApex) {
        Init();
    }
    Dynamics2D (const Dynamics2D& orig) : Component(orig), m_jumpHeight(orig.m_jumpHeight), m_timeToJumpApex(orig.m_timeToJumpApex) {
        Init();
    }
    void Init() {
        m_gravity = -(2.0f * m_jumpHeight) / (m_timeToJumpApex * m_timeToJumpApex);
        m_jumpVelocity = fabs(m_gravity) * m_timeToJumpApex;
    }
    void Start() override {}
    void Update(double) override {}
    std::shared_ptr<Component> clone() const override {
        return std::make_shared<Dynamics2D>(Dynamics2D(*this));
    }
    glm::vec2 m_velocity;
    float m_gravity;
    float m_jumpVelocity;
    float m_timeToJumpApex;
    float m_jumpHeight;
    using ParentClass = Dynamics2D;
};
