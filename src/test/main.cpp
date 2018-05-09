#include <iostream>
#include "test/io.h"
#include "gfx/engine.h"
#include <gfx/error.h>
#include "test/testgfx.h"


//void TestPoly1() {
//
//    std::vector<glm::vec2> a1 { glm::vec2(0, 0), glm::vec2(0, 10), glm::vec2(10, 10), glm::vec2(10, 0)};
//    Polygon p (a1);
//    std::cout << p.isPointInside(glm::vec2(0,0)) << std::endl;
//    std::cout << p.isPointInside(glm::vec2(3,3)) << std::endl;
//    std::cout << p.isPointInside(glm::vec2(12,0)) << std::endl;
//    std::cout << p.isPointInside(glm::vec2(8,4)) << std::endl;
//}


int main() {
    try {
        App::Init(320, 200, 800, 600, "Hello world!");
        EngineConfig config;
        config.window = window;
        Engine &g = Engine::get();
        g.Init(config);
        g.SetSceneFactory(std::unique_ptr<Factory1>(new Factory1));
        g.MainLoop();
    } catch (Error& err){
        std::cerr << err.what() << std::endl;
        return 1;
    }

    //TestPoly1();
    return 0;
//    Graph<int> g;
//
//    // add two nodes, labeled 1 and 2
//    for (int i = 0; i <= 8; ++i)
//        g.AddNode(i);
//
//    g.AddEdge(0, 1, 4);
//    g.AddEdge(0, 7, 8);
//    g.AddEdge(1, 7, 11);
//    g.AddEdge(1, 2, 8);
//    g.AddEdge(7, 8, 7);
//    g.AddEdge(7, 6, 1);
//    g.AddEdge(6, 8, 6);
//    g.AddEdge(2, 8, 2);
//    g.AddEdge(2, 3, 7);
//    g.AddEdge(2, 5, 4);
//    g.AddEdge(6, 5, 2);
//    g.AddEdge(3, 5, 14);
//    g.AddEdge(3, 4, 9);
//    g.AddEdge(5, 4, 10);
//    std::cout << "Number of nodes = " << g.GetNodeCount() << std::endl;
//    auto path = FindShortestPath(g, 0, 8);
//    printPath(path);
//    path = FindShortestPath(g, 0, 4);
//    printPath(path);
//
}


