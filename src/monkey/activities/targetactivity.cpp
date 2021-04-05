#include <monkey/activities/targetactivity.h>
#include <monkey/engine.h>
#include <monkey/monkey.h>

TargetActivity::TargetActivity(int id) : Activity(), m_id(id), m_entity(nullptr) {

}

TargetActivity::TargetActivity(const ITab & t) : Activity(), m_id(-1) {
    if (t.has("tag")) {
        m_tag = t.get<std::string>("tag");
    } else {
        m_id = t.get<int>("id");
    }
}

TargetActivity::TargetActivity(const std::string& tag) : Activity(), m_tag(tag), m_id(-1), m_entity(nullptr) {

}

void TargetActivity::Start() {
    auto& m = Monkey::get();
    try {
        if (m_id == -1) {
            // use tag
            Entity *e = m.Get<Entity>(m_tag);
            m_entity = Handle<Entity>(e);
        } else {
            // use id
            if (!m.isAlive(m_id)) {
                SetComplete();
                return;
            }
            Entity *e = m.Get<Entity>(m_id);
            m_entity = Handle<Entity>(e);
        }
        m_entity->onDestroy.Register(this, [&] (Entity*) {
            SetComplete();
        });
    } catch (Error& e) {
        GLIB_FAIL(e.what());
    }

    // action will complete if the underlying entity is destroyed

}

void TargetActivity::Reset() {
    Activity::Reset();
    m_entity = Handle<Entity>();
}