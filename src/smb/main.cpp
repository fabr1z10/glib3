#include <iostream>
#include <monkey/lua/luawrapper.h>
#include <monkey/lua/luatable.h>
#include <platformer/platformerfactory.h>
#include <set>
#include <monkey/engine.h>


int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Usage: monkey <directory>" << std::endl;
        return 1;
    }
    try {
        std::string homeDir(argv[1]);
        auto& engine = Engine::get();
        engine.SetSceneFactory(std::unique_ptr<SceneFactory>(new PlatformerFactory));
        engine.Init(homeDir);
        engine.MainLoop();

    } catch (Error& err) {
        std::cout << err.what() << std::endl;
        return 1;
    } catch (...) {

    }
    return 0;
}
