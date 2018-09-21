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
#include <gfx/keyinput.h>

using namespace luabridge;

MonkeyFactory::MonkeyFactory() {

    AddFactory<TextComponentFactory>("text");
    AddFactory<OutlineTextComponentFactory>("outlinetext");
    AddFactory<CameraFactory>("camera");
    AddFactory<KeyInputFactory>("keyinput");
    AddFactory<GfxComponentFactory>("gfx");
    AddFactory<ColliderComponentFactory>("collider");
    AddFactory<WalkAreaComponentFactory>("walkarea");
    AddFactory<HotSpotComponentFactory>("hotspot");
    AddFactory<KeyboardCollisionComponentFactory>("keyboardcontrollercollision");
    AddFactory<LuaKeyboardComponentFactory>("luakey");
    AddFactory<SwitchComponentFactory>("switch");
    AddFactory<DepthComponentFactory>("depth");
    AddFactory<InfoComponentFactory>("info");

    m_specialKeys.insert("tag");
    m_specialKeys.insert("pos");
    m_specialKeys.insert("angle");
    m_specialKeys.insert("children");
    m_specialKeys.insert("active");
}


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
    bool active = item.Get<bool>("active", true);
    if (item.HasKey("angle")) {
        float angle = item.Get<float>("angle",0.0f);
        entity->SetPosition(pos, deg2rad* angle);
    } else {
        entity->SetPosition(pos);
    }


    // int layer = item.Get<int>("layer", 0);


    auto keyValueMap = LuaTable::getKeyValueMap(ref);
    for (auto& pair : keyValueMap) {
        auto iter = m_componentFactories.find(pair.first);
        std::cout << "Reading " << pair.first << "\n";
        if (iter == m_componentFactories.end()) {
            if (m_specialKeys.count(pair.first) == 0) {
                GLIB_FAIL("Unknown component " << pair.first);
            }
        } else {
            iter->second->operator()(pair.second, entity.get());
        }
    }
//
//
//
//
//    if (item.HasKey("camera")) {
//        LuaRef cam = item.Get<LuaRef>("camera");
//        LuaTable tcam(cam);
//        std::string camType = tcam.Get<std::string>("type");
//        std::string tag = tcam.Get<std::string>("tag", "");
//        glm::vec2 pos = tcam.Get<glm::vec2>("pos", glm::vec2(0.0f));
//        glm::vec4 viewport = tcam.Get<glm::vec4>("viewport", glm::vec4(0.0f, 0.0f, Engine::get().GetDeviceSize()));
//        if (camType == "ortho") {
//            // orhographic camera
//            glm::vec2 size = tcam.Get<glm::vec2>("size");
//            glm::vec4 bounds = tcam.Get<glm::vec4>("bounds", glm::vec4(0.0));
//
//            auto camera = std::unique_ptr<OrthographicCamera> (new OrthographicCamera(size.x, size.y, viewport));
//            if (bounds != glm::vec4(0.0f))
//                camera->SetBounds(bounds[0], bounds[2], bounds[1], bounds[3]);
//            camera->SetPosition(glm::vec3(pos, 5.0f), glm::vec3(0,0,-1), glm::vec3(0,1,0));
//            if (!tag.empty())
//                camera->SetTag(tag);
//            entity->SetCamera(std::move(camera));
//        }
//
//
//    }
//
//

//    if (item.HasKey("gfx")) {
//        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("gfx");
//        ReadGfxComponent(c, entity.get());
//    }
//    if (item.HasKey("textview")) {
//        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("textview");
//        ReadTextViewComponent(c, entity.get());
//    }
//    if (item.HasKey("text")) {
//        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("text");
//        ReadTextComponent(c, entity.get());
//    }
//    if (item.HasKey("keyinput")) {
//        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("keyinput");
//        ReadKeyInputComponent(c, entity.get());
//    }
//    if (item.HasKey("collider")) {
//        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("collider");
//        ReadColliderComponent(c, entity.get());
//    }
//    if (item.HasKey("keyboardcontroller")) {
//        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("keyboardcontroller");
//        ReadKeyboardComponent(c, entity.get());
//    }
//    if (item.HasKey("keyboardcontrollercollision")) {
//        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("keyboardcontrollercollision");
//        ReadKeyboardCollisionComponent(c, entity.get());
//    }
//    if (item.HasKey("luakey")) {
//        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("luakey");
//        ReadLuaKeyboard(c, entity.get());
//    }
//    if (item.HasKey("outlinetext")) {
//        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("outlinetext");
//        ReadOutlineTextComponent(c, entity.get());
//    }
//    if (item.HasKey("follow")) {
//        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("follow");
//        ReadFollowComponent(c, entity.get());
//    }
//    if (item.HasKey("walkarea")) {
//        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("walkarea");
//        ReadWalkarea(c, entity.get());
//    }
//    if (item.HasKey("hotspot")) {
//        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("hotspot");
//        ReadHotspot(c, entity.get());
//    }
//    if (item.HasKey("button")) {
//        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("button");
//        ReadButton(c, entity.get());
//    }
//    if (item.HasKey("scaling")) {
//        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("scaling");
//        ReadScaling(c, entity.get());
//    }
//    if (item.HasKey("walktrigger")) {
//        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("walktrigger");
//        ReadWalkTrigger(c, entity.get());
//    }
//    if (item.HasKey("cursor")) {
//        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("cursor");
//        ReadCursor(c, entity.get());
//    }
//    //entity->SetLayer(layer);

    if (item.HasKey("children")) {
        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("children");
        ReadItems (c, entity.get());
    }
    entity->SetActive(active);
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



//
//void MonkeyFactory::ReadTextComponent(luabridge::LuaRef &ref, Entity *parent) {
//    auto renderer = GetTextComponent(ref);
//    parent->AddComponent(renderer);
//}
//
//void MonkeyFactory::ReadKeyInputComponent(luabridge::LuaRef &ref, Entity *parent) {
//    LuaTable table(ref);
//    int maxLength = table.Get<int>("maxlength");
//    luabridge::LuaRef shapeR = table.Get<luabridge::LuaRef>("func");
//    parent->AddComponent(std::make_shared<KeyInput>(maxLength, shapeR));
//}

void MonkeyFactory::ReadFollowComponent(luabridge::LuaRef &ref, Entity *parent) {
    LuaTable table(ref);
    std::string cam = table.Get<std::string>("cam");
    parent->AddComponent(std::make_shared<Follow>(cam));
}


void MonkeyFactory::ReadKeyboardComponent(luabridge::LuaRef &ref, Entity *parent) {
    LuaTable table(ref);

    //luabridge::LuaRef shapeR = table.Get<luabridge::LuaRef>("shape");
    //auto shape = ReadShape(shapeR);
    parent->AddComponent(std::make_shared<KeyboardController>());
}







//std::shared_ptr<HotSpot> MonkeyFactory::GetHotSpot (luabridge::LuaRef& ref) {
//    LuaTable table(ref);
//    luabridge::LuaRef shapeR = table.Get<luabridge::LuaRef>("shape");
//    auto shape = ReadShape(shapeR);
//    return GetHotSpot(ref, shape);
//
//}



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
    auto mesh = std::make_shared<TextMesh>(f, text, size, align, maxWidth);
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



void MonkeyFactory::PostInit() {

    // Create the local assets
    luabridge::LuaRef roomRef = luabridge::getGlobal(LuaWrapper::L, "room");
    LuaTable roomTable(roomRef);
    if (roomTable.HasKey("afterstartup")) {
        luabridge::LuaRef r1 = roomTable.Get<luabridge::LuaRef>("afterstartup");
        r1();
    }
}


