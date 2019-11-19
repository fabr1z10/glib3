#include <gfx/components/skeletalrenderer.h>
#include <gfx/entity.h>

SkeletalRenderer::SkeletalRenderer(std::shared_ptr<IModel> model) : Renderer() {
    m_model = std::dynamic_pointer_cast<SkeletalModel>(model).get();
    m_baseModel = m_model;
}

SkeletalRenderer::SkeletalRenderer(const SkeletalRenderer & orig) : Renderer(orig), m_model(orig.m_model) {}

std::shared_ptr<Component> SkeletalRenderer::clone() const {
    return std::make_shared<SkeletalRenderer>(*this);
}


void SkeletalRenderer::Start() {
    m_animator = dynamic_cast<SkeletalAnimator*>(m_entity->GetComponent<IAnimator>());

}

void SkeletalRenderer::Draw(Shader * shader) {
    Renderer::Draw(shader);
    const auto& angles = m_animator->getAngles();
    m_model->Draw(shader, angles);
    Bounds b = m_model->getDynamicBounds();
    std::cerr << "(" << b.min.x << ", " << b.min.y << ") (" << b.max.x << ", " << b.max.y << ")\n";
}

std::type_index SkeletalRenderer::GetType() {
    return std::type_index(typeid(Renderer));
}

ShaderType SkeletalRenderer::GetShaderType() const {
    return (m_model == nullptr ? ShaderType::NONE : m_model->GetShaderType());
}

void SkeletalRenderer::SetModel(std::shared_ptr<IModel> model) {
    m_model = std::dynamic_pointer_cast<SkeletalModel>(model).get();
    m_baseModel = m_model;
}