#pragma once

#include <gfx/activity.h>
#include <unordered_map>
#include <unordered_set>

// a script is basically a graph of activities. At every point in time it contains a set of
// active task. At each iteration, each active task is run and check for completion. If complete, the
// complete task is removed from the active tasks and all its children are examined. Each child
// checks if all its parents are complete. If so, the child is added to the active set. When the
// active set is empty, the script is itself complete.
class Script {
public:
    Script(const std::string& startActivityId) : m_complete{false}, m_startId{startActivityId}, m_suspended{false} {}
    void Run (float);
    void Start();
    void AddActivity(const std::string& id, std::unique_ptr<Activity>);
    void AddEdge (const std::string& fromActivity, const std::string& toActivity);
    bool IsComplete() const;
    void SetSuspended(bool);
    void SetLoop(const std::string&);
private:
    std::unordered_set<Activity*> m_active;
    std::unordered_map<std::string, std::unique_ptr<Activity> > m_activities;
    bool m_suspended;
    bool m_complete;
    std::string m_startId;
    std::string m_loop;
};

inline void Script::SetLoop(const std::string& id) {
    m_loop =id;
}
inline void Script::SetSuspended(bool value) {
    m_suspended = value;
}

inline bool Script::IsComplete() const {
    return m_complete;
}