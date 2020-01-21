#include <monkey/components/dynamics2d.h>
#include <monkey/math/geom.h>
#include <iostream>
Dynamics2D::Dynamics2D(float gravity) : Properties(), m_gravity(gravity), m_velocity(0.0f), m_velocitySmoothing(0.0f),
m_velocitySmoothingZ(0.0f)
{
    m_getters.insert(std::make_pair("vx", std::unique_ptr<Accessor<float>>(new Accessor<float>(&(m_velocity.x), true))));

}

Dynamics2D::Dynamics2D(const Dynamics2D& orig) : Properties(orig) {
    m_gravity = orig.m_gravity;
    m_velocity = orig.m_velocity;
    m_velocitySmoothing = orig.m_velocitySmoothing;
    m_velocitySmoothingZ = orig.m_velocitySmoothingZ;
}

std::shared_ptr<Component> Dynamics2D::clone() const {
    return std::make_shared<Dynamics2D>(*this);
}


glm::vec3 Dynamics2D::step(float dt, float targetVelocityX, float accelerationX) {
    // first, apply gravity
    m_velocity.y += m_gravity * dt;
    m_velocity.x = SmoothDamp(
            m_velocity.x, targetVelocityX,
            m_velocitySmoothing,
            accelerationX, dt);
    glm::vec3 delta = m_velocity * dt;

    return delta;

}

glm::vec3 Dynamics2D::step(float dt, float targetVelocityX, float targetVelocityZ, float accelerationX) {
    // first, apply gravitystd::cerr << "11\n";
    m_velocity.y += m_gravity * dt;

    m_velocity.x = SmoothDamp(
            m_velocity.x, targetVelocityX,
            m_velocitySmoothing,
            accelerationX, dt);
    m_velocity.z = SmoothDamp(
            m_velocity.z, targetVelocityZ,
            m_velocitySmoothingZ,
            accelerationX, dt);

    glm::vec3 delta = m_velocity * dt;
    return delta;

}
