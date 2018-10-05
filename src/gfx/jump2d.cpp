#include <gfx/jump2d.h>
#include <gfx/controller2d.h>
#include <gfx/entity.h>
#include <GLFW/glfw3.h>
#include <gfx/renderer.h>
#include <graph/geom.h>

extern GLFWwindow* window;

Jump2D::Jump2D(const std::string& anim, float accelerationTimeAirborne, float gravity, float speed) :
        PlatformerState(anim), m_velocity(glm::vec2(0.0f)), m_accTimeAir(accelerationTimeAirborne), m_velocitySmoothing(0.0f), m_gravity(gravity), m_speed(speed)
{}

bool Jump2D::Run(double dt) {
    // if not touching the ground, set status to jump
    if (m_controller->m_details.below && m_velocity.y < 0) {
        m_velocity.y = 0.0f;
        m_nextState = "idle";
        return true;
    }

    // bump head
    if (m_controller->m_details.above)	{
        m_velocity.y = 0;
    }

    // apply gravity
    m_velocity.y += m_gravity * dt;

    // check keyboard
    bool left = (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS);
    bool right = (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS);

    float targetVelocityX = 0.0f;
    if (left) {
        targetVelocityX = -m_speed;
        m_renderer->SetFlipX(true);
    }
    else if (right) {
        targetVelocityX = m_speed;
        m_renderer->SetFlipX(false);
    }
    m_velocity.x = SmoothDamp(
            m_velocity.x, targetVelocityX,
            m_velocitySmoothing,
            m_accTimeAir, dt);
    glm::vec2 delta = static_cast<float>(dt) * m_velocity;


    m_controller->Move(delta);
    return false;
}