#include "fly.h"
#include <monkey/components/controller3d.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/entity.h>
#include <monkey/components/animator.h>

Fly::Fly(const ITab & t) : State(t) {
    m_goingUpAnim = t.get<std::string>("anim_up");
    m_goingDownAnim = t.get<std::string>("anim_down");
    m_initialVelocity = t.get<glm::vec2>("v0");
    m_lieAnim = t.get<std::string>("anim_lie");
}

void Fly::AttachStateMachine(StateMachine * sm) {
    State::AttachStateMachine(sm);
    m_entity = sm->GetObject();
    m_controller = dynamic_cast<Controller3D *>(m_entity->GetComponent<IController>());
    if (m_controller == nullptr) {
        GLIB_FAIL("Platformer state requires a <Controller3D> component!");
    }
    m_animator = m_entity->GetComponent<IAnimator>();

    m_dynamics = m_entity->GetComponent<Dynamics2D>();
    if (m_dynamics == nullptr) {
        GLIB_FAIL("Platormer state requires a <Dynamics2D> component!");
    }
}

void Fly::Init(const ITab & t) {
    auto dir = t.get<float>("sign");
    m_targetVelocityX = m_initialVelocity.x * dir;
    m_dynamics->m_velocity.y = m_initialVelocity.y;
    m_seq = 0;
}


void Fly::Run(double dt) {

    if (m_seq == 1) {
        m_animator->SetAnimation(m_lieAnim);

    } else {
        glm::vec3 delta = m_dynamics->step(dt, m_targetVelocityX, 0.0f, 0.0f);
        m_controller->Move(delta);

        // handle animation
        if (m_dynamics->m_velocity.y > 0) {
            m_animator->SetAnimation(m_goingUpAnim);
        } else {
            m_animator->SetAnimation(m_goingDownAnim);
            if (m_controller->grounded()) {
                m_seq =1 ;
            }
        }
    }
}