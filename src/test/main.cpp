#include <iostream>
#include <monkey/math/algo/closest.h>
#include <monkey/math/algo/graph.h>
#include <monkey/math/shapes/rect.h>
#include <monkey/math/geom.h>
#include <monkey/math/shapes/poly.h>

void help01 (std::shared_ptr<IShape> shape, glm::vec2 P, glm::vec2 o) {
    auto& ce = ClosestPointOnEdge::get();
    glm::vec2 p =  ce.find(P, shape.get());
    if (isEqual(p.x, o.x) && isEqual(p.y, o.y)) {
        std::cout << "OK\n";
    }
    else {
        std::cout << "FAIL\n";
    }

}

void t01 (float w, float h, float ox, float oy, glm::vec2 P, glm::vec2 out) {
    auto shape = std::make_shared<Rect>(w, h, glm::vec3(ox, oy, 0.0f));
    help01 (shape, P, out);

}

void t02 () {
    std::vector<float> outline = {0, 0, 100, 0, 100, 50, 0, 50};
    auto u = std::make_shared<Polygon>(outline);
    help01(u, glm::vec2(20.0f, 31.0f), glm::vec2(20.0f, 50.0f));
    help01(u, glm::vec2(20.0f, 28.0f), glm::vec2(0.0f, 28.0f));
    help01(u, glm::vec2(20.0f, 19.0f), glm::vec2(20.0f, 0.0f));

    help01(u, glm::vec2(98.0f, 19.0f), glm::vec2(100.0f, 19.0f));
    help01(u, glm::vec2(98.0f, 19.0f), glm::vec2(100.0f, 19.0f));
    help01(u, glm::vec2(98.0f, 49.0f), glm::vec2(98.0f, 50.0f));

    // point outside
    help01(u, glm::vec2(-5.0, -20.0f), glm::vec2(0.0f));
    help01(u, glm::vec2(-10.0, 20.0f), glm::vec2(0.0f, 20.0f));
    help01(u, glm::vec2(-10.0, 60.0f), glm::vec2(0.0f, 50.0f));
    help01(u, glm::vec2(30.0f, -50.0f), glm::vec2(30.0f, 0.0f));
    help01(u, glm::vec2(40.0f, 80.0f), glm::vec2(40.0f, 50.0f));
    help01(u, glm::vec2(105.0, -20.0f), glm::vec2(100.0f, 0.0f));
    help01(u, glm::vec2(110.0, 20.0f), glm::vec2(100.0f, 20.0f));
    help01(u, glm::vec2(110.0, 60.0f), glm::vec2(100.0f, 50.0f));
}

void t03 () {
//    std::vector<float> outline = {0, 0, 100, 0, 100, 50, 0, 50};
//    std::vector<float> hole = {0, 0,  glm::vec2(0.0f, 0.0f),
//    glm::vec2(0.0f, 10.0f), glm::vec2(20.0f, 10.0f), glm::vec2(20.0f, 0.0f)};
//    auto u = std::make_unique<Polygon>(outline);
//    auto p =  std::make_shared<Poly>(std::move(u));
//    p->addHole(glm::vec2(60.0f, 20.0f), std::make_shared<Polygon>(hole));
//
//    help01(p, glm::vec2(3.0f, 2.0f), glm::vec2(3.0f, 0.0f));
//    help01(p, glm::vec2(58.0f, 18.0f), glm::vec2(60.0f, 20.0f));
//    help01(p, glm::vec2(58.0f, 23.0f), glm::vec2(60.0f, 23.0f));
//    help01(p, glm::vec2(58.0f, 33.0f), glm::vec2(60.0f, 30.0f));
//    help01(p, glm::vec2(10.0f, 23.0f), glm::vec2(0.0f, 23.0f));


}


