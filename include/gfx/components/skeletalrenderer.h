#pragma once

#include <gfx/components/renderer.h>
#include <gfx/model/skeletalmodel.h>
#include <gfx/components/skeletalanimator.h>

// a sprite renderer requires a spritemodel
class SkeletalRenderer : public Renderer {
public:
    SkeletalRenderer (std::shared_ptr<IModel>);
    void Draw(Shader*) override;
    void Start() override;
    std::type_index GetType() override;
    ShaderType GetShaderType() const override;
private:
    SkeletalModel* m_model;
    SkeletalAnimator* m_animator;
};