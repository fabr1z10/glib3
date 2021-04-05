#include <monkey/entities/sprite.h>
#include <monkey/engine.h>

#include <monkey/components/spriterenderer.h>
#include <monkey/components/animator.h>

Sprite::Sprite(const ITab& t) : Entity(t) {
    auto modelId = t.get<std::string>("model");
    auto blend = static_cast<Blend>(t.get<int>("blend", 0));
	auto depth = static_cast<GLenum>(t.get<int>("depth", GL_LESS));
    auto model = Engine::get().GetAssetManager().GetModel(modelId);
    auto renderer = std::make_shared<SpriteRenderer>(model);
    renderer->setDepthFunc(depth);
    renderer->setBlendMode(blend);
    auto animator = std::make_shared<Animator>(model);
    AddComponent(renderer);
    AddComponent(animator);

    if (t.has("anim")) {
        auto anim = t.get<std::string>("anim");
        animator->SetInitialAnimation(anim);
    } else {
        animator->SetInitialAnimation(model->GetDefaultAnimation());
    }

}

