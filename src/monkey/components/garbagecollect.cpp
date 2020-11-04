#include <monkey/components/garbagecollect.h>
#include <monkey/engine.h>

GarbageCollect::GarbageCollect(const ITable& t) : Component()
{
    m_target = nullptr;
    m_tag = t.get<std::string>("cam", "");
    m_Dxmax = t.get<float>("dx", 0.0f);
    m_Dymax = t.get<float>("dy", 0.0f);
    m_timeout = t.get<float>("timeout", 0.0f);


}


GarbageCollect::GarbageCollect(const GarbageCollect& other) : Component(other){
    m_tag = other.m_tag;
    m_Dxmax=other.m_Dxmax;
    m_Dymax=other.m_Dymax;

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


std::shared_ptr<Component> GarbageCollect::clone() const {
    return std::make_shared<GarbageCollect>(GarbageCollect(*this));
}