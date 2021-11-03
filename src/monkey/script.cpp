#include <monkey/script.h>
#include <monkey/error.h>
#include <iostream>
#include <monkey/activities/noop.h>
#include <monkey/engine.h>
#include <monkey/scenefactory.h>

namespace py = pybind11;

Script::Script(const ITab& table) : m_complete(false), m_suspended(false), m_loop(false) {
    m_name = table.get<std::string>("id", "");
    auto factory = Engine::get().GetSceneFactory();
    int id = 0;
    table.foreach("actions", [&] (const ITab& a) {
        auto action = factory->make2<Activity>(a);
        AddActivity(id, action);
        ++id;
    });

    table.foreach("edges", [&] (const ITab& a) {
        auto b = a.as<std::vector<int>>();
        int tailId = b[0];
        int headId = b[1];
        AddEdge (tailId, headId);
    });

    if (table.has("loop")) {
        m_loop = true;
        m_loopId = table.get<int>("loop");
    }

    if (table.has("on_kill")) {
        m_onKill = table.get<py::function>("on_kill");
    }
}

Script::Script() : m_complete{false}, m_suspended{false}, m_loop{false}, m_loopId{0} {
    AddActivity(0, std::unique_ptr<NoOp>(new NoOp));
}

Script::~Script() {
    //std::cerr << "script: clearing " << m_activities.size() << " acts\n";
    m_activities.clear();
    //std::cerr << "done.\n";
}

void Script::Start() {
    // by convention, the script starts from 0
    if (m_activities.empty()) {
        m_complete = true;
        return;
    }
    PushToFrontier(0);
}

void Script::PushToFrontier(int id) {
    m_frontier.insert(id);
    m_activities[id]->Start();
}

void Script::AddActivity(int id, std::shared_ptr<Activity> act) {
    //m_externalToInternalIdMap[id] = m_activities.size();
    m_activities.push_back(std::move(act));
    m_edges.emplace_back(std::vector<size_t>());
    m_incomingEdgeCount.push_back(0);
}

void Script::AddEdge (int tail, int head) {
    //if (m_externalToInternalIdMap.count(fromActivity) == 0)
    //    GLIB_FAIL("Don't know activity " << fromActivity);
    //if (m_externalToInternalIdMap.count(toActivity) == 0)
    //    GLIB_FAIL("Don't know activity " << toActivity);
    //size_t head = m_externalToInternalIdMap.at(toActivity);
    //m_edges[m_externalToInternalIdMap.at(fromActivity)].push_back(head);
    //7m_incomingEdgeCount[head] ++;
    m_edges[tail].push_back(head);
    m_incomingEdgeCount[head]++;
}

void Script::Print() {

}

void Script::SetSuspended(bool value) {
    m_suspended = value;
    for (auto& a : m_frontier) {
        m_activities[a]->NotifySuspend();
    }
}

void Script::Restart() {
	ResetActivity(0);
	m_complete = false;
}

void Script::ResetActivity(int id) {
    auto activity = m_activities[id].get();
    activity->Reset();
    const auto& followers = m_edges[id];
    for (auto& fid : followers) {
        m_incomingEdgeCount[fid]++;
        ResetActivity(fid);
    }
}

void Script::SetLoop(int id) {
    auto it = m_externalToInternalIdMap.find(id);
    if (it == m_externalToInternalIdMap.end())
        GLIB_FAIL("In setting loop for script, don't know action " << id);
    m_loop = true;
    m_loopId = it->second;
}

void Script::Kill() {

    m_complete = true;
    for (auto& id : m_frontier) {
        m_activities[id]->SetComplete();
    }

    if (m_onKill) {
        m_onKill();
    }
}

void Script::Run (float dt) {
    if (m_suspended || m_complete) {
        return;
    }

    // check the frontier. If any
    std::unordered_set<int> toRemove;
    for (auto& id : m_frontier) {
        Activity* activity = m_activities[id].get();
        //activity->Run(dt);
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
        } else {
            activity->Run(dt);
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
        if (!m_loop) {
            m_complete = true;
        }
        else {
            // reset loop action and all its successors
            for (auto& n : m_incomingEdgeCount) {
                n = 0;
            }
            ResetActivity(m_loopId);
            PushToFrontier(m_loopId);
        }
    }

}
