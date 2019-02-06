#include <gfx/simplemodel.h>
#include <gfx/entity.h>
#include <iostream>

void SimpleModelStatus::Init(Entity* entity) {
    renderer = entity->GetComponent<Renderer>();
    SetAnimation(m_mesh.GetDefaultAnimation(), true);
}

void SimpleModelStatus::SetAnimation(const std::string& anim, bool fwd) {
    std::cout << "setting anim to " << anim<<"\n";
    m_animCompleted = false;
    inc = fwd ? 1 : -1;
    animation = anim;
    time = 0.0;
    m_animInfo = m_mesh.GetAnimInfo(anim);
    frame = fwd ? 0 : m_animInfo->frameCount-1;
    const FrameInfo& frameInfo = m_animInfo->frameInfo[frame];
    renderer->SetMeshInfo(frameInfo.offset, frameInfo.count);
}

void SimpleModelStatus::AdvanceFrame(int inc) {
    frame += inc;
    if (frame >= m_animInfo->frameCount) {
        m_animCompleted = true;
        frame = m_animInfo->loop ? 0 : m_animInfo->frameCount - 1;
    } else if (frame < 0) {
        m_animCompleted = true;
        frame = m_animInfo->loop ? m_animInfo->frameCount - 1 : 0;
    }
    const FrameInfo &frameInfo = m_animInfo->frameInfo[frame];
    renderer->SetMeshInfo(frameInfo.offset, frameInfo.count);
}

void SimpleModelStatus::Update(double dt) {

    time += dt;
    float frameDuration = m_animInfo->frameInfo[frame].duration;
    if (time >= frameDuration) {
        frame += inc;
        if (frame >= m_animInfo->frameCount) {
            frame = m_animInfo->loop ? 0 : m_animInfo->frameCount - 1;
            m_animCompleted = true;
        } else if (frame < 0) {
            frame = m_animInfo->loop ? m_animInfo->frameCount - 1 : 0;
            m_animCompleted = true;
        }
        // this will be >= 0
        time = time - frameDuration;
        const FrameInfo &frameInfo = m_animInfo->frameInfo[frame];
        //std::cout << "(" << frameInfo.offset<<"," << frameInfo.count << ")\n";
        renderer->SetMeshInfo(frameInfo.offset, frameInfo.count);
    }
}

std::unique_ptr<IModelStatus> SimpleModel::GetModelStatus() {
    auto ptr = std::unique_ptr<SimpleModelStatus>(new SimpleModelStatus(*m_mesh));
    return ptr;
}

std::vector<std::string> SimpleModel::GetAnimations() {
    const auto& m = m_mesh->GetAnimInfo();
    std::vector<std::string> animations;
    for (auto& a : m) {
        animations.push_back(a.first);
    }
    return animations;
}