void shortestPath1() {
    Graph<std::string> ciao;
    ciao.addNode("A");
    ciao.addNode("B");
    ciao.addNode("C");
    ciao.addNode("D");
    ciao.addNode("E");
    ciao.addEdge("A", "C", 1);
    ciao.addEdge("A", "B", 3);
    ciao.addEdge("B", "C", 7);
    ciao.addEdge("C", "D", 2);
    ciao.addEdge("B", "D", 5);
    ciao.addEdge("B", "E", 1);
    ciao.addEdge("D", "E", 7);
    std::vector<std::string> path;
    auto dist = ciao.shortestPath("C", "E", path);

    std::cout << " the shortest path from C to E is:\n";
    for (auto it = path.rbegin(); it != path.rend(); it++) {
        std::cout << *it << ", ";
    }
    std::cout << "\nthe length is: " << dist << "\n";
}

int main(int argc, char* argv[]) {
    shortestPath1();
//
//    t01 (20, 10, 0, 0, glm::vec2(2,4), glm::vec2(0,4));
//    t01 (20, 10, 0, 0, glm::vec2(11,4), glm::vec2(11, 0));
//    t01 (20, 10, 0, 0, glm::vec2(17,5), glm::vec2(20, 5));
//    t01 (20, 10, 0, 0, glm::vec2(16,8), glm::vec2(16, 10));
//    t01 (20, 10, 0, 0, glm::vec2(-5,-8), glm::vec2(0.0f));
//    t01 (20, 10, 0, 0, glm::vec2(32,15), glm::vec2(20, 10));
//    t01 (20, 10, 0, 0, glm::vec2(-5,15), glm::vec2(0,10));
//    t01 (20, 10, 0, 0, glm::vec2(32,-15), glm::vec2(20, 0));
//    t01 (20, 10, 0, 0, glm::vec2(5,15), glm::vec2(5, 10));
//    t01 (20, 10, 0, 0, glm::vec2(5,-2), glm::vec2(5, 0));
//    t01 (20, 10, 0, 0, glm::vec2(-2,3), glm::vec2(0, 3));
//    t01 (20, 10, 0, 0, glm::vec2(400,3), glm::vec2(20, 3));
//
//    t01 (20, 10, 50, 40, glm::vec2(52,44), glm::vec2(50,44));
//    t01 (20, 10, 50, 40, glm::vec2(61,44), glm::vec2(61,40));
//    t01 (20, 10, 50, 40, glm::vec2(68,45), glm::vec2(70,45));
//    t01 (20, 10, 50, 40, glm::vec2(0,0), glm::vec2(50, 40));
//    t01 (20, 10, 50, 40, glm::vec2(0,45), glm::vec2(50, 45));
//    t01 (20, 10, 50, 40, glm::vec2(0,70), glm::vec2(50, 50));
//    t01 (20, 10, 50, 40, glm::vec2(60,0), glm::vec2(60, 40));
//    t01 (20, 10, 50, 40, glm::vec2(60,70), glm::vec2(60, 50));
//    t01 (20, 10, 50, 40, glm::vec2(80,0), glm::vec2(70, 40));
//    t01 (20, 10, 50, 40, glm::vec2(90,46), glm::vec2(70, 46));
//    t01 (20, 10, 50, 40, glm::vec2(90,70), glm::vec2(70, 50));
//
//    t02();
//    t03();

//    t01 (20, 10, 50, 40, glm::vec2(11,4), glm::vec2(11, 0));
//    t01 (20, 10, 50, 40, glm::vec2(17,5), glm::vec2(20, 5));
//    t01 (20, 10, 50, 40, glm::vec2(16,8), glm::vec2(16, 10));
//    t01 (20, 10, 50, 40, glm::vec2(-5,-8), glm::vec2(0.0f));
//    t01 (20, 10, 50, 40, glm::vec2(32,15), glm::vec2(20, 10));
//    t01 (20, 10, 50, 40, glm::vec2(-5,15), glm::vec2(0,10));
//    t01 (20, 10, 50, 40, glm::vec2(32,-15), glm::vec2(20, 0));
//    t01 (20, 10, 50, 40, glm::vec2(5,15), glm::vec2(5, 10));
//    t01 (20, 10, 50, 40, glm::vec2(5,-2), glm::vec2(5, 0));
//    t01 (20, 10, 50, 40, glm::vec2(-2,3), glm::vec2(0, 3));
//    t01 (20, 10, 50, 40, glm::vec2(400,3), glm::vec2(20, 3));





}


