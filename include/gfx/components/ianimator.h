#pragma once

#include <gfx/component.h>
#include <gfx/event.h>

class IAnimator : public Component {
public:
    std::string GetAnimation() const ;
    virtual void SetAnimation (const std::string& anim, bool forward = true) = 0;
    virtual bool IsComplete() const = 0;
    using ParentClass = IAnimator;
    Event<IAnimator*> onAnimationChange;
protected:
    // the current animation being played
    std::string m_animation;
};

inline std::string IAnimator::GetAnimation() const {
    return m_animation;
}