#include <gfx/model.h>
#include <gfx/entity.h>
#include <gfx/engine.h>
#include <gfx/components/renderer.h>

std::shared_ptr<Entity> Model::Create() {
    auto entity = std::make_shared<Entity>();
    auto& assetManager = Engine::get().GetAssetManager();
    std::unordered_map<std::string, std::shared_ptr<Entity>> entities;

    for (auto& component : m_components) {
        auto entity = std::make_shared<Entity>();
        entity->SetName(component.name);
        entity->SetPosition(component.pos);
        auto renderer = std::make_shared<Renderer>();
        renderer->SetMesh(assetManager.GetMesh(component.mesh));
        entity->AddComponent(renderer);
        entities[component.name] = entity;
    }

    // build the hierarchy
    for (auto& component : m_components) {
        auto ptr = entities.at(component.name);
        if (component.parent.empty()) {
            entity->AddChild(ptr);
        } else {
            entities.at(component.parent)->AddChild(ptr);
        }
    }

    return entity;


}