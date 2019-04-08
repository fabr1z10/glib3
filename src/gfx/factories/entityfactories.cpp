#include <gfx/factories.h>
#include <gfx/math/geom.h>
#include <gfx/engine.h>
#include <gfx/textmesh.h>
#include <gfx/components/renderer.h>
#include <gfx/entities/textview.h>
#include <gfx/meshfactory.h>
#include <gfx/entities/heightmap.h>
#include <gfx/quadmesh.h>

std::shared_ptr<Entity> EntityFactory::Create(luabridge::LuaRef& ref) {

    auto entity = std::make_shared<Entity>();

    LuaTable item(ref);
    std::string tag = item.Get<std::string>("tag", "");
    //std::cout << "creating " << tag << "\n";
    std::string name = item.Get<std::string>("name", "");
    if (!tag.empty()) entity->SetTag(tag);
    if (!name.empty()) entity->SetName(name);
    bool active = item.Get<bool>("active", true);
    glm::vec3 pos = item.Get<glm::vec3>("pos", glm::vec3(0.0f));
    bool flipx = item.Get<bool>("flipx", false);
    entity->SetFlipX(flipx);
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

        auto camera = factory->makeCam(cam);
        entity->SetCamera(camera);
    }

    // add components
    if (item.HasKey("components")) {
        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("components");
        for (int i = 0; i < c.length(); ++i) {
            luabridge::LuaRef rcomponent = c[i+1];
            auto component = factory->makeComponent(rcomponent);
            entity->AddComponent(component);
        }

    }

    if (item.HasKey("children")) {
        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("children");
        for (int i = 0; i < c.length(); ++i) {
            luabridge::LuaRef child = c[i+1];
            auto childEntity = factory->makeEntity(child);
            if (childEntity != nullptr)
                entity->AddChild(childEntity);
        }
    }
    if (active == false) {
        std::cout << "ciaos";
    }
    entity->SetActive(active);
    return entity;
}

std::shared_ptr<Entity> ButtonFactory::Create(luabridge::LuaRef &ref) {

    LuaTable table(ref);
    auto parent = std::unique_ptr<Entity>(new Entity);
    std::string tag = table.Get<std::string>("tag", "");
    std::string name = table.Get<std::string>("name", "");
    if (!tag.empty()) parent->SetTag(tag);
    if (!name.empty()) parent->SetName(name);
    glm::vec3 pos = table.Get<glm::vec3>("pos", glm::vec3(0.0f));
    if (table.HasKey("angle")) {
        float angle = table.Get<float>("angle",0.0f);
        parent->SetPosition(pos, deg2rad* angle);
    } else {
        parent->SetPosition(pos);
    }

    return parent;

}

std::shared_ptr<Entity> OutlineTextFactory::Create(luabridge::LuaRef &ref) {

    LuaTable table(ref);
    auto parent = std::unique_ptr<Entity>(new Entity);
    std::string tag = table.Get<std::string>("tag", "");
    std::string name = table.Get<std::string>("name", "");
    if (!tag.empty()) parent->SetTag(tag);
    if (!name.empty()) parent->SetName(name);
    //bool active = table.Get<bool>("active", true);
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
    Font* f = Engine::get().GetAssetManager().GetFont(font).get();
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
    return parent;
}

std::shared_ptr<Entity> TextViewFactory::Create(luabridge::LuaRef &ref) {
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
    auto r = std::make_shared<TextView>(pos, size.x, size.y, fontSize, lines, factory);
    r->SetTag(tag);
    return r;

}

