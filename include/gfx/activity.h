#pragma once

//#include <chrono>
#include <memory>
#include <vector>

class Edge;

class Activity {
public:
    Activity (int id) : m_id{id}, m_complete{false} {}
    virtual ~Activity();
    virtual void Start() = 0;
    virtual void Run (float dt) = 0;

    bool IsComplete () const;
    void SetComplete();
    bool IsReady() const;
    std::vector<Activity*>& GetPrevious();
    std::vector<Activity*>& GetFollowing();
    void AddPrevious (Activity*);
    void AddNext (Activity*);
    int GetId() const;
private:
    int m_id;
    std::vector<Activity*> m_previous;
    std::vector<Activity*> m_following;
    bool m_complete;
    //std::chrono::time_point<std::chrono::system_clock> m_timeComplete;
};

inline int Activity::GetId() const {
    return m_id;
}

inline bool Activity::IsComplete () const{
    return m_complete;
}

inline std::vector<Activity*>& Activity::GetPrevious() {
    return m_previous;
}

inline std::vector<Activity*>& Activity::GetFollowing() {
    return m_following;
}


class Edge {
public:
    Edge (std::shared_ptr<Activity> tail, std::shared_ptr<Activity> head, float weight);
    Activity* GetTail() const;
    Activity* GetHead() const;
private:
    float m_weight;
    std::shared_ptr<Activity> m_tail;
    std::shared_ptr<Activity> m_head;
};

inline Activity* Edge::GetHead() const {
    return m_head.get();
}

inline Activity* Edge::GetTail() const {
    return m_tail.get();
}
