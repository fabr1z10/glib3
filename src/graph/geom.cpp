#include "graph/geom.h"
#include "graph/poly.h"
#include "graph/graph.h"

void FindPathInPoly (const Poly& poly, glm::vec2 Start, glm::vec2 End) {
    int nHoles = poly.GetHoleCount();
    int nVertices = poly.GetVertexCount();
    Graph<int, glm::vec2> g;
    int n = 0;
    for (int i = 0; i < nVertices; ++i) {
        if (poly.isVertexConcave(i)) {
            g.AddNode(n++, poly.GetVertex(i));
        }
    }

    // add hole points
    for (int h = 0; h < nHoles; ++h) {
        int nvh = poly.GetVertexCount(h+1);
        for (int j = 0; j < nvh; ++j) {
            if (!poly.isVertexConcave(j, h+1)) {
                g.AddNode(n++, poly.GetVertex(j, h+1));
            }
        }
    }

    g.AddNode(n++, Start);
    g.AddNode(n++, End);

    // now you need to set up the edges

}