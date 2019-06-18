#pragma once

#include <gfx/properties.h>
#include <glm/glm.hpp>

// properties for dynamics
class Dynamics2D : public Properties {
public:
    Dynamics2D(float gravity);
    glm::vec2 step(float dt, float tvx, float a);
    glm::vec2 m_velocity;
    float m_gravity;
    std::type_index GetType() override;
    using ParentClass = Properties;
private:
    float m_velocitySmoothing;
};

inline std::type_index Dynamics2D::GetType() {
    return std::type_index(typeid(Properties));
}

