#pragma once

#include <monkey/activities/targetactivity.h>
#include <monkey/entity.h>
#include <monkey/components/animrenderer.h>


class __attribute__ ((visibility ("default"))) Animate : public TargetActivity {
public:
    //! \name Constructors
    //@{
    /*! Animate the given actor with animation animId. If flip is 0, no flip is applied. Otherwise,
    the sprite horizontal flip is set to false if flip = 1, or true if flip = 2.
     */
    Animate(const std::string& animId, bool forward, int flip = 0);
    Animate(const ITab&);
    //Animate(Entity* entity, const std::string& animId, bool forward, int flip = 0);
    //@}
    void Start() override;
    void Reset() override {
        Activity::Reset();
        m_entity = Handle<Entity>();
    }
    void Run (float dt) override ;
    // action ends when animation is completed.
    void SetSync (bool);
private:
    bool m_forward;
    bool m_sync;
    int m_flipX;
    AnimationRenderer* m_animator;
    std::string m_animId;
};

inline void Animate::SetSync (bool sync) {
    m_sync = sync;
}
