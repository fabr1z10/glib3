#include <gfx/components/skeletalrenderer.h>
#include <gfx/entity.h>

SkeletalRenderer::SkeletalRenderer(std::shared_ptr<IModel> model) : Renderer() {
    m_model = std::dynamic_pointer_cast<SkeletalModel>(model).get();
}

void SkeletalRenderer::Start() {
    m_animator = dynamic_cast<SkeletalAnimator*>(m_entity->GetComponent<IAnimator>());

}

void SkeletalRenderer::Draw(Shader * shader) {
    Renderer::Draw(shader);
    const auto& angles = m_animator->getAngles();
    m_model->Draw(shader, angles);
}

std::type_index SkeletalRenderer::GetType() {
    return std::type_index(typeid(Renderer));
}

ShaderType SkeletalRenderer::GetShaderType() const {
    return (m_model == nullptr ? ShaderType::NONE : m_model->GetShaderType());
}

