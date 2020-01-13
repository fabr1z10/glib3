#include <monkey/activities/targetactivity.h>
#include <monkey/engine.h>

TargetActivity::TargetActivity(int id) : Activity(), m_id(id), m_entity(nullptr) {

}

TargetActivity::TargetActivity(const std::string& tag) : Activity(), m_tag(tag), m_id(-1), m_entity(nullptr) {

}

void TargetActivity::Start() {
    if (m_id == -1) {
        // use tag
        m_entity = Ref::Get<Entity>(m_tag);
    } else {
        // use id
        m_entity = Ref::Get<Entity>(m_id);
    }


}

void TargetActivity::Reset() {
    Activity::Reset();
    m_entity = nullptr;
}