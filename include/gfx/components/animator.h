#pragma once

#include <gfx/component.h>
#include <gfx/spritemesh.h>
#include <gfx/imodel.h>

class Renderer;

struct Status {
    Renderer* renderer;
    std::string animation;
    int frame;
    double time;
    const AnimInfo* m_animInfo;
    SpriteMesh* m_mesh;
    bool loopEnd;
    void SetAnimation(const std::string& animation, int frame = 0);
    void Update(double, int);
};

class AnimatorState {
public:
    virtual ~AnimatorState() = default;
};

// the animator doesn't know which model is animating.
// For instance it doesn't know if it's a simple mesh or a composite model.
// however it abstracts some functionalities, for instance:
// set the animation
// set the animation for a given node
// check whether animation exists
//
class Animator : public Component {
public:
    Animator(std::shared_ptr<IModel> model) : m_model(model), m_forward(true) {}
    Animator(const Animator&);
    virtual ~Animator() {}
    void Start() override;
    void AdvanceFrame(int);
    void Update(double dt) override;
    void SetInitialAnimation (const std::string& anim);
    void SetAnimation (const std::string& anim);
    //virtual void SetAnimation (const std::string& node, const std::string& anim) = 0;
    //bool HasAnimation(const std::string&) = 0;
    //virtual bool HasAnimation(const std::string&, const std::string&) = 0;
    bool IsComplete() const;
    void SetPlayForward (bool);
    // allows to backup the status in order to restore it later
    //virtual std::shared_ptr<AnimatorState> SaveState()  = 0;
    //virtual void LoadState(std::shared_ptr<AnimatorState>) = 0;
    std::shared_ptr<Component> clone() const override;
    using ParentClass = Animator;
protected:
    // play animation forward
    bool m_forward;
    std::string m_initAnim;
    std::shared_ptr<IModel> m_model;
    std::unique_ptr<IModelStatus> m_status;

};

inline void Animator::SetPlayForward (bool value) {
    m_forward = value;
}

inline void Animator::SetInitialAnimation (const std::string& anim) {
    m_initAnim = anim;
}
