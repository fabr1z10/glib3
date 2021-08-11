#pragma once

#include <monkey/component.h>
#include <glm/glm.hpp>

// properties for dynamics
class __attribute__ ((visibility ("default"))) Dynamics2D : public Component {
public:
    Dynamics2D(float gravity);
    Dynamics2D(const ITab&);
    glm::vec3 step(float dt, float tvx, float a);
    glm::vec3 step_xy(float dt, float vx, float vy, float a);
    glm::vec3 step(float dt, float tvx, float tvz, float a);
    glm::vec3 m_velocity;
    void Start() override {}
    void Update(double) override {}
    float m_gravity;
    using ParentClass = Dynamics2D;
    //std::type_index GetType() override;
private:
    float m_velocitySmoothing;
    float m_velocitySmoothingZ;
};


