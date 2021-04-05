#include <monkey/components/garbagecollect.h>
#include <monkey/engine.h>

GarbageCollect::GarbageCollect(const ITab& t) : Component()
{
    m_target = nullptr;
    m_tag = t.get<std::string>("cam", "");
    m_Dxmax = t.get<float>("dx", 0.0f);
    m_Dymax = t.get<float>("dy", 0.0f);
    m_timeout = t.get<float>("timeout", 0.0f);


}



void GarbageCollect::Start() {
    if (!m_tag.empty())
        m_target = Monkey::get().Get<Camera>(m_tag);
    m_t = 0.0f;


}

void GarbageCollect::Update(double dt) {
    if (m_target != nullptr) {
        glm::vec3 pos = m_target->GetPosition();
        glm::vec3 epos = m_entity->GetPosition();
        if (fabs(pos.x - epos.x) > m_Dxmax || fabs(pos.y - epos.y) > m_Dymax) {
            Engine::get().Remove(m_entity->GetId());
        }
    }
    m_t += dt;
    if (m_t >= m_timeout) {
        Engine::get().Remove(m_entity->GetId());
    }

}

