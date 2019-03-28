#include "gfx/activities/targetactivity.h"
#include "gfx/engine.h"

TargetActivity::TargetActivity(int id) : Activity(), m_id(id), m_entity(nullptr) {

}

TargetActivity::TargetActivity(const std::string& tag) : Activity(), m_tag(tag), m_id(-1), m_entity(nullptr) {

}

void TargetActivity::Start() {
    if (m_id == -1) {
        // use tag
        m_entity = Engine::get().GetRef<Entity>(m_tag);
    } else {
        // use id
        m_entity = Ref::GetFromId<Entity>(m_id);
    }


}

void TargetActivity::Reset() {
    Activity::Reset();
    m_entity = nullptr;
}