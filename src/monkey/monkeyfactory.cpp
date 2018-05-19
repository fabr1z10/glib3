#include <monkey/monkeyfactory.h>
#include <monkey/monkey.h>
#include <iostream>
#include <gfx/renderer.h>
#include <gfx/quadmesh.h>

std::shared_ptr<Entity> MonkeyFactory::Create() {

    auto entity = std::make_shared<Entity>();
    
    // get current room
    Monkey& m = Monkey::get();
    std::string room = m["variables"].Get<std::string>("_room");
    std::cout << "Loading room "<< room << std::endl;
    LuaWrapper::Load(Engine::get().GetAssetManager().GetDirectory() + "rooms/" + room + ".lua");
    
    // Creating the room
    luabridge::LuaRef scene = luabridge::getGlobal(LuaWrapper::L, "scene");
    ReadItems (scene, entity.get());
    return entity;

}

void MonkeyFactory::ReadItems(luabridge::LuaRef& scene, Entity* parent) {
    for (int i = 0; i < scene.length(); ++i) {
        // create new entity
        luabridge::LuaRef r = scene[i+1];
        LuaTable item(r);
        auto entity = std::make_shared<Entity>();
        glm::vec3 pos = item.Get<glm::vec3>("pos", glm::vec3(0.0f));
        entity->SetPosition(pos);
        // children
        if (item.HasKey("children")) {
            luabridge::LuaRef c = item.Get<luabridge::LuaRef>("children");
            ReadItems (c, entity.get());
        }
        if (item.HasKey("gfx")) {
            luabridge::LuaRef c = item.Get<luabridge::LuaRef>("gfx");
            ReadGfxComponent(c, entity.get());
        }
        parent->AddChild(entity);
    }
    
}

void MonkeyFactory::ReadGfxComponent(luabridge::LuaRef &ref, Entity *parent) {
    LuaTable table(ref);
    auto renderer = std::make_shared<Renderer>();
    if (table.HasKey("image")) {
        std::string image = table.Get<std::string>("image");
        float w = table.Get<float>("width");
        float h = table.Get<float>("height");
        auto mesh = std::make_shared<QuadMesh>(image, w, h);
    }
    
}
