#include <monkey/activities/move.h>
#include <iostream>
#include <monkey/engine.h>
#include <monkey/math/geom.h>

MoveTo::MoveTo(glm::vec2 pos, float speed, bool relative, bool immediate, bool flip) : TargetActivity(),
    m_toPos(pos), m_speed{speed}, m_lengthCovered{0.0f}, m_lengthToCover{0.0f}, m_flip(flip),
    m_relative{relative}, m_immediate{immediate}, m_acceleration(0.0f), m_accelerationVector(0.0f)
{

}

MoveToScaled::MoveToScaled(glm::vec2 pos, float speed, bool relative, bool immediate) :
        MoveTo(pos,speed,relative,immediate)
{

}

MoveToScaled::MoveToScaled(int id, glm::vec2 pos, float speed, bool relative, bool immediate)
        : MoveTo(id,pos,speed,relative,immediate)
{

}
void MoveTo::Reset() {
    Activity::Reset();
    m_lengthToCover = 0.0f;
    m_lengthCovered = 0.0f;
    m_lengthCovered = 0.0f;
}

void MoveTo::Start() {
    TargetActivity::Start();

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
    //if (displacement.x < 0) {
    if (m_flip) {
        m_entity->SetFlipX(displacement.x < 0);
    }

    if (m_immediate) {
        m_entity->MoveOrigin(displacement);

        SetComplete();
    } else {
        m_lengthToCover = glm::length(displacement);
        if (m_lengthToCover == 0) {
            SetComplete();
        } else {
            m_unitDisplacement = glm::normalize(displacement);
            m_velocity = m_unitDisplacement * m_speed;
            m_accelerationVector = m_unitDisplacement * m_acceleration;
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

void MoveToScaled::Run(float dt) {
    // simply update velocity at each iteration
    // scale 1 = full speed
    m_velocity = m_unitDisplacement * m_speed * m_entity->GetScale();
    MoveTo::Run(dt);

}

MoveAndRotateTo::MoveAndRotateTo(glm::vec2 pos, float speed, bool relative, bool immediate,
    float angle, bool angleRelative) : MoveTo(pos, speed, relative, immediate), m_angle(angle), m_angleRelative(angleRelative)
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
    glm::vec2 initialVelocity,
    glm::vec2 acceleration,
    float yStop,
    float rotationSpeed,
    float finalRotation) : TargetActivity(), m_initialVelocity(initialVelocity),
    m_acceleration(acceleration), m_yStop(yStop), m_rotationSpeed(rotationSpeed), m_finalRotation(finalRotation)
{

}


void MoveAccelerated::Start() {
    TargetActivity::Start();
    m_velocity = m_initialVelocity;
    m_angle = 0.0f;
}

void MoveAccelerated::Run(float dt) {
    glm::vec3 p(m_entity->GetPosition());
    //glm::mat4 wt = m_entity->GetWorldTransform();
    m_angle += m_rotationSpeed*dt;
    glm::vec2 pos(p);
    pos += m_velocity * dt;
    m_velocity += m_acceleration * dt;
    //std::cerr << m_velocity.y << "\n";
    if (pos.y <= m_yStop && m_velocity.y<0) {
        pos.y = m_yStop;
        m_angle = m_finalRotation;
        SetComplete();
    }
    m_entity->SetPosition(glm::vec3(pos, p.z), m_angle);
}
