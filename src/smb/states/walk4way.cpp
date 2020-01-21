#include <platformer/states/walk4way.h>

#include <monkey/math/geom.h>

#include <monkey/entity.h>
#include <monkey/components/icontroller.h>
#include <monkey/components/inputmethod.h>
#include <monkey/components/dynamics2d.h>
#include <GLFW/glfw3.h>

Walk4Way::Walk4Way(float speed, float acceleration, bool fliph) : m_speed(speed),
    m_acceleration(acceleration), m_flipHorizontally(fliph), m_velocitySmoothing(0.0f) {}

Walk4Way::Walk4Way(const Walk4Way &orig) : PlatformerState(orig) {
    m_speed = orig.m_speed;
    m_acceleration = orig.m_acceleration;
    m_flipHorizontally =orig.m_flipHorizontally;
}

std::shared_ptr<State> Walk4Way::clone() const {
    return std::make_shared<Walk4Way>(*this);
}

void Walk4Way::Init() {

}

void Walk4Way::End() {

}

void Walk4Way::Run (double dt) {

    bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
    bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);

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
    glm::vec3 delta = static_cast<float>(dt) * m_dynamics->m_velocity;
    m_controller->Move(delta);

    //UpdateAnimation(left, right);

}


//#include <monkey/components/controller2d.h>
//#include <monkey/entity.h>
//#include <GLFW/glfw3.h>
//#include <monkey/components/renderer.h>
//#include <monkey/math/geom.h>
//#include <monkey/components/dynamics2d.h>
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