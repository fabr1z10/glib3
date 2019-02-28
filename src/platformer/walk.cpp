#include <platformer/walk.h>

#include <gfx/components/controller2d.h>
#include <gfx/components/animator.h>
#include <gfx/components/inputmethod.h>
#include <gfx/components/dynamics2d.h>

#include <gfx/error.h>
#include <gfx/math/geom.h>
#include <gfx/entity.h>
#include <GLFW/glfw3.h>


extern GLFWwindow* window;

std::shared_ptr<State2> Walk::clone() const {
    return std::make_shared<Walk>(*this);
}


void Walk::AttachStateMachine(StateMachine2* sm) {
    m_sm = sm;
    m_entity = sm->GetObject();
    m_controller = m_entity->GetComponent<Controller2D>();
    m_dynamics = dynamic_cast<Dynamics2D*>(m_entity->GetComponent<Properties>());
    //m_animator = m_entity->GetComponent<Animator>();
    m_input = m_entity->GetComponent<InputMethod>();
    if (m_input == nullptr) {
        GLIB_FAIL("Walk state requires an input method component attached!");
    }
    // when walking, I want to know when the user press the up key, because this allows me to jump
    m_input->onKeyDown.Register(this, [&] (int key) { this->KeyListener(key); });
}

void Walk::KeyListener(int key) {
    if (key == GLFW_KEY_DOWN) {
        // duck
    }

    if (key == GLFW_KEY_UP) {
        // set jump speed
        m_dynamics->m_velocity.y = m_jumpVelocity;
        m_sm->SetState("jump");
    }
}

void Walk::Run (double dt) {
    if (!m_controller->m_details.below) {
        m_sm->SetState("jump");
        return;
    }

    bool left =m_input->isKeyDown(GLFW_KEY_LEFT);
    bool right =m_input->isKeyDown(GLFW_KEY_RIGHT);

    m_dynamics->m_velocity.y = m_dynamics->m_gravity * static_cast<float>(dt);
    float targetVelocityX = 0.0f;
    if (left || right) {
        m_entity->SetFlipX(left);
        targetVelocityX = m_speed;
    }

    m_dynamics->m_velocity.x = SmoothDamp(m_dynamics->m_velocity.x, targetVelocityX, m_velocitySmoothing, m_acceleration, dt);
    glm::vec2 delta = static_cast<float>(dt) * m_dynamics->m_velocity;
    m_controller->Move(delta);

}