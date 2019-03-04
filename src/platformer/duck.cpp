#include <platformer/duck.h>
#include <gfx/components/controller2d.h>
#include <gfx/components/inputmethod.h>
#include <gfx/components/dynamics2d.h>
#include <gfx/entity.h>
#include <gfx/math/geom.h>

#include <GLFW/glfw3.h>

std::shared_ptr<State2> Duck::clone() const {
    return std::make_shared<Duck>(*this);
}

void Duck::AttachStateMachine(StateMachine2* sm) {
    m_sm = dynamic_cast<CharacterStateMachine*>(sm);
    auto entity = sm->GetObject();
    m_controller = entity->GetComponent<Controller2D>();
    m_dynamics = dynamic_cast<Dynamics2D*>(entity->GetComponent<Properties>());
    m_input = entity->GetComponent<InputMethod>();
}

void Duck::Init() {
    m_velocitySmoothing=0.0f;
    m_sm->SetAnimation(m_duckAnim);
    m_sm->SetCollider(m_colliderId);
}

// the logic for duck state is very simple
// stay ducked until the UP button is released
void Duck::Run (double dt) {
    if (!m_controller->m_details.below) {
        m_sm->SetState("jump");
        return;
    }

    bool down = m_input->isKeyDown(GLFW_KEY_DOWN);

    m_dynamics->m_velocity.y = m_dynamics->m_gravity * static_cast<float>(dt);

    m_dynamics->m_velocity.x = SmoothDamp(m_dynamics->m_velocity.x, 0.0f, m_velocitySmoothing, m_acceleration, dt);
    glm::vec2 delta = static_cast<float>(dt) * m_dynamics->m_velocity;
    m_controller->Move(delta);

    if (!down) {
        m_sm->SetState("walk");
        return;
    }
}