#pragma once

#include <monkey/components/renderer.h>
#include <monkey/model/skeletalmodel.h>
#include <monkey/components/skeletalanimator.h>

// a sprite renderer requires a spritemodel
class SkeletalRenderer : public Renderer {
public:
    SkeletalRenderer (std::shared_ptr<IModel>);
    SkeletalRenderer (const SkeletalRenderer&);
    std::shared_ptr<Component> clone() const override;
    void SetModel(std::shared_ptr<IModel> mesh) override;

    void Draw(Shader*) override;
    void Start() override;
    std::type_index GetType() override;
    ShaderType GetShaderType() const override;
private:
    SkeletalModel* m_model;
    SkeletalAnimator* m_animator;
};