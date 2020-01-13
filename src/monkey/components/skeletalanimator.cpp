#include <monkey/components/skeletalanimator.h>
#include <monkey/entity.h>
#include <monkey/math/geom.h>
#include <monkey/components/renderer.h>

SkeletalAnimator::SkeletalAnimator(std::shared_ptr<IModel> model) : IAnimator(), m_currentAnim(nullptr) {
    m_model = std::dynamic_pointer_cast<SkeletalModel>(model);
}

//SkeletalAnimator::SkeletalAnimator() : IAnimator(), m_looped(false), m_l_offset_y(0.0f), m_r_offset_y(0.0f) {
//
//}

SkeletalAnimator::SkeletalAnimator(const SkeletalAnimator & orig) : IAnimator(orig), m_model(orig.m_model), m_currentAnim(nullptr) {

}

std::shared_ptr<Component> SkeletalAnimator::clone() const {
    return std::make_shared<SkeletalAnimator>(SkeletalAnimator(*this));
}

SkeletalModel* SkeletalAnimator::getModel() const {
    return m_model.get();
}

void SkeletalAnimator::setModel (std::shared_ptr<IModel> model) {
    m_model = std::dynamic_pointer_cast<SkeletalModel>(model);
    m_initAnim = model->GetDefaultAnimation();
    Start();
}

void SkeletalAnimator::Start() {
    if (!m_initAnim.empty()) {
        SetAnimation(m_initAnim);
    }
    SetAnimation(m_model->GetDefaultAnimation());

    //m_ls =m_bones.at("lshin")->GetComponent<Renderer>();
    //m_rs =m_bones.at("rshin")->GetComponent<Renderer>();

}
float SkeletalAnimator::getTime() const {

    return m_time;
}

void SkeletalAnimator::AddBone(const std::string &id, Entity *bone, float length) {
    m_bones.insert(std::make_pair(id, bone));
    m_bonesLength.insert(std::make_pair(id, length));
}


void SkeletalAnimator::Update(double dt) {
    if (m_currentAnim == nullptr) {
        return;
    }
    //float oldTime = m_time;
    m_time += dt;
    float duration = m_currentAnim->getDuration();
    bool loop = m_currentAnim->loop();
    if (m_time >= duration) {
        if (loop) {
            m_time = 0;
        } else {
            m_time = duration;
        }
        m_looped = true;
    }

    //std::cerr << "t = " << m_time << " " << duration << " " << std::endl;
    auto state = m_currentAnim->getTransformation(m_time);
    //const auto& boneIds = m_currentAnim->getBoneIds();
    m_angles = state.boneAngles;


//    for (size_t j = 0; j < boneIds.size(); ++j) {
//        std::cerr << j << " (" << state.boneAngles[j] << ")\n";
//        m_model->getBone(boneIds[j]).setAngle(state.boneAngles[j]);
//        //m_bones.at(boneIds[j])->SetAngle(state.boneAngles[j]);
//    }

    // check attacks
    // m_currentAnim->checkAttack(oldTime, m_time);

    // update position of torso ... thisshould be in a subclass like human figure skeletal animator

//    auto b = m_rs->GetBounds();
//    const auto& tr = m_rs->GetObject()->GetWorldTransform();
//    b.Transform(tr);
//    auto c = m_ls->GetBounds();
//    const auto& tr2 = m_ls->GetObject()->GetWorldTransform();
//    c.Transform(tr2);
//    auto torso = m_bones.at("torso");
//    glm::vec3 torsoPos = torso->GetPosition();
//    float yMin = std::min(b.min.y - m_r_offset_y, c.min.y - m_l_offset_y);
//    float dist = fabs(torsoPos.y - yMin);
////    glm::vec3 currentPos = m_entity->GetPosition();
////
////    float delta = fabs(currentPos.y-b.min.y);
//    torso->SetPosition(glm::vec3(0, dist, 0));
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
    m_currentAnim = m_model->getAnimation(anim);
    m_looped=false;
    onAnimationChange.Fire(this);
    m_angles = m_currentAnim->getTransformation(m_time).boneAngles;
}

//std::string SkeletalAnimator::GetAnimation() const {
//    return m_animation;
//}


bool SkeletalAnimator::IsComplete() const {
    return m_looped;
}


void SkeletalAnimator::setOffsetY(float l, float r) {
    m_l_offset_y = l;
    m_r_offset_y = r;

}

