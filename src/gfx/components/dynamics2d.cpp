#include <gfx/components/dynamics2d.h>

Dynamics2D::Dynamics2D(float gravity) : Properties(), m_gravity(gravity), m_velocity(glm::vec2(0.0f)) {
    m_getters.insert(std::make_pair("vx", std::unique_ptr<Accessor<float>>(new Accessor<float>(&(m_velocity.x), true))));

}
