#include <platformer/states/walkside.h>

#include <gfx/math/geom.h>

#include <gfx/entity.h>
#include <gfx/components/controller2d.h>
#include <gfx/components/inputmethod.h>
#include <gfx/components/dynamics2d.h>
#include <gfx/components/animator.h>
#include <gfx/components/statemachine2.h>
#include <GLFW/glfw3.h>

WalkSide::WalkSide(float speed, float acceleration, bool fliph, float jumpSpeed) :
        m_speed(speed), m_acceleration(acceleration), m_flipHorizontally(fliph), m_velocitySmoothing(0.0f), m_jumpSpeed(jumpSpeed) {}

WalkSide::WalkSide(const WalkSide &orig) : PlatformerState(orig) {
    m_speed = orig.m_speed;
    m_acceleration = orig.m_acceleration;
    m_flipHorizontally =orig.m_flipHorizontally;
}

std::shared_ptr<State2> WalkSide::clone() const {
    return std::make_shared<WalkSide>(*this);
}

void WalkSide::Init() {

}

void WalkSide::End() {

}

void WalkSide::Run (double dt) {

    if (!m_controller->m_details.below) {
        m_sm->SetState("jump");
        return;
    }

    bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
    bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);
    bool up = m_input->isKeyDown(GLFW_KEY_UP);

    if (up) {
        m_dynamics->m_velocity.y = m_jumpSpeed;
        m_sm->SetState("jump");
        return;
    }


    m_dynamics->m_velocity.y = m_dynamics->m_gravity * static_cast<float>(dt);
    float targetVelocityX = 0.0f;

    if (left || right) {
        if (m_flipHorizontally) {
            m_entity->SetFlipX(left);
            targetVelocityX = m_speed;
        } else {
            targetVelocityX = (left ? -1.0f : 1.0f) * m_speed;
        }

    }

    m_dynamics->m_velocity.x = SmoothDamp(m_dynamics->m_velocity.x, targetVelocityX, m_velocitySmoothing, m_acceleration, dt);
    glm::vec2 delta = static_cast<float>(dt) * m_dynamics->m_velocity;
    m_controller->Move(delta);

    if (fabs(m_dynamics->m_velocity.x) > 1.0f) {
        m_animator->SetAnimation("walk");
    } else {
        m_animator->SetAnimation("idle");
    }
    //UpdateAnimation(left, right);

}


//#include <gfx/components/controller2d.h>
//#include <gfx/entity.h>
//#include <GLFW/glfw3.h>
//#include <gfx/components/renderer.h>
//#include <gfx/math/geom.h>
//#include <gfx/components/dynamics2d.h>
//#include <iostream>
//
//extern GLFWwindow* window;
//
//Walk2D::Walk2D(float accelerationTimeGrounded, float speed) :
//        PlatformerState(), m_accTimeGnd(accelerationTimeGrounded), m_velocitySmoothing(0.0f), m_speed(speed)
//{}
//
//bool Walk2D::Run(double dt) {
//    // if not touching the ground, set status to jump
//    if (!m_controller->m_details.below) {
//        m_nextState = "jump";
//        return true;
//    }
//
//    m_dynamics->m_velocity.y = m_dynamics->m_gravity * dt;
//    bool left = m_keyboard.isPressed(GLFW_KEY_LEFT);
//    bool right = m_keyboard.isPressed(GLFW_KEY_RIGHT);
//
//    // what if both are pressed? right wins
//    if (left && right) left = false;
//
//
//
//
//
//    float targetVelocityX = 0.0f;
//    if (left || right) {
//        // set the character orientation
//        m_entity->SetFlipX(left);
//        targetVelocityX = m_speed;
//    }
//
////    if (left) {
////        m_entity->SetFlipX(l)
////        targetVelocityX = -m_speed;
////        m_renderer->SetFlipX(true);
////    } else if (right) {
////        targetVelocityX = m_speed;
////        m_renderer->SetFlipX(false);
////    }
//    m_dynamics->m_velocity.x = SmoothDamp(
//            m_dynamics->m_velocity.x, targetVelocityX, m_velocitySmoothing, m_accTimeGnd, dt);
//    glm::vec2 delta = static_cast<float>(dt) * m_dynamics->m_velocity;
//    std::cout << "Moving by " << delta.x << ", " << delta.y << std::endl;
//    m_controller->Move(delta);
//
//    // if not button is pressed and velocity is small enough, move to idle
//    if (!left && !right) {
//        if (fabs(m_dynamics->m_velocity.x) < 0.1f) {
//            m_nextState="idle";
//            return true;
//        }
//    }
//    return false;
//
//}