#include <monkey/components/animator.h>
#include <monkey/components/renderer.h>
#include <monkey/entity.h>
#include <monkey/error.h>
#include <glm/gtx/transform.hpp>
#include <monkey/math/geom.h>


Animator::Animator(std::shared_ptr<IModel> model) : IAnimator() {
    m_model = std::dynamic_pointer_cast<SpriteModel>(model);
    m_animInfo = m_model->GetAnimInfo();
    m_initAnim = model->GetDefaultAnimation();
}

void Animator::Start() {
    m_renderer = m_entity->GetComponent<Renderer>();
    //m_mesh = dynamic_cast<SpriteMesh*>(m_model->GetModel().get());
    std::string anim = m_animation.empty() ? m_initAnim : m_animation;
    if (!anim.empty()) {
        SetAnimation(anim);
    }
}

void Animator::Update(double dt) {
    m_time += dt;
    float frameDuration = m_animInfo->frameInfo[m_frame].duration;
    if (m_time >= frameDuration) {
        int oldFrame = m_frame;
        m_frame += m_inc;
        if (m_frame >= m_animInfo->frameCount) {
            m_frame = m_animInfo->loop ? m_animInfo->loopFrame : m_animInfo->frameCount - 1;
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
            if (frameInfo.move) {
                glm::mat4 x (1.0f);
                if (frameInfo.flipx) x[0][0] *= -1;

                x *= glm::translate(glm::vec3(frameInfo.origin, 0.0f)) *
                        glm::rotate(deg2rad * frameInfo.angle, glm::vec3(0,0,1)) * glm::translate(glm::vec3(-frameInfo.origin, 0.0f));
                x[3][0] += frameInfo.translation.x;
                x[3][1] += frameInfo.translation.y;

                m_renderer->SetTransform(x);
                //                m_entity->SetAngle(frameInfo.angle);
                //m_entity->SetPosition(frameInfo.translation);
            }
            if (frameInfo.applyAlpha) {
            	m_renderer->setMultColor(glm::vec4(1.0, 1.0, 1.0, frameInfo.alpha));
            }
            //m_renderer->SetMeshInfo(frameInfo.offset, frameInfo.count);
            onFrameUpdate.Fire(this);
        }
    }
}


// play the given animation (forward or backward)
void Animator::SetAnimation(const std::string &anim, bool fwd) {
    // if the current animation is the same as the new one,
    // do nothing
    if (anim == m_animation && fwd == m_fwd)
    {
        return;
    }

    m_animCompleted = false;
    m_inc = fwd ? 1 : -1;
    m_animation = anim;
    m_fwd = fwd;
    m_time = 0.0;

    m_animInfo = m_model->GetAnimInfo(anim);
    if (m_animInfo == nullptr) {
        GLIB_FAIL("Don't know animation: " << anim);
    }
    m_frame = fwd ? 0 : m_animInfo->frameCount-1;
    const FrameInfo& frameInfo = m_animInfo->frameInfo[m_frame];
    //m_renderer->SetMeshInfo(frameInfo.offset, frameInfo.count);
    onFrameUpdate.Fire(this);
}


bool Animator::IsComplete() const {
    return m_animCompleted;
}

void Animator::setModel(std::shared_ptr<IModel> model) {
    m_model = std::dynamic_pointer_cast<SpriteModel>(model);
    m_animInfo = m_model->GetAnimInfo();
    m_initAnim = model->GetDefaultAnimation();
    Start();
}

IModel* Animator::getModel() const {
    return m_model.get();
}

const FrameInfo* Animator::getFrameInfo() {
    return &(m_animInfo->frameInfo[m_frame]);

}




