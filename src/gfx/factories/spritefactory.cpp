#include <gfx/simplemodel.h>
#include <gfx/compositemodel.h>
#include <gfx/spritefactory.h>
#include <gfx/components/renderer.h>
#include <gfx/components/animator.h>
#include <gfx/engine.h>

std::unique_ptr<Entity> SpriteFactory::Create (luabridge::LuaRef& ref) {
    LuaTable table(ref);
    std::string tag = table.Get<std::string>("tag");
    std::string name = table.Get<std::string>("name");

    
    std::string modelId = table.Get<std::string>("model");
    auto model = Engine::get().GetAssetManager().GetModel(modelId);
    auto entity = Create(model);
    
    if (table.HasKey("anim")) {
        std::string anim = table.Get<std::string>("anim");
        auto animator = entity->GetComponent<Animator>();
        animator->SetAnimation(anim);
    }
    
    // set the position (default origin)
    glm::vec3 pos = table.Get<glm::vec3>("pos", glm::vec3(0.0f));
    bool flip = table.Get<bool>("flipx", false);
    entity->SetPosition(pos);
    entity->SetFlipX(flip);
  
    auto factory = Engine::get().GetSceneFactory();
    
    // additional components
    if (table.HasKey("components")) {
        luabridge::LuaRef c = table.Get<luabridge::LuaRef>("components");
        for (int i = 0; i < c.length(); ++i) {
            luabridge::LuaRef rcomponent = c[i+1];
            auto component = factory->GetShared<Component>(rcomponent);
            entity->AddComponent(component);
        }
    }
    
    if (!tag.empty()) {
        entity->SetTag(tag);
    }
    if (!name.empty()) {
        entity->SetName(name);
    }

    return entity;
}

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
    //auto& assetManager = Engine::get().GetAssetManager();

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
