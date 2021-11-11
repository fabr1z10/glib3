#include <monkey/components/spriterenderer.h>

SpriteRenderer::SpriteRenderer(std::shared_ptr<Model> model) : AnimationRenderer(model), m_currentAnimInfo(nullptr),
    m_frame(0), m_frameCount(0), m_time(0.0)
{
    m_spriteModel = dynamic_cast<SpriteModel*>(model.get());
}

void SpriteRenderer::Draw(Shader * s) {
    const auto& frameInfo = m_currentAnimInfo->frames[m_frame];
    m_model->getMesh(0)->draw(s, frameInfo.offset, frameInfo.count);
}

void SpriteRenderer::Update(double dt) {
    m_time += dt;
    if (m_time > m_currentAnimInfo->frames[m_frame].time) {
        // reset timer
        m_time = m_time - m_currentAnimInfo->frames[m_frame].time;
        // update frame
        if (m_playForward) {
            m_frame++;
            if (m_frame >= m_currentAnimInfo->frames.size()) {
                m_frame = 0;
            }
        } else {
            m_frame--;
            if (m_frame < 0) {
                m_frame = m_currentAnimInfo->frames.size() - 1;
            }
        }
    }
}

void SpriteRenderer::setAnimation(const std::string& anim) {
    if (anim == m_animation) {
        return;
    }

    m_complete = false;
    m_currentAnimInfo = m_spriteModel->getAnimationInfo(anim);
    m_frameCount = m_currentAnimInfo->frames.size();
    m_time = 0.0;
    m_frame = (m_playForward ? 0 : m_frameCount-1);


}

std::type_index SpriteRenderer::GetType() {
    return std::type_index(typeid(Renderer));
}