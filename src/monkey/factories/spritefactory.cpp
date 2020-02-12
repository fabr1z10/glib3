#include <monkey/model/spritemodel.h>
#include <monkey/spritefactory.h>
#include <monkey/components/spriterenderer.h>
#include <monkey/components/animator.h>
#include <monkey/engine.h>

std::shared_ptr<Entity> SpriteFactory::Create (luabridge::LuaRef& ref) {
    LuaTable table(ref);
    std::string tag = table.Get<std::string>("tag", "");
    std::string name = table.Get<std::string>("name", "");

    
    std::string modelId = table.Get<std::string>("model");
    auto model = Engine::get().GetAssetManager().GetModel(modelId);
    auto entity = Create(model);
    
    if (table.HasKey("anim")) {
        std::string anim = table.Get<std::string>("anim");
        auto animator = entity->GetComponent<IAnimator>();
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
            auto component = factory->make<Component>(rcomponent);
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
            auto childEntity = factory->make<Entity>(child);
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
    auto entity = std::make_shared<Entity>();
    auto renderer = std::make_shared<SpriteRenderer>(model);
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
//        renderer->SetModel(mc.model->GetModel());
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
