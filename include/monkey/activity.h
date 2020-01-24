#pragma once

#include <memory>
#include <vector>
#include <monkey/ref.h>

class Activity : public Ref {
public:
    Activity () : Ref(), m_complete{false}, m_success{true} {}
    virtual ~Activity();
    virtual void Start() = 0;
    virtual void Run (float dt) = 0;
    bool IsSuccessful() const;
    bool IsComplete () const;
    virtual void SetComplete();
    virtual void Reset();
    //bool IsReady() const;
    //std::vector<Activity*>& GetPrevious();
    //std::vector<Activity*>& GetFollowing();
    //void AddPrevious (Activity*);
    //void AddNext (Activity*);
    // called when a script is suspended and this activity is current.
    // default behavior is do nothing
    virtual void NotifySuspend() {}
private:
    //int m_id;
    //std::vector<Activity*> m_previous;
    //std::vector<Activity*> m_following;
    bool m_complete;
protected:
    //! the outcome of the activity. This is used in a script to determine whether the script should proceed or not.
    // this flag is set to true in the ctor, so if you want to use it, just set it to the correct value when the
    // action ends.
    bool m_success;

};


inline bool Activity::IsComplete () const{
    return m_complete;
}

inline bool Activity::IsSuccessful() const {
    return m_success;
}

