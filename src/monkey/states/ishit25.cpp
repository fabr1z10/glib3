#include <monkey/states/ishit25.h>
#include <monkey/monkey.h>
#include <monkey/entity.h>
#include <monkey/components/controller25.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/animrenderer.h>
#include <monkey/components/statemachine.h>

IsHit25::IsHit25(const ITab & t) : State(t) {
    m_acceleration = t.get<float>("acceleration");
    m_anim = t.get<std::string>("anim");
}


void IsHit25::Run(double dt) {

    glm::vec3 delta = m_dynamics->step(dt, m_sgn * 100.0f, 0.0f, 0.0f);
    glm::vec3 deltaH(delta.x, delta.y, delta.z);

    m_controller->Move(deltaH);
    m_distanceTravelled += deltaH.x;
    std::cerr << "aa:" << deltaH.x;
    if (fabs(m_distanceTravelled) > 64 || fabs(deltaH.x) <0.01f) {
    // if (abs(m_dynamics->m_velocity.x) < 20.0f) {
        m_sm->SetState("walk");
    }
}


void IsHit25::Init(const ITab& d) {
    m_animator->setAnimation(m_anim);
    m_sgn = d.get<float>("sign");
    m_distanceTravelled = 0.0f;
}

void IsHit25::End() {
}

void IsHit25::AttachStateMachine(StateMachine * sm) {
    State::AttachStateMachine(sm);
    m_entity = sm->GetObject();
    m_dynamics = m_entity->GetComponent<Dynamics2D>();
    m_controller = dynamic_cast<Controller25*>(m_entity->GetComponent<IController>());
    m_animator = dynamic_cast<AnimationRenderer*>(m_entity->GetComponent<Renderer>());

}