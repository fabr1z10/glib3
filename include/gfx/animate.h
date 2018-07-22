#pragma once

#include <gfx/activity.h>
#include <gfx/entity.h>

class Renderer;

class Animate : public Activity {
public:
    //! \name Constructors
    //@{
    /*! Animate the given actor with animation animId. If flip is 0, no flip is applied. Otherwise,
    the sprite horizontal flip is set to false if flip = 1, or true if flip = 2.
     */
    Animate(int activityId, const std::string& actorId, const std::string& animId, int flip = 0);
    Animate(int activityId, Entity* entity, const std::string& animId, int flip = 0);
    //@}
    void Start() override;
    void Reset() override {
        Activity::Reset();
        m_entity = nullptr;
    }
    void Run (float dt) override ;
    void SetLoop (int);
private:
    int m_loop;
    int m_flipX;
    Entity* m_entity;
    Renderer* m_renderer;
    std::string m_animId;
    std::string m_actorId;
};

inline void Animate::SetLoop (int count) {
    m_loop = count;
}
