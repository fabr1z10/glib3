#include <monkey/entities/sprite.h>
#include <monkey/lua/luatable.h>
#include <monkey/engine.h>

#include <monkey/components/spriterenderer.h>
#include <monkey/components/animator.h>

Sprite::Sprite(const ITable & t) : Entity(t) {
    auto modelId = t.get<std::string>("model");
    std::cerr << "model = " << modelId << "\n";
    auto model = Engine::get().GetAssetManager().GetModel(modelId);
    auto renderer = std::make_shared<SpriteRenderer>(model);
    auto animator = std::make_shared<Animator>(model);
    std::cout << "pos = " << GetLocalTransform()[3][0]<<" " << GetLocalTransform()[3][2] <<"\n";
    AddComponent(renderer);
    AddComponent(animator);

    if (t.hasKey("anim")) {
        auto anim = t.get<std::string>("anim");
        animator->SetInitialAnimation(anim);
    } else {
        animator->SetInitialAnimation(model->GetDefaultAnimation());
    }

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
