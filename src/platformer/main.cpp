#include <iostream>
#include <gfx/lua/luawrapper.h>
#include <gfx/lua/luatable.h>
#include <platformer/platformerfactory.h>
#include <gfx/monkey.h>
#include <set>
#include <gfx/components/statemachine.h>
int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Usage: monkey <directory>" << std::endl;
        return 1;
    }
    try {


        std::string homeDir(argv[1]);
        Engine::get().GetAssetManager().SetDirectory(homeDir);
        Monkey& m = Monkey::get();
        m.Init<PlatformerFactory>();
        m.Start();

    } catch (Error& err) {
        std::cout << err.what() << std::endl;
        return 1;
    } catch (...) {

        int ciao = 2;
    }
    return 0;
}
