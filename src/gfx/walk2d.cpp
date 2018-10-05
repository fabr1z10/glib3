#include <gfx/walk2d.h>
#include <gfx/controller2d.h>
#include <gfx/entity.h>
#include <GLFW/glfw3.h>
#include <gfx/renderer.h>
#include <graph/geom.h>

extern GLFWwindow* window;

Walk2D::Walk2D(const std::string& anim, float accelerationTimeGrounded, float gravity, float speed) :
        PlatformerState(anim), m_velocity(glm::vec2(0.0f)), m_accTimeGnd(accelerationTimeGrounded), m_velocitySmoothing(0.0f), m_gravity(gravity), m_speed(speed)
{}

bool Walk2D::Run(double dt) {
    // if not touching the ground, set status to jump
    if (!m_controller->m_details.below) {
        m_nextState = "jump";
        return true;
    }

    m_velocity.y += m_gravity * dt;
    bool left = (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS);
    bool right = (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS);
    float targetVelocityX = 0.0f;
    if (left) {
        targetVelocityX = -m_speed;
        m_renderer->SetFlipX(true);
    } else if (right) {
        targetVelocityX = m_speed;
        m_renderer->SetFlipX(false);
    }
    m_velocity.x = SmoothDamp(
            m_velocity.x, targetVelocityX, m_velocitySmoothing, m_accTimeGnd, dt);
    glm::vec2 delta = static_cast<float>(dt) * m_velocity;
    m_controller->Move(delta);

    // if not button is pressed and velocity is small enough, move to idle
    if (!left && !right) {
        if (fabs(m_velocity.x) < 0.1f) {
            m_nextState="idle";
            return true;
        }
    }
    return false;

}