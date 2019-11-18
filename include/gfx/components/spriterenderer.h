#pragma once

#include <gfx/components/renderer.h>
#include <gfx/model/spritemodel.h>
#include <gfx/components/animator.h>

// a sprite renderer requires a spritemodel
class SpriteRenderer : public Renderer {
public:
    SpriteRenderer (std::shared_ptr<IModel>);
    void Draw(Shader*) override;
    std::type_index GetType() override;

private:
    SpriteModel* m_model;
    Animator* m_animator;
};