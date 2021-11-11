#include <monkey/entities/sprite.h>
#include <monkey/engine.h>
#include <monkey/components/renderer.h>

#include <monkey/components/animator.h>

Sprite::Sprite(const ITab& t) : Entity(t) {
//    auto modelId = t.get<std::string>("model");
//    auto blend = static_cast<Blend>(t.get<int>("blend", 0));
//	auto depth = static_cast<GLenum>(t.get<int>("depth", GL_LESS));
//    m_model = std::dynamic_pointer_cast<SpriteModel>(Engine::get().GetAssetManager().get<Model>(modelId));
//    auto renderer = std::make_shared<Renderer>(m_model);
//    renderer->setDepthFunc(depth);
//    renderer->setBlendMode(blend);
//    auto animator = std::make_shared<Animator>(m_model);
//    AddComponent(renderer);
//    AddComponent(animator);
//
//    if (t.has("anim")) {
//        auto anim = t.get<std::string>("anim");
//        animator->SetInitialAnimation(anim);
//    } else {
//        animator->SetInitialAnimation(m_model->getDefaultAnimation());
//    }

}

