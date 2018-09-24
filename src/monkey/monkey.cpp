//
//  monkey.cpp
//  glib
//
//  Created by Fabrizio Venturini on 19/05/2018.
//
//

#include <monkey/monkey.h>
#include <gfx/engine.h>
#include <monkey/monkeyfactory.h>
#include <gfx/hotspot.h>
#include <monkey/luakeylistener.h>
#include <gfx/collisionengine.h>

Monkey::Monkey() {
    LuaWrapper::Init();
    luabridge::setGlobal(LuaWrapper::L,Engine::get().GetAssetManager().GetDirectory().c_str(), "_path" );
    LuaWrapper::Load(Engine::get().GetAssetManager().GetDirectory() + "main.lua");
    AddTable("engine");
    AddTable("variables");
}

void Monkey::LoadFonts() {
    // load fonts
    luabridge::LuaRef fonts = luabridge::getGlobal(LuaWrapper::L, "fonts");
    for (int i = 0; i < fonts.length(); ++i) {
        luabridge::LuaRef f = fonts[i+1];
        std::string name = f["name"].cast<std::string>();
        std::string file = f["file"].cast<std::string>();
        Engine::get().GetAssetManager().AddFont(name, file);
    }
}

void Monkey::AddTable (const std::string& name) {
    m_tables.insert(std::make_pair(name, LuaTable(name)));
    
}

void Monkey::Start() {
    LuaTable& engine =(*this)["engine"];
    glm::vec2 devSize = engine.Get<glm::vec2>("device_size");
    glm::vec2 winSize = engine.Get<glm::vec2>("window_size");
    std::string title = engine.Get<std::string>("title");


    EngineConfig config (devSize.x, devSize.y);
    config.enableMouse = true;
    config.enableKeyboard = true;
    config.windowWidth = winSize.x;
    config.windowHeight = winSize.y;
    config.name = title;
    Engine &g = Engine::get();

    g.Init(config);

    // set-up the rendering engine
    auto renderingEngine = std::unique_ptr<RenderingEngine>(new RenderingEngine);
    renderingEngine->AddShader(TEXTURE_SHADER);
    renderingEngine->AddShader(COLOR_SHADER);
    renderingEngine->AddShader(TEXT_SHADER);
    g.SetRenderingEngine(std::move(renderingEngine));

    // set-up the scripting engine
//    auto scheduler = std::unique_ptr<Scheduler>(new Scheduler);
//    g.SetScriptingEngine(std::move(scheduler));
//
//    // set up the collision engine
//    if (collisionEngine) {
//        auto ce = std::unique_ptr<CollisionEngine>(new CollisionEngine(collisionSize.x, collisionSize.y));
//        g.SetCollisionEngine(std::move(ce));
//    }

    // set-up the input system (mouse & keyboard)
    //auto hsm = std::unique_ptr<HotSpotManager>(new HotSpotManager);
    //g.RegisterToMouseEvent(hsm.get());

//    std::unique_ptr<LuaKeyListener> kl(new LuaKeyListener);
//    luabridge::LuaRef hk = luabridge::getGlobal(LuaWrapper::L, "hotkeys");
//    if (!hk.isNil()) {
//        for (int i = 0; i < hk.length(); ++i) {
//            luabridge::LuaRef h = hk[i + 1];
//            int keyCode = h["key"].cast<int>();
//            luabridge::LuaRef ref = h["func"];
//            kl->AddHotKey(keyCode, ref);
//        }
//    }
//    g.RegisterToKeyboardEvent(std::move(kl));


//    auto hotspotManager = std::make_shared<HotSpotManager>();
//
//
//
//    engineNode->AddComponent(renderingEngine);
//    engineNode->AddComponent(scheduler);


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
//
//
//
//    engineNode->AddComponent(hotspotManager);
//    engineNode->AddComponent(keyListener);
//    entity->AddChild(engineNode);


    LoadFonts();
    g.SetSceneFactory(std::unique_ptr<SceneFactory>(new MonkeyFactory));

    g.MainLoop();
    
    
}


LuaTable& Monkey::operator[] (const std::string& key) {
    auto it = m_tables.find(key);
    if (it == m_tables.end()) {
        GLIB_FAIL("Unknown table " << key);
    }
    return it->second;
}
