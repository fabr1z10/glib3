#include <gfx/simplemodel.h>
#include <gfx/compositemodel.h>
#include <gfx/spritefactory.h>
#include <gfx/components/renderer.h>
#include <gfx/components/animator.h>
#include <gfx/engine.h>

std::unique_ptr<Entity> SpriteFactory::Create (std::shared_ptr<IModel> mesh) {
    switch (mesh->GetType()) {
        case ModelType::SIMPLESPRITE: {
            auto ptr = std::dynamic_pointer_cast<SimpleModel>(mesh);
            return Create(ptr);
        }
        case ModelType::COMPOSITESPRITE: {
            auto ptr = std::dynamic_pointer_cast<CompositeModel>(mesh);
            return Create(ptr);
        }
    }
    return nullptr;
}

std::unique_ptr<Entity> SpriteFactory::Create(std::shared_ptr<SimpleModel> model) {

    auto entity = std::unique_ptr<Entity>(new Entity);
    auto renderer = std::make_shared<Renderer>();
    renderer->SetMesh(model->GetMesh());

    auto animator = std::make_shared<Animator>(model);
    entity->AddComponent(renderer);
    entity->AddComponent(animator);
    return entity;
}

std::unique_ptr<Entity> SpriteFactory::Create (std::shared_ptr<CompositeModel> model) {
    auto entity = std::unique_ptr<Entity>(new Entity);
    auto& assetManager = Engine::get().GetAssetManager();

    std::unordered_map<std::string, std::shared_ptr<Entity>> entities;

    auto animator = std::make_shared<Animator>(model);
    const auto& components = model->GetComponents();
    for (const auto& component : components) {
        const ModelComponent& mc = component.second;
        auto ie = std::make_shared<Entity>();
        ie->SetName(mc.name);
        //ie->SetPosition(mc.pos);
        auto renderer = std::make_shared<Renderer>();
        renderer->SetMesh(mc.model->GetMesh());
        ie->AddComponent(renderer);
        entities[mc.name] = ie;
    }
    entity->AddComponent(animator);
    // build the hierarchy
    for (auto& component : components) {
        const ModelComponent& mc = component.second;
        auto ptr = entities.at(mc.name);
        if (mc.parent.empty()) {
            entity->AddChild(ptr);
        } else {
            entities.at(mc.parent)->AddChild(ptr);
        }
    }

    return entity;
}

//
//Sprite::Sprite(std::shared_ptr<Model> model) {
//
//    auto renderer
//
//}