#include <iostream>
#include <gfx/lua/luawrapper.h>
#include <gfx/lua/luatable.h>
#include <phy/phyfactory.h>
#include <gfx/monkey.h>
#include <set>


int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Usage: phy <directory>" << std::endl;
        return 1;
    }
    try {
        std::string homeDir(argv[1]);
        Engine::get().GetAssetManager().SetDirectory(homeDir);
        Monkey& m = Monkey::get();
        m.Init<PhyFactory>();
        m.Start();

    } catch (Error& err) {
        std::cout << err.what() << std::endl;
        return 1;
    } catch (...) {

    }
    return 0;
}
