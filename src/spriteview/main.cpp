#include <iostream>
#include <gfx/lua/luawrapper.h>
#include <gfx/lua/luatable.h>
#include <platformer/platformerfactory.h>

#include <spriteview/sv.h>
#include <set>
#include <spriteview/sv.h>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Usage: spriteview <directory>" << std::endl;
        return 1;
    }
    try {
        std::string homeDir(argv[1]);
        auto& engine = Engine::get();
        engine.SetSceneFactory(std::unique_ptr<SceneFactory>(new SpriteViewFactory));
        engine.Init(homeDir);
        engine.MainLoop();


    } catch (Error& err) {
        std::cout << err.what() << std::endl;
        return 1;
    } catch (...) {

    }
    return 0;
}