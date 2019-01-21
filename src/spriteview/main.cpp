#include <iostream>
#include <gfx/lua/luawrapper.h>
#include <gfx/lua/luatable.h>
#include <platformer/platformerfactory.h>
#include <gfx/monkey.h>
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

        auto& m = SpriteView::get();
        m.Init(argv[1]);
        m.Start();

    } catch (Error& err) {
        std::cout << err.what() << std::endl;
        return 1;
    } catch (...) {

    }
    return 0;
}