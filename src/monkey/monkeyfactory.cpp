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
#include <monkey/luacollision.h>
#include <gfx/follow.h>
#include <monkey/scaling.h>
#include <monkey/luakeylistener.h>
#include <monkey/scriptwalktrigger.h>
#include <gfx/textview.h>
#include "gfx/cursor.h"
#include <gfx/collider.h>
#include <gfx/keyboardcontroller.h>

using namespace luabridge;

std::shared_ptr<Entity> MonkeyFactory::Create() {

    auto entity = std::make_shared<Entity>();
    
    // get current room
    Monkey& m = Monkey::get();
    std::string room = m["variables"].Get<std::string>("_room");
    std::cout << "Loading room "<< room << std::endl;
    LuaWrapper::Load(Engine::get().GetAssetManager().GetDirectory() + "rooms/" + room + "/room.lua");


    // Create the local assets
    luabridge::LuaRef roomRef = luabridge::getGlobal(LuaWrapper::L, "room");
    LuaTable roomTable(roomRef);

    if (roomTable.HasKey("init")) {
        luabridge::LuaRef r1 = roomTable.Get<luabridge::LuaRef>("init");
        r1();
    }

    if (roomTable.HasKey("collisionresponse")) {
        // set the collision responses
        luabridge::LuaRef resp = roomTable.Get<luabridge::LuaRef>("collisionresponse");
        std::unique_ptr<CollisionResponseManager> crm (new CollisionResponseManager);
        for (int i = 0; i < resp.length();++i) {
            luabridge::LuaRef a = resp[i+1];
            LuaTable at(a);
            std::vector<int> tags = at.GetVector<int>("tag");
            std::unique_ptr<LuaCollisionResponse> l(new LuaCollisionResponse);
            if (at.HasKey("onenter")) {
                luabridge::LuaRef onEnter = at.Get<luabridge::LuaRef>("onenter");
                l->SetOnEnter(onEnter);
            }
            if (at.HasKey("onleave")) {
                luabridge::LuaRef onLeave = at.Get<luabridge::LuaRef>("onleave");
                l->SetOnLeave(onLeave);
            }
            if (at.HasKey("onstay")) {
                luabridge::LuaRef onStay = at.Get<luabridge::LuaRef>("onstay");
                l->SetOnStay(onStay);
            }
            crm->AddCollisionResponse(tags[0], tags[1], std::move(l));

        }
        Engine::get().GetCollisionEngine()->SetResponseManager(std::move(crm));
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


//    // create the cameras
//    auto engineNode = std::make_shared<Entity>();
//    auto renderingEngine = std::make_shared<RenderingEngine>();
//
//    // add key listener to handle savegame, quit, pause etc.
//    auto keyListener = std::make_shared<LuaKeyListener>();
//
//
//
//    luabridge::LuaRef hotkeys = roomTable.Get<luabridge::LuaRef>("hotkeys");
//    for (int i = 0; i < hotkeys.length(); ++i) {
//        luabridge::LuaRef hotkey = hotkeys[i+1];
//        int key = hotkey["key"].cast<int>();
//        luabridge::LuaRef callback = hotkey["func"];
//        keyListener->AddHotKey(key, callback);
//    }
//
//
//    renderingEngine->AddShader(TEXTURE_SHADER);
//    renderingEngine->AddShader(COLOR_SHADER);
//    renderingEngine->AddShader(TEXT_SHADER);
//
//
//
//    auto scheduler =std::make_shared<Scheduler>();
//    scheduler->SetTag("_scheduler");
//    auto hotspotManager = std::make_shared<HotSpotManager>();
//    hotspotManager->SetTag("_hotspotmanager");
//    renderingEngine->SetTag("_renderingengine");
//
//    if (roomTable.HasKey("groups")) {
//        luabridge::LuaRef groups = roomTable.Get<luabridge::LuaRef>("groups");
//        for (int i = 0; i < groups.length(); ++i) {
//            luabridge::LuaRef groupR = groups[i + 1];
//            int id = groupR["id"].cast<int>();
//            std::string cam = groupR["cam"].cast<std::string>();
//            hotspotManager->AddGroup(id, cam);
//        }
//    }
//
//
//    engineNode->AddComponent(renderingEngine);
//    engineNode->AddComponent(scheduler);
//    engineNode->AddComponent(hotspotManager);
//    engineNode->AddComponent(keyListener);
//    entity->AddChild(engineNode);

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

    //Monkey& m = Monkey::get();
    //std::string ciao = m["variables"].Get<std::string>("_previousroom");
    //std::string cr = m["variables"].Get<std::string>("_room");
    //m["variables"].Set("_previousroom", cr);
    //std::string ciao = m["variables"].Get<std::string>("_previousroom");
}

std::shared_ptr<Entity> MonkeyFactory::ReadItem(luabridge::LuaRef& ref) {
    LuaTable item(ref);
    auto entity = std::make_shared<Entity>();
    std::string tag = item.Get<std::string>("tag", "");
    if (!tag.empty()) entity->SetTag(tag);
    glm::vec3 pos = item.Get<glm::vec3>("pos", glm::vec3(0.0f));
    if (item.HasKey("angle")) {
        float angle = item.Get<float>("angle",0.0f);
        entity->SetPosition(pos, deg2rad* angle);
    } else {
        entity->SetPosition(pos);
    }
    // int layer = item.Get<int>("layer", 0);
    if (item.HasKey("camera")) {
        LuaRef cam = item.Get<LuaRef>("camera");
        LuaTable tcam(cam);
        std::string camType = tcam.Get<std::string>("type");
        std::string tag = tcam.Get<std::string>("tag", "");
        glm::vec2 pos = tcam.Get<glm::vec2>("pos", glm::vec2(0.0f));
        glm::vec4 viewport = tcam.Get<glm::vec4>("viewport", glm::vec4(0.0f, 0.0f, Engine::get().GetDeviceSize()));
        if (camType == "ortho") {
            // orhographic camera
            glm::vec2 size = tcam.Get<glm::vec2>("size");
            glm::vec4 bounds = tcam.Get<glm::vec4>("bounds", glm::vec4(0.0));

            auto camera = std::unique_ptr<OrthographicCamera> (new OrthographicCamera(size.x, size.y, viewport));
            if (bounds != glm::vec4(0.0f))
                camera->SetBounds(bounds[0], bounds[2], bounds[1], bounds[3]);
            camera->SetPosition(glm::vec3(pos, 5.0f), glm::vec3(0,0,-1), glm::vec3(0,1,0));
            if (!tag.empty())
                camera->SetTag(tag);
            entity->SetCamera(std::move(camera));
        }


    }


    if (item.HasKey("children")) {
        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("children");
        ReadItems (c, entity.get());
    }
    if (item.HasKey("gfx")) {
        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("gfx");
        ReadGfxComponent(c, entity.get());
    }
    if (item.HasKey("textview")) {
        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("textview");
        ReadTextViewComponent(c, entity.get());
    }
    if (item.HasKey("text")) {
        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("text");
        ReadTextComponent(c, entity.get());
    }
    if (item.HasKey("collider")) {
        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("collider");
        ReadColliderComponent(c, entity.get());
    }
    if (item.HasKey("keyboardcontroller")) {
        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("keyboardcontroller");
        ReadKeyboardComponent(c, entity.get());
    }
    if (item.HasKey("keyboardcontrollercollision")) {
        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("keyboardcontrollercollision");
        ReadKeyboardCollisionComponent(c, entity.get());
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
    if (item.HasKey("walktrigger")) {
        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("walktrigger");
        ReadWalkTrigger(c, entity.get());
    }
    if (item.HasKey("cursor")) {
        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("cursor");
        ReadCursor(c, entity.get());
    }
    //entity->SetLayer(layer);
    return entity;


}


void MonkeyFactory::ReadItems(luabridge::LuaRef& scene, Entity* parent) {
    for (int i = 0; i < scene.length(); ++i) {
        // create new entity
        luabridge::LuaRef r = scene[i+1];
        auto entity = ReadItem(r);
        parent->AddChild(entity);
    }



    
}

void MonkeyFactory::ReadTextViewComponent(luabridge::LuaRef &ref, Entity *parent) {
    LuaTable table(ref);
    glm::vec4 viewport = table.Get<glm::vec4>("viewport");
    float w = table.Get<float>("width");
    float h = table.Get<float>("height");
    float size = table.Get<float>("size");
    float deltax = table.Get<float>("deltax", 0.0f);
    glm::vec4 color = table.Get<glm::vec4>("color", glm::vec4(255.0f));
    color /= 255.0f;
    std::string font = table.Get<std::string>("font");
    auto r = std::make_shared<TextView>(w, h, size, font, color, viewport, deltax);
    parent->AddComponent(r);


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
        bool flip = table.Get<bool>("flip", false);
        renderer->SetMesh(Engine::get().GetAssetManager().GetMesh(model));
        renderer->SetFlipX(flip);
        renderer->SetAnimation(anim);
    } else if (table.HasKey("shape")) {
        LuaRef sref = table.Get<LuaRef>("shape");
        std::string draw = table.Get<std::string>("draw","outline");
        glm::vec4 color = table.Get<glm::vec4>("color");
        color /= 255.0f;
        auto shape = ReadShape(sref);
        if (draw == "outline") {
            auto mesh = MeshFactory::CreateMesh(*(shape.get()), 0.0f);
            renderer->SetMesh(mesh);
        } else if (draw == "solid") {
            auto mesh = MeshFactorySolid::CreateMesh(*(shape.get()), 0.0f);
            renderer->SetMesh(mesh);

        }
        renderer->SetTint(color);

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

void MonkeyFactory::ReadColliderComponent(luabridge::LuaRef &ref, Entity *parent) {
    LuaTable table(ref);
    luabridge::LuaRef shapeR = table.Get<luabridge::LuaRef>("shape");
    int tag = table.Get<int>("tag");
    int flag = table.Get<int>("flag");
    auto shape = ReadShape(shapeR);
    parent->AddComponent(std::make_shared<Collider>(shape, tag, flag));
}

void MonkeyFactory::ReadKeyboardComponent(luabridge::LuaRef &ref, Entity *parent) {
    LuaTable table(ref);

    //luabridge::LuaRef shapeR = table.Get<luabridge::LuaRef>("shape");
    //auto shape = ReadShape(shapeR);
    parent->AddComponent(std::make_shared<KeyboardController>());
}
void MonkeyFactory::ReadKeyboardCollisionComponent(luabridge::LuaRef &ref, Entity *parent) {
    LuaTable table(ref);
    float width = table.Get<float>("width");
    float height = table.Get<float>("height");
    float speed = table.Get<float>("speed");
    int horRays = table.Get<int>("horizontal_rays");
    int vertRays = table.Get<int>("vertical_rays");
    //luabridge::LuaRef shapeR = table.Get<luabridge::LuaRef>("shape");
    //auto shape = ReadShape(shapeR);
    parent->AddComponent(std::make_shared<KeyboardControllerCollision>(width, height, speed, horRays, vertRays));
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

    //int group = table.Get<int>("group");
    int priority = table.Get<int>("priority");
    std::string targetId = table.Get<std::string>("target");
    luabridge::LuaRef shapeR = table.Get<luabridge::LuaRef>("shape");
    auto shape = ReadShape(shapeR);
    auto hotspot = std::make_shared<WalkArea>(shape, priority, targetId);
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

    if (table.HasKey("blockedlines")) {
        luabridge::LuaRef ref = table.Get<luabridge::LuaRef>("blockedlines");
        for (int i = 0; i < ref.length(); ++i) {
            luabridge::LuaRef bl = ref[i+1];
            LuaTable t(bl);
            glm::vec2 A = t.Get<glm::vec2>("A");
            glm::vec2 B = t.Get<glm::vec2>("B");
            bool active = t.Get<bool>("active");
            hotspot->AddBlockedLine(A, B, active);
        }
    }

    parent->AddComponent(hotspot);

    // see if we want to plot the outline of the walk area
//    auto mesh = MeshFactory::CreateMesh(*(shape.get()), 1.0f);
//    auto ce = std::make_shared<Entity>();
//    ce->SetLayer(1);
//    auto cer = std::make_shared<Renderer>();
//    cer->SetMesh(mesh);
//    ce->AddComponent(cer);
//    parent->AddChild(ce);





}

std::shared_ptr<HotSpot> MonkeyFactory::GetHotSpot (luabridge::LuaRef& ref) {
    LuaTable table(ref);
    luabridge::LuaRef shapeR = table.Get<luabridge::LuaRef>("shape");
    auto shape = ReadShape(shapeR);
    return GetHotSpot(ref, shape);

}

std::shared_ptr<HotSpot> MonkeyFactory::GetHotSpot (luabridge::LuaRef& ref, std::shared_ptr<Shape> shape) {
    LuaTable table(ref);
    //int group = table.Get<int>("group");
    int priority = table.Get<int>("priority");
    auto hotspot = std::make_shared<ScriptHotSpot>(shape, priority);
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
    if (table.HasKey("onmove")) {
        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onmove");
        hotspot->SetOnMove(r);
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
    float size = table.Get<float>("size", 8);
    TextAlignment align = table.Get<TextAlignment>("align", TOP_LEFT);
    float maxWidth = table.Get<float>("maxwidth", 0.0f);
    glm::vec4 color = table.Get<glm::vec4>("color", glm::vec4(255.0f));
    color /= 255.0f;
    Font* f = Engine::get().GetAssetManager().GetFont(font);
    auto mesh = std::make_shared<TextMesh>(f, text, 8, align, maxWidth);
    glm::vec2 offset = mesh->getOffset();
    renderer->SetRenderingTransform(glm::translate(glm::vec3(offset, 0.0f)));
    renderer->SetTint(color);
    renderer->SetMesh(mesh);
    return renderer;
}


void MonkeyFactory::ReadCursor (luabridge::LuaRef& ref, Entity* parent) {
    LuaTable table(ref);
    auto cursor = std::make_shared<Cursor>();
    parent->AddComponent(cursor);
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

void MonkeyFactory::ReadWalkTrigger (luabridge::LuaRef& ref, Entity* parent) {
    LuaTable table(ref);
    luabridge::LuaRef shapeR = table.Get<luabridge::LuaRef>("shape");
    auto shape = ReadShape(shapeR);

    std::string target = table.Get<std::string>("target");
    auto wt = std::make_shared<ScriptWalkTrigger>(shape, target);
    if (table.HasKey("onenter")) {
        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onenter");
        wt->SetOnEnter(r);
    }
    if (table.HasKey("onleave")) {
        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onleave");
        wt->SetOnLeave(r);
    }
    if (table.HasKey("onstay")) {
        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onstay");
        wt->SetOnStay(r);
    }
    parent->AddComponent(wt);
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
    //auto debugMesh = MeshFactory::CreateMesh(*(shape.get()), 1.0f);
    auto hs = GetHotSpot(ref, shape);

    // logic to draw the debug mesh
//    glm::vec2 debugMeshPos(0.0f);
//    std::string align = table.Get<std::string>("align", "topleft");
//    int layer = table.Get<int>("layer", 1);
//    if (align == "bottomright") {
//        debugMeshPos = glm::vec2(-bounds.max.x, 0.0f);
//    } else if (align == "topleft") {
//        debugMeshPos = glm::vec2(0.0f, bounds.min.y);
//    } else if (align == "topright") {
//        debugMeshPos = glm::vec2(-bounds.max.x, bounds.min.y);
//    }
//
//    auto ce = std::make_shared<Entity>();
    //ce->SetPosition(debugMeshPos);
    //ce->SetLayer(layer);
    //auto cer = std::make_shared<Renderer>();
    //cer->SetMesh(debugMesh);
    //ce->AddComponent(cer);

    //parent->AddChild(ce);
    parent->AddComponent(renderer);
    parent->AddComponent(hs);
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
                q.z = qt.Get<float>("z", 0.0f);
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
    } else if (type=="line") {
        glm::vec2 A = at.Get<glm::vec2>("A");
        glm::vec2 B = at.Get<glm::vec2>("B");
        return std::make_shared<Line>(A, B);
    } else if (type == "poly") {
        std::vector<float> outline = at.GetVector<float>("outline");
        std::vector<glm::vec2> points;
        for (int i = 0; i < outline.size(); i = i + 2)
            points.push_back(glm::vec2(outline[i], outline[i + 1]));
        if (at.HasKey("holes")) {
            std::unique_ptr<Polygon> mainOutline(new Polygon(points));
            luabridge::LuaRef holes = at.Get<luabridge::LuaRef>("holes");
            LuaTable ha(holes);
            auto poly = std::make_shared<Poly>(std::move(mainOutline));
            for (int j = 0; j < holes.length(); ++j) {
                luabridge::LuaRef h = holes[j + 1];
                std::vector<float> holeOutline = ReadVector<float>(h);
                std::vector<glm::vec2> points;
                for (int i = 0; i < holeOutline.size(); i = i + 2)
                    points.push_back(glm::vec2(holeOutline[i], holeOutline[i + 1]));
                poly->AddHole(std::unique_ptr<Polygon>(new Polygon(points)));

            }
            return poly;

        } else {


            return std::make_shared<Polygon>(points);
        }
    } else if (type == "circle") {
        float radius = at.Get<float>("radius");
        return std::make_shared<Circle>(radius, offset);
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
    } else if (type =="compound") {
        luabridge::LuaRef rshapes = at.Get<luabridge::LuaRef>("shapes");
        auto cs = std::make_shared<CompoundShape>();
        for (int i = 0; i<rshapes.length(); ++i) {
            luabridge::LuaRef rshape = rshapes[i+1];
            auto s = ReadShape(rshape);
            cs->AddShape(s);
        }
        return cs;
    }

    return nullptr;
}

void MonkeyFactory::PostInit() {

    // Create the local assets
    luabridge::LuaRef roomRef = luabridge::getGlobal(LuaWrapper::L, "room");
    LuaTable roomTable(roomRef);
    if (roomTable.HasKey("afterstartup")) {
        luabridge::LuaRef r1 = roomTable.Get<luabridge::LuaRef>("afterstartup");
        r1();
    }
}