std::shared_ptr<Entity> BoxedMessageFactory::Create(luabridge::LuaRef& ref) {
    LuaTable table(ref);

    auto entity = std::make_shared<Entity>();
    std::string tag = table.Get<std::string>("tag");
    if (!tag.empty()) entity->SetTag(tag);
    glm::vec3 pos = table.Get<glm::vec3>("pos");
    entity->SetPosition(pos);
    std::string font = table.Get<std::string>("font");
    std::string message = table.Get<std::string>("message");
    float size = table.Get<float>("size");
    float maxWidth = table.Get<float>("maxwidth");
    float padding = table.Get<float>("padding", 0.0f);
    auto f = Engine::get().GetAssetManager().GetFont(font);
    auto renderer = std::make_shared<Renderer>();
    auto textMesh = std::make_shared<TextMesh>(f.get(), message, size, CENTER, maxWidth);

    //std::string cornerImage = table.Get<std::string>("corner", std::string());
    //std::string borders = table.Get<std::string>("border", std::string());

    auto bounds =textMesh->GetBounds();
    renderer->SetMesh(textMesh);
    glm::vec4 color = table.Get<glm::vec4>("color");
    glm::vec4 bgColor = table.Get<glm::vec4>("bgcolor");
    color/=255.0f;
    bgColor /=255.0f;
    renderer->SetTint(color);
    entity->AddComponent(renderer);

    // create the box
    auto box = std::make_shared<Entity>();
    glm::vec3 extents = bounds.GetExtents();
    auto box_renderer = std::make_shared<Renderer>();
    auto rect = std::make_shared<Rect>(extents.x+2*padding, extents.y+2*padding);
    auto boxMesh = MeshFactorySolid::CreateMesh(*(rect.get()), 0.0f);
    box_renderer->SetMesh(boxMesh);
    box->AddComponent(box_renderer);
    box_renderer->SetTint(bgColor);
    box->SetPosition(glm::vec3(bounds.min.x - padding, bounds.min.y - padding, -0.1));
    entity->AddChild(box);
    float width = extents.x +2 *padding;
    float height = extents.y +2 * padding;

    auto fb = [] (const std::string& img, float width, float thickness, float x, float y, float imgw, bool flipv, bool rot) {
        auto b = std::make_shared<Entity>();
        auto b_renderer = std::make_shared<Renderer>();
        auto qm = std::make_shared<QuadMesh>(img, width, thickness, width/imgw, flipv ? -1 : 1 );
        b_renderer->SetMesh(qm);
        b->AddComponent(b_renderer);
        b->SetPosition(glm::vec3(x, y, 0.09));
        if (rot)
            b->SetAngle(90.0f);
        return b;
    };

    auto cb = [] (const std::string& img, float x, float y, float w, float h, bool flipx, bool flipy) {
        auto b = std::make_shared<Entity>();
        auto b_renderer = std::make_shared<Renderer>();
        auto qm = std::make_shared<QuadMesh>(img, w, h, flipx ? -1 : 1, flipy ? -1 : 1 );
        b_renderer->SetMesh(qm);
        b->AddComponent(b_renderer);
        b->SetPosition(glm::vec3(x, y, 0.095));
        return b;
    };

    if (table.HasKey("border")) {
        luabridge::LuaRef borders = table.Get<luabridge::LuaRef>("border");
        LuaTable border(borders);
        std::string img = border.Get<std::string>("img");
        auto tex = Engine::get().GetAssetManager().GetTex(img);
        float imgw = tex->GetWidth();
        float thickness = border.Get<float>("thickness");
        auto upperBorder = fb(img, width, thickness, bounds.min.x - padding, bounds.max.y + padding - thickness, imgw, false, false);
        auto lowerBorder = fb(img, width, thickness, bounds.min.x - padding, bounds.min.y - padding, imgw, true, false);
        auto leftBorder = fb(img, height, thickness, bounds.min.x - padding + thickness, bounds.min.y - padding, imgw, false, true);
        auto rb = fb (img, height, thickness, bounds.max.x + padding, bounds.min.y - padding, imgw, true, true);
        entity->AddChild(upperBorder);
        entity->AddChild(lowerBorder);
        entity->AddChild(leftBorder);
        entity->AddChild(rb);
    }


    if (table.HasKey("corner")) {
        luabridge::LuaRef corners = table.Get<luabridge::LuaRef>("corner");
        LuaTable corner(corners);
        std::string img = corner.Get<std::string>("img");
        auto tex = Engine::get().GetAssetManager().GetTex(img);
        float imgw = tex->GetWidth();
        float imgh = tex->GetHeight();
        auto tl = cb(img, bounds.min.x - padding, bounds.max.y + padding - imgh, imgw, imgh, false, false);
        auto bl = cb(img, bounds.min.x - padding, bounds.min.y - padding, imgw, imgh, false, true);
        auto tr = cb(img, bounds.max.x + padding - imgw, bounds.max.y + padding - imgh, imgw, imgh, true, false);
        auto br = cb(img, bounds.max.x + padding - imgw, bounds.min.y - padding, imgw, imgh, true, true);

        entity->AddChild(tl);
        entity->AddChild(bl);
        entity->AddChild(tr);
        entity->AddChild(br);
        //entity->AddChild(lowerBorder);
        //entity->AddChild(leftBorder);
        //entity->AddChild(rb);

    }

    return entity;

}
