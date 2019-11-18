#include <gfx/components/spriterenderer.h>


SpriteRenderer::SpriteRenderer(std::shared_ptr<IModel> model) : Renderer() {
    m_model = std::dynamic_pointer_cast<SpriteModel>(model).get();
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
