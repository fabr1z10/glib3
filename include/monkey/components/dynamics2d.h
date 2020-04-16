#pragma once

#include <monkey/properties.h>
#include <glm/glm.hpp>

// properties for dynamics
class Dynamics2D : public Properties {
public:
    Dynamics2D(float gravity);
    Dynamics2D(const Dynamics2D&);
    Dynamics2D(const ITable&);
    std::shared_ptr<Component> clone() const override;
    glm::vec3 step(float dt, float tvx, float a);
    glm::vec3 step(float dt, float tvx, float tvz, float a);
    glm::vec3 m_velocity;
    float m_gravity;
    std::type_index GetType() override;
    using ParentClass = Properties;
private:
    float m_velocitySmoothing;
    float m_velocitySmoothingZ;
};

inline std::type_index Dynamics2D::GetType() {
    return std::type_index(typeid(Properties));
}

