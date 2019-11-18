#include <gfx/components/skeletalrenderer.h>


SkeletalRenderer::SkeletalRenderer(std::shared_ptr<IModel> model) : Renderer() {
    m_model = std::dynamic_pointer_cast<SkeletalModel>(model).get();
}

void SkeletalRenderer::Draw(Shader * shader) {
    Renderer::Draw(shader);
    const auto& angles = m_animator->getAngles();
    m_model->Draw(shader, angles);
}

std::type_index SkeletalRenderer::GetType() {
    return std::type_index(typeid(Renderer));
}
