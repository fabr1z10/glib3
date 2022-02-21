#include <monkey/states/foepath.h>
#include <monkey/components/controller3d.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/entity.h>
#include <monkey/engine.h>
#include <monkey/components/icollider.h>
#include <monkey/random.h>

FoePath::FoePath(const ITab& t) : Base3D(t) {
    t.foreach("moves", [&] (const ITab& u) {
       PathSeg seg;
       seg.direction = glm::normalize(u.get<glm::vec3>("direction"));
       seg.time = u.get<float>("time");
       m_segments.push_back(seg);
    });
}

void FoePath::AttachStateMachine(StateMachine * sm) {
    Base3D::AttachStateMachine(sm);
}

void FoePath::Init(const ITab& d) {
    m_currentIndex = 0;
    m_time = 0.0f;
    m_renderer->setAnimation("walk");
}

void FoePath::Run(double dt) {
    m_time += dt;
    auto& seg = m_segments[m_currentIndex];

    glm::vec3 delta = seg.direction * m_maxSpeed * static_cast<float>(dt);
    m_controller->Move(delta);
    if (m_time >= seg.time) {
        Engine::get().Remove(m_entity);
    }


}

void FoePath::End() {

}