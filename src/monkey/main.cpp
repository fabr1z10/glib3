#include <iostream>
#include <gfx/lua/luawrapper.h>
#include <gfx/lua/luatable.h>
#include <monkey/monkeyfactory.h>
#include <gfx/engine.h>
#include <set>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Usage: monkey <directory>" << std::endl;
        return 1;
    }
    try {
        std::string homeDir(argv[1]);
        auto& engine = Engine::get();
        engine.SetSceneFactory(std::unique_ptr<SceneFactory>(new MonkeyFactory));
        engine.Init(homeDir);
        engine.MainLoop();
    } catch (Error& err) {
        std::cout << err.what() << std::endl;
        return 1;
    } catch (...) {

    }
    return 0;
}