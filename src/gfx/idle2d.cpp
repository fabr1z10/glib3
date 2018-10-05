#include <gfx/idle2d.h>
#include <gfx/controller2d.h>
#include <gfx/entity.h>
#include <GLFW/glfw3.h>
#include <graph/geom.h>

extern GLFWwindow* window;

Idle2D::Idle2D(const std::string& anim, float accelerationTimeGrounded, float g) :
        PlatformerState(anim), m_velocity(glm::vec2(0.0f)), m_accTimeGnd(accelerationTimeGrounded), m_velocitySmoothing(0.0f), m_gravity(g)
{}

bool Idle2D::Run(double dt) {
    // if not touching the ground, set status to jump
    if (!m_controller->m_details.below) {
        m_nextState = "jump";
        return true;
    }

    m_velocity.y = m_gravity * dt;
    float targetVelocityX = 0.0f;
    m_velocity.x = SmoothDamp(
            m_velocity.x, targetVelocityX, m_velocitySmoothing, m_accTimeGnd, dt);
    glm::vec2 delta = static_cast<float>(dt) * m_velocity;
    m_controller->Move(delta);
    return false;
}