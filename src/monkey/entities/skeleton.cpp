#include <monkey/entities/skeleton.h>
#include <monkey/engine.h>
#include <monkey/components/renderer.h>
#include <monkey/skeletal/skanimator.hpp>
#include <monkey/skeletal/animation/skanimator2.hpp>


Skeleton::Skeleton(const ITab& t) : Entity(t) {
    // TODO restore
//
//    auto* factory = Engine::get().GetSceneFactory();
//    auto modelId = t.get<pybind11::object>("model");
//
//    //    auto modelId = t.get<std::string>("model");auto model = factory->make2<IModel>(t.get<PyDict>("model"));
//    auto model = Engine::get().GetAssetManager().get<Model>(modelId);
//
//    auto speedUp = t.get<float>("speed_up", 1.0f);
//
//    auto renderer = std::make_shared<Renderer>(model);
//
//	auto depth = static_cast<GLenum>(t.get<int>("depth", GL_LESS));
//	renderer->setDepthFunc(depth);
//    // renderer->setForcedZ(0.0);
//
//    this->AddComponent(renderer);
//
//    auto anim = t.get<std::string>("anim", "");
//    auto animator = std::make_shared<SkAnimator>(model);
//
//    animator->setSpeedUp(speedUp);
//
//
//    AddComponent(animator);

}

Skeleton2::Skeleton2(const ITab& t) : Entity(t) {

    auto modelId = t.get<std::string>("model");
    auto model = Engine::get().GetAssetManager().get<Model>(modelId);

    auto renderer = std::make_shared<Renderer>(model);
    this->AddComponent(renderer);

//    auto anim = t.get<std::string>("anim", "");
//    auto animator = std::make_shared<SkeletalAnimator>(model);
//    animator->SetInitialAnimation(anim);
//    AddComponent(animator);

}