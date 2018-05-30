#include <monkey/monkeyfactory.h>
#include <monkey/monkey.h>
#include <iostream>
#include <gfx/renderer.h>
#include <gfx/quadmesh.h>
#include <gfx/renderingengine.h>
#include <gfx/spritemesh.h>
#include <monkey/walkarea.h>
#include <gfx/scheduler.h>
#include <graph/poly.h>
#include <gfx/meshfactory.h>
#include <gfx/textmesh.h>
#include <glm/gtx/transform.hpp>

std::shared_ptr<Entity> MonkeyFactory::Create() {

    auto entity = std::make_shared<Entity>();
    
    // get current room
    Monkey& m = Monkey::get();
    std::string room = m["variables"].Get<std::string>("_room");
    std::cout << "Loading room "<< room << std::endl;
    LuaWrapper::Load(Engine::get().GetAssetManager().GetDirectory() + "rooms/" + room + ".lua");

    // Create the local assets
    luabridge::LuaRef assets = luabridge::getGlobal(LuaWrapper::L, "assets");
    for (int i = 0; i < assets.length();++i) {
        luabridge::LuaRef a = assets[i+1];
        LuaTable assetTable(a);
        std::string type = assetTable.Get<std::string>("type");
        if (type == "sprite") {
           ReadSprite(assetTable);

        }


    }

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
        std::string tag = tcam.Get<std::string>("tag", "");
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
            if (!tag.empty())
                cam->SetTag(tag);
            renderingEngine->AddCamera(std::move(cam));
        }
    }
    renderingEngine->AddShader(TEXTURE_SHADER);
    renderingEngine->AddShader(COLOR_SHADER);
    renderingEngine->AddShader(TEXT_SHADER);



    auto scheduler =std::make_shared<Scheduler>();
    scheduler->SetTag("_scheduler");
    engineNode->AddComponent(renderingEngine);
    engineNode->AddComponent(scheduler);
    entity->AddChild(engineNode);
    
    return entity;

}

