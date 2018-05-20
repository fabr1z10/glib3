#include <monkey/monkeyfactory.h>
#include <monkey/monkey.h>
#include <iostream>
#include <gfx/renderer.h>
#include <gfx/quadmesh.h>
#include <gfx/renderingengine.h>

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
    
    // create the cameras
    auto engineNode = std::make_shared<Entity>();
    auto renderingEngine = std::make_shared<RenderingEngine>();
    luabridge::LuaRef cams = luabridge::getGlobal(LuaWrapper::L, "cameras");
    for (int i = 0; i < cams.length(); ++i) {
        luabridge::LuaRef cam = cams[i+1];
        LuaTable tcam(cam);
        std::string camType = tcam.Get<std::string>("type");
        glm::vec2 pos = tcam.Get<glm::vec2>("pos", glm::vec2(0.0f));
        if (camType == "ortho") {
            // orhographic camera
            glm::vec2 size = tcam.Get<glm::vec2>("size");
            int layer = tcam.Get<int>("layer");
            glm::vec4 bounds = tcam.Get<glm::vec4>("bounds", glm::vec4(0.0));
            glm::vec4 viewport = tcam.Get<glm::vec4>("viewport", glm::vec4(0.0f, 0.0f, Engine::get().GetDeviceSize()));
            auto cam = std::unique_ptr<OrthographicCamera> (new OrthographicCamera(size.x, size.y, layer, viewport));
            if (bounds != glm::vec4(0.0f))
                cam->SetBounds(bounds[0], bounds[2], bounds[1], bounds[3]);
            cam->SetPosition(glm::vec3(pos, 5.0f), glm::vec3(0,0,-1), glm::vec3(0,1,0));
            renderingEngine->AddCamera(std::move(cam));
        }
    }
    renderingEngine->AddShader(TEXTURE_SHADER);
    renderingEngine->AddShader(COLOR_SHADER);
    renderingEngine->AddShader(TEXT_SHADER);
    engineNode->AddComponent(renderingEngine);
    entity->AddChild(engineNode);
    
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
        int layer = item.Get<int>("layer");
        // children
        if (item.HasKey("children")) {
            luabridge::LuaRef c = item.Get<luabridge::LuaRef>("children");
            ReadItems (c, entity.get());
        }
        if (item.HasKey("gfx")) {
            luabridge::LuaRef c = item.Get<luabridge::LuaRef>("gfx");
            ReadGfxComponent(c, entity.get());
        }
        entity->SetLayer(layer);
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
        renderer->SetMesh(mesh);
    }
    parent->AddComponent(renderer);
    
}
