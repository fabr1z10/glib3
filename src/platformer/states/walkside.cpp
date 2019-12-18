#include <platformer/states/walkside.h>

#include <gfx/math/geom.h>

#include <gfx/entity.h>
#include <gfx/components/icontroller.h>
#include <gfx/components/inputmethod.h>
#include <gfx/components/dynamics2d.h>
#include <gfx/components/animator.h>
#include <gfx/components/statemachine.h>
#include <GLFW/glfw3.h>

WalkSide::WalkSide(float speed, float acceleration, bool fliph, float jumpSpeed) :
        m_speed(speed), m_acceleration(acceleration), m_flipHorizontally(fliph), m_velocitySmoothing(0.0f), m_jumpSpeed(jumpSpeed),
        m_jumpState("jump"), m_idleAnim("idle"), m_walkAnim("walk") {}

WalkSide::WalkSide(const WalkSide &orig) : PlatformerState(orig) {
    m_speed = orig.m_speed;
    m_acceleration = orig.m_acceleration;
    m_flipHorizontally =orig.m_flipHorizontally;
    m_jumpSpeed = orig.m_jumpSpeed;
    m_jumpState = orig.m_jumpState;
    m_idleAnim = orig.m_idleAnim;
    m_walkAnim = orig.m_walkAnim;

}

std::shared_ptr<State> WalkSide::clone() const {
    return std::make_shared<WalkSide>(*this);
}

void WalkSide::Init() {

}

void WalkSide::End() {

}

void WalkSide::Run (double dt) {

    if (!m_controller->grounded()) {
        m_sm->SetState(m_jumpState);
        return;
    } else {
        m_dynamics->m_velocity.y = 0.0f;
    }

    bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
    bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);
    bool up = m_input->isKeyDown(GLFW_KEY_UP);

    if (up) {
        m_dynamics->m_velocity.y = m_jumpSpeed;
        m_sm->SetState(m_jumpState);
        return;
    }

    float targetVelocityX = 0.0f;
    if (left || right) {
        if (m_flipHorizontally) {
            m_entity->SetFlipX(left);
            targetVelocityX = m_speed;
        } else {
            targetVelocityX = (left ? -1.0f : 1.0f) * m_speed;
        }
        //targetVelocityX = m_speed;
    }

    glm::vec3 delta =m_dynamics->step(dt, targetVelocityX, m_acceleration);
    //if (m_speed < 30.0f) std::cout << delta.x << "\n";
    m_controller->Move(delta);

    UpdateAnimation();
}


void WalkSide::ResetAnimation() {}

void WalkSide::ModifyAnimation() {
    if (fabs(m_dynamics->m_velocity.x) > 1.0f) {
        m_animator->SetAnimation(m_walkAnim);
    } else {
        m_animator->SetAnimation(m_idleAnim);
    }


}

