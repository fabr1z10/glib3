#include "bounce.h"
#include "monkey/components/controller2d.h"
#include <monkey/components/dynamics2d.h>
#include "monkey/entity.h"

Bounce::Bounce(const ITable & t) : PlatformerState(t) {
    m_speed = t.get<float>("speed");
    m_a = t.get<float>("a");
    m_b = t.get<float>("b");
}

void Bounce::AttachStateMachine(StateMachine * sm) {
    PlatformerState::AttachStateMachine(sm);
}
//Bounce::Bounce(float speed, float acceleration) : PlatformerState(), m_speed(speed), m_acceleration(acceleration) {}
//
Bounce::Bounce(const Bounce &orig) : PlatformerState(orig) {
    m_speed = orig.m_speed;
//    m_acceleration = orig.m_acceleration;
}
//
std::shared_ptr<State> Bounce::clone() const {
    return std::make_shared<Bounce>(*this);
}

void Bounce::Init(pybind11::dict&) {

}

void Bounce::End() {

}

void Bounce::Run (double dt) {
    if (m_controller->m_details.below || m_controller->m_details.above) {
        m_dynamics->m_velocity.y = -m_a * m_dynamics->m_velocity.y + (m_controller->m_details.below ? m_b : -m_b);
    }
    if (m_controller->m_details.left || m_controller->m_details.right) {
        m_entity->SetFlipX(!m_entity->GetFlipX());
    }
    glm::vec3 delta = m_dynamics->step(dt, m_speed, 0.0);
    m_controller->Move(delta);

}

