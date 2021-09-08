#include <monkey/components/spriterenderer.h>


SpriteRenderer::SpriteRenderer(std::shared_ptr<IModel> model) : Renderer(), m_animator(nullptr) {
    m_model = std::dynamic_pointer_cast<SpriteModel>(model);
    m_baseModel = model.get();
}


void SpriteRenderer::Start() {
    m_animator = dynamic_cast<Animator*>(m_entity->GetComponent<IAnimator>());

}

void SpriteRenderer::Draw(Shader * shader) {
    Renderer::Draw(shader);
    const auto* frameInfo = m_animator->getFrameInfo();
    if (frameInfo != nullptr) {
        m_model->draw(shader, frameInfo->offset, frameInfo->count);
    }

}

std::type_index SpriteRenderer::GetType() {
    return std::type_index(typeid(Renderer));
}

void SpriteRenderer::SetModel(std::shared_ptr<IModel> model) {
    m_model = std::dynamic_pointer_cast<SpriteModel>(model);
    m_baseModel = m_model.get();

}

