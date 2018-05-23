#include <gfx/script.h>
#include <gfx/error.h>

void Script::Start() {
    auto it = m_activities.find(m_startId);
    m_active.insert(it->second.get());
    it->second->Start();
}

void Script::AddActivity(std::shared_ptr<Activity> act) {
    m_activities[act->GetId()] = act;
}

void Script::AddEdge (int fromActivity, int toActivity) {
    auto itFrom = m_activities.find(fromActivity);
    if (itFrom == m_activities.end())
        GLIB_FAIL("Don't know activity " << fromActivity);
    auto itTo = m_activities.find(toActivity);
    if (itTo == m_activities.end())
        GLIB_FAIL("Don't know activity " << toActivity);
    itFrom->second->AddNext(itTo->second);
    itTo->second->AddPrevious(itFrom->second);

}



void Script::Run (float dt) {
    if (m_suspended)
        return;

    std::unordered_set<Activity*> toRemove;
    for (auto& a : m_active) {
        a->Run(dt);
        if (a->IsComplete()) {
            // check its children
            toRemove.insert(a);
            auto& following = a->GetFollowing();
            for (auto& child : following) {
                if (child->IsReady()) {

                    m_active.insert(child.get());
                    child->Start();
                }
            }
        }
    }

    for(auto& a : toRemove)
        m_active.erase(a);

    if (m_active.empty())
    {
        m_complete = true;
    }

}