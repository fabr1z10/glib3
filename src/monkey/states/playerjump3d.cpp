#include "monkey/states/playerjump3d.h"
#include <monkey/components/inputmethod.h>
#include <monkey/components/controller3d.h>
#include <monkey/entity.h>
#include <monkey/math/geom.h>
#include <monkey/components/dynamics2d.h>
#include <GLFW/glfw3.h>

PlayerJump3D::PlayerJump3D(const ITab& t) : Base3D(t) {
    m_walkState = t.get<std::string>("walk_state", "walk");
    //m_flipHorizontally = t.get<bool>("flipH");
	m_jumpUp = t.get<std::string>("anim_up", "idle");
	m_jumpDown = t.get<std::string>("anim_down", "idle");
}


void PlayerJump3D::AttachStateMachine(StateMachine * sm) {
	Base3D::AttachStateMachine(sm);
	m_input = m_entity->GetComponent<InputMethod>();
}

void PlayerJump3D::Run(double dt) {
    auto dtf = static_cast<float>(dt);

    if (m_controller->grounded() && m_dynamics->m_velocity.y < 0) {
        // landed on a platform
        m_dynamics->m_velocity.y = 0.0f;

        m_sm->SetState(m_walkState);
        return;
    }

    // bump head
    if (m_controller->ceiling()) {
        m_dynamics->m_velocity.y = 0;
    }


    bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
    bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);
    bool up = m_input->isKeyDown(GLFW_KEY_UP);
    bool down = m_input->isKeyDown(GLFW_KEY_DOWN);

    glm::vec3 a(0.0f);
    a.y = -m_gravity;

    if (left || right) {
        a.x = m_acceleration;
        m_entity->SetFlipX(left);
    } else {
        // apply deceleration only if velocity above theshold
        if (fabs(m_dynamics->m_velocity.x) > 0.1f) {
            a.x = -m_acceleration;
        } else {
            a.x = 0.0f;
            m_dynamics->m_velocity.x = 0.0f;
        }
    }
    if (up || down) {
        a.z = (down ? 1.0f : -1.0f) * m_acceleration;
    } else {
        // apply deceleration only if velocity above theshold
        if (fabs(m_dynamics->m_velocity.z) > 0.1f) {
            a.z = -signf(m_dynamics->m_velocity.z) * m_acceleration;
        } else {
            a.z = 0.0f;
            m_dynamics->m_velocity.z = 0.0f;
        }
    }

    m_dynamics->m_velocity += a * dtf;
    // limit horizontal vel to max speed
    if (left || right) {
        if (fabs(m_dynamics->m_velocity.x > m_maxSpeed)) {
            m_dynamics->m_velocity.x = sign(m_dynamics->m_velocity.x) * m_maxSpeed;
        }
    }

    auto delta = m_dynamics->m_velocity * dtf;
    //m_entity->MoveLocal(delta);
    std::cerr << delta.z << std::endl;
    m_controller->Move(delta);
    if (m_renderer != nullptr) {
        if (!m_overrideAnim.empty()) {
            if (m_renderer->isComplete()) {
                m_overrideAnim.clear();
            }
        } else {
            if (m_dynamics->m_velocity.y >= 0) {
                m_renderer->setAnimation(m_jumpUp);
            } else {
                m_renderer->setAnimation(m_jumpDown);
            }
        }
    }
}
