#include <gfx/components/animator.h>
#include <gfx/components/renderer.h>
#include <gfx/entity.h>
#include <gfx/error.h>

void Animator::Start() {
    m_status = m_model->GetModelStatus();
    m_status->Init(m_entity);

}
void Animator::Update(double dt) {
    m_status->Update(dt);
}

void Animator::SetAnimation(const std::string &anim) {
    m_status->SetAnimation(anim);
}

void Animator::AdvanceFrame(int inc) {
    m_status->AdvanceFrame(inc);
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



