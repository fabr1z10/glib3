#include <gfx/script.h>
#include <gfx/error.h>
#include <iostream>
#include <gfx/activities/noop.h>

Script::Script() : m_complete{false}, m_suspended{false}, m_loop{-1} {
    m_activities[0] = std::unique_ptr<NoOp>(new NoOp);

}

void Script::Start() {
    // by convention, the script starts from 0
    auto it = m_activities.find(0);
    m_frontier.insert(std::make_pair(0, it->second.get()));
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
    if (m_activities.count(fromActivity) == 0)
        GLIB_FAIL("Don't know activity " << fromActivity);
    if (m_activities.count(toActivity) == 0)
        GLIB_FAIL("Don't know activity " << toActivity);
    m_directedEdges[fromActivity].push_back(toActivity);

}

void Script::Print() {
    for (auto& a: m_activities) {
        std::cout << a.first << typeid(*a.second.get()).name() << "\n";
    }
}

void Script::SetSuspended(bool value) {
    m_suspended = value;
    for (auto& a : m_frontier) {
        a.second->NotifySuspend();
    }
}


void Script::ResetActivity(int id) {
    auto activity = m_activities.at(id).get();
    if (activity->IsComplete()) {
        activity->Reset();
        auto ifollow = m_directedEdges.find(id);
        if (ifollow != m_directedEdges.end()) {
            for (auto& fid : ifollow->second) {
                ResetActivity(fid);
            }
        }
    }
}


void Script::Run (float dt) {
    if (m_suspended)
        return;

    // check the frontier. If any
    std::unordered_set<int> toRemove;
    for (auto& a : m_frontier) {
        Activity* activity = a.second;
        activity->Run(dt);
        if (activity->IsComplete()) {
            // check its children
            toRemove.insert(a.first);
            // proceed only if it's successful
            if (activity->IsSuccessful()) {
                auto ifollow = m_directedEdges.find(a.first);
                if (ifollow != m_directedEdges.end()) {
                    for (auto& fid : ifollow->second) {
                        Activity * act = m_activities.at(fid).get();
                        m_frontier.insert(std::make_pair(fid, act));
                        act->Start();
                    }
                }
            }
        }
    }

    for(auto& a : toRemove) {
        //a->Reset();
        m_frontier.erase(a);
    }

    // if the frontier is empty, and this script doesn't loop, then
    // mark it as complete. Otherwise restart the script at the position
    // indicated by loop. Of course all actions should be reset
    if (m_frontier.empty())
    {
        if (m_loop == -1) {
            m_complete = true;
        }
        else {
            // reset loop action and all its successors
            ResetActivity(m_loop);
            auto restartActivity = m_activities.find(m_loop)->second.get();
            m_frontier.insert(std::make_pair(m_loop, restartActivity));
            restartActivity->Start();
        }
    }

}
