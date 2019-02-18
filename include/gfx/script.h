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
    Script();
    void Run (float);
    void Start();
    void AddActivity(int id, std::unique_ptr<Activity>);
    void AddEdge (int fromActivity, int toActivity);
    bool IsComplete() const;
    void Kill () { m_complete=true;}
    void SetSuspended(bool);
    void SetLoop(int);
    void Print();
private:
    void PushToFrontier(int);
    void ResetActivity(int);
    std::unordered_set<size_t> m_frontier;
    std::vector<std::unique_ptr<Activity>> m_activities;

    //std::unordered_map<int, std::vector<int>> m_directedEdges;
    //std::unordered_map<int, int> m_incomingEdgeCount;
    // use of vector to make it more efficient
    std::vector<std::vector<size_t>> m_edges;
    std::vector<size_t> m_incomingEdgeCount;
    std::unordered_map<int, size_t> m_externalToInternalIdMap;

    bool m_suspended;
    bool m_complete;
    //std::string m_startId;
    int m_loop;
};

inline void Script::SetLoop(int id) {
    m_loop =id;
}


inline bool Script::IsComplete() const {
    return m_complete;
}