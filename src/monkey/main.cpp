#include <iostream>
#include <monkey/lua/luawrapper.h>
#include <monkey/lua/luatable.h>
#include <monkey/engine.h>
#include <set>
#include <foo.h>
#include <nlohmann/json.hpp>
#include <fstream>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "The Monkey Engine " << VERSION << "\n";
        std::cout << "Usage: monkey <directory>" << std::endl;
        return 1;
    }
    try {
        // read config file
        std::ifstream ifs("config.json");
        nlohmann::json j = nlohmann::json::parse(ifs);
        std::string homeDir = j["home"];
        std::string game(argv[1]);
        auto& engine = Engine::get();
        engine.SetSceneFactory(std::unique_ptr<SceneFactory>(new SceneFactory));
        engine.Init(homeDir, game);
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