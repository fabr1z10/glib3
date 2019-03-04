#include <gfx/activities/move.h>
#include <iostream>
#include "gfx/engine.h"
#include <gfx/math/geom.h>

MoveTo::MoveTo(const std::string& actor, glm::vec2 pos, float speed, bool relative, bool immediate) : Activity(),
    m_entity(nullptr), m_actorId(actor), m_toPos(pos), m_speed{speed}, m_lengthCovered{0.0f}, m_lengthToCover{0.0f}, m_relative{relative},
                                                                                                      m_immediate{immediate}, m_acceleration(0.0f), m_accelerationVector(0.0f)
{

}

MoveTo::MoveTo(Entity* entity, glm::vec2 pos, float speed, bool relative, bool immediate) : Activity(),
    m_entity(entity), m_toPos(pos), m_speed{speed}, m_lengthCovered{0.0f}, m_lengthToCover{0.0f}, m_relative{relative},m_acceleration(0.0f), m_immediate{immediate},m_accelerationVector(0.0f)

{

}

void MoveTo::Reset() {
    Activity::Reset();
    m_lengthToCover = 0.0f;
    m_lengthCovered = 0.0f;
    m_lengthCovered = 0.0f;
}

void MoveTo::Start() {
    if (m_entity == nullptr) {
        m_entity = Engine::get().GetRef<Entity>(m_actorId);
    }
    glm::vec2 displacement;
    //glm::mat4 m = m_entity->GetWorldTransform();
    glm::vec2 pos(m_entity->GetPosition());
    if (m_relative) {
        displacement = m_toPos;
        m_finalPosition = pos + displacement;
    } else {
        m_finalPosition = m_toPos;
        displacement = m_toPos - pos;
    }

    if (m_immediate) {
        m_entity->MoveOrigin(displacement);

        SetComplete();
    } else {
        m_lengthToCover = glm::length(displacement);
        if (m_lengthToCover == 0) {
            SetComplete();
        } else {
            glm::vec2 nd = glm::normalize(displacement);
            m_velocity = nd * m_speed;
            m_accelerationVector = nd * m_acceleration;
        }
    }
}


void MoveTo::Run (float dt) {
    glm::vec2 delta = dt * m_velocity;
    m_velocity += m_accelerationVector * dt;

    m_lengthCovered += glm::length(delta);
    if (m_lengthCovered >= m_lengthToCover) {
        m_entity->SetPosition(m_finalPosition);
        SetComplete();
    }
    else {
        m_entity->MoveOrigin(delta);
    }

}

MoveAndRotateTo::MoveAndRotateTo(const std::string &actorId, glm::vec2 pos, float speed, bool relative, bool immediate,
                                 float angle, bool angleRelative)
        : MoveTo(actorId, pos, speed, relative, immediate), m_angle(angle), m_angleRelative(angleRelative)
{

}

void MoveAndRotateTo::Start() {
    MoveTo::Start();
    m_initAngle = m_entity->GetAngle();
    if (!m_angleRelative) {
        m_endAngle = m_angle;
        m_deltaAngle = m_endAngle - m_initAngle;
    } else {
        m_endAngle = m_initAngle + m_angle;
        m_deltaAngle = m_angle;
    }
}

void MoveAndRotateTo::Run(float dt) {
    MoveTo::Run(dt);
    float angle = m_initAngle + m_deltaAngle * (m_lengthCovered/m_lengthToCover);
    if (this->IsComplete()) {
        m_entity->SetAngle(m_endAngle);
    } else {
        m_entity->SetAngle(angle);
    }
}

MoveAccelerated::MoveAccelerated (
    const std::string& actorId,
    glm::vec2 initialVelocity,
    glm::vec2 acceleration,
    float yStop,
    float rotationSpeed,
    float finalRotation) :
Activity(), m_entity{nullptr}, m_actorId(actorId),
m_initialVelocity(initialVelocity), m_acceleration(acceleration), m_yStop(yStop), m_rotationSpeed(rotationSpeed), m_finalRotation(finalRotation) {

}


void MoveAccelerated::Start() {
    if (m_entity == nullptr) {
        m_entity = Engine::get().GetRef<Entity>(m_actorId);
    }
    m_velocity = m_initialVelocity;
    m_angle = 0.0f;
    //std::cout << "Initial velocity " << m_velocity.x << "," << m_velocity.y << "\n";
    //std::cout << "rot speed  " << m_rotationSpeed << "\n";
}

void MoveAccelerated::Run(float dt) {
    glm::vec3 p(m_entity->GetPosition());
    //glm::mat4 wt = m_entity->GetWorldTransform();
    m_angle += m_rotationSpeed*dt;
    glm::vec2 pos(p);
    pos += m_velocity * dt;
    m_velocity += m_acceleration * dt;
    if (pos.y <= m_yStop && m_velocity.y<0) {
        pos.y = m_yStop;
        m_angle = m_finalRotation;
        SetComplete();
    }
    m_entity->SetPosition(glm::vec3(pos, p.z), m_angle);
}
