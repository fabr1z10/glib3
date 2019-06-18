#include <gfx/simplemodel.h>
#include <gfx/compositemodel.h>
#include <gfx/spritefactory.h>
#include <gfx/components/renderer.h>
#include <gfx/components/animator.h>
#include <gfx/engine.h>

std::shared_ptr<Entity> SpriteFactory::Create (luabridge::LuaRef& ref) {
    LuaTable table(ref);
    std::string tag = table.Get<std::string>("tag", "");
    std::string name = table.Get<std::string>("name", "");

    
    std::string modelId = table.Get<std::string>("model");
    auto model = Engine::get().GetAssetManager().GetModel(modelId);
    auto entity = Create(model);
    
    if (table.HasKey("anim")) {
        std::string anim = table.Get<std::string>("anim");
        auto animator = entity->GetComponent<Animator>();
        animator->SetInitialAnimation(anim);
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
            auto component = factory->makeComponent(rcomponent);
            entity->AddComponent(component);
        }
    }
    
    if (!tag.empty()) {
        entity->SetTag(tag);
    }
    if (!name.empty()) {
        entity->SetName(name);
    }

    if (table.HasKey("children")) {
        luabridge::LuaRef c = table.Get<luabridge::LuaRef>("children");
        for (int i = 0; i < c.length(); ++i) {
            luabridge::LuaRef child = c[i+1];
            auto childEntity = factory->makeEntity(child);
            if (childEntity != nullptr)
                entity->AddChild(childEntity);
        }
    }
    if (table.HasKey("scale")) {
        float scale = table.Get<float>("scale");
        entity->SetScale(scale);
    }
    return entity;
}

std::shared_ptr<Entity> SpriteFactory::Create (const std::string& name) {
    auto model = Engine::get().GetAssetManager().GetModel(name);
    return SpriteFactory::Create(model);
}

std::shared_ptr<Entity> SpriteFactory::Create (std::shared_ptr<IModel> model) {
    auto entity = Ref::Create<Entity>();
    auto renderer = Ref::Create<Renderer>();
    renderer->SetMesh(model->GetMesh());
    auto animator = std::make_shared<Animator>(model);
    entity->AddComponent(renderer);
    entity->AddComponent(animator);
    return entity;
}



//std::shared_ptr<Entity> SpriteFactory::Create (std::shared_ptr<CompositeModel> model) {
//    auto entity = Ref::Create<Entity>();
//    //auto& assetManager = Engine::get().GetAssetManager();
//
//    std::unordered_map<std::string, std::shared_ptr<Entity>> entities;
//
//    auto animator = Ref::Create<Animator>(model);
//    const auto& components = model->GetComponents();
//    for (const auto& component : components) {
//        const ModelComponent& mc = component.second;
//        auto ie = Ref::Create<Entity>();
//        ie->SetName(mc.name);
//        //ie->SetPosition(mc.pos);
//        auto renderer = Ref::Create<Renderer>();
//        renderer->SetMesh(mc.model->GetMesh());
//        ie->AddComponent(renderer);
//        entities[mc.name] = ie;
//    }
//    entity->AddComponent(animator);
//    // build the hierarchy
//    for (auto& component : components) {
//        const ModelComponent& mc = component.second;
//        auto ptr = entities.at(mc.name);
//        if (mc.parent.empty()) {
//            entity->AddChild(ptr);
//        } else {
//            entities.at(mc.parent)->AddChild(ptr);
//        }
//    }
//
//    return entity;
//}

//
//Sprite::Sprite(std::shared_ptr<Model> model) {
//
//    auto renderer
//
//}
