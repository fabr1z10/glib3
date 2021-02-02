#include <monkey/entities/skeleton.h>
#include <monkey/engine.h>
#include <monkey/skeletal/skrenderer.hpp>
#include <monkey/skeletal/skanimator.hpp>


Skeleton::Skeleton(const ITable& t) : Entity(t) {

    auto* factory = Engine::get().GetSceneFactory();

    auto model = factory->make2<IModel>(t.get<PyDict>("model"));

    auto speedUp = t.get<float>("speed_up", 1.0f);

    auto renderer = std::make_shared<SkRenderer>(model);

	auto depth = static_cast<GLenum>(t.get<int>("depth", GL_LESS));
	renderer->setDepthFunc(depth);
    // renderer->setForcedZ(0.0);

    this->AddComponent(renderer);

    auto anim = t.get<std::string>("anim", "");
    auto animator = std::make_shared<SkAnimator>(model);
    animator->setSpeedUp(speedUp);

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