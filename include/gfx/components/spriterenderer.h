#pragma once

#include <gfx/components/renderer.h>
#include <gfx/model/spritemodel.h>
#include <gfx/components/animator.h>

// a sprite renderer requires a spritemodel
class SpriteRenderer : public Renderer {
public:
    SpriteRenderer (std::shared_ptr<IModel>);
    SpriteRenderer (const SpriteRenderer&);
    std::shared_ptr<Component> clone() const override;
    void Draw(Shader*) override;
    std::type_index GetType() override;
    void SetModel(std::shared_ptr<IModel> mesh) override;

private:
    SpriteModel* m_model;
    Animator* m_animator;
};