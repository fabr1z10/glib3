#include <monkey/entities/sprite.h>
#include <monkey/lua/luatable.h>
#include <monkey/engine.h>

#include <monkey/components/spriterenderer.h>
#include <monkey/components/animator.h>

Sprite::Sprite(const PyTable & t) : Entity(t) {
}

Sprite::Sprite(const LuaTable & t) : Entity(t) {

    auto modelId = t.Get<std::string>("model");
    auto model = Engine::get().GetAssetManager().GetModel(modelId);

    auto renderer = std::make_shared<SpriteRenderer>(model);
    auto animator = std::make_shared<Animator>(model);

    AddComponent(renderer);
    AddComponent(animator);

    if (t.HasKey("anim")) {
        auto anim = t.Get<std::string>("anim");
        animator->SetInitialAnimation(anim);
    }
}
