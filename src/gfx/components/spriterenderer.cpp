#include <gfx/components/spriterenderer.h>


SpriteRenderer::SpriteRenderer(std::shared_ptr<IModel> model) : Renderer() {
    m_model = std::dynamic_pointer_cast<SpriteModel>(model).get();
}

SpriteRenderer::SpriteRenderer(const SpriteRenderer & orig) : Renderer(orig), m_model(orig.m_model) {}

std::shared_ptr<Component> SpriteRenderer::clone() const {
    return std::make_shared<SpriteRenderer>(*this);
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
    m_model = std::dynamic_pointer_cast<SpriteModel>(model).get();
    m_baseModel = m_model;

}

