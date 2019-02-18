#include <gfx/script.h>
#include <gfx/error.h>
#include <iostream>
#include <gfx/activities/noop.h>

Script::Script() : m_complete{false}, m_suspended{false}, m_loop{-1} {
    m_activities[0] = std::unique_ptr<NoOp>(new NoOp);

}

void Script::Start() {
    // by convention, the script starts from 0
    PushToFrontier(0);
}

void Script::PushToFrontier(int id) {
    m_frontier.insert(id);
    m_activities[id]->Start();
}

void Script::AddActivity(int id, std::unique_ptr<Activity> act) {
    m_externalToInternalIdMap[id] = m_activities.size();
    m_activities.push_back(std::move(act));
    m_edges.push_back(std::vector<size_t>());
    m_incomingEdgeCount.push_back(0);
}

void Script::AddEdge (int fromActivity, int toActivity) {
    if (m_externalToInternalIdMap.count(fromActivity) == 0)
        GLIB_FAIL("Don't know activity " << fromActivity);
    if (m_externalToInternalIdMap.count(toActivity) == 0)
        GLIB_FAIL("Don't know activity " << toActivity);
    size_t head = m_externalToInternalIdMap.at(toActivity);
    m_edges[m_externalToInternalIdMap.at(fromActivity)].push_back(head);
    m_incomingEdgeCount[head] ++;

}

void Script::Print() {
//    for (auto& a: m_activities) {
//        std::cout << a.first << typeid(*a.second.get()).name() << "\n";
//    }
}

void Script::SetSuspended(bool value) {
    m_suspended = value;
    for (auto& a : m_frontier) {
        m_activities[a]->NotifySuspend();
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
    if (m_suspended) {
        return;
    }

    // check the frontier. If any
    std::unordered_set<int> toRemove;
    for (auto& id : m_frontier) {
        Activity* activity = m_activities[id].get();
        activity->Run(dt);
        if (activity->IsComplete()) {
            // check its children
            // this definitely  needs to be removed rom the froniter
            toRemove.insert(id);
            // proceed only if it's successful!
            if (activity->IsSuccessful()) {
                const auto& followers = m_edges[id];
                for (auto f : followers) {
                    m_incomingEdgeCount[f] --;
                    if (m_incomingEdgeCount[f] == 0) {
                        PushToFrontier(f);
                    }
                }
            }
        }
    }

    for(auto& a : toRemove) {
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
