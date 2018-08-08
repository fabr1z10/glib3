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
    Script() : m_complete{false}, m_suspended{false}, m_loop{-1} {}
    void Run (float);
    void Start();
    void AddActivityAfter(int id, std::unique_ptr<Activity>, std::vector<int> after = {0});
    void AddActivity(int id, std::unique_ptr<Activity>);
    void AddEdge (int fromActivity, int toActivity);
    bool IsComplete() const;
    void SetSuspended(bool);
    void SetLoop(int);
    void Print();
private:
    std::unordered_set<Activity*> m_active;
    std::unordered_map<int, std::unique_ptr<Activity> > m_activities;
    bool m_suspended;
    bool m_complete;
    //std::string m_startId;
    int m_loop;
};

inline void Script::SetLoop(int id) {
    m_loop =id;
}
inline void Script::SetSuspended(bool value) {
    m_suspended = value;
}

inline bool Script::IsComplete() const {
    return m_complete;
}