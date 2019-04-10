#include <gfx/activities/rotate.h>
#include <gfx/engine.h>
#include <gfx/math/geom.h>

Rotate::Rotate(float degrees, float acceleration, float initialSpeed) :
        TargetActivity(), m_degrees(degrees), m_acceleration(acceleration), m_speed(initialSpeed), m_degreesCount(0.0f), m_entity(nullptr)
{
}

void Rotate::Start() {
    TargetActivity::Start();

    m_degreesCount = 0.0f;
}

void Rotate::Run(float dt) {
    m_degreesCount += m_speed * dt;
    glm::vec3 pos = m_entity->GetPosition();
    if (fabs(m_degreesCount) >= fabs(m_degrees)) {
        m_degreesCount = m_degrees;
        SetComplete();
    }
    m_entity->SetPosition(pos, deg2rad * m_degreesCount);
    m_speed += m_acceleration * dt;
}