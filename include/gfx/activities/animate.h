#pragma once

#include <gfx/activity.h>
#include <gfx/entity.h>

class Animator;

class Animate : public Activity {
public:
    //! \name Constructors
    //@{
    /*! Animate the given actor with animation animId. If flip is 0, no flip is applied. Otherwise,
    the sprite horizontal flip is set to false if flip = 1, or true if flip = 2.
     */
    Animate(int id, const std::string& animId, bool forward, int flip = 0);
    //Animate(Entity* entity, const std::string& animId, bool forward, int flip = 0);
    //@}
    void Start() override;
    void Reset() override {
        Activity::Reset();
        m_entity = nullptr;
    }
    void Run (float dt) override ;
    // action ends when animation is completed.
    void SetSync (bool);
private:
    bool m_forward;
    bool m_sync;
    int m_flipX;
    Entity* m_entity;
    Animator* m_animator;
    std::string m_animId;
    int m_id;
};

inline void Animate::SetSync (bool sync) {
    m_sync = sync;
}
