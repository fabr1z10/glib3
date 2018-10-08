#include <gfx/monkeyfactory.h>
#include <gfx/monkey.h>
#include <iostream>
#include <gfx/spritemesh.h>
#include <glm/gtx/transform.hpp>
#include <gfx/math/geom.h>
//#include <mo/components/scriptwalktrigger.h>

using namespace luabridge;

MonkeyFactory::MonkeyFactory() {

    AddFactory<TextComponentFactory>("text");
    AddFactory<OutlineTextComponentFactory>("outlinetext");
    AddFactory<CameraFactory>("camera");
    AddFactory<KeyInputFactory>("keyinput");
    AddFactory<GfxComponentFactory>("gfx");
    AddFactory<ColliderComponentFactory>("collider");
    //AddFactory<WalkAreaComponentFactory>("walkarea");
    AddFactory<HotSpotComponentFactory>("hotspot");
    AddFactory<StateMachineComponentFactory>("statemachine");
    AddFactory<LuaKeyboardComponentFactory>("luakey");
    AddFactory<SwitchComponentFactory>("switch");
    AddFactory<DepthComponentFactory>("depth");
    AddFactory<InfoComponentFactory>("info");
    AddFactory<FollowComponentFactory>("follow");
    AddFactory<BillboardComponentFactory>("billboard");
    //AddFactory<ScalingComponentFactory>("scaling");
    AddFactory<ButtonComponentFactory>("button");
    AddFactory<TextViewComponentFactory>("textview");
    AddFactory<ShadowComponentFactory>("shadow");
    AddFactory<Controller2DComponentFactory>("controller2d");
    AddFactory<Dynamics2DComponentFactory>("dynamics2d");

    AddRunnerFactory<HotSpotManagerFactory>("hotspotmanager");
    AddRunnerFactory<SchedulerFactory>("scheduler");
    AddRunnerFactory<CollisionEngineFactory>("collision");

    m_specialKeys.insert("tag");
    m_specialKeys.insert("name");
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

    std::cout << "Loading engines ...\n";
    if (roomTable.HasKey("engines")) {
        luabridge::LuaRef engines = roomTable.Get<luabridge::LuaRef>("engines");
        for (int i = 0; i < engines.length(); ++i) {
            luabridge::LuaRef e = engines[i+1];
            std::string type = e["type"].cast<std::string>();
            auto it = m_runnerFactories.find(type);
            if (it == m_runnerFactories.end()) {
                GLIB_FAIL("Unknown runner " << type);
            }
            std::cout << "Adding runner: " << type << std::endl;
            it->second->Create(e);
        }
    }



    // read assets
    luabridge::LuaRef assets = roomTable.Get<luabridge::LuaRef>("assets");
    for (int i = 0; i < assets.length();++i) {
        luabridge::LuaRef a = assets[i+1];
        LuaTable assetTable(a);
        std::string type = assetTable.Get<std::string>("type");
        if (type == "sprite") {
           ReadSprite(assetTable);
        }
    }

    // read the scene tree
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

}

std::shared_ptr<Entity> MonkeyFactory::ReadItem(luabridge::LuaRef& ref) {
    LuaTable item(ref);
    auto entity = std::make_shared<Entity>();
    std::string tag = item.Get<std::string>("tag", "");
    std::string name = item.Get<std::string>("name", "");
    if (!tag.empty()) entity->SetTag(tag);
    if (!name.empty()) entity->SetName(name);
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
        //std::cout << "Reading " << pair.first << "\n";
        if (iter == m_componentFactories.end()) {
            if (m_specialKeys.count(pair.first) == 0) {
                GLIB_FAIL("Unknown component " << pair.first);
            }
        } else {
            iter->second->operator()(pair.second, entity.get());
        }
    }


    if (item.HasKey("children")) {
        luabridge::LuaRef c = item.Get<luabridge::LuaRef>("children");
        ReadItems (c, entity.get());
    }
    //entity->SetActive(active);
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

//
//
//
//void MonkeyFactory::ReadKeyboardComponent(luabridge::LuaRef &ref, Entity *parent) {
//    LuaTable table(ref);
//
//    //luabridge::LuaRef shapeR = table.Get<luabridge::LuaRef>("shape");
//    //auto shape = ReadShape(shapeR);
//    parent->AddComponent(std::make_shared<KeyboardController>());
//}
//






//std::shared_ptr<HotSpot> MonkeyFactory::GetHotSpot (luabridge::LuaRef& ref) {
//    LuaTable table(ref);
//    luabridge::LuaRef shapeR = table.Get<luabridge::LuaRef>("shape");
//    auto shape = ReadShape(shapeR);
//    return GetHotSpot(ref, shape);
//
//}



//std::shared_ptr<Renderer> MonkeyFactory::GetTextComponent (luabridge::LuaRef& ref) {
//    LuaTable table(ref);
//    auto renderer = std::make_shared<Renderer>();
//    std::string text = table.Get<std::string>("id");
//    std::string font = table.Get<std::string>("font");
//    float size = table.Get<float>("size", 8);
//    TextAlignment align = table.Get<TextAlignment>("align", TOP_LEFT);
//    float maxWidth = table.Get<float>("maxwidth", 0.0f);
//    glm::vec4 color = table.Get<glm::vec4>("color", glm::vec4(255.0f));
//    color /= 255.0f;
//    Font* f = Engine::get().GetAssetManager().GetFont(font);
//    auto mesh = std::make_shared<TextMesh>(f, text, size, align, maxWidth);
//    glm::vec2 offset = mesh->getOffset();
//    renderer->SetRenderingTransform(glm::translate(glm::vec3(offset, 0.0f)));
//    renderer->SetTint(color);
//    renderer->SetMesh(mesh);
//    return renderer;
//}
//
//
//void MonkeyFactory::ReadCursor (luabridge::LuaRef& ref, Entity* parent) {
//    LuaTable table(ref);
//    auto cursor = std::make_shared<Cursor>();
//    parent->AddComponent(cursor);
//}



//void MonkeyFactory::ReadWalkTrigger (luabridge::LuaRef& ref, Entity* parent) {
//    LuaTable table(ref);
//    luabridge::LuaRef shapeR = table.Get<luabridge::LuaRef>("shape");
//    auto shape = ReadShape(shapeR);
//
//    std::string target = table.Get<std::string>("target");
//    auto wt = std::make_shared<ScriptWalkTrigger>(shape, target);
//    if (table.HasKey("onenter")) {
//        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onenter");
//        wt->SetOnEnter(r);
//    }
//    if (table.HasKey("onleave")) {
//        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onleave");
//        wt->SetOnLeave(r);
//    }
//    if (table.HasKey("onstay")) {
//        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onstay");
//        wt->SetOnStay(r);
//    }
//    parent->AddComponent(wt);
//}





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


