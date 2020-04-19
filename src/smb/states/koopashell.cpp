#include "koopashell.h"
#include <monkey/components/controller2d.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/animator.h>


KoopaShell::KoopaShell(float time, float timeWalk) : PlatformerState(), m_time(time), m_time_walk(timeWalk) {

}

KoopaShell::KoopaShell(const KoopaShell &orig) : PlatformerState(orig) {
    m_time = orig.m_time;
    m_time_walk = orig.m_time_walk;
}

std::shared_ptr<State> KoopaShell::clone() const {
    return std::make_shared<KoopaShell>(*this);
}


void KoopaShell::Init(pybind11::dict&) {
    m_animator->SetAnimation("hide");
    m_timer = 0.0f;
    m_id = m_entity->GetId();
    m_seq = 0;
}


void KoopaShell::Run(double dt) {
    m_timer += dt;
    if (m_controller->grounded()) {
        m_dynamics->m_velocity.y = 0.0f;
    }

    glm::vec3 delta =m_dynamics->step(dt, 0.0f, 0.0f);
    m_controller->Move(delta);
    if (m_seq == 0 && m_timer > m_time) {
        m_animator->SetAnimation("hide_blink");
        m_seq = 1;
    }
    if (m_seq == 1 && m_timer > m_time_walk) {
        m_sm->SetState("walk");
    }

}

void KoopaShell::End() {}