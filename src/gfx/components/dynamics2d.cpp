#include <gfx/components/dynamics2d.h>
#include <gfx/math/geom.h>

Dynamics2D::Dynamics2D(float gravity) : Properties(), m_gravity(gravity), m_velocity(glm::vec2(0.0f)), m_velocitySmoothing(0.0f) {
    m_getters.insert(std::make_pair("vx", std::unique_ptr<Accessor<float>>(new Accessor<float>(&(m_velocity.x), true))));

}


glm::vec2 Dynamics2D::step(float dt, float targetVelocityX, float accelerationX) {
    // first, apply gravity
    m_velocity.y += m_gravity * dt;

    m_velocity.x = SmoothDamp(
            m_velocity.x, targetVelocityX,
            m_velocitySmoothing,
            accelerationX, dt);
    glm::vec2 delta = m_velocity * dt;
    return delta;

}