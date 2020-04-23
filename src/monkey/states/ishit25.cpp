#include <monkey/states/ishit25.h>
#include <monkey/monkey.h>
#include <monkey/entity.h>
#include <monkey/components/controller25.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/animator.h>
#include <monkey/components/statemachine.h>

IsHit25::IsHit25(const ITable & t) : State(t) {
    m_acceleration = t.get<float>("acceleration");
    m_anim = t.get<std::string>("anim");
}

IsHit25::IsHit25(const IsHit25 & orig) : State(orig) {
}

std::shared_ptr<State> IsHit25::clone() const {
    return std::make_shared<IsHit25>(*this);
}


void IsHit25::Run(double dt) {

    glm::vec3 delta = m_dynamics->step(dt, 0.0f, 0.0f, m_acceleration);
    glm::vec3 deltaH(delta.x, delta.y, delta.z);
    m_controller->Move(deltaH);
    if (abs(m_dynamics->m_velocity.x) < 20.0f) {
        m_sm->SetState("walk");
    }
}


void IsHit25::Init(pybind11::dict &) {
    m_animator->SetAnimation(m_anim);
}

void IsHit25::End() {
}

void IsHit25::AttachStateMachine(StateMachine * sm) {
    State::AttachStateMachine(sm);
    m_entity = sm->GetObject();
    m_dynamics = m_entity->GetComponent<Dynamics2D>();
    m_controller = dynamic_cast<Controller25*>(m_entity->GetComponent<IController>());
    m_animator = m_entity->GetComponent<IAnimator>();

}