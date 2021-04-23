#pragma once

#include <monkey/component.h>
#include <monkey/event.h>

class IModel;
class IShape;

class IAnimator : public Component {
public:
    IAnimator() : m_forward(true) {}
    std::string GetAnimation() const ;
    virtual void SetAnimation (const std::string& anim, bool forward = true) = 0;
    virtual IShape* getShapeCast() = 0;
    virtual IShape* getShape(const std::string& anim = "");
    void resetAnimation();
    void SetInitialAnimation (const std::string& anim);
    void SetPlayForward (bool);
    virtual bool IsComplete() const = 0;
    virtual void setModel (std::shared_ptr<IModel> model) = 0;
    virtual IModel* getModel() const = 0 ;
    using ParentClass = IAnimator;
    Event<IAnimator*> onAnimationChange;
protected:
    // the current animation being played
    std::string m_animation;
    std::string m_initAnim;
    bool m_forward;

};

inline std::string IAnimator::GetAnimation() const {
    return m_animation;
}

inline void IAnimator::SetInitialAnimation (const std::string& anim) {
    m_initAnim = anim;
}


inline void IAnimator::SetPlayForward (bool value) {
    m_forward = value;
}

inline IShape * IAnimator::getShape(const std::string&) {
	return nullptr;
}