#include <monkey/skeletal/skrenderer.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <monkey/components/ianimator.h>

SkRenderer::SkRenderer(std::shared_ptr<IModel> model) : Renderer() {
    m_model = dynamic_cast<SkModel*>(model.get());
    m_baseModel = model.get();

}

void SkRenderer::SetModel(std::shared_ptr<IModel> model) {
    m_model = dynamic_cast<SkModel*>(model.get());
    m_baseModel = model.get();
    m_ic->setModel(model);
}


void SkRenderer::Start() {
    m_ic = m_entity->GetComponent<IAnimator>();
}

void SkRenderer::Draw(Shader * shader) {
    Renderer::Draw(shader);
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
