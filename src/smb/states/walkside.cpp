#include "walkside.h"

#include <monkey/math/geom.h>


#include <monkey/entity.h>
#include <monkey/components/controller2d.h>
#include <monkey/components/inputmethod.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/animator.h>
#include <monkey/components/statemachine.h>
#include <GLFW/glfw3.h>

WalkSide::WalkSide(float speed, float acceleration, bool fliph, float jumpSpeed) :
        m_speed(speed), m_acceleration(acceleration), m_flipHorizontally(fliph), m_velocitySmoothing(0.0f), m_jumpSpeed(jumpSpeed),
        m_jumpState("jump"), m_idleAnim("idle"), m_walkAnim("walk") {}


WalkSide::WalkSide(const ITab& t) : PlatformerState(t) {
    m_speed = t.get<float>("speed");
    m_acceleration = t.get<float>("acceleration");
    m_flipHorizontally = t.get<bool>("flipH");
    m_jumpSpeed = t.get<float>("jumpSpeed");
    //auto state = std::make_shared<WalkSide>(speed, a, fliph, jumpSpeed);
    auto jumpState = t.get<std::string>("jumpState", "jump");
    auto idleAnim = t.get<std::string>("idleAnim", "idle");
    auto walkAnim = t.get<std::string>("walkAnim", "walk");
    setJumpState(jumpState);
    setIdleAnimation(idleAnim);
    setWalkAnimation(walkAnim);

}




void WalkSide::Init(pybind11::dict&) {

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
	if (m_animator == nullptr)
		return;
    if (fabs(m_dynamics->m_velocity.x) > 1.0f) {
        m_animator->SetAnimation(m_walkAnim);
    } else {
        m_animator->SetAnimation(m_idleAnim);
    }


}

