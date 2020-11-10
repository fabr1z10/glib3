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
private:
    IAnimator* m_ic;
    SkModel* m_model;
};