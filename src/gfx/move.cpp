#include <gfx/move.h>
#include <iostream>
#include "gfx/engine.h"

MoveTo::MoveTo(const std::string& actor, glm::vec2 pos, float speed, bool relative, bool immediate) : Activity(),
    m_entity(nullptr), m_actorId(actor), m_toPos(pos), m_speed{speed}, m_lengthCovered{0.0f}, m_lengthToCover{0.0f}, m_relative{relative}, m_immediate{immediate}
{

}

MoveTo::MoveTo(Entity* entity, glm::vec2 pos, float speed, bool relative, bool immediate) : Activity(),
    m_entity(entity), m_toPos(pos), m_speed{speed}, m_lengthCovered{0.0f}, m_lengthToCover{0.0f}, m_relative{relative}, m_immediate{immediate}
{

}

void MoveTo::Reset() {
    Activity::Reset();
    m_lengthToCover = 0.0f;
    m_lengthCovered = 0.0f;

}

void MoveTo::Start() {
    if (m_entity == nullptr) {
        m_entity = Engine::get().GetRef<Entity>(m_actorId);
    }
    glm::vec2 displacement;
    if (m_relative) {
        displacement = m_toPos;
    } else {
        glm::vec2 pos(m_entity->GetPosition());
        displacement = m_toPos - pos;
    }

    if (m_immediate) {
        m_entity->Move(displacement);
        SetComplete();
    } else {
        m_lengthToCover = glm::length(displacement);
        if (m_lengthToCover == 0) {
            SetComplete();
        } else {
            m_velocity = glm::normalize(displacement) * m_speed;
        }
    }
}


void MoveTo::Run (float dt) {
    glm::vec2 delta = dt * m_velocity;
    m_lengthCovered += glm::length(delta);
    if (m_lengthCovered >= m_lengthToCover) {
        m_entity->SetPosition(m_toPos);
        SetComplete();
    }
    else {
        m_entity->Move(delta);
    }

}

MoveGravity::MoveGravity (const std::string& actorId, glm::vec2 initialVelocity, float g, float yStop) :
        Activity(), m_entity{nullptr}, m_actorId(actorId), m_initialVelocity(initialVelocity), m_g(g), m_yStop(yStop) {}


void MoveGravity::Start() {
    if (m_entity == nullptr) {
        m_entity = Engine::get().GetRef<Entity>(m_actorId);
    }
    m_velocity = m_initialVelocity;
    m_angle = 0.0f;
}

void MoveGravity::Run(float dt) {
    glm::vec3 p(m_entity->GetPosition());
    glm::mat4 wt = m_entity->GetWorldTransform();
    m_angle += 0.2f;
    glm::vec2 pos(p);
    pos += m_velocity * dt;
    m_velocity += glm::vec2(0, -m_g) *dt;
    if (pos.y <= m_yStop) {
        pos.y = m_yStop;
        m_angle = 0.0f;
        SetComplete();
    }
    m_entity->SetPosition(glm::vec3(pos, p.z), m_angle);
}