void MonkeyFactory::ReadItems(luabridge::LuaRef& scene, Entity* parent) {
    for (int i = 0; i < scene.length(); ++i) {
        // create new entity
        luabridge::LuaRef r = scene[i+1];
        LuaTable item(r);
        auto entity = std::make_shared<Entity>();
        std::string tag = item.Get<std::string>("tag", "");
        if (!tag.empty()) entity->SetTag(tag);
        glm::vec3 pos = item.Get<glm::vec3>("pos", glm::vec3(0.0f));
        entity->SetPosition(pos);
        int layer = item.Get<int>("layer", 0);
        // children
        if (item.HasKey("children")) {
            luabridge::LuaRef c = item.Get<luabridge::LuaRef>("children");
            ReadItems (c, entity.get());
        }
        if (item.HasKey("gfx")) {
            luabridge::LuaRef c = item.Get<luabridge::LuaRef>("gfx");
            ReadGfxComponent(c, entity.get());
        }
        if (item.HasKey("text")) {
            luabridge::LuaRef c = item.Get<luabridge::LuaRef>("text");
            ReadTextComponent(c, entity.get());
        }

        if (item.HasKey("walkarea")) {
            luabridge::LuaRef c = item.Get<luabridge::LuaRef>("walkarea");
            ReadWalkarea(c, entity.get());
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
        float w = table.Get<float>("width", 0.0f);
        float h = table.Get<float>("height", 0.0f);
        auto mesh = std::make_shared<QuadMesh>(image, w, h);
        renderer->SetMesh(mesh);
    } else if (table.HasKey("model")) {
        std::string model = table.Get<std::string>("model");
        std::string anim = table.Get<std::string>("anim", "");
        renderer->SetMesh(Engine::get().GetAssetManager().GetMesh(model));
        renderer->SetAnimation(anim);

    }
    parent->AddComponent(renderer);
    
}

void MonkeyFactory::ReadTextComponent(luabridge::LuaRef &ref, Entity *parent) {
    LuaTable table(ref);
    auto renderer = std::make_shared<Renderer>();
    std::string text = table.Get<std::string>("id");
    std::string font = table.Get<std::string>("font");
    std::string align = table.Get<std::string>("align", "topleft");
    Font* f = Engine::get().GetAssetManager().GetFont(font);
    auto mesh = std::make_shared<TextMesh>(f, text, 8, glm::vec4(1.0f));
    // default alignment is top left
    auto bounds = mesh->GetBounds();
    if (align == "bottomleft") {
        renderer->SetRenderingTransform(glm::translate(glm::vec3(0.0f, -bounds.min.y, 0.0f)));
    }
    renderer->SetMesh(mesh);
    parent->AddComponent(renderer);
}

void MonkeyFactory::ReadWalkarea (luabridge::LuaRef& ref, Entity* parent) {
    LuaTable table(ref);
    std::string id = table.Get<std::string>("cam");
    std::string targetId = table.Get<std::string>("target");
    luabridge::LuaRef shapeR = table.Get<luabridge::LuaRef>("shape");
    auto shape = ReadShape(shapeR);
    // see if we want to plot the outline of the walk area
    auto mesh = MeshFactory::CreateMesh(*(shape.get()), 1.0f);
    auto ce = std::make_shared<Entity>();
    ce->SetLayer(1);
    auto cer = std::make_shared<Renderer>();
    cer->SetMesh(mesh);
    ce->AddComponent(cer);
    parent->AddChild(ce);


    auto hotspot = std::make_shared<WalkArea>(id, shape);

    parent->AddComponent(hotspot);
}

void MonkeyFactory::ReadSprite (LuaTable& t) {
    float ppu = t.Get<float>("ppu", 1.0);
    std::string name = t.Get<std::string>("id");
    std::string sheetName = t.Get<std::string>("sheet");
    luabridge::LuaRef an = t.Get<luabridge::LuaRef>("animations");
    std::vector<Animation> anims;
    for (int i = 0; i < an.length(); ++i) {
        Animation animation;
        luabridge::LuaRef a = an[i+1];
        LuaTable at (a);
        animation.name = at.Get<std::string>("name");
        luabridge::LuaRef fr = at.Get<luabridge::LuaRef>("frames");
        for (int j = 0; j < fr.length(); ++j) {
            luabridge::LuaRef a2 = fr[j+1];
            LuaTable ft (a2);
            Frame frame;
            frame.time = ft.Get<float>("duration");
            luabridge::LuaRef qu = ft.Get<luabridge::LuaRef>("quads");
            for (int k = 0; k < qu.length(); ++k) {
                luabridge::LuaRef a3 = qu[k+1];
                LuaTable qt (a3);
                Quad q;
                q.x = qt.Get<float>("x");
                q.y = qt.Get<float>("y");
                q.width = qt.Get<float>("width");
                q.height = qt.Get<float>("height");
                glm::vec2 anchor = qt.Get<glm::vec2>("anchor", glm::vec2(0.0f));
                q.anchorx = anchor.x;
                q.anchory = anchor.y;
                frame.quads.push_back(q);
            }
            animation.frames.push_back(frame);
        }
        anims.push_back(animation);
    }
    std::unique_ptr<IMesh> mesh(new SpriteMesh (ppu, sheetName, anims));

    Engine::get().GetAssetManager().AddMesh(name, std::move(mesh));

}

std::shared_ptr<Shape> MonkeyFactory::ReadShape(luabridge::LuaRef& ref) {
    LuaTable at (ref);
    std::string type = at.Get<std::string>("type");
    if (type == "rect") {
        float w = at.Get<float>("width");
        float h = at.Get<float>("height");
        return std::make_shared<Rect>(w, h);
    } else if (type == "poly") {
        std::vector<float> outline = at.GetVector<float>("outline");
        std::vector<glm::vec2> points;
        for (int i = 0; i < outline.size(); i = i +2)
            points.push_back(glm::vec2(outline[i], outline[i+1]));
        if (at.HasKey("holes")) {
            std::unique_ptr<Polygon> mainOutline(new Polygon(points));
            luabridge::LuaRef holes = at.Get<luabridge::LuaRef>("holes");
            LuaTable ha(holes);
            auto poly = std::make_shared<Poly>(std::move(mainOutline));
            for (int j = 0; j<holes.length(); ++j) {
                luabridge::LuaRef h = holes[j+1];
                std::vector<float> holeOutline = ReadVector<float>(h);
                std::vector<glm::vec2> points;
                for (int i = 0; i < holeOutline.size(); i = i +2)
                    points.push_back(glm::vec2(holeOutline[i], holeOutline[i+1]));
                poly->AddHole(std::unique_ptr<Polygon>(new Polygon(points)));

            }
            return poly;

        } else {


            return std::make_shared<Polygon>(points);
        }
    }
    return nullptr;
}
