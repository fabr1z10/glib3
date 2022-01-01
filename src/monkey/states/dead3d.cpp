#include <monkey/states/dead3d.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/controller3d.h>

Dead3D::Dead3D(const ITab& t) : Base3D(t) {
    m_initialVelocity = t.get<float>("vy");
    m_animStart = t.get<std::string>("start_anim");
    m_animFall = t.get<std::string>("fall_anim");
    m_animLie = t.get<std::string>("lie_anim");


}

void Dead3D::Init(const ITab& d) {
    m_dir = d.get<float>("dir");
    m_dynamics->m_velocity = glm::vec3(m_maxSpeed, m_initialVelocity, 0.0f);
    m_dynamics->m_velocity.x *= m_dir;
    m_renderer->setAnimation(m_animStart);
    m_timer = 0.0f;
    m_t1 = 0.5 * m_initialVelocity / m_gravity;
    m_state = 0;
}

void Dead3D::Run(double dt) {
    if (m_state == 0) {
        auto dtf = static_cast<float>(dt);
        m_timer += dt;
        glm::vec3 a(0.0f);
        a.y = -m_gravity;
        m_dynamics->m_velocity += a * dtf;
        auto delta = m_dynamics->m_velocity * dtf;
        m_controller->Move(delta);
        if (m_timer > m_t1) {
            m_renderer->setAnimation(m_animFall);
        }
        if (m_controller->grounded()) {
            m_state = 1;
            m_renderer->setAnimation(m_animLie);
        }
    }

}

void Dead3D::End() {}