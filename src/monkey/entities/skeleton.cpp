#include <monkey/entities/skeleton.h>
#include <monkey/engine.h>
#include <monkey/skeletal/skrenderer.hpp>
#include <monkey/skeletal/skanimator.hpp>


Skeleton::Skeleton(const ITable& t) : Entity(t) {

    auto modelId = t.get<std::string>("model");
    auto model = Engine::get().GetAssetManager().GetModel(modelId);

    auto renderer = std::make_shared<SkRenderer>(model);
    this->AddComponent(renderer);

    auto anim = t.get<std::string>("anim", "");
    auto animator = std::make_shared<SkAnimator>(model);

    // check if we have offset


    if (!anim.empty())
        animator->SetInitialAnimation(anim);
    AddComponent(animator);

}

Skeleton2::Skeleton2(const ITable& t) : Entity(t) {

    auto modelId = t.get<std::string>("model");
    auto model = Engine::get().GetAssetManager().GetModel(modelId);

    auto renderer = std::make_shared<SkRenderer>(model);
    this->AddComponent(renderer);

//    auto anim = t.get<std::string>("anim", "");
//    auto animator = std::make_shared<SkeletalAnimator>(model);
//    animator->SetInitialAnimation(anim);
//    AddComponent(animator);

}