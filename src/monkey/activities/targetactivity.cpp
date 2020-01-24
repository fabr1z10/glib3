#include <monkey/activities/targetactivity.h>
#include <monkey/engine.h>
#include <monkey/monkey.h>

TargetActivity::TargetActivity(int id) : Activity(), m_id(id), m_entity(nullptr) {

}

TargetActivity::TargetActivity(const std::string& tag) : Activity(), m_tag(tag), m_id(-1), m_entity(nullptr) {

}

void TargetActivity::Start() {
    auto& m = Monkey::get();

    if (m_id == -1) {
        // use tag
        m_entity = Handle<Entity>(m.Get<Entity>(m_tag));
    } else {
        // use id
        if (!m.isAlive(m_id)) {
            SetComplete();
            return;
        }
        m_entity = Handle<Entity>(m.Get<Entity>(m_id));
    }

    // action will complete if the underlying entity is destroyed
    m_entity->onDestroy.Register(this, [&] (Entity*) {
        SetComplete();
    });

}

void TargetActivity::Reset() {
    Activity::Reset();
    m_entity = Handle<Entity>();
}