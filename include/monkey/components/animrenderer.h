#pragma once

#include "renderer.h"

class AnimationRenderer : public Renderer {
public:
    AnimationRenderer(std::shared_ptr<Model> model) : Renderer(model), m_complete(false), m_playForward(true) {}
    std::string getAnimation() const;
    virtual void setAnimation(const std::string&) = 0;
    bool isComplete() const;
    void setPlayForward(bool);
protected:
    // the animation currently played
    std::string m_animation;
    bool m_complete;
    bool m_playForward;
};

inline std::string AnimationRenderer::getAnimation() const {
    return m_animation;
}

inline bool AnimationRenderer::isComplete() const {
    return m_complete;
}

inline void AnimationRenderer::setPlayForward(bool fwd) {
    m_playForward = fwd;
}