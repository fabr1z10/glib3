#include <gfx/script.h>
#include <gfx/error.h>
#include <iostream>

void Script::Start() {
    // by convention, the script starts from 0
    auto it = m_activities.find(0);
    if (it == m_activities.end())
    {
        std::cout << "Mmmh, script ended straight away, as we cannot find its start activity!\n";
        m_complete = true;
        return;
    }
    m_active.insert(it->second.get());
    it->second->Start();
}

void Script::AddActivityAfter(int id, std::unique_ptr<Activity> act, std::vector<int> after) {
    Script::AddActivity(id, std::move(act));
    for (auto& a : after)
        AddEdge (a, id);

}
void Script::AddActivity(int id, std::unique_ptr<Activity> act) {
    m_activities[id] = std::move( act);

}

void Script::AddEdge (int fromActivity, int toActivity) {
    auto itFrom = m_activities.find(fromActivity);
    if (itFrom == m_activities.end())
        GLIB_FAIL("Don't know activity " << fromActivity);
    auto itTo = m_activities.find(toActivity);
    if (itTo == m_activities.end())
        GLIB_FAIL("Don't know activity " << toActivity);
    auto ptr = itFrom->second.get();
    auto ptr2 = itTo->second.get();
    itFrom->second->AddNext(itTo->second.get());
    itTo->second->AddPrevious(itFrom->second.get());

}

void Script::Print() {
    for (auto& a: m_activities) {
        std::cout << a.first << typeid(*a.second.get()).name() << "\n";
    }
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
            // proceed only if it's successful
            if (a->IsSuccessful()) {
                auto &following = a->GetFollowing();
                for (auto &child : following) {
                    if (child->IsReady()) {

                        m_active.insert(child);
                        child->Start();
                    }
                }
            }
        }
    }

    for(auto& a : toRemove) {
        //a->Reset();
        m_active.erase(a);
    }

    if (m_active.empty())
    {
        if (m_loop == -1) {
            m_complete = true;
        }
        else {
            auto act = m_activities.find(m_loop)->second.get();
            act->Reset();
            act->Start();
            m_active.insert(act);
        }
    }

}