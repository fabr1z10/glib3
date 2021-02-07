#pragma once

#include <monkey/components/renderer.h>
#include <monkey/skeletal/skmodel.hpp>

class IAnimator;

class SkRenderer : public Renderer {
public:
    // requires a skmodel
    SkRenderer (std::shared_ptr<IModel>);
    void SetModel(std::shared_ptr<IModel> mesh) override;

    void Draw(Shader*) override;
    void Start() override;

    std::type_index GetType() override;
    ShaderType GetShaderType() const override;
    const glm::mat4& getJointTransform(size_t);
private:
    IAnimator* m_ic;
    SkModel* m_model;
    std::vector<glm::mat4> m_jointTransforms;

};

inline const glm::mat4 & SkRenderer::getJointTransform(size_t i) {
    return m_jointTransforms[i];
}