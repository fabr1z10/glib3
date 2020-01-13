#include <monkey/components/spriterenderer.h>


SpriteRenderer::SpriteRenderer(std::shared_ptr<IModel> model) : Renderer(), m_animator(nullptr) {
    m_model = std::dynamic_pointer_cast<SpriteModel>(model);
    m_baseModel = model.get();
}

SpriteRenderer::SpriteRenderer(const SpriteRenderer & orig) : Renderer(orig), m_model(orig.m_model) {}


std::shared_ptr<Component> SpriteRenderer::clone() const {
    return std::make_shared<SpriteRenderer>(*this);
}


void SpriteRenderer::Start() {
    m_animator = dynamic_cast<Animator*>(m_entity->GetComponent<IAnimator>());

}
void SpriteRenderer::Draw(Shader * shader) {
    Renderer::Draw(shader);
    const auto* frameInfo = m_animator->getFrameInfo();
    if (frameInfo != nullptr) {
        m_model->Draw(shader, frameInfo->offset, frameInfo->count);
    }
}

std::type_index SpriteRenderer::GetType() {
    return std::type_index(typeid(Renderer));
}

void SpriteRenderer::SetModel(std::shared_ptr<IModel> model) {
    m_model = std::dynamic_pointer_cast<SpriteModel>(model);
    m_baseModel = m_model.get();

}

