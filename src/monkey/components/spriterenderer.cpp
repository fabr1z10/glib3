#include <monkey/components/spriterenderer.h>
#include <monkey/shader.h>


SpriteRenderer::SpriteRenderer(std::shared_ptr<Model> model) : AnimationRenderer(model), m_currentAnimInfo(nullptr),
    m_frame(0), m_frameCount(0), m_time(0.0)
{
    m_spriteModel = dynamic_cast<SpriteModel*>(model.get());
}

void SpriteRenderer::setModel(std::shared_ptr<Model> model) {
	Renderer::setModel(model);
	m_spriteModel = dynamic_cast<SpriteModel*>(model.get());
	// reset animation
	auto anim = m_animation;
	m_animation.clear();
	setAnimation(anim);
}

void SpriteRenderer::Draw(Shader * s) {
    if (s->getShaderType() == m_model->getMesh(0)->getShaderType()) {
        const auto& frameInfo = m_currentAnimInfo->frames[m_frame];
        m_model->getMesh(0)->draw(s, frameInfo.offset, frameInfo.count);
    }


}

void SpriteRenderer::Update(double dt) {
    m_time += dt;
    if (m_time > m_currentAnimInfo->frames[m_frame].time) {
        // reset timer
        m_time = m_time - m_currentAnimInfo->frames[m_frame].time;
        // update frame
        if (m_playForward) {
            if (m_frame == m_currentAnimInfo->frames.size() - 1) {
                m_frame = (m_currentAnimInfo->loop ? m_currentAnimInfo->loopFrame : m_frame);
                m_complete = true;
            } else {
                m_frame++;
            }
//            if (m_frame >= m_currentAnimInfo->frames.size()) {
//                m_frame = 0;
//            }
        } else {
            m_frame--;
            if (m_frame < 0) {
                m_frame = m_currentAnimInfo->frames.size() - 1;
                m_complete = true;
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
    m_animation = anim;

}

std::type_index SpriteRenderer::GetType() {
    return std::type_index(typeid(Renderer));
}