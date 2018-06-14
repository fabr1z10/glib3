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
#include <graph/polyline.h>
#include <gfx/meshfactory.h>
#include <gfx/textmesh.h>
#include <glm/gtx/transform.hpp>
#include <monkey/scripthotspot.h>
#include <gfx/follow.h>
#include <monkey/scaling.h>



std::shared_ptr<Entity> MonkeyFactory::Create() {

    auto entity = std::make_shared<Entity>();
    
    // get current room
    Monkey& m = Monkey::get();
    std::string room = m["variables"].Get<std::string>("_room");
    std::cout << "Loading room "<< room << std::endl;
    LuaWrapper::Load(Engine::get().GetAssetManager().GetDirectory() + "rooms/" + room + ".lua");


    // Create the local assets
    luabridge::LuaRef roomRef = luabridge::getGlobal(LuaWrapper::L, "room");
    LuaTable roomTable(roomRef);

    if (roomTable.HasKey("init")) {
        luabridge::LuaRef r1 = roomTable.Get<luabridge::LuaRef>("init");
        r1();
    }

    luabridge::LuaRef assets = roomTable.Get<luabridge::LuaRef>("assets");
    for (int i = 0; i < assets.length();++i) {
        luabridge::LuaRef a = assets[i+1];
        LuaTable assetTable(a);
        std::string type = assetTable.Get<std::string>("type");
        if (type == "sprite") {
           ReadSprite(assetTable);

        }


    }

    // Creating the room
    //luabridge::LuaRef scene = luabridge::getGlobal(LuaWrapper::L, "scene");
    luabridge::LuaRef scene = roomTable.Get<luabridge::LuaRef>("scene");
    ReadItems (scene, entity.get());

    // create the cameras
    auto engineNode = std::make_shared<Entity>();
    auto renderingEngine = std::make_shared<RenderingEngine>();
    luabridge::LuaRef cams = roomTable.Get<luabridge::LuaRef>("cameras");
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
    auto hotspotManager = std::make_shared<HotSpotManager>();
    hotspotManager->SetTag("_hotspotmanager");
    luabridge::LuaRef groups = roomTable.Get<luabridge::LuaRef>("groups");
    for (int i = 0; i< groups.length(); ++i) {
        luabridge::LuaRef groupR = groups[i+1];
        int id = groupR["id"].cast<int>();
        std::string cam = groupR["cam"].cast<std::string>();
        hotspotManager->AddGroup(id, cam);
    }


    engineNode->AddComponent(renderingEngine);
    engineNode->AddComponent(scheduler);
    engineNode->AddComponent(hotspotManager);
    entity->AddChild(engineNode);

    //luabridge::LuaRef roomRef = luabridge::getGlobal(LuaWrapper::L, "room");
    //LuaTable roomTable(roomRef);
    if (roomTable.HasKey("start")) {
        luabridge::LuaRef r1 = roomTable.Get<luabridge::LuaRef>("start");
        r1();
    }

    return entity;

}

