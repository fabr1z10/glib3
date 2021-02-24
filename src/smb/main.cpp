#include <iostream>
#include <version.h>
#include <monkey/engine.h>
#include "factories.h"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "The Monkey Engine " << VERSION << "\n";
        std::cout << "Usage: monkey <directory>" << std::endl;
        return 1;
    }
    try {
        std::string gameDir(argv[1]);
        auto& engine = Engine::get();
        auto* factory = engine.GetSceneFactory();
        Extension ext;
        //Extension ext;
        ext.extend(factory);
        engine.init(gameDir);
        engine.MainLoop();

//        // read config file
//        std::ifstream ifs("config.json");
//        nlohmann::json j = nlohmann::json::parse(ifs);
//        std::string homeDir = j["home"];
//        std::string game(argv[1]);
//        auto& engine = Engine::get();
//        auto factory = std::make_shared<SceneFactory>();
//        Extension ext;
//        ext.extend(factory.get());
//        engine.SetSceneFactory(factory);
//        engine.Init(homeDir, game);
//        engine.MainLoop();
    }
    catch (Error & err) {

        std::cout << err.what() << std::endl;
        return 1;
    }

    return 0;
}
