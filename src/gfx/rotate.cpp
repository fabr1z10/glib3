#include <gfx/rotate.h>
#include <gfx/engine.h>
#include <graph/geom.h>

Rotate::Rotate(const std::string& actorId, float degrees, float acceleration, float initialSpeed) :
        Activity(), m_actorId(actorId), m_degrees(degrees), m_acceleration(acceleration), m_speed(initialSpeed), m_degreesCount(0.0f), m_entity(nullptr)
{
}

void Rotate::Start() {

    m_entity = Engine::get().GetRef<Entity>(m_actorId);
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