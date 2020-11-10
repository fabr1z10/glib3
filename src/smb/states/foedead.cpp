#include "foedead.h"
#include <monkey/components/controller2d.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/animator.h>


FoeDead::FoeDead(float time) : PlatformerState(),
m_time(time) {

}

FoeDead::FoeDead(const ITable & t) : PlatformerState(t) {
    m_time = t.get<float>("time");
    m_anim = t.get<std::string>("anim");
}


void FoeDead::Init(pybind11::dict&) {
    m_animator->SetAnimation(m_anim);
    m_timer = 0.0f;
    m_id = m_entity->GetId();
}


void FoeDead::Run(double dt) {
    m_timer += dt;
    if (m_controller->grounded()) {
        m_dynamics->m_velocity.y = 0.0f;
    }

    glm::vec3 delta =m_dynamics->step(dt, 0.0f, 0.0f);
    m_controller->Move(delta);
    if (m_timer > m_time) {
        Engine::get().Remove(m_id);
    }
}

void FoeDead::End() {}