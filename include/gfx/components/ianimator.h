#pragma once

#include <gfx/component.h>

class IAnimator : public Component {
public:
    virtual void SetAnimation (const std::string& anim, bool forward = true) = 0;
    virtual bool IsComplete() const = 0;
    using ParentClass = IAnimator;

};