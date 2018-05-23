#include <gfx/activity.h>

void Activity::AddPrevious (std::shared_ptr<Activity> act) {
    m_previous.push_back(act);
}

void Activity::AddNext (std::shared_ptr<Activity> act) {
    m_following.push_back(act);
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