void MonkeyFactory::CleanUp() {
    luabridge::LuaRef roomRef = luabridge::getGlobal(LuaWrapper::L, "room");
    LuaTable table (roomRef);
    luabridge::LuaRef assets = table.Get<luabridge::LuaRef>("assets");
    for (int i = 0; i < assets.length();++i) {
        luabridge::LuaRef a = assets[i+1];
        LuaTable assetTable(a);
        std::string id = assetTable.Get<std::string>("id");
        std::string type = assetTable.Get<std::string>("type");
        if (type == "sprite") {
            Engine::get().GetAssetManager().RemoveMesh(id);
            
        }
    }

    roomRef = luabridge::Nil();


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
        if (item.HasKey("outlinetext")) {
            luabridge::LuaRef c = item.Get<luabridge::LuaRef>("outlinetext");
            ReadOutlineTextComponent(c, entity.get());
        }
        if (item.HasKey("follow")) {
            luabridge::LuaRef c = item.Get<luabridge::LuaRef>("follow");
            ReadFollowComponent(c, entity.get());
        }
        if (item.HasKey("walkarea")) {
            luabridge::LuaRef c = item.Get<luabridge::LuaRef>("walkarea");
            ReadWalkarea(c, entity.get());
        }
        if (item.HasKey("hotspot")) {
            luabridge::LuaRef c = item.Get<luabridge::LuaRef>("hotspot");
            ReadHotspot(c, entity.get());
        }
        if (item.HasKey("button")) {
            luabridge::LuaRef c = item.Get<luabridge::LuaRef>("button");
            ReadButton(c, entity.get());
        }
        if (item.HasKey("scaling")) {
            luabridge::LuaRef c = item.Get<luabridge::LuaRef>("scaling");
            ReadScaling(c, entity.get());
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
    auto renderer = GetTextComponent(ref);
    parent->AddComponent(renderer);
}
void MonkeyFactory::ReadFollowComponent(luabridge::LuaRef &ref, Entity *parent) {
    LuaTable table(ref);
    std::string cam = table.Get<std::string>("cam");
    parent->AddComponent(std::make_shared<Follow>(cam));
}

void MonkeyFactory::ReadOutlineTextComponent(luabridge::LuaRef &ref, Entity *parent) {
    LuaTable table(ref);

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
    glm::vec2 offset = mesh->getOffset();
    glm::vec2 outlineOffsets[] = {{0, 0}, {-1, 0}, {-1,1}, {0, 1}, {1,1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
    for (int i =0; i < 9; ++i) {
        auto entity = std::make_shared<Entity>();
        auto renderer = std::make_shared<Renderer>();
        renderer->SetMesh(mesh);
        entity->SetPosition(glm::vec3(outlineOffsets[i] * 0.5f, i == 0 ? 0 : -1));
        renderer->SetTint(i==0 ? fontColor : outlineColor);
        renderer->SetRenderingTransform(glm::translate(glm::vec3(offset, 0.0f)));
        entity->AddComponent(renderer);
        parent->AddChild(entity);
    }
}


std::unique_ptr<Function2D> MonkeyFactory::GetFunc2D(luabridge::LuaRef& ref) {
    std::unique_ptr<PatchwiseLinear2D> p (new PatchwiseLinear2D);
    for (int i = 0; i < ref.length(); ++i) {
        luabridge::LuaRef f = ref[i+1];
        LuaTable funcTable(f);
        glm::vec4 domain = funcTable.Get<glm::vec4>("rect");
        bool isX = (funcTable.Get<char>("dir") == 'x');
        glm::vec2 bounds = funcTable.Get<glm::vec2>("bounds");
        p->AddFunction(domain, isX, bounds.x, bounds.y);
    }
    return std::move(p);
}

// Read the walk-area
void MonkeyFactory::ReadWalkarea (luabridge::LuaRef& ref, Entity* parent) {
    LuaTable table(ref);
    std::string tag = table.Get<std::string>("tag", "");

    int group = table.Get<int>("group");
    int priority = table.Get<int>("priority");
    std::string targetId = table.Get<std::string>("target");
    luabridge::LuaRef shapeR = table.Get<luabridge::LuaRef>("shape");
    auto shape = ReadShape(shapeR);
    auto hotspot = std::make_shared<WalkArea>(shape, priority, group, targetId);
    if (!tag.empty()) hotspot->SetTag(tag);

    // see if it has a depthfunc
    if (table.HasKey("scaling")) {
        luabridge::LuaRef sref = table.Get<luabridge::LuaRef>("scaling");
        luabridge::LuaRef depthRef = sref["depth"];
        auto depthFunc = GetFunc2D(depthRef);
        hotspot->SetDepthFunction(std::move(depthFunc));
        luabridge::LuaRef scaleRef = sref["scale"];
        auto scaleFunc = GetFunc2D(scaleRef);
        hotspot->SetScalingFunction(std::move(scaleFunc));


    }


    parent->AddComponent(hotspot);

    // see if we want to plot the outline of the walk area
    auto mesh = MeshFactory::CreateMesh(*(shape.get()), 1.0f);
    auto ce = std::make_shared<Entity>();
    ce->SetLayer(1);
    auto cer = std::make_shared<Renderer>();
    cer->SetMesh(mesh);
    ce->AddComponent(cer);
    parent->AddChild(ce);





}

std::shared_ptr<HotSpot> MonkeyFactory::GetHotSpot (luabridge::LuaRef& ref) {
    LuaTable table(ref);
    luabridge::LuaRef shapeR = table.Get<luabridge::LuaRef>("shape");
    auto shape = ReadShape(shapeR);
    return GetHotSpot(ref, shape);

}

std::shared_ptr<HotSpot> MonkeyFactory::GetHotSpot (luabridge::LuaRef& ref, std::shared_ptr<Shape> shape) {
    LuaTable table(ref);
    int group = table.Get<int>("group");
    int priority = table.Get<int>("priority");
    auto hotspot = std::make_shared<ScriptHotSpot>(shape, priority, group);
    if (table.HasKey("onenter")) {
        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onenter");
        hotspot->SetOnEnter(r);
    }
    if (table.HasKey("onleave")) {
        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onleave");
        hotspot->SetOnLeave(r);
    }
    if (table.HasKey("onclick")) {
        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onclick");
        hotspot->SetOnClick(r);
    }
    //std::string onEnter = table.Get<std::string>("onenter", "");
    //std::string onLeave = table.Get<std::string>("onleave", "");
    //std::string onClick = table.Get<std::string>("onclick", "");
    
    return hotspot;
}

std::shared_ptr<Renderer> MonkeyFactory::GetTextComponent (luabridge::LuaRef& ref) {
    LuaTable table(ref);
    auto renderer = std::make_shared<Renderer>();
    std::string text = table.Get<std::string>("id");
    std::string font = table.Get<std::string>("font");
    TextAlignment align = table.Get<TextAlignment>("align", TOP_LEFT);
    glm::vec4 color = table.Get<glm::vec4>("color", glm::vec4(255.0f));
    color /= 255.0f;
    Font* f = Engine::get().GetAssetManager().GetFont(font);
    auto mesh = std::make_shared<TextMesh>(f, text, 8, align);
    glm::vec2 offset = mesh->getOffset();
    renderer->SetRenderingTransform(glm::translate(glm::vec3(offset, 0.0f)));
    renderer->SetTint(color);
    renderer->SetMesh(mesh);
    return renderer;
}

void MonkeyFactory::ReadHotspot (luabridge::LuaRef& ref, Entity* parent) {
    LuaTable table(ref);
    auto hs = GetHotSpot(ref);
    Shape* s = hs->GetShape();
    parent->AddComponent(hs);
    int layer = table.Get<int>("layer", 1);
    auto ce = std::make_shared<Entity>();
    ce->SetLayer(layer);
    auto cer = std::make_shared<Renderer>();
    auto debugMesh = MeshFactory::CreateMesh(*s, 1.0f);
    cer->SetMesh(debugMesh);
    ce->AddComponent(cer);
    parent->AddChild(ce);
}

void MonkeyFactory::ReadScaling (luabridge::LuaRef& ref, Entity* parent) {
    parent->AddComponent(std::make_shared<ScalingDepthComponent>());

}

void MonkeyFactory::ReadButton (luabridge::LuaRef& ref, Entity* parent) {
    LuaTable table(ref);
    auto renderer = GetTextComponent(ref);

    // for a button the shape is determined by the text size
    auto bounds = renderer->GetBounds();
    float w = bounds.max.x - bounds.min.x;
    float h = bounds.max.y - bounds.min.y;
    auto shape = std::make_shared<Rect>(w, h);
    auto debugMesh = MeshFactory::CreateMesh(*(shape.get()), 1.0f);
    auto hs = GetHotSpot(ref, shape);

    // logic to draw the debug mesh
    glm::vec2 debugMeshPos(0.0f);
    std::string align = table.Get<std::string>("align", "topleft");
    int layer = table.Get<int>("layer", 1);
    if (align == "bottomright") {
        debugMeshPos = glm::vec2(-bounds.max.x, 0.0f);
    } else if (align == "topleft") {
        debugMeshPos = glm::vec2(0.0f, bounds.min.y);
    } else if (align == "topright") {
        debugMeshPos = glm::vec2(-bounds.max.x, bounds.min.y);
    }

    auto ce = std::make_shared<Entity>();
    ce->SetPosition(debugMeshPos);
    ce->SetLayer(layer);
    auto cer = std::make_shared<Renderer>();
    cer->SetMesh(debugMesh);
    ce->AddComponent(cer);

    parent->AddChild(ce);
    parent->AddComponent(renderer);
    ce->AddComponent(hs);
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
    glm::vec2 offset = at.Get<glm::vec2>("offset", glm::vec2(0.0f));
    if (type == "rect") {
        float w = at.Get<float>("width");
        float h = at.Get<float>("height");
        return std::make_shared<Rect>(w, h, offset);
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
    } else if (type == "graph") {
        // read the vertices
        luabridge::LuaRef rVert = at.Get<luabridge::LuaRef>("vertices");
        std::vector<glm::vec2> vertices;
        std::vector<std::pair<int, int>> edges;
        for (int i = 0; i< rVert.length(); ++i) {
            luabridge::LuaRef vertex = rVert[i+1];
            glm::vec2 p(vertex[1].cast<float>(), vertex[2].cast<float>());
            vertices.push_back(p);
        }
        luabridge::LuaRef rEdges = at.Get<luabridge::LuaRef>("edges");
        for (int i = 0; i< rEdges.length(); ++i) {
            luabridge::LuaRef edge = rEdges[i+1];
            std::pair<int, int> e(edge[1].cast<int>(), edge[2].cast<int>());
            edges.push_back(e);
        }
        return std::make_shared<PolyLine>(vertices,edges);
    }

    return nullptr;
}

void MonkeyFactory::PostInit() {


}


