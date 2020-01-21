#include <monkey/components/garbagecollect.h>
#include <monkey/engine.h>

GarbageCollect::GarbageCollect(const std::string& target, float deltaXMax, float deltaYMax) :
    Component(), m_tag(target), m_target(nullptr), m_Dxmax(deltaXMax), m_Dymax(deltaYMax)
{}

GarbageCollect::GarbageCollect(const GarbageCollect& other) : Component(other){
    m_tag = other.m_tag;
    m_Dxmax=other.m_Dxmax;
    m_Dymax=other.m_Dymax;
}

void GarbageCollect::Start() {
    m_target = Monkey::get().Get<Camera>(m_tag);



}

void GarbageCollect::Update(double) {
    glm::vec3 pos = m_target->GetPosition();
    glm::vec3 epos = m_entity->GetPosition();
    if (fabs(pos.x - epos.x) > m_Dxmax || fabs(pos.y -epos.y)>m_Dymax) {
        Engine::get().Remove(m_entity->GetId());
    }

}


std::shared_ptr<Component> GarbageCollect::clone() const {
    return std::make_shared<GarbageCollect>(GarbageCollect(*this));
}