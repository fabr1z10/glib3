#include <iostream>
#include <gfx/lua/luawrapper.h>
#include <gfx/lua/luatable.h>
#include <monkey/monkeyfactory.h>
#include <monkey/monkeyactivityfactory.h>
#include <gfx/monkey.h>
#include <set>

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
        m.Init<MonkeyFactory>();
        m.Start();

    } catch (Error& err) {
        std::cout << err.what() << std::endl;
        return 1;
    } catch (...) {

    }
    return 0;
}