#include <monkey/components/dynamics2d.h>
#include <monkey/math/geom.h>
#include <iostream>
Dynamics2D::Dynamics2D(float gravity) : Component(), m_gravity(gravity), m_velocity(0.0f), m_velocitySmoothing(0.0f),
m_velocitySmoothingZ(0.0f)
{
    // m_getters.insert(std::make_pair("vx", std::unique_ptr<Accessor<float>>(new Accessor<float>(&(m_velocity.x), true))));

}

Dynamics2D::Dynamics2D(const ITab & t) : m_velocity(0.0f), m_velocitySmoothing(0.0f), m_velocitySmoothingZ(0.0f) {
    //LuaTable table(ref);mics2
    m_gravity = t.get<float>("gravity");
}

Dynamics::Dynamics(const ITab& t ) {
    m_velocity = t.get<glm::vec2>("velocity", glm::vec2(0.0f));
}

Dynamics3D::Dynamics3D(const ITab&) {
    m_velocity = glm::vec3(0.0f);
}

Dynamics3D::Dynamics3D() : m_velocity(glm::vec3(0.0f)) {

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
