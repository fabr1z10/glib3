#include <platformer/states/jump2d.h>
#include <gfx/components/controller2d.h>
#include <gfx/entity.h>
#include <GLFW/glfw3.h>
#include <gfx/components/renderer.h>
#include <gfx/math/geom.h>
#include <gfx/components/dynamics2d.h>

extern GLFWwindow* window;

Jump2D::Jump2D(float accelerationTimeAirborne, float speed) :
        PlatformerState(), m_accTimeAir(accelerationTimeAirborne), m_velocitySmoothing(0.0f), m_speed(speed)
{


}

void Jump2D::ResetState() {
    //PlatformerState::Start();
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        m_dynamics->m_velocity.y = m_dynamics->m_jumpVelocity;
}

bool Jump2D::Run(double dt) {
    // if not touching the ground, set status to jump
    bool left = (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS);
    bool right = (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS);
    if (m_controller->m_details.below && m_dynamics->m_velocity.y < 0) {
        m_dynamics->m_velocity.y = 0.0f;

        m_nextState = (left || right) ? "walk" : "idle";
        return true;
    }

    // bump head
    if (m_controller->m_details.above)	{
        m_dynamics->m_velocity.y = 0;
    }

    // apply gravity
    m_dynamics->m_velocity.y += m_dynamics->m_gravity * dt;

    // check keyboard
    //bool left = (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS);
    //bool right = (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS);

    float targetVelocityX = 0.0f;
    if (left) {
        targetVelocityX = -m_speed;
        m_renderer->SetFlipX(true);
    }
    else if (right) {
        targetVelocityX = m_speed;
        m_renderer->SetFlipX(false);
    }
    m_dynamics->m_velocity.x = SmoothDamp(
            m_dynamics->m_velocity.x, targetVelocityX,
            m_velocitySmoothing,
            m_accTimeAir, dt);
    glm::vec2 delta = static_cast<float>(dt) * m_dynamics->m_velocity;
    m_controller->Move(delta);
    return false;
}