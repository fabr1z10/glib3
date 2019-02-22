//#include <platformer/states/enemybounce2d.h>
//#include <gfx/components/controller2d.h>
//#include <gfx/entity.h>
//#include <GLFW/glfw3.h>
//#include <gfx/components/renderer.h>
//#include <gfx/math/geom.h>
//#include <gfx/components/dynamics2d.h>
//#include <gfx/lua/luatable.h>
//
//extern GLFWwindow* window;
//
//EnemyBounce2D::EnemyBounce2D(float speed, float vy, bool enableFlip) :
//        PlatformerState(), m_speed(speed), m_vy(vy), m_enableFlip(enableFlip)
//{}
//
//
//
//bool EnemyBounce2D::Run(double dt) {
//    // apply gravity
//    if (m_controller->m_details.below)
//        m_dynamics->m_velocity.y = m_vy;
//    m_dynamics->m_velocity.y += m_dynamics->m_gravity * dt;
//
//    float targetVelocityX = 0.0f;
//    if (m_dir < 0) {
//        targetVelocityX = -m_speed;
//        if (m_enableFlip)
//            m_renderer->SetFlipX(true);
//    } else {
//        targetVelocityX = m_speed;
//        if (m_enableFlip)
//            m_renderer->SetFlipX(false);
//    }
//    m_dynamics->m_velocity.x = targetVelocityX;
//    glm::vec2 delta = static_cast<float>(dt) * m_dynamics->m_velocity;
//    m_controller->Move(delta);
//    if ((m_controller->m_details.left && m_dir < 0) || (m_controller->m_details.right && m_dir > 0))
//        m_dir = -m_dir;
//
//    return false;
//
//}