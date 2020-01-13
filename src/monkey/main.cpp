#include <iostream>
#include <monkey/lua/luawrapper.h>
#include <monkey/lua/luatable.h>
#include <monkey/engine.h>
#include <set>
#include <foo.h>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "The Monkey Engine " << VERSION << "\n";
        std::cout << "Usage: monkey <directory>" << std::endl;
        return 1;
    }
    try {
        std::string homeDir(argv[1]);
        auto& engine = Engine::get();
        engine.SetSceneFactory(std::unique_ptr<SceneFactory>(new SceneFactory));
        engine.Init(homeDir);
        engine.MainLoop();
    } catch (Error& err) {
        std::cout << err.what() << std::endl;
        return 1;
    } catch (luabridge::LuaException& e) {
        std::cerr << e.what ();
    } catch (...) {

    }
    return 0;
}