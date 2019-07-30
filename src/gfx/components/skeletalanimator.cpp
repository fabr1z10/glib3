#include <gfx/components/skeletalanimator.h>
#include <gfx/entity.h>
#include <gfx/math/geom.h>

SkeletalAnimator::SkeletalAnimator() : IAnimator() {

}

SkeletalAnimator::SkeletalAnimator(const SkeletalAnimator & orig) : IAnimator(orig) {

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
    m_thighLength = m_bonesLength.at("rthigh");
    m_shinLength = m_bonesLength.at("rshin");

    m_angles["rthigh"] =m_bones.at("rthigh")->GetAngle();
    m_angles["rshin"] =m_bones.at("rshin")->GetAngle();
    m_angles["lthigh"] =m_bones.at("lthigh")->GetAngle();
    m_angles["lshin"] =m_bones.at("lshin")->GetAngle();
}

void SkeletalAnimator::AddBone(const std::string &id, Entity *bone, float length) {
    m_bones.insert(std::make_pair(id, bone));
    m_bonesLength.insert(std::make_pair(id, length));
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
        m_angles[b.name] = b.angle * deg2rad;
    }



    // update position of torso ... thisshould be in a subclass like human figure skeletal animator
    float rta = m_angles.at("rthigh");
    float rsa = m_angles.at("rshin");
    float lta = m_angles.at("lthigh");
    float lsa = m_angles.at("lshin");
    float yR = m_thighLength * cos(rta) + m_shinLength * cos(rta+rsa);
    float yL = m_thighLength * cos(lta) + m_shinLength * cos(lta+lsa);
    float yOffset = std::max(yR, yL);
    m_bones.at("torso")->SetPosition(glm::vec3(0, yOffset, 0));

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


bool SkeletalAnimator::IsComplete() const {
    return false;
}