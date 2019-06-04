#include <platformer/states/jump2d.h>
#include <gfx/components/inputmethod.h>


#include <gfx/components/controller2d.h>
#include <gfx/entity.h>
#include <gfx/math/geom.h>

//#include <GLFW/glfw3.h>
//#include <gfx/components/renderer.h>
//#include <gfx/math/geom.h>
#include <gfx/components/dynamics2d.h>
#include <gfx/components/animator.h>
#include <GLFW/glfw3.h>
//extern GLFWwindow* window;
//
Jump2D::Jump2D(float accelerationTimeAirborne, float speed, bool flipH) :
    m_accTimeAir(accelerationTimeAirborne), m_velocitySmoothing(0.0f), m_speed(speed), m_flipHorizontally(flipH)
{}

Jump2D::Jump2D(const Jump2D &orig) : PlatformerState(orig) {
    m_speed = orig.m_speed;
    m_accTimeAir = orig.m_accTimeAir;
}

std::shared_ptr<State2> Jump2D::clone() const {
    return std::make_shared<Jump2D>(*this);
}

void Jump2D::Init() {

    m_animator->SetAnimation("jump");
}

void Jump2D::Run(double dt) {
    // if not touching the ground, set status to jump
    bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
    bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);
//    if (left && right) left = false;
//
    if (m_controller->m_details.below && m_dynamics->m_velocity.y < 0) {
        m_dynamics->m_velocity.y = 0.0f;
        m_sm->SetState("walk");
        return;
    }

    // bump head
    if (m_controller->m_details.above)	{
        m_dynamics->m_velocity.y = 0;
    }

    // apply gravity
    m_dynamics->m_velocity.y += m_dynamics->m_gravity * dt;
//
//    if (m_goingUp && m_dynamics->m_velocity.y < 0) {
//        m_goingUp = false;
//        if (m_setJumpDownAnim) {
//            m_renderer->SetAnimation(m_jumpDownAnim);
//        }
//    }
//
//
//    // check keyboard
//    //bool left = (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS);
//    //bool right = (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS);
//
//
    float targetVelocityX = 0.0f;
    if (left || right) {
        if (m_flipHorizontally) {
            m_entity->SetFlipX(left);
            targetVelocityX = m_speed;
        } else {
            targetVelocityX = (left ? -1.0f : 1.0f) * m_speed;
        }

    }
////    else if (right) {
////        targetVelocityX = m_speed;
////        m_renderer->SetFlipX(false);
////    }
    m_dynamics->m_velocity.x = SmoothDamp(
            m_dynamics->m_velocity.x, targetVelocityX,
            m_velocitySmoothing,
            m_accTimeAir, dt);
    glm::vec2 delta = static_cast<float>(dt) * m_dynamics->m_velocity;
    m_controller->Move(delta);

}