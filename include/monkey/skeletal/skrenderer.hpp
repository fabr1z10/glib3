#pragma once

#include <monkey/components/renderer.h>
#include <monkey/skeletal/skmodel.hpp>

class SkRenderer : public Renderer {
public:
    // requires a skmodel
    SkRenderer (std::shared_ptr<IModel>);
    SkRenderer (const SkRenderer&);
    std::shared_ptr<Component> clone() const override;

    void SetModel(std::shared_ptr<IModel> mesh) override;

    void Draw(Shader*) override;
    void Start() override;

    std::type_index GetType() override;
    ShaderType GetShaderType() const override;
private:
    SkModel* m_model;
};