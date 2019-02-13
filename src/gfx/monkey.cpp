//
//  monkey.cpp
//  glib
//
//  Created by Fabrizio Venturini on 19/05/2018.
//
//

#include <gfx/monkey.h>
#include <gfx/engine.h>

void Monkey::InitLUA() {
    // initialize lua
    LuaWrapper::Init();
    luabridge::setGlobal(LuaWrapper::L,Engine::get().GetDirectory().c_str(), "_path" );
    LuaWrapper::Load(Engine::get().GetDirectory() + "main.lua");
    AddTable("engine");
    AddTable("variables");
}



//void Monkey::LoadFonts() {
//    // load fonts
//    auto fontsRef = LuaWrapper::GetGlobal("fonts");
//    if (!fontsRef.isNil()) {
//        for (int i = 0; i < fontsRef.length(); ++i) {
//            luabridge::LuaRef f = fontsRef[i + 1];
//            std::string name = f["name"].cast<std::string>();
//            std::string file = f["file"].cast<std::string>();
//            Engine::get().GetAssetManager().AddFont(name, file);
//        }
//    }
//}

void Monkey::AddTable (const std::string& name) {
    m_tables.insert(std::make_pair(name, LuaTable(name)));

}

void Monkey::Start() {
    Engine &g = Engine::get();
    g.MainLoop();
}



LuaTable& Monkey::operator[] (const std::string& key) {
    auto it = m_tables.find(key);
    if (it == m_tables.end() || it->second.isNil()) {
        GLIB_FAIL("Unknown table " << key);
    }
    return it->second;
}
