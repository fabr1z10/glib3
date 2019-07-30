#include <gfx/components/skeletalanimator.h>
#include <gfx/entity.h>

SkeletalAnimator::SkeletalAnimator() : Component() {

}

SkeletalAnimator::SkeletalAnimator(const SkeletalAnimator & orig) : Component(orig) {

}

std::shared_ptr<Component> SkeletalAnimator::clone() const {
    return std::make_shared<SkeletalAnimator>(SkeletalAnimator(*this));
}

void SkeletalAnimator::AddAnimation(const std::string& name, std::shared_ptr<SkeletalAnimation> anim) {
    if (m_initAnim.empty()) m_initAnim = name;
    m_animations.insert(std::make_pair(name, anim));
}

void SkeletalAnimator::Start() {
    if (!m_initAnim.empty()) {
        SetAnimation(m_initAnim);
    }

}

void SkeletalAnimator::AddBone(const std::string &id, Entity *bone) {
    m_bones.insert(std::make_pair(id, bone));
}


void SkeletalAnimator::Update(double dt) {
    m_time += dt;
    float duration = m_currentAnim->getDuration();
    if (m_time >= duration) {
        m_time = m_time - duration;
    }

    auto state = m_currentAnim->getTransformation(m_time);
    for (const auto& b : state.bones) {
        // set the correct angle for each bone
        m_bones.at(b.name)->SetAngle(b.angle);
    }


}

void SkeletalAnimator::SetAnimation(const std::string &anim, bool forward) {
    // if the current animation is the same as the new one,
    // do nothing
    if (m_animation == anim) {
        return;
    }

    // reset timer
    m_time = 0.0;
    m_animation = anim;
    m_currentAnim = m_animations.at(anim).get();

}

std::string SkeletalAnimator::GetAnimation() const {
    return m_animation;
}