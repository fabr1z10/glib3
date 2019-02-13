#pragma once

#include <gfx/lua/luatable.h>
#include <gfx/singleton.h>
#include <gfx/engine.h>
#include <unordered_map>

class Monkey : public Singleton<Monkey> {
public:
    LuaTable& operator[] (const std::string& key);
    void AddTable (const std::string& name);
    Monkey() = default;

    template <typename SCENE_FACTORY>
    void Init(const std::string& home) {
        Engine::get().SetDirectory(home);
        InitLUA();

        LuaTable engine(std::string("engine"));
        //LuaTable& engine =(*this)["engine"];
        glm::vec2 devSize = engine.Get<glm::vec2>("device_size");
        glm::vec2 winSize = engine.Get<glm::vec2>("window_size");
        std::string title = engine.Get<std::string>("title");
        EngineConfig config (devSize.x, devSize.y);
        config.enableMouse = true;
        config.enableKeyboard = true;
        config.windowWidth = winSize.x;
        config.windowHeight = winSize.y;
        config.shaders = engine.GetVector<std::string>("shaders");
        config.name = title;
        Engine &g = Engine::get();
        g.Init(config);



        //LoadFonts();
        auto factory = std::unique_ptr<SceneFactory>(new SCENE_FACTORY);
        factory->extendLua();
        g.SetSceneFactory(std::move(factory));
    }

    void Start();
    
private:
    //  void LoadFonts();
    void InitLUA();
    std::unordered_map<std::string, LuaTable> m_tables;
};
