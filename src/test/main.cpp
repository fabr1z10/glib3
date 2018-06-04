#include <test/io.h>
#include <gfx/engine.h>
#include <test/testgfx.h>
#include <test/solution.h>
#include <iostream>

std::string homeDir;

void testTCS() {
    Solution s("/home/fabrizio/sources/tcs_processor/TestCaseUP/output/output_BR_76_Scenario_2_B_planner_input.xml");
    std::cout << s.GetPosition("MNPPC", 1517810300) << std::endl;
    std::cout << s.GetPosition("MNPPC", 1517810400) << std::endl;
    std::cout << s.GetPosition("MNPPC", 1517810527) << std::endl;
    std::cout << s.GetPosition("MNPPC", 1517810528) << std::endl;
    std::cout << s.GetPosition("MNPPC", 1517813767) << std::endl;
    std::cout << s.GetPosition("MNPPC", 1517813768) << std::endl;



}

int main(int argc, char* argv[]) {
    std::string homeDir = "/home/fabrizio/sources/tcs_processor/TestCaseUP/";

//    try {
//        if (argc < 2)
//        {
//            std::cerr << "Usage: viewer <file>\n";
//            return 1;
//        }
//        std::string fileName(argv[1]);
//        if (argc == 3) {
//            homeDir = argv[2];
//        } else {
//            homeDir = "../TestCaseUP/";
//        }
//
//
//        Solution s(fileName);
//        //App::Init(800, 600, "Schedule viewer");
//
//        EngineConfig config (800, 600);
//        config.enableMouse = true;
//        config.enableKeyboard = true;
//        config.windowWidth = 800;
//        config.windowHeight = 600;
//        config.name = "Schedule viewer";
//        Engine &g = Engine::get();
//        g.Init(config);
//        g.SetSceneFactory(std::unique_ptr<SceneFactory>(new Factory2(s)));
//        g.MainLoop();
//    } catch (Error& err){
//        std::cerr << err.what() << std::endl;
//        return 1;
//    }
//
//    //TestPoly1();
//    return 0;
////    Graph<int> g;
////
////    // add two nodes, labeled 1 and 2
////    for (int i = 0; i <= 8; ++i)
////        g.AddNode(i);
////
////    g.AddEdge(0, 1, 4);
////    g.AddEdge(0, 7, 8);
////    g.AddEdge(1, 7, 11);
////    g.AddEdge(1, 2, 8);
////    g.AddEdge(7, 8, 7);
////    g.AddEdge(7, 6, 1);
////    g.AddEdge(6, 8, 6);
////    g.AddEdge(2, 8, 2);
////    g.AddEdge(2, 3, 7);
////    g.AddEdge(2, 5, 4);
////    g.AddEdge(6, 5, 2);
////    g.AddEdge(3, 5, 14);
////    g.AddEdge(3, 4, 9);
////    g.AddEdge(5, 4, 10);
////    std::cout << "Number of nodes = " << g.GetNodeCount() << std::endl;
////    auto path = FindShortestPath(g, 0, 8);
////    printPath(path);
////    path = FindShortestPath(g, 0, 4);
////    printPath(path);
//
}

