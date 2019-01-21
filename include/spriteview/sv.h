#pragma once

#include <gfx/lua/luatable.h>
#include <gfx/singleton.h>
#include <gfx/engine.h>
#include <spriteview/svfactory.h>
#include <unordered_map>

class SpriteView : public Singleton<SpriteView> {
public:
    SpriteView();

    void Init(const std::string& dir) {
        m_dir = dir;
        EngineConfig config (800, 600);
        config.enableMouse = true;
        config.enableKeyboard = true;
        config.windowWidth = 800;
        config.windowHeight = 600;
        config.shaders.push_back("unlit_textured");
        config.shaders.push_back("unlit_color");
        config.shaders.push_back("text");
        config.name = "Ciao";
        Engine &g = Engine::get();
        g.Init(config);
        LoadFonts();
        auto factory = std::unique_ptr<SceneFactory>(new SpriteViewFactory);
        g.SetSceneFactory(std::move(factory));
    }

    void Start();


private:
    std::string m_dir;
    void LoadFonts();
    std::unordered_map<std::string, LuaTable> m_tables;
};
