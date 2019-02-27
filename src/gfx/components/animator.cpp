#include <gfx/components/animator.h>
#include <gfx/components/renderer.h>
#include <gfx/entity.h>
#include <gfx/error.h>

Animator::Animator(const Animator& orig) : Component(orig),
m_forward(orig.m_forward), m_initAnim(orig.m_initAnim), m_model(orig.m_model) {
    
}

std::shared_ptr<Component> Animator::clone() const {
    return std::make_shared<Animator>(Animator(*this));
}
void Animator::Start() {
    m_status = m_model->GetModelStatus();
    m_status->Init(m_entity);
    if (!m_initAnim.empty()) {
        SetAnimation(m_initAnim);
    }

}
void Animator::Update(double dt) {
    m_status->Update(dt);
}

void Animator::SetAnimation(const std::string &anim) {
    m_status->SetAnimation(anim, m_forward);
}

void Animator::AdvanceFrame(int inc) {
    m_status->AdvanceFrame(inc);
}
bool Animator::IsComplete() const {
    return m_status->IsAnimComplete();
}

//void Animator::SetForward (bool value) {
//    m_increment = value ? 1 : -1;
//}
//
//
//
//
//
//void Status::Update(double dt, int inc) {
//    time += dt;
//
//    float frameDuration = m_animInfo->frameInfo[frame].duration;
//    if (time >= frameDuration) {
//        frame += inc;
//        if (frame >= m_animInfo->frameCount) {
//            frame = m_animInfo->loop ? 0 : m_animInfo->frameCount-1;
//            loopEnd = true;
//        } else if (frame < 0) {
//            frame = m_animInfo->loop ? m_animInfo->frameCount - 1 : 0;
//            loopEnd = true;
//        }
//        // this will be >= 0
//        time = time - frameDuration;
//        const FrameInfo& frameInfo = m_animInfo->frameInfo[frame];
//        renderer->SetMeshInfo(frameInfo.offset, frameInfo.count);
//    }
//
//}
//
//void Status::SetAnimation(const std::string& anim, int f) {
//    animation = anim;
//    frame = f;
//    time = 0.0;
//    loopEnd = false;
//    m_animInfo = m_mesh->GetAnimInfo(anim);
//    const FrameInfo& frameInfo = m_animInfo->frameInfo[frame];
//    renderer->SetMeshInfo(frameInfo.offset, frameInfo.count);
//}
//


