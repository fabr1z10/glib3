#pragma once

#include <gfx/lua/luatable.h>
#include <gfx/singleton.h>
#include <gfx/engine.h>
#include <unordered_map>

class Monkey : public Singleton<Monkey> {
public:
    LuaTable& operator[] (const std::string& key);
    void AddTable (const std::string& name);
    Monkey();

    template <typename SCENE_FACTORY>
    void Init() {

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

        LoadFonts();
        g.SetSceneFactory(std::unique_ptr<SceneFactory>(new SCENE_FACTORY));
    }

    void Start();
    
private:
    void LoadFonts();
    std::unordered_map<std::string, LuaTable> m_tables;
};
