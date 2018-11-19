#include <gfx/factories.h>
#include <gfx/math/geom.h>
#include <gfx/engine.h>
#include <gfx/textmesh.h>
#include <gfx/components/renderer.h>
#include <gfx/entities/textview.h>

std::unique_ptr<Entity> EntityFactory::Create(luabridge::LuaRef& ref) {

    auto entity = std::unique_ptr<Entity>(new Entity);

    LuaTable item(ref);
    std::string tag = item.Get<std::string>("tag", "");
    std::string name = item.Get<std::string>("name", "");
    if (!tag.empty()) entity->SetTag(tag);
    if (!name.empty()) entity->SetName(name);
    bool active = item.Get<bool>("active", true);
    glm::vec3 pos = item.Get<glm::vec3>("pos", glm::vec3(0.0f));
    if (item.HasKey("angle")) {
        float angle = item.Get<float>("angle",0.0f);
        entity->SetPosition(pos, deg2rad* angle);
    } else {
        entity->SetPosition(pos);
    }
    if (item.HasKey("scale")) {
        float scale = item.Get<float>("scale");
        entity->SetScale(scale);
    }
    auto factory = Engine::get().GetSceneFactory();

    // setup camera
    if (item.HasKey("camera")) {
        luabridge::LuaRef cam = item.Get<luabridge::LuaRef>("camera");
        auto camera = factory->GetShared<Camera>(cam);
        entity->SetCamera(camera);
    }

    // add components
    if (item.HasKey("components")) {
        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("components");
        for (int i = 0; i < c.length(); ++i) {
            luabridge::LuaRef rcomponent = c[i+1];
            auto component = factory->GetShared<Component>(rcomponent);
            entity->AddComponent(component);
        }

    }

    if (item.HasKey("children")) {
        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("children");
        for (int i = 0; i < c.length(); ++i) {
            luabridge::LuaRef child = c[i+1];
            auto childEntity = factory->GetShared<Entity>(child);
            if (childEntity != nullptr)
                entity->AddChild(childEntity);
        }
    }
    if (active == false) {
        std::cout << "ciaos";
    }
    entity->SetActive(active);
    return std::move(entity);
}

std::unique_ptr<Entity> ButtonFactory::Create(luabridge::LuaRef &ref) {

    LuaTable table(ref);
    auto parent = std::unique_ptr<Entity>(new Entity);
    std::string tag = table.Get<std::string>("tag", "");
    std::string name = table.Get<std::string>("name", "");
    if (!tag.empty()) parent->SetTag(tag);
    if (!name.empty()) parent->SetName(name);
    bool active = table.Get<bool>("active", true);
    glm::vec3 pos = table.Get<glm::vec3>("pos", glm::vec3(0.0f));
    if (table.HasKey("angle")) {
        float angle = table.Get<float>("angle",0.0f);
        parent->SetPosition(pos, deg2rad* angle);
    } else {
        parent->SetPosition(pos);
    }



}

std::unique_ptr<Entity> OutlineTextFactory::Create(luabridge::LuaRef &ref) {

    LuaTable table(ref);
    auto parent = std::unique_ptr<Entity>(new Entity);
    std::string tag = table.Get<std::string>("tag", "");
    std::string name = table.Get<std::string>("name", "");
    if (!tag.empty()) parent->SetTag(tag);
    if (!name.empty()) parent->SetName(name);
    bool active = table.Get<bool>("active", true);
    glm::vec3 pos = table.Get<glm::vec3>("pos", glm::vec3(0.0f));
    if (table.HasKey("angle")) {
        float angle = table.Get<float>("angle",0.0f);
        parent->SetPosition(pos, deg2rad* angle);
    } else {
        parent->SetPosition(pos);
    }

    std::string font = table.Get<std::string>("font");
    float size = table.Get<float>("size");
    std::string text = table.Get<std::string>("id");
    TextAlignment align = table.Get<TextAlignment>("align", TOP_LEFT);
    glm::vec4 fontColor = table.Get<glm::vec4>("fontcolor", glm::vec4(255.0f));
    glm::vec4 outlineColor = table.Get<glm::vec4>("outlinecolor", glm::vec4(255.0f));
    fontColor /= 255.0f;
    outlineColor /= 255.0f;
    Font* f = Engine::get().GetAssetManager().GetFont(font);
    auto mesh = std::make_shared<TextMesh>(f, text, size, align);
    //glm::vec2 offset = mesh->getOffset();
    glm::vec2 outlineOffsets[] = {{0, 0}, {-1, 0}, {-1,1}, {0, 1}, {1,1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
    for (int i =0; i < 9; ++i) {
        auto entity = std::make_shared<Entity>();
        auto renderer = std::make_shared<Renderer>();
        renderer->SetMesh(mesh);
        entity->SetPosition(glm::vec3(outlineOffsets[i] * 0.5f, i == 0 ? 0 : -1));
        renderer->SetTint(i==0 ? fontColor : outlineColor);
        //renderer->SetRenderingTransform(glm::translate(glm::vec3(offset, 0.0f)));
        //entity->AddComponent(renderer);
        parent->AddChild(entity);
    }
    return std::move(parent);
}

std::unique_ptr<Entity> TextViewFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string tag = table.Get<std::string>("tag", "");
    glm::vec2 pos = table.Get<glm::vec2>("pos");
    //glm::vec4 viewport = table.Get<glm::vec4>("viewport");
    glm::vec2 size = table.Get<glm::vec2>("size");
    float fontSize = table.Get<float>("font_size");
    int lines = table.Get<int>("lines");
    //float deltax = table.Get<float>("deltax", 0.0f);
    luabridge::LuaRef factory = table.Get<luabridge::LuaRef>("factory");
    //glm::vec4 color = table.Get<glm::vec4>("color", glm::vec4(255.0f));
    //color /= 255.0f;
    //std::string font = table.Get<std::string>("font");
    auto r = std::unique_ptr<TextView>(new TextView(pos, size.x, size.y, fontSize, lines, factory));
    r->SetTag(tag);
    return r;

}
