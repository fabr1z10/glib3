#pragma once

#include <monkey/components/ianimator.h>
#include <monkey/spritemesh.h>
#include <monkey/model/spritemodel.h>
#include <monkey/event.h>

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

// the animator is the component used to change the sprite animation
// and updating frames.
class Animator : public IAnimator {
public:
    Animator(std::shared_ptr<IModel> model);
    virtual ~Animator() {}
    void Start() override;
    void Update(double dt) override;

    void SetAnimation (const std::string& anim, bool forward = true) override;
    //std::string GetAnimation() const;
    //virtual void SetAnimation (const std::string& node, const std::string& anim) = 0;
    //bool HasAnimation(const std::string&) = 0;
    //virtual bool HasAnimation(const std::string&, const std::string&) = 0;
    bool IsComplete() const override;
    int GetFrame() const;
    std::shared_ptr<SpriteModel> GetModel();
    void setModel (std::shared_ptr<IModel> model) override;
    IModel* getModel() const override;
    // allows to backup the status in order to restore it later
    //virtual std::shared_ptr<AnimatorState> SaveState()  = 0;
    //virtual void LoadState(std::shared_ptr<AnimatorState>) = 0;
    using ParentClass = Animator;
    std::type_index GetType() override;
    const FrameInfo* getFrameInfo();
    Event<Animator*> onFrameUpdate;
protected:

    // play animation forward
    std::shared_ptr<SpriteModel> m_model;
    // the current animation
    //std::string m_animation;
    double m_time;
    int m_inc;
    bool m_fwd;
    // the current frame
    int m_frame;
    const AnimInfo* m_animInfo;
    bool m_animCompleted;
    Renderer* m_renderer;
    // SpriteMesh* m_mesh;
    //std::unique_ptr<IModelStatus> m_status;

};





inline int Animator::GetFrame() const {
    return m_frame;
}

inline std::shared_ptr<SpriteModel> Animator::GetModel() {
    return m_model;
}


//inline std::string Animator::GetAnimation() const {
//    return m_animation;
//}


inline std::type_index Animator::GetType() {
    return std::type_index(typeid(IAnimator));
}