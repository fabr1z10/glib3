#include <gfx/sequence.h>

Sequence::Sequence() : Activity(), m_current(nullptr) {}

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