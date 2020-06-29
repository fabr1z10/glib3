#include <monkey/skeletal/skrenderer.hpp>
#include <glm/gtc/type_ptr.hpp>

SkRenderer::SkRenderer(std::shared_ptr<IModel> model) {
    m_model = dynamic_cast<SkModel*>(model.get());
}

std::shared_ptr<Component> SkRenderer::clone() const {
    return std::make_shared<SkRenderer>(*this);
}

void SkRenderer::SetModel(std::shared_ptr<IModel> model) {
    m_model = dynamic_cast<SkModel*>(model.get());
    m_baseModel = model.get();
}


SkRenderer::SkRenderer(const SkRenderer & orig): Renderer(orig), m_model(orig.m_model) {}

void SkRenderer::Start() {}

void SkRenderer::Draw(Shader * shader) {

    // we need to send the bone transforms to the shader
    auto boneId = shader->GetUniformLocation(BONES);

    auto jointTransforms = m_model->getJointTransforms();

    glUniformMatrix4fv(boneId, jointTransforms.size(), GL_FALSE, glm::value_ptr(jointTransforms[0]));

    m_model->Draw(shader);

}

ShaderType SkRenderer::GetShaderType() const {
    return SKELETAL_SHADER;
}


std::type_index SkRenderer::GetType() {
    return std::type_index(typeid(Renderer));
}
