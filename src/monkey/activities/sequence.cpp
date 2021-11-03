#include <monkey/activities/sequence.h>
#include <monkey/engine.h>
#include <monkey/scenefactory.h>

Sequence::Sequence() : Activity(), m_current(nullptr) {}

Sequence::Sequence(const ITab& t) {
    auto factory = Engine::get().GetSceneFactory();
    t.foreach("activities", [&] (const ITab& a) {
        auto activity = factory->make2<Activity>(a);
        m_innerActivities.push(activity);
    });

}

void Sequence::Push(std::shared_ptr<Activity> activity) {
    m_innerActivities.push(activity);
}

void Sequence::Run(float dt) {
    if (m_current == nullptr) {
        if (m_innerActivities.empty())
            SetComplete();
        else {
            m_current = m_innerActivities.front();
            m_innerActivities.pop();
            m_current->Start();
        }
    } else {
        m_current->Run(dt);
        if (m_current->IsComplete()) {
            m_current = nullptr;
            if (m_innerActivities.empty())
                SetComplete();
            else {
                m_current = m_innerActivities.front();
                m_innerActivities.pop();
                m_current->Start();
            }
        }
    }

}

void Sequence::NotifySuspend() {
    if (m_current != nullptr)
        m_current->NotifySuspend();
}