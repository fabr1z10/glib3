#include <monkey/states/hit3d.h>
#include <monkey/entity.h>
#include <monkey/components/controller3d.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/statemachine.h>
#include <monkey/engine.h>

Hit3D::Hit3D(const ITab& t) : Base3D(t) {
    m_hitAnim = t.get<std::string>("hit_anim");
    m_nextState = t.get<std::string>("next_state", "");//	m_speed = t.get<float>("speed");
    m_timeOut = t.get<float>("timeout", std::numeric_limits<float>::infinity());
}

void Hit3D::Init(const ITab& d) {
    m_dir = d.get<float>("dir");
    m_dynamics->m_velocity.x = m_dir * m_maxSpeed;
    m_renderer->setAnimation(m_hitAnim);
    m_timer = 0.0f;
}

void Hit3D::Run(double dt) {
    auto dtf = static_cast<float>(dt);
    m_timer += dt;
    glm::vec3 a(0.0f);
    a.y = - m_gravity;
    a.x = -m_dir * m_acceleration;
    m_dynamics->m_velocity += a * dtf;
    auto delta = m_dynamics->m_velocity * dtf;
    m_controller->Move(delta);
    if (fabs(m_dynamics->m_velocity.x) < 0.1f || m_timer > m_timeOut) {
        if (m_nextState.empty()) {
            Engine::get().Remove(m_entity);
        } else {
            m_sm->SetState(m_nextState);
        }
    }

}

void Hit3D::End() {}