#pragma once

//#include <chrono>
#include <memory>
#include <vector>

class Edge;

class Activity {
public:
    Activity () : m_complete{false}, m_success{true} {}
    virtual ~Activity();
    virtual void Start() = 0;
    virtual void Run (float dt) = 0;
    bool IsSuccessful() const;
    bool IsComplete () const;
    virtual void SetComplete();
    virtual void Reset();
    bool IsReady() const;
    std::vector<Activity*>& GetPrevious();
    std::vector<Activity*>& GetFollowing();
    void AddPrevious (Activity*);
    void AddNext (Activity*);
    // called when a script is suspended and this activity is current.
    // default behavior is do nothing
    virtual void NotifySuspend() {}
private:
    //int m_id;
    std::vector<Activity*> m_previous;
    std::vector<Activity*> m_following;
    bool m_complete;
protected:
    bool m_success;

};


inline bool Activity::IsComplete () const{
    return m_complete;
}

inline bool Activity::IsSuccessful() const {
    return m_success;
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
