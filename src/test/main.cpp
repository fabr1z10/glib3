#include <test/io.h>
#include <gfx/engine.h>
#include <test/testgfx.h>
#include <test/solution.h>
#include <iostream>
#include <test/global.h>
//
//std::string homeDir;
//
//void testTCS() {
//    Solution s("/home/fabrizio/sources/tcs_processor/TestCaseUP/output/output_BR_76_Scenario_2_B_planner_input.xml");
//    std::cout << s.GetPosition("MNPPC", 1517810300) << std::endl;
//    std::cout << s.GetPosition("MNPPC", 1517810400) << std::endl;
//    std::cout << s.GetPosition("MNPPC", 1517810527) << std::endl;
//    std::cout << s.GetPosition("MNPPC", 1517810528) << std::endl;
//    std::cout << s.GetPosition("MNPPC", 1517813767) << std::endl;
//    std::cout << s.GetPosition("MNPPC", 1517813768) << std::endl;
//
//
//
//}

int main(int argc, char* argv[]) {

    //return 0;
    try {
        if (argc < 3) {
            std::cerr << "Usage: viewer <dir> <solution>\n";
            return 1;
        }
        Config::get().SetHomeDir(argv[1]);
        Config::get().GetRailway().Load();
        Solution s(argv[2]);

        glm::vec2 devSize (800, 600);
        glm::vec2 winSize = devSize;
        std::string title = "Solution viewer";
        EngineConfig config (devSize.x, devSize.y);
        config.enableMouse = true;
        config.enableKeyboard = true;
        config.windowWidth = winSize.x;
        config.windowHeight = winSize.y;
        config.name = title;
        Engine &g = Engine::get();
        g.Init(config);

        // set-up the rendering engine
        auto renderingEngine = std::unique_ptr<RenderingEngine>(new RenderingEngine);
        renderingEngine->AddShader(TEXTURE_SHADER);
        renderingEngine->AddShader(COLOR_SHADER);
        renderingEngine->AddShader(TEXT_SHADER);
        g.SetRenderingEngine(std::move(renderingEngine));

        //LoadFonts();
        auto factory = std::unique_ptr<SceneFactory>(new SceneFactory3(s));
        //factory->extendLua();
        g.SetSceneFactory(std::move(factory));
//
//        // set-up the scripting engine
//        auto scheduler = std::make_shared<Scheduler>();
//        g.AddRunner(scheduler);
//        //g.SetScriptingEngine(std::move(scheduler));
//
        Engine::get().GetAssetManager().AddFont("main", "/home/fabrizio/Scaricati/arial.ttf");
        g.MainLoop();
    } catch (Error& err){
        std::cerr << err.what() << std::endl;
        return 1;
    }
}


