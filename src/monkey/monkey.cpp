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

Monkey::Monkey() {
    LuaWrapper::Init();
    LuaWrapper::Load(Engine::get().GetAssetManager().GetDirectory() + "main.lua");
    AddTable("engine");
    AddTable("variables");
    
    
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
