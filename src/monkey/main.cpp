#include <iostream>
#include <monkey/luawrapper.h>
#include <monkey/luatable.h>
#include <gfx/error.h>
#include <gfx/engine.h>
#include <monkey/monkeyfactory.h>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: monkey <directory>";
        return 1;
    }

    try {
        std::string homeDir(argv[1]);
        LuaWrapper::Init();
        LuaWrapper::Load(homeDir + "main.lua");
        LuaTable a("engine");
        //int c = a.Get<int>("ciao");
        glm::vec2 devSize = a.Get<glm::vec2>("device_size");
        glm::vec2 winSize = a.Get<glm::vec2>("window_size");
        std::string title = a.Get<std::string>("title");
        //std::cout << "prova = " << a.Get<int>("prova")<< "\n";

        luabridge::LuaRef r = luabridge::getGlobal(LuaWrapper::L, "ciao");
        r();
        a.Set("prova", 20);
        //std::cout << "prova = " << a.Get<int>("prova")<< "\n";
        r();
//        EngineConfig config (devSize.x, devSize.y);
//        config.enableMouse = true;
//        config.enableKeyboard = true;
//        config.windowWidth = winSize.x;
//        config.windowHeight = winSize.y;
//        config.name = title;
//        Engine &g = Engine::get();
//        g.Init(config);
//        g.SetSceneFactory(std::unique_ptr<SceneFactory>(new MonkeyFactory));
//        g.MainLoop();

    } catch (Error& err) {
        std::cerr << err.what();
        return 1;
    }
    std::cout << "pippo\n";
    return 0;
}
