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
    m_renderer = m_entity->GetComponent<Renderer>();
    m_mesh = dynamic_cast<SpriteMesh*>(m_model->GetMesh().get());
    if (!m_initAnim.empty()) {
        SetAnimation(m_initAnim);
    }

}
void Animator::Update(double dt) {
    m_time += dt;
    float frameDuration = m_animInfo->frameInfo[m_frame].duration;
    if (m_time >= frameDuration) {
        int oldFrame = m_frame;
        m_frame += m_inc;
        if (m_frame >= m_animInfo->frameCount) {
            m_frame = m_animInfo->loop ? 0 : m_animInfo->frameCount - 1;
            m_animCompleted = true;
        } else if (m_frame < 0) {
            m_frame = m_animInfo->loop ? m_animInfo->frameCount - 1 : 0;
            m_animCompleted = true;
        }
        // if frame has changed, notify the model that might do something
        if (oldFrame != m_frame) {
            // this will be >= 0
            m_time = m_time - frameDuration;
            const FrameInfo &frameInfo = m_animInfo->frameInfo[m_frame];
            m_renderer->SetMeshInfo(frameInfo.offset, frameInfo.count);
            onFrameUpdate.Fire(this);
        }
    }
}


// play the given animation (forward or backward)
void Animator::SetAnimation(const std::string &anim, bool fwd) {
    // if the current animation is the same as the new one,
    // do nothing
    if (anim == m_animation)
    {
        return;
    }
    m_animCompleted = false;
    m_inc = fwd ? 1 : -1;
    m_animation = anim;
    m_time = 0.0;

    m_animInfo = m_mesh->GetAnimInfo(anim);
    if (m_animInfo == nullptr) {
        GLIB_FAIL("Don't know animation: " << anim);
    }
    m_frame = fwd ? 0 : m_animInfo->frameCount-1;
    const FrameInfo& frameInfo = m_animInfo->frameInfo[m_frame];
    m_renderer->SetMeshInfo(frameInfo.offset, frameInfo.count);
}


bool Animator::IsComplete() const {
    return m_animCompleted;
}





