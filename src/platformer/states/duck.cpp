#include <platformer/states/duck.h>
#include <gfx/components/icontroller.h>
#include <gfx/components/dynamics2d.h>
#include <gfx/components/inputmethod.h>
#include <gfx/components/animator.h>
#include <GLFW/glfw3.h>

Duck::Duck(float acceleration) : PlatformerState(), m_acceleration(acceleration) {}

Duck::Duck(const Duck &orig) : PlatformerState(orig) {}

std::shared_ptr<State> Duck::clone() const {
    return std::make_shared<Duck>(*this);
}

void Duck::Init() {
    ResetAnimation();
}

void Duck::Run (double dt) {

    if (!m_controller->grounded()) {
        m_sm->SetState("jump");
        return;
    } else {
        m_dynamics->m_velocity.y = 0.0f;
    }

    bool up = m_input->isKeyDown(GLFW_KEY_DOWN);

    if (!up) {
        m_sm->SetState("walk");
        return;
    }


    float targetVelocityX = 0.0f;
    glm::vec3 delta =m_dynamics->step(dt, targetVelocityX, m_acceleration);
    m_controller->Move(delta);

    UpdateAnimation();
}


void Duck::ResetAnimation() {
    m_animator->SetAnimation("duck");
}