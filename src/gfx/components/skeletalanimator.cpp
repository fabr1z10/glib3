#include <gfx/components/skeletalanimator.h>
#include <gfx/entity.h>
#include <gfx/math/geom.h>
#include <gfx/components/renderer.h>

SkeletalAnimator::SkeletalAnimator() : IAnimator(), m_looped(false) {

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

    m_ls =m_bones.at("lshin")->GetComponent<Renderer>();
    m_rs =m_bones.at("rshin")->GetComponent<Renderer>();

}

void SkeletalAnimator::AddBone(const std::string &id, Entity *bone, float length) {
    m_bones.insert(std::make_pair(id, bone));
    m_bonesLength.insert(std::make_pair(id, length));
}


void SkeletalAnimator::Update(double dt) {
    //float oldTime = m_time;
    m_time += dt;
    float duration = m_currentAnim->getDuration();
    if (m_time >= duration) {
        m_looped = true;
        m_time = m_time - duration;
    }

    auto state = m_currentAnim->getTransformation(m_time);
    for (const auto& b : state.bones) {
        // set the correct angle for each bone
        m_bones.at(b.name)->SetAngle(b.angle);
    }

    // check attacks
    // m_currentAnim->checkAttack(oldTime, m_time);

    // update position of torso ... thisshould be in a subclass like human figure skeletal animator

    auto b = m_rs->GetBounds();
    const auto& tr = m_rs->GetObject()->GetWorldTransform();
    b.Transform(tr);
    auto c = m_ls->GetBounds();
    const auto& tr2 = m_ls->GetObject()->GetWorldTransform();
    c.Transform(tr2);
    auto torso = m_bones.at("torso");
    glm::vec3 torsoPos = torso->GetPosition();
    float yMin = std::min(b.min.y, c.min.y);
    float dist = fabs(torsoPos.y - yMin);
//    glm::vec3 currentPos = m_entity->GetPosition();
//
//    float delta = fabs(currentPos.y-b.min.y);
    torso->SetPosition(glm::vec3(0, dist, 0));
    //m_bones.at("torso")->SetPosition(glm::vec3(0, yOffset, 0));

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
    auto it = m_animations.find(anim);
    if (it == m_animations.end()) {
        GLIB_FAIL("Skeleton doesn't have animation " << anim);
    }
    m_currentAnim =it->second.get();
    m_looped=false;
    onAnimationChange.Fire(this);
}

//std::string SkeletalAnimator::GetAnimation() const {
//    return m_animation;
//}


bool SkeletalAnimator::IsComplete() const {
    return m_looped;
}


