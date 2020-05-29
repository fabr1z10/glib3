#pragma once

#include <monkey/components/renderer.h>
#include <monkey/model/skeletalmodel.h>
#include <monkey/model/skeletalmodel2.h>

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

// a sprite renderer requires a spritemodel
class SkeletalRenderer2 : public Renderer {
public:
    SkeletalRenderer2 (std::shared_ptr<IModel>);
    SkeletalRenderer2 (const SkeletalRenderer2&);
    std::shared_ptr<Component> clone() const override;
    void SetModel(std::shared_ptr<IModel> mesh) override;

    void Draw(Shader*) override;
    void Start() override;
    std::type_index GetType() override;
    ShaderType GetShaderType() const override;
private:
    SkeletalModel2* m_model;
    //SkeletalAnimator* m_animator;
};