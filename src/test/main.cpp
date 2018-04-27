#include <iostream>
#include "graph/algo.h"
#include "test/io.h"

int main() {

    Graph<int> g;

    // add two nodes, labeled 1 and 2
    for (int i = 0; i <= 8; ++i)
        g.AddNode(i);

    g.AddEdge(0, 1, 4);
    g.AddEdge(0, 7, 8);
    g.AddEdge(1, 7, 11);
    g.AddEdge(1, 2, 8);
    g.AddEdge(7, 8, 7);
    g.AddEdge(7, 6, 1);
    g.AddEdge(6, 8, 6);
    g.AddEdge(2, 8, 2);
    g.AddEdge(2, 3, 7);
    g.AddEdge(2, 5, 4);
    g.AddEdge(6, 5, 2);
    g.AddEdge(3, 5, 14);
    g.AddEdge(3, 4, 9);
    g.AddEdge(5, 4, 10);
    std::cout << "Number of nodes = " << g.GetNodeCount() << std::endl;
    auto path = FindShortestPath(g, 0, 8);
    printPath(path);
    path = FindShortestPath(g, 0, 4);
    printPath(path);

}


