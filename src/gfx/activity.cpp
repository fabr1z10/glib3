#include <gfx/activity.h>

Activity::~Activity() {
    if (!m_complete)
        SetComplete();
}

void Activity::AddPrevious (Activity* act) {
    m_previous.push_back(act);
}

void Activity::AddNext (Activity* act) {
    m_following.push_back(act);
}
void Activity::Reset() {
    m_complete = false;
    for (auto& a : m_following) {
        a->Reset();
    }
}


bool Activity::IsReady() const {
    for (const auto& i : m_previous) {
        if (!(i->IsComplete()))
            return false;
    }
    return true;

}

void Activity::SetComplete() {
    m_complete = true;

}