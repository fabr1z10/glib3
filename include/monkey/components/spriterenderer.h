#pragma once

#include <monkey/components/renderer.h>
#include <monkey/model/spritemodel.h>
#include <monkey/components/animator.h>

// a sprite renderer requires a spritemodel
class SpriteRenderer : public Renderer {
public:
    SpriteRenderer (std::shared_ptr<IModel>);
    void Draw(Shader*) override;
    std::type_index GetType() override;
    void SetModel(std::shared_ptr<IModel> mesh) override;
    void Start() override;

private:
    std::shared_ptr<SpriteModel> m_model;
    Animator* m_animator;
};