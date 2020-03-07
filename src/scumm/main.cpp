#include <iostream>
#include <monkey/lua/luawrapper.h>
#include <monkey/lua/luatable.h>
#include <monkey/engine.h>
#include <set>
#include <version.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include "factories.h"

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
        auto factory = std::make_shared<SceneFactory>();
        Extension ext;
        ext.extend(factory.get());
        engine.SetSceneFactory(factory);
        engine.Init(homeDir, game);
        ext.extendLua();
        engine.MainLoop();
    }
    catch (Error & err) {
        std::cerr << err.what() << std::endl;
        return 1;
    }
    catch (luabridge::LuaException & e) {
        std::cerr << e.what();
    }
    catch (nlohmann::json::parse_error & ecd) {
        std::cerr << ecd.what();

    }
    return 0;
}
