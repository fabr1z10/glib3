#pragma once

#include <monkey/component.h>
#include <glm/glm.hpp>

// properties for dynamics
class Dynamics2D : public Component {
public:
    Dynamics2D(float gravity);
    Dynamics2D(const Dynamics2D&);
    Dynamics2D(const ITable&);
    std::shared_ptr<Component> clone() const override;
    glm::vec3 step(float dt, float tvx, float a);
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


