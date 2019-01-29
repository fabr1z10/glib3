#include <gfx/simplemodel.h>
#include <gfx/entity.h>

void SimpleModelStatus::Init(Entity* entity) {
    renderer = entity->GetComponent<Renderer>();
}

void SimpleModelStatus::SetAnimation(const std::string& anim) {
    animation = anim;
    frame = 0;
    time = 0.0;
    m_animInfo = m_mesh.GetAnimInfo(anim);
    const FrameInfo& frameInfo = m_animInfo->frameInfo[frame];
    renderer->SetMeshInfo(frameInfo.offset, frameInfo.count);
}


void SimpleModelStatus::Update(double dt) {
    time += dt;
    float frameDuration = m_animInfo->frameInfo[frame].duration;
    if (time >= frameDuration) {
        frame += inc;
        if (frame >= m_animInfo->frameCount) {
            frame = m_animInfo->loop ? 0 : m_animInfo->frameCount - 1;

        } else if (frame < 0) {
            frame = m_animInfo->loop ? m_animInfo->frameCount - 1 : 0;
        }
        // this will be >= 0
        time = time - frameDuration;
        const FrameInfo &frameInfo = m_animInfo->frameInfo[frame];
        renderer->SetMeshInfo(frameInfo.offset, frameInfo.count);
    }
}

std::unique_ptr<IModelStatus> SimpleModel::GetModelStatus() {
    auto ptr = std::unique_ptr<SimpleModelStatus>(new SimpleModelStatus(*m_mesh));
    return ptr;
}